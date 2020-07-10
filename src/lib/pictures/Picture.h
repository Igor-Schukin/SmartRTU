#pragma once

//OpenVG stuff//VgImage
extern "C"
{
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"
   
}



//#define ONDEBUG

enum PictureType
{
    picJPG,
    picPNG,
    picUnknown
};

class Picture
{
public:
    Picture(const char *path);
    ~Picture();

    void render(int x, int y);
    void render(int x, int y, float scaleX, 
                float scaleY, float shearX, 
                float shearY, float rotate
               );
    //

    int Get_width();
    int Get_height();

    void GetPixels(int x, int y, int w, int h, unsigned long *pixels);
    void SetPixels(int x, int y, int w, int h, unsigned long *pixels);

    void Set_Scale(float scaleX, float scaleY);

    int GetColor(float r, float g, float b, float alpha);
    int GetColor(int r, int g, int b, int alpha);
    float GetRedColor(int color);
    float GetGreenColor(int color);
    float GetBlueColor(int color);
    float GetAlphaColor(int color);
private:
    int width, height;
    float scaleX, scaleY;
    float shearX, shearY;
    float rotate;
    VGImage finImg;

    PictureType GetPictureType(const char *Path);

    VGImage m_CreateImageFromPNG(const char *path);
    void m_CreateImageFromJPG(const char *path);
    VGImage m_CreateImageFromJpeg(const char *filename);

};

/*
    Authors: Maksims Denisovs, Igors Sčukins.
    RTU.
    DAUGAVPILS, LATVIA.

        Install openvg:
             sudo apt-get update && sudo apt-get upgrade
             sudo apt-get install libjpeg8-dev indent libfreetype6-dev ttf-dejavu-core
             git clone git://github.com/ajstarks/openvg
             cd openvg
             make
             sudo make install
             cd client
             make test

        Install libpng:
            sudo apt-get install libpng-dev

        Example:
            //	your pictures creation
            #include "lib/Pictures.h"

            Picture *image1 = new Picture("png.png");
            printf("width: %i, height: %i\n", image1->Get_width(), image1->Get_height());
            Picture *image2 = new Picture("rad.jpg");
            printf("width: %i, height: %i\n", image2->Get_width(), image2->Get_height());

            //	if you want to use all pixels of image
            unsigned int *pixels = new unsigned int[image2->Get_width() * image2->Get_height()];
            image2->GetPixels(0, 0, image2->Get_width(), image2->Get_height(), pixels);

            //	if just some part of image 150 X 150
            // unsigned int *pixels = new unsigned int[150 * 150];
            // image2->GetPixels(0, 0, 150, 150, pixels);

            //	change some pixel color
            for (int i = 0; i < image2->Get_width() * image2->Get_height(); i++)
            {
                if (pixels[i] == Picture::GetColor(252, 155, 16, 255)) pixels[i] = Picture::GetColor(41, 128, 21, 255);
                if (pixels[i] == Picture::GetColor(255, 255, 255, 255)) pixels[i] = Picture::GetColor(5, 32, 58, 255);
            }
            image2->SetPixels(0, 0, image2->Get_width(), image2->Get_height(), pixels);
            delete[] pixels;


            //	drawing on the screen
            Start(width, height);
            Background(100, 100, 120);
            image2->drawImage(100, 100);
            image1->drawImage(105, 105);
            End();

            //	do not forget to destroy
            delete image1;
            delete image2;
*/