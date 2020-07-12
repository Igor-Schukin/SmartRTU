#include "TFont.h"

#include <cstring>/*strlen,memset e.tc*/
#include<cwchar>

#include "ftf.h"/*LoadFTFont()*/

bool TFont::m_CreateGlyphs(int *Pnt, int *PntInd, unsigned char *Ins, int *InsInd, int *InsCnt)
{
	memset(m_glyphs, 0, m_glyphs_count * sizeof(VGPath));
	for (int i = 0; i < m_glyphs_count; i++)
	{
		const int *p = &Pnt[PntInd[i] * 2];
		const unsigned char *instructions = &Ins[InsInd[i]];
		int ic = InsCnt[i];
		m_glyphs[i] = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
								 1.0f / 65536.0f, 0.0f, 0, 0,
								 VG_PATH_CAPABILITY_ALL);
		if (ic)
		{
			vgAppendPathData(m_glyphs[i], ic, instructions, p);
		}
	}
	return true;
}

TFont::TFont(const char *FTFileName)
:m_font_size(0),R(0),G(0),B(0)
{
	int *Pnt, *PntInd, *InsInd, *InsCnt;
	unsigned char *Ins;
	m_char_map = new short[NGLYPHS];
	LoadFTFont(FTFileName, Pnt, PntInd, Ins,
	 			InsInd, InsCnt, m_glyph_advances, m_char_map,
				 m_glyphs_count, m_font_height, m_descender_height
				);
	m_glyphs = new VGPath[m_glyphs_count];
	m_CreateGlyphs(Pnt, PntInd, Ins, InsInd, InsCnt);
	delete[] Pnt;
	delete[] PntInd;
	delete[] Ins;
	delete[] InsInd;
	delete[] InsCnt;
}

TFont::~TFont()
{
	delete[] m_char_map;
	for (int i = 0; i <= m_glyphs_count; ++i)
	{
		vgDestroyPath(m_glyphs[i]);
	}
	delete[] m_glyphs;
	delete[] m_glyph_advances;
}

unsigned char *TFont::m_NextUtf8Char(unsigned char *utf8, int *codepoint)
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
	VGfloat localsize = (VGfloat)m_font_size, xx = x, mm[9];
	vgGetMatrix(mm);
	int character;
	unsigned char *ss = (unsigned char *)str;
	while ((ss = m_NextUtf8Char(ss, &character)) != nullptr)
	{
		int glyph = m_char_map[character];
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
		vgDrawPath(m_glyphs[glyph], VG_FILL_PATH);
		xx += localsize * m_glyph_advances[glyph] / 65536.0f;
	}
	vgLoadMatrix(mm);
}

VGfloat TFont::TextWidth(const char *str)
{
	VGfloat tw = 0.0;
	VGfloat localsize = (VGfloat)m_font_size;
	int character;
	unsigned char *ss = (unsigned char *)str;
	while ((ss = m_NextUtf8Char(ss, &character)) != nullptr)
	{
		int glyph = m_char_map[character];
		if (glyph == -1)
		{
			continue;
		}
		tw += localsize * m_glyph_advances[glyph] / 65536.0f;
	}
	return tw;
}

VGfloat TFont::TextHeight()
{
	return (m_font_height * m_font_size) / 65536;
}

VGfloat TFont::TextDepth()
{
	return (-m_descender_height * m_font_size) / 65536;
}

void TFont::Set_Size(int localsize)
{
	m_font_size = localsize;
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