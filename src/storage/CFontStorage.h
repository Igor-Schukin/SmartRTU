/*CFontStorage
 * --This is a Font Storage
 * 		You can add here fonts and
 * 		and use it anywhere in project,
 * 		just add #include "CFontStorage.h" 
 * --Here uses library TFont.h frow Georgiy Gamarnik
 */
#pragma once

#ifndef SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_
#define SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_

#include "TFont.h"/*TFont obj*/
#include <cstring>/*strcpy*/

constexpr auto MAX_FONTS_COUNT = 4;
//#define ONDEBUG

struct sFont
{
	char *font_name;
	TFont *font_file;
	sFont(const char *AName, TFont *AFont)
	{
		font_name = strcpy(new char[strlen(AName) + 1], AName);
		font_file = AFont;
	}
	~sFont()
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
	sFont *fonts[MAX_FONTS_COUNT];
	
 	//retunt font position in fonts massive; return -1 if name not found
	int m_FindFontName(char *font_name);
	sFont m_NewFont(char *font_name, char *font_file);

};

extern CFontStorage *FontStorage;
#endif /*SMART_RTU_SRC_STORAGE_CFONTSTORAGE_H_*/