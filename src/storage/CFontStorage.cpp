#include "CFontStorage.h"
#include "iostream"
#include <cstring>
using namespace std;

CFontStorage *FontStorage;

CFontStorage::CFontStorage()
{
	for (int i = 0; i < MAX_FONTS_COUNT; i++)
		fonts[i] = NULL;
}

CFontStorage::~CFontStorage()
{
	for (int i = 0; i < MAX_FONTS_COUNT; i++)
	{
		if (fonts[i])
			delete fonts[i];
	}
}

int CFontStorage::findFontName(char *fontName)
{
	for (int i = 0; i < MAX_FONTS_COUNT; i++)
	{
		if (fonts[i])
		{
			if (!strcmp(fontName, fonts[i]->fontName))
			{
				return i;
			}
		}
	}
	return -1;
}

bool CFontStorage::setFont(char *fontName, char *fontFile)
{
#ifdef ONDEBUG
	std::cout << "Loading font: name \"" << fontName << "\", file \"" << fontFile << "\" ..." << '\n';
#endif

	int fontId = findFontName(fontName); //fontId it is position in massive fonts[MAX_FONTS_COUNT];
	if (fontId > -1)
	{
		std::cerr << "-- ERROR: \"" << fontName << "\" font name already exist. Font not loaded." << '\n';
		return false;
	}

	for (int i = 0; i < MAX_FONTS_COUNT; i++)
	{
		if (fonts[i] == NULL)
		{
			fonts[i] = new sFont(fontName, new TFont(fontFile));

#ifdef ONDEBUG
			std::cout << "-- OK: font loaded. Position: " << i << endl;
#endif
			return true;
		}
	}
	std::cerr << "-- ERROR: font massive is full " << MAX_FONTS_COUNT << "/" << MAX_FONTS_COUNT << ". Font not loaded." << '\n';
	return false;
}

TFont *CFontStorage::getFont(char *fontName)
{
#ifdef ONDEBUG
	std::cout << "Get font: name \"" << fontName << "\" ..." << endl;
#endif

	int fontId = findFontName(fontName); //fontId it is position in massive fonts[MAX_FONTS_COUNT];
	if (fontId == -1)
	{
		std::cerr << "-- ERROR: can't found font with name: " << fontName << endl;
		std::cerr << "		Try add font: setFont((char*)\"name\", (char*)\"path to .ttf file\");" << endl;
	}

#ifdef ONDEBUG
	std::cout << "-- OK: Font founded." << endl;
#endif
	return fonts[fontId]->fontFile;
}
