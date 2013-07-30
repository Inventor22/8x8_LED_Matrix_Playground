
#include "Max7219_64Display.h"

void Max7219::init(uint8_t _pin_din, uint8_t _pin_cs, uint8_t _pin_clk) {
    init(_pin_din, _pin_cs, _pin_clk, 0x0F);
}

void Max7219::init(uint8_t _pin_din, uint8_t _pin_cs, uint8_t _pin_clk, uint8_t intensity) {
    PIN_DIN = _pin_din;
    PIN_CS  = _pin_cs;
    PIN_CLK = _pin_clk;
    pinMode(PIN_DIN, OUTPUT);
    pinMode(PIN_CS,  OUTPUT);
    pinMode(PIN_CLK, OUTPUT);
    digitalWrite(PIN_CLK, LOW);
    digitalWrite(PIN_CS, HIGH);
    write(DISPLAY_TEST, 0x00);
    write(DECODE_MODE,  0x00);
    write(INTENSITY,    intensity);
    write(SCAN_LIMIT,   0x07);
    write(SHUTDOWN,     0x01);
    clear();
}

Matrix64_Bool& Max7219::getImage() {
    return image;
}

void Max7219::setImage(Matrix64_Bool& _image) {
    image = _image;
}

Matrix64_Bool& Max7219::loadImage(prog_uchar _image[8]) {
    for (int i = 0; i < 8; i++) {
        image.setRow(i, pgm_read_byte(_image+i));
    }
    return image;
}

Matrix64_Bool& Max7219::loadImage(prog_uchar _image[8], Operator op) {
    for (int i = 0; i < 8; i++) {
        image.setRow(i, pgm_read_byte(_image+i), op);
    }
    return image;
}

void Max7219::write(uint8_t address, uint8_t value) {
    uint16_t packet = (address << 8) + value;
    digitalWrite(PIN_CS, LOW);
    for (int i = 15; i >= 0; i--) {
        digitalWrite(PIN_CLK, LOW);
        digitalWrite(PIN_DIN, (packet >> i) & 1);
        digitalWrite(PIN_CLK, HIGH);
    }
    digitalWrite(PIN_CS, HIGH);
}

boolean Max7219::write(uint8_t x, uint8_t y, boolean state) {
    if (!((x >= 0 && x < 8) && (y >= 0 && y < 8))) return false;
    uint8_t address = (Address)(y+1);
    image.set(x, y, state);
    write(address, image[y]);
    return true;
}

void Max7219::write(Matrix64_Bool& _image) {
    image = _image;
    for (int i = 0; i < 8; i++) {
        write((Address)(i+1), image[i]);
    }
}

void Max7219::write(char ch){
    loadChar(ch, image);
    write(image);
}

void Max7219::write(char c, Operator op) {
    for(int i = 0; i < 8; i++)
        image.setRow(i,pgm_read_byte(font+(c*8)+i), op);
    image.rotate(CCW);
    image >>= 1;
    write(image);
}

void Max7219::loadChar(char ch, Matrix64_Bool& matrix) {
    for(int i = 0; i < 8; i++)
        matrix.setRow(i,pgm_read_byte(font+(ch*8)+i));
    matrix.rotate(CCW);
    matrix >>= 1;
}

void Max7219::write(char* string, int scrollSpeed) {
    if (!string) return;
    uint32_t now=millis(), then=0;
    Matrix64_Bool nextChar;
    int pos = 0;
    bool lastChar = false;

    loadChar(' ', image);
    loadChar(*string, nextChar);

    //bool up = true;
    //int count = 2;
    //if (pos%3==1) {
    //    image.shiftOff(up?UP:DOWN);
    //    if (count == 2 || count == -2) {
    //        up = !up;
    //    }
    //    count += up?1:-1;
    //}

    while (pos < 8) {
        now = millis();
        if (now - then > scrollSpeed) {
            then = now;
            write(image);
            image <<= 1;
            if (!lastChar) {
                image.setCol(7, nextChar.getCol(pos));
                if (pos >= 7) { 
                    pos = 0;
                    string++;
                    if (*string == '\0') {
                        lastChar = true;
                        loadChar(' ', nextChar);
                    }
                    else loadChar(*string, nextChar);
                }
            }
            pos++;
        }
    }
}

boolean Max7219::writeRow(uint8_t row, uint8_t value) {
    if (!(row >= 0 && row < 8)) return false;
    image.setRow(row, value);
    write((Address)(row + 1), value);
    return true;
}

boolean Max7219::writeRow(uint8_t row, uint8_t value, Operator op) {
    if (!(row >= 0 && row < 8)) return false;
    image.setRow(row, value, op);
    write((Address)(row + 1), value);
    return true;
}

boolean Max7219::writeCol(uint8_t col, uint8_t val) {
    if (!(col >= 0 && col < 8)) return false;
    image = ~image; // transpose
    image.setRow(col, val); // write column as a row
    image = ~image; // transpose
    write(image);
}

boolean Max7219::writeCol(uint8_t col, uint8_t val, Operator op) {
    if (!(col >= 0 && col < 8)) return false;
    image = ~image; // transpose
    image.setRow(col, val, op); // write column as a row
    image = ~image; // transpose
    write(image);
}

void Max7219::redraw() {
    write(image);
}

void Max7219::fill() {
    for (uint8_t i = 0; i < 8; i++) {
        image.setRow(i, 0xFF);
    }
    write(image);
}
void Max7219::clear() {
    //image >>= 8;
    for (uint8_t i = 0; i < 8; i++) {
        image.setRow(i, 0x00);
    }
    write(image);
    delay(1000);
}

void Max7219::invert() {
    image = !image;
    write(image);
}

void Max7219::randomize() {
    for (int i = 0; i < 8; i++) {
        image.setRow(i, random(0, 0xFF));
    }
    write(image);
}