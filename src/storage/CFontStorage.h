/*CFontStorage
 * --This is a Font Storage
 * 		You can add here fonts and
 * 		and use it anywhere in project,
 * 		just add #include "CFontStorage.h" 
 * --Here uses library TFont.h frow Georgiy Gamarnik
 */
#pragma once
#include "TFont.h"

constexpr auto MAX_FONTS_COUNT = 4;
//#define ONDEBUG

struct sFont
{
	char *fontName;
	TFont *fontFile;
	sFont(const char *AName, TFont *AFont)
	{
		fontName = strcpy(new char[strlen(AName) + 1], AName);
		fontFile = AFont;
	}
	~sFont()
	{
		delete[] fontName;
		delete fontFile; //quit
	}
};

class CFontStorage
{
public:
	CFontStorage();
	~CFontStorage();

	bool setFont(char *fontName, char *fontFile);
	TFont *getFont(char *fontName);
private:
	sFont *fonts[MAX_FONTS_COUNT];
	
 	//retunt font position in fonts massive; return -1 if name not found
	int findFontName(char *fontName);
	sFont newFont(char *fontName, char *fontFile);

};

extern CFontStorage *FontStorage;
