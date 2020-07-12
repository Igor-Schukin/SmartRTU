/*
Writed by Georgiy Gamarnik in RTU DF.
*/
#pragma once
#ifndef SMART_RTU_SRC_LIB_FONTS_TFONT_H_
#define SMART_RTU_SRC_LIB_FONTS_TFONT_H_

//probably do not need all of them
extern "C"
{
#include "VG/openvg.h"/*OpenVG stuff like vgLoadIdenty*/
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"
}



#define NGLYPHS 2000

class TFont
{
public:
	TFont(const char *FTFileName);
	~TFont();
	void TextOut(const char *str, int x, int y);
	void TextMid(const char *str, int x, int y);
	void TextEnd(const char *str, int x, int y);
	VGfloat TextWidth(const char *);
	VGfloat TextHeight();
	VGfloat TextDepth();
	void Set_Size(int localsize);
	void Set_Color(unsigned char local_R, unsigned char local_G, unsigned char local_B, VGfloat local_A = 1.0);

private:
	short *m_char_map;
	VGPath *m_glyphs;
	int m_glyphs_count;
	int *m_glyph_advances;
	int m_font_height;
	int m_descender_height;
	int m_font_size;

	unsigned char R;
	unsigned char G;
	unsigned char B;
	VGfloat A;

	bool m_CreateGlyphs(int *Pnt, int *PntInd, unsigned char *Ins, int *InsInd, int *InsCnt);
	unsigned char *m_NextUtf8Char(unsigned char *utf8, int *codepoint);

};

#endif/*SMART_RTU_SRC_LIB_FONTS_TFONT_H_*/