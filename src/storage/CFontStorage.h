/*CFontStorage
 * --This is a Font Storage
 * 		You can add here fonts_ and
 * 		and use it anywhere in project,
 * 		just add #include "CFontStorage.h" 
 * --Here uses library TFont.h frow Georgiy Gamarnik
 */
#pragma once

#ifndef SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_
#define SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_

#include "TFont.h"/*TFont obj*/
#include <cstring>/*strcpy*/
#include<array>

constexpr auto MAX_FONTS_COUNT = 4;
//#define ONDEBUG

struct FontStruct
{
	char *font_name;
	TFont *font_file;
	FontStruct(const char *a_font_name, TFont *A_font)
	{
		font_name = std::strcpy(
			new char[std::strlen(a_font_name) + 1], a_font_name
			);
		font_file = A_font;
	}
	~FontStruct()
	{
		delete[] font_name;
		delete font_file; //quit
	}
};

class CFontStorage
{
public:
	CFontStorage();
	~CFontStorage();

	bool SetFont(char *font_name, char *font_file);
	TFont *GetFont(char *font_name);
private:
	FontStruct *fonts_[MAX_FONTS_COUNT];
	
 	//retunt font position in fonts_ massive; return -1 if name not found
	int FindFontName_(char *font_name);
};

extern CFontStorage *FontStorage;
#endif /*SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_*/