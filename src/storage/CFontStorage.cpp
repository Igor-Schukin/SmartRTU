#include "CFontStorage.h"

#include <iostream>/*cout*/
#include <cstring>/*strcpy*/

CFontStorage *FontStorage;

CFontStorage::CFontStorage()
{
	for (int i = 0; i < MAX_FONTS_COUNT; ++i){
		fonts_[i] = nullptr;
	}
}

CFontStorage::~CFontStorage()
{
	for (int i = 0; i < MAX_FONTS_COUNT; ++i)
	{
		if (fonts_[i]){
			delete fonts_[i];
		}
	}
}

int CFontStorage::FindFontName_(char *font_name)
{
	for (int i = 0; i < MAX_FONTS_COUNT; ++i)
	{
		if (fonts_[i])
		{
			if (!std::strcmp(font_name, fonts_[i]->font_name))
			{
				return i;
			}
		}
	}
	return -1;
}

bool CFontStorage::SetFont(char *font_name, char *font_file)
{
#ifdef ONDEBUG
	std::cout << "Loading font: name \"" << font_name 
	<< "\", file \"" << font_file << "\" ..." << '\n';
#endif

	int font_id = this->FindFontName_(font_name); //font_id it is position in massive fonts_[MAX_FONTS_COUNT];
	if (font_id > -1)
	{
		std::cerr << "-- ERROR: \"" << font_name 
		<< "\" font name already exist. Font not loaded.\n";
		return false;
	}

	for (int i = 0; i < MAX_FONTS_COUNT; ++i)
	{
		if (fonts_[i] == nullptr)
		{
			fonts_[i] = new FontStruct(font_name, new TFont(font_file));

#ifdef ONDEBUG
			std::cout << "-- OK: font loaded. Position: " << i <<'\n';
#endif
			return true;
		}
	}
	std::cerr << "-- ERROR: font massive is full " << MAX_FONTS_COUNT 
	<< "/" << MAX_FONTS_COUNT << ". Font not loaded.\n";
	return false;
}

TFont *CFontStorage::GetFont(char *font_name)
{
#ifdef ONDEBUG
	std::cout << "Get font: name \"" << font_name << "\" ..." << '\n';
#endif

	//font_id it is position in massive fonts_[MAX_FONTS_COUNT];
	int font_id = this->FindFontName_(font_name); 
	if (font_id == -1)
	{
		std::cerr << "-- ERROR: can't found font with name: " << font_name << '\n';
		std::cerr << "Try add font: SetFont((char*)\"name\", (char*)\"path to .ttf file\");\n";
	}

#ifdef ONDEBUG
	std::cout << "-- OK: Font founded.\n";
#endif
	return fonts_[font_id]->font_file;
}
