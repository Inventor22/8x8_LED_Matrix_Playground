
#include "ImageManager.h"


Matrix64_Bool ImageManager::loadImage(Image::ImageEnum imageEnum) {
    Matrix64_Bool image;
    const prog_uchar* pImage = Image::pFlashImage[imageEnum];
    for (int i = 0; i < 8; i++) {
        image.setRow(i, pgm_read_byte(pImage+i));
    }
    return image;
}

Matrix64_Bool ImageManager::loadImage(int index) {
    if (index > maxIndex) index = maxIndex;
    return loadImage((Image::ImageEnum)index);
}

Matrix64_Bool ImageManager::loadImage(char ch) {
    Matrix64_Bool image;
    for(int i = 0; i < 8; i++)
        image.setRow(i,pgm_read_byte(font+(ch*8)+i));
    image.rotate(CCW);
    image >>= 1;
    return image;
}
