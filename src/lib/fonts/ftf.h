#pragma once

#ifndef SMART_RTU_SRC_LIB_FONTS_FTF_H_
#define SMART_RTU_SRC_LIB_FONTS_FTF_H_

#include "ft2build.h"/*‘FT_Done_FreeType’*/
//needed stuff for library to work
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#define NGLYPHS 2000

class Vector2
{
public:
	Vector2();
	Vector2(float px, float py);
	float x;
	float y;
};

Vector2 operator+(const Vector2 &a, const Vector2 &b);
Vector2 operator*(const Vector2 &a, float b);
float ConvertFTFixed(const FT_Pos &x);
Vector2 ConvertFTVector(const FT_Vector &v);
bool IsOn(char b);

bool LoadFTFont(const char *FileName,
				int *&Pt,
				int *&PtInd,
				unsigned char *&Ins,
				int *&InsInd,
				int *&InsCnt,
				int *&Adv,
				short Map[],
				int &Count,
				int &FontHeight,
				int &DescenderHeight
				);

#endif /*SMART_RTU_SRC_LIB_FONTS_FTF_H_*/