#include "Picture.h"

#include <cstring> //strcpy
#include <cstdio>//std::printf,freed e.tc
#include <cstdlib>//malloc
#include<csetjmp>//setjmp

extern "C"{
#include "png.h"//need be above jpeglib.h otherwise compilating error #1
#include <jpeglib.h>//need png.h be up or otherwise error mising <cstdef> lib #2 
}


#define MAX_SIGNATURE_LENGTH 10
//#include <string.h> //FIX

//#define BREV(b) ((b) >> 24 | (b) << 24 | ((b) & 0x00FF0000) >> 8 | ((b) & 0x0000FF00 ) << 8)

VGImage Picture::CreateImageFromPng_(const char *path)
{
    unsigned char header[8];

    FILE *file = std::fopen(path, "rb");
    if (!file)
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: no file\n");
#endif
        return VG_INVALID_HANDLE;
    }
    std::fread(header, 1, 8, file);
    bool is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png)
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: it's not png file\n");
#endif
        return VG_INVALID_HANDLE;
    }
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr)
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: ptr_error\n");
#endif
        return VG_INVALID_HANDLE;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp)nullptr, (png_infopp)nullptr);
#ifdef ONDEBUG
        std::printf("ONDEBUG: info_ptr error\n");
#endif
        std::fclose(file);
        return VG_INVALID_HANDLE;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return VG_INVALID_HANDLE;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: Error during init_io\n");
#endif
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)nullptr);
        std::fclose(file);
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        std::fclose(file);
        return VG_INVALID_HANDLE;
    }

    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    png_uint_32 width1 = png_get_image_width(png_ptr, info_ptr);
    png_uint_32 height1 = png_get_image_height(png_ptr, info_ptr);

    int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    int color_type = png_get_color_type(png_ptr, info_ptr);
   // int filter_method = png_get_filter_type(png_ptr, info_ptr); //UNUSED VAR  FIXME
    //int compression_type = png_get_compression_type(png_ptr, info_ptr);//UNUSED VAR  FIXME
    int interlace_type = png_get_interlace_type(png_ptr, info_ptr);
    
    png_get_IHDR(png_ptr, info_ptr, &width1, &height1, &bit_depth, &color_type, &interlace_type, nullptr, nullptr);
    picture_width_ = static_cast<int>(width1);
    picture_height_ = static_cast<int>(height1);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY &&
        bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr,
                      PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (bit_depth < 8)
        png_set_packing(png_ptr);
    png_color_8p sig_bit;
    if (png_get_sBIT(png_ptr, info_ptr, &sig_bit))
        png_set_shift(png_ptr, sig_bit);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    if (bit_depth == 16)
        png_set_swap(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
        png_set_swap_alpha(png_ptr);

    png_bytep *row_pointers = new png_bytep[picture_height_];

    unsigned long *pixels = new unsigned long[picture_width_ * picture_height_];

    for (int y = 0; y < picture_height_; ++y){
        row_pointers[picture_height_ - y - 1] = (png_byte *)&pixels[y * picture_width_];
    }
    png_read_image(png_ptr, row_pointers);

    delete[] row_pointers;

    png_read_end(png_ptr, end_info);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    for (int x = 0; x < picture_width_; ++x)
    {
        for (int y = 0; y < picture_height_; ++y)
        {
            pixels[x + y * picture_width_] = GetColor(GetRedColor(pixels[x + y * picture_width_]),
                                             GetGreenColor(pixels[x + y * picture_width_]), 
                                             GetBlueColor(pixels[x + y * picture_width_]), 
                                             GetAlphaColor(pixels[x + y * picture_width_])
                                             );
        }
    }

    VGImage img;
    img = vgCreateImage(VG_sRGBA_8888, picture_width_, picture_height_, VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(img, pixels, picture_width_ * 4, VG_sRGBA_8888, 0, 0, picture_width_, picture_height_);
    delete[] pixels;
    std::fclose(file);
    return img;
}

float Picture::GetBlueColor(int color) { return (0xff & (color >> 24)) / 255.0; } // vozvrat ot 0.0 do 1.0
float Picture::GetGreenColor(int color) { return (0xff & (color >> 16)) / 255.0; }
float Picture::GetRedColor(int color) { return (0xff & (color >> 8)) / 255.0; }
float Picture::GetAlphaColor(int color) { return (0xff & color) / 255.0; }

int Picture::GetColor(float r, float g, float b, float alpha) // vozvrat v 15-4noj sisteme
{
    return ((int)((float)r * 255.0 + 0.5) << 24 |
            (int)((float)g * 255.0 + 0.5) << 16 |
            (int)((float)b * 255.0 + 0.5) << 8 |
            (int)((float)alpha * 255.0 + 0.5));
}

void Picture::CreateImageFromJpg_(const char *path)
{
    finImg = CreateImageFromJpeg_(path);
    picture_width_ = vgGetParameteri(finImg, VG_IMAGE_WIDTH);
    picture_height_ = vgGetParameteri(finImg, VG_IMAGE_HEIGHT);
}

// CreateImageFromJpeg_ decompresses a JPEG image to the standard image format
// source: https://github.com/ileben/ShivaVG/blob/master/examples/test_image.c
VGImage Picture::CreateImageFromJpeg_(const char *filename)
{
    FILE *infile;
    struct jpeg_decompress_struct jdc;
    struct jpeg_error_mgr jerr;
    JSAMPARRAY buffer;
    unsigned int bstride;
    unsigned int bbpp;

    VGImage img;
    VGubyte *data;
    unsigned int picture_width_;
    unsigned int picture_height_;
    unsigned int dstride;
    unsigned int dbpp;

    VGubyte *brow;
    VGubyte *drow;
    unsigned int x;
    unsigned int lilEndianTest = 1;
    VGImageFormat rgbaFormat;

    // Check for endianness
    if (((unsigned char *)&lilEndianTest)[0] == 1)
        rgbaFormat = VG_sABGR_8888;
    else
        rgbaFormat = VG_sRGBA_8888;

    // Try to open image file
    infile = std::fopen(filename, "rb");
    if (infile == nullptr)
    {
        std::fprintf(stderr,"Failed opening '%s' for reading!\n", filename);
        return VG_INVALID_HANDLE;
    }
    // Setup default error handling
    jdc.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&jdc);

    // Set input file
    jpeg_stdio_src(&jdc, infile);

    // Read header and start
    jpeg_read_header(&jdc, TRUE);
    jpeg_start_decompress(&jdc);
    picture_width_ = jdc.output_width;
    picture_height_ = jdc.output_height;

    // Allocate buffer using jpeg allocator
    bbpp = jdc.output_components;
    bstride = picture_width_ * bbpp;
    buffer = (*jdc.mem->alloc_sarray)((j_common_ptr)&jdc, JPOOL_IMAGE, bstride, 1);

    // Allocate image data buffer
    dbpp = 4;
    dstride = picture_width_ * dbpp;
    data = (VGubyte *)std::malloc(dstride * picture_height_);

    // Iterate until all scanlines processed
    while (jdc.output_scanline < picture_height_)
    {

        // Read scanline into buffer
        jpeg_read_scanlines(&jdc, buffer, 1);
        drow = data + (picture_height_ - jdc.output_scanline) * dstride;
        brow = buffer[0];
        // Expand to RGBA
        for (x = 0; x < picture_width_; ++x, drow += dbpp, brow += bbpp)
        {
            switch (bbpp)
            {
            case 4:
                drow[0] = brow[0];
                drow[1] = brow[1];
                drow[2] = brow[2];
                drow[3] = brow[3];
                break;
            case 3:
            {
                drow[0] = brow[0];
                drow[1] = brow[1];
                drow[2] = brow[2];
                drow[3] = 255;
                break;
            }
            }
        }
    }

    // Create VG image
    img = vgCreateImage(rgbaFormat, picture_width_, picture_height_, VG_IMAGE_QUALITY_BETTER);
    vgImageSubData(img, data, dstride, rgbaFormat, 0, 0, picture_width_, picture_height_);

    // Cleanup
    jpeg_destroy_decompress(&jdc);
    std::fclose(infile);
    std::free(data);

    return img;
}

void Picture::render(int x, int y)
{
    if (finImg != VG_INVALID_HANDLE)
    {
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

        vgTranslate(x, y);
        vgTranslate(this->picture_width_ / 2, this->picture_height_ / 2);
        vgRotate(this->rotate);
        vgTranslate(-this->picture_width_ / 2, -this->picture_height_ / 2);
        vgShear(this->shearX, this->shearY);
        vgScale(this->scaleX, this->scaleY);
        vgDrawImage(finImg);
        vgScale(1 / this->scaleX, 1 / this->scaleY);
        vgShear(-shearX, -shearY);
        vgTranslate(this->picture_width_ / 2, this->picture_height_ / 2);
        vgRotate(-this->rotate);
        vgTranslate(-this->picture_width_ / 2, -this->picture_height_ / 2);
        vgTranslate(-x, -y);
    }
    else
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: can't draw\n");
#endif
    }
}

void Picture::render(int x, int y, 
                    float scaleX, float scaleY, 
                    float shearX, float shearY, float rotate
)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->shearX = shearX;
    this->shearY = shearY;
    this->rotate = rotate;

    if (finImg != VG_INVALID_HANDLE)
    {
        vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

        float w = this->picture_width_ * this->scaleX;
        float h = this->picture_height_ * this->scaleY;

        vgTranslate(x, y);
        vgTranslate(w / 2, h / 2);
        vgRotate(this->rotate);
        vgTranslate(-w / 2, -h / 2);
        vgShear(this->shearX, this->shearY);
        vgScale(this->scaleX, this->scaleY);
        vgDrawImage(finImg);
        vgScale(1 / this->scaleX, 1 / this->scaleY);
        vgShear(-shearX, -shearY);
        vgTranslate(w / 2, h / 2);
        vgRotate(-this->rotate);
        vgTranslate(-w / 2, -h / 2);
        vgTranslate(-x, -y);
    }
    else
    {
#ifdef ONDEBUG
        std::printf("ONDEBUG: can't draw\n");
#endif
    }
}

PictureType Picture::GetPictureType_(const char *Path)
{
    const char *FileSignatures[] = {
        "\xFF\xD8\xFF",                     // JPG signature
        "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", // PNG signature
        ""                                  // end of list
    };
    FILE *f = std::fopen(Path, "rb");
    if (!f){
        return picUnknown;
    }
    char sign[MAX_SIGNATURE_LENGTH] = {0};
    std::fread(sign, 1, MAX_SIGNATURE_LENGTH, f);
    std::fclose(f);
    for (int i = 0; FileSignatures[i][0]; i++)
    {
        if (std::memcmp(sign, FileSignatures[i], std::strlen(FileSignatures[i])) == 0){
            return PictureType(i);
        }
    }
    return picUnknown;
}

Picture::Picture(const char *path)
{
    picture_width_ = 0;
    picture_height_ = 0;
    scaleX = 1;
    scaleY = 1;
    shearX = 0;
    shearY = 0;
    rotate = 0;
    finImg = VG_INVALID_HANDLE;

    switch (GetPictureType_(path))
    {
    case picJPG:
    {
        CreateImageFromJpeg_(path);

#ifdef ONDEBUG
        std::printf("File contains picture in JPG format\n");
#endif
        break;
    }
    case picPNG:
    {
        finImg = CreateImageFromPng_(path);

#ifdef ONDEBUG
        std::printf("File contains picture in PNG format\n");
#endif
        break;
    }
    default:
    {
#ifdef ONDEBUG
        std::printf("File does not contain picture or file read error\n");
#endif
    }
    }
}

Picture::~Picture()
{
  // std::printf("Destroyed pic \n");
    if (finImg != VG_INVALID_HANDLE){
        vgDestroyImage(finImg);
    }
}

//Getters
int Picture::Get_width()
{
    return picture_width_;
}
int Picture::Get_height()
{
    return picture_height_;
}

void Picture::GetPixels(int x, int y, int w, int h, unsigned long *pixels)
{

    if (finImg != VG_INVALID_HANDLE)
    {
        if (x + w > picture_width_ || x < 0)
        {
#ifdef ONDEBUG
            std::printf("ONDEBUG: out of borders of image (picture_width_, get) : w: %i, h: %i \n", x + w, y + h);
#endif
            return;
        }
        if (y + h > picture_height_ || y < 0)
        {
#ifdef ONDEBUG
            std::printf("ONDEBUG: out of borders of image (picture_height_, get) : w: %i, h: %i \n", x + w, y + h);
#endif
            return;
        }

        unsigned long *pix = new unsigned long[picture_width_ * picture_height_];
        vgGetImageSubData(finImg, pix, picture_width_ * 4, VG_lRGBA_8888, 0, 0, picture_width_, picture_height_);

            //FIXME //left operand of comma operator has no effect [-Wunused-value]
        for (int i = x, a = 0; i < x + w, a < w; i++, a++)
        {
            for (int j = y, b = 0; j < y + h, b < h; j++, b++)
            {
                pixels[a + b * w] = pix[i + j * picture_width_];
            }
        }
        delete[] pix;
    }
}

void Picture::SetPixels(int x, int y, int w, int h, unsigned long *pixels)
{
    if (finImg != VG_INVALID_HANDLE)
    {
        if (x + w > picture_width_ || x < 0)
        {
#ifdef ONDEBUG
            std::printf("ONDEBUG: out of borders of image (picture_width_, set)\n");
#endif
            return;
        }
        if (y + h > picture_height_ || y < 0)
        {
#ifdef ONDEBUG
            std::printf("ONDEBUG: out of borders of image (picture_height_, set)\n");
#endif
            return;
        }

        unsigned long *pix = new unsigned long[picture_width_ * picture_height_];
        vgGetImageSubData(finImg, pix, picture_width_ * 4, VG_lRGBA_8888, 0, 0, picture_width_, picture_height_);

        for (int i = x, a = 0; i < x + w, a < w; i++, a++)
        {
            for (int j = y, b = 0; j < y + h, b < h; j++, b++)
            {
                pix[i + j * picture_width_] = pixels[a + b * w];
            }
        }

        vgImageSubData(finImg, pix, picture_width_ * 4, VG_lRGBA_8888, 0, 0, picture_width_, picture_height_);
        delete[] pix;
    }
}

int Picture::GetColor(int r, int g, int b, int alpha)
{
    return (r << 24 | g << 16 | b << 8 | alpha);
}

void Picture::Set_Scale(float scaleX, float scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}
