#include "TFont.h"

#include <cstring>/*strlen,memset e.tc*/
#include<cwchar>

#include "ftf.h"/*LoadFTFont()*/

bool TFont::CreateGlyphs_(int *Pnt, int *PntInd, unsigned char *Ins, int *InsInd, int *InsCnt)
{
	memset(glyphs_, 0, glyphs_count_ * sizeof(VGPath));
	for (int i = 0; i < glyphs_count_; i++)
	{
		const int *p = &Pnt[PntInd[i] * 2];
		const unsigned char *instructions = &Ins[InsInd[i]];
		int ic = InsCnt[i];
		glyphs_[i] = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
								 1.0f / 65536.0f, 0.0f, 0, 0,
								 VG_PATH_CAPABILITY_ALL);
		if (ic)
		{
			vgAppendPathData(glyphs_[i], ic, instructions, p);
		}
	}
	return true;
}

TFont::TFont(const char *FTFileName)
:m_font_size_(0),R(0),G(0),B(0)
{
	int *Pnt, *PntInd, *InsInd, *InsCnt;
	unsigned char *Ins;
	char_map_ = new short[NGLYPHS];
	LoadFTFont(FTFileName, Pnt, PntInd, Ins,
	 			InsInd, InsCnt, glyph_advances_, char_map_,
				 glyphs_count_, font_height_, descender_height_
				);
	glyphs_ = new VGPath[glyphs_count_];
	CreateGlyphs_(Pnt, PntInd, Ins, InsInd, InsCnt);
	delete[] Pnt;
	delete[] PntInd;
	delete[] Ins;
	delete[] InsInd;
	delete[] InsCnt;
}

TFont::~TFont()
{
	delete[] char_map_;
	for (int i = 0; i <= glyphs_count_; ++i)
	{
		vgDestroyPath(glyphs_[i]);
	}
	delete[] glyphs_;
	delete[] glyph_advances_;
}

unsigned char *TFont::NextUtf8Char_(unsigned char *utf8, int *codepoint)
{
	int seqlen;
	int datalen = (int)std::strlen((const char *)utf8);
	unsigned char *p = utf8;

	if (datalen < 1 || *utf8 == 0)
	{
		return nullptr;
	}
	if (!(utf8[0] & 0x80))
	{
		*codepoint = static_cast<wchar_t>(utf8[0]);
		seqlen = 1;
	}
	else if ((utf8[0] & 0xE0) == 0xC0)
	{
		*codepoint = (int)(((utf8[0] & 0x1F) << 6) | (utf8[1] & 0x3F));
		seqlen = 2;
	}
	else if ((utf8[0] & 0xF0) == 0xE0)
	{
		*codepoint = (int)(((utf8[0] & 0x0F) << 12) | ((utf8[1] & 0x3F) << 6) | (utf8[2] & 0x3F));
		seqlen = 3;
	}
	else
	{
		return nullptr;
	}
	p += seqlen;
	return p;
}

void TFont::TextOut(const char *str, int x, int y)
{

	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	Fill(static_cast<int>(R), static_cast<int>(G), static_cast<int>(B), A);
	VGfloat localsize = (VGfloat)m_font_size_, xx = x, mm[9];
	vgGetMatrix(mm);
	int character;
	unsigned char *ss = (unsigned char *)str;
	while ((ss = NextUtf8Char_(ss, &character)) != nullptr)
	{
		int glyph = char_map_[character];
		if (glyph == -1)
		{
			continue;
		}
		VGfloat mat[9] = {
			localsize, 0.0f, 0.0f,
			0.0f, localsize, 0.0f,
			xx, (VGfloat)y, 1.0f};
		vgLoadMatrix(mm);
		vgMultMatrix(mat);
		vgDrawPath(glyphs_[glyph], VG_FILL_PATH);
		xx += localsize * glyph_advances_[glyph] / 65536.0f;
	}
	vgLoadMatrix(mm);
}

VGfloat TFont::TextWidth(const char *str)
{
	VGfloat tw = 0.0;
	VGfloat localsize = (VGfloat)m_font_size_;
	int character;
	unsigned char *ss = (unsigned char *)str;
	while ((ss = NextUtf8Char_(ss, &character)) != nullptr)
	{
		int glyph = char_map_[character];
		if (glyph == -1)
		{
			continue;
		}
		tw += localsize * glyph_advances_[glyph] / 65536.0f;
	}
	return tw;
}

VGfloat TFont::TextHeight()
{
	return (font_height_ * m_font_size_) / 65536;
}

VGfloat TFont::TextDepth()
{
	return (-descender_height_ * m_font_size_) / 65536;
}

void TFont::Set_Size(int localsize)
{
	m_font_size_ = localsize;
}

void TFont::Set_Color(unsigned char local_R, unsigned char local_G, 
					  unsigned char local_B, VGfloat local_A)

{
	R = local_R;
	G = local_G;
	B = local_B;
	A = local_A;
}

void TFont::TextMid(const char *str, int x, int y)
{
	VGfloat tw = TextWidth(str);
	TextOut(str, x - (tw / 2), y);
}

void TFont::TextEnd(const char *str, int x, int y)
{
	VGfloat tw = TextWidth(str);
	TextOut(str, x - tw, y);
}