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
	short *char_map_;
	VGPath *glyphs_;
	int glyphs_count_;
	int *glyph_advances_;
	int font_height_;
	int descender_height_;
	int font_size_;

	unsigned char R;
	unsigned char G;
	unsigned char B;
	VGfloat A;

	bool CreateGlyphs_(int *Pnt, int *PntInd, unsigned char *Ins, int *InsInd, int *InsCnt);
	unsigned char *NextUtf8Char_(unsigned char *utf8, int *codepoint);

};

#endif/*SMART_RTU_SRC_LIB_FONTS_TFONT_H_*/