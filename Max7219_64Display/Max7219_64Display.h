// Max7219.h

#ifndef MAX7219_H
#define MAX7219_H

#include "Arduino.h"
#include "Matrix64_Bool.h"
#include "CharactersFont.h"
#include "Image64.h"

enum MAX7219_CONTROL_REGISTERS {
    NOOP         = 0x00,
    DIGIT_0      = 0x01,
    DIGIT_1      = 0x02,
    DIGIT_2      = 0x03,
    DIGIT_3      = 0x04,
    DIGIT_4      = 0x05,
    DIGIT_5      = 0x06,
    DIGIT_6      = 0x07,
    DIGIT_7      = 0x08,
    DECODE_MODE  = 0x09,
    INTENSITY    = 0x0A,
    SCAN_LIMIT   = 0x0B,
    SHUTDOWN     = 0x0C,
    DISPLAY_TEST = 0x0F
};

typedef MAX7219_CONTROL_REGISTERS Address;

class Max7219 {
 private:
     uint8_t PIN_DIN, PIN_CS, PIN_CLK;
     void write(uint8_t address, uint8_t value);
     void loadChar(char ch, Matrix64_Bool& matrix);
     Matrix64_Bool image;

 public:
	void init(uint8_t _pin_din, uint8_t _pin_cs, uint8_t _pin_clk);
    void init(uint8_t _pin_din, uint8_t _pin_cs, uint8_t _pin_clk, uint8_t intensity);
    Matrix64_Bool& getImage();
    void    setImage(Matrix64_Bool& _image);
    Matrix64_Bool& loadImage(prog_uchar _image[8]);
    Matrix64_Bool& loadImage(prog_uchar _image[8], Operator op);
    boolean write(uint8_t x, uint8_t y, boolean state);
    void    write(Matrix64_Bool& _image);
    void    write(char ch);
    void    write(char ch, Operator op);
    void    write(char* string, int scrollSpeed = 50);
    boolean writeRow(uint8_t row, uint8_t value);
    boolean writeRow(uint8_t row, uint8_t value, Operator op);
    boolean writeCol(uint8_t col, uint8_t value);
    boolean writeCol(uint8_t row, uint8_t value, Operator op);
    void    redraw();
    void    invert();
    void    fill();
    void    clear();
    void    randomize();

};

#endif
