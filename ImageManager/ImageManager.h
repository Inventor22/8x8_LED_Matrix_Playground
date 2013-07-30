
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Matrix64_Bool.h"
#include "Image64.h"
#include "CGoL_Shapes.h"
#include "CharactersFont.h"

namespace Image {
    enum ImageEnum {
        SINE,
        SMILEY,
        SURPRISED,
        LARGE_BOX,
        MEDIUM_BOX,
        SMALL_BOX,
        TINY_BOX,
        WAVE,
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        BEACON,
        BLINKER,
        TOAD,
        GLIDER,
        SHIP,
        PATTERN_ONE,
        PATTERN_TWO,
        MAN
    };

    static const prog_uchar* pFlashImage[] = {
        Image64::sine,
        Image64::smiley,
        Image64::surprised,
        Image64::largeBox,
        Image64::mediumBox,
        Image64::smallBox,
        Image64::tinyBox,
        Image64::wave,
        Image64::up,
        Image64::down,
        Image64::left,
        Image64::right,
        CGol_Shapes::Oscillator::beacon,
        CGol_Shapes::Oscillator::blinker,
        CGol_Shapes::Oscillator::toad,
        CGol_Shapes::Spaceship::glider,
        CGol_Shapes::Spaceship::ship,
        CGol_Shapes::Pattern::one,
        CGol_Shapes::Pattern::two,
        Image64::man
    };
};

class ImageManager {
private:
    static const int maxIndex = 19;
public:
    Matrix64_Bool loadImage(Image::ImageEnum imageEnum);
    Matrix64_Bool loadImage(int index);
    Matrix64_Bool loadImage(char ch);
};

#endif