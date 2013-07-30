// Matrix64.h

#ifndef MATRIX64_BOOL_H
#define MATRIX64_BOOL_H

#include <binary.h>
#include "Point.h"
#include "Image64.h"

enum BITWISE_OPERATORS { AND, NAND, OR, NOR, XOR, XNOR, NOT };
typedef BITWISE_OPERATORS Operator;

enum Rotation    { CW, CCW };
enum Orientation { HORIZONTAL, VERTICAL };

typedef Point Direction;
const Direction
    UP    = Point( 0, 1),
    DOWN  = Point( 0,-1),
    LEFT  = Point(-1, 0),
    RIGHT = Point( 1, 0);

class Matrix64_Bool
{
private:
    uint8_t row[8];
    void flipHorizontal();

public:
    Matrix64_Bool(uint8_t initVal = 0);
    Matrix64_Bool(uint8_t arr[8]);
    ~Matrix64_Bool();
    Matrix64_Bool& set(uint8_t x, uint8_t y, bool state);
    Matrix64_Bool& set(Point&  p, bool state);
    Matrix64_Bool& setRow(uint8_t y, uint8_t val);
    Matrix64_Bool& setRow(uint8_t y, uint8_t val, Operator op);
    Matrix64_Bool& setRows(uint8_t val);
    Matrix64_Bool& setRows(uint8_t val, Operator op);
    Matrix64_Bool& setCol(uint8_t x, uint8_t val);
    Matrix64_Bool& setCol(uint8_t x, uint8_t val, Operator op);
    bool           get(uint8_t x, uint8_t y) const;
    bool           get(Point&  p) const;
    uint8_t        getRow(int y);
    uint8_t        getCol(int x);

    void           clear();

    bool           isEmpty();
    Matrix64_Bool& rotate(Rotation  rotate);
    Matrix64_Bool& flip(Orientation orient);

    Matrix64_Bool  identity();

    Matrix64_Bool& shift(Direction dir, uint8_t units=1);
    Matrix64_Bool& shiftOff(Direction dir, uint8_t units=1);
    bool operator==(const Matrix64_Bool& rhs) const;
    bool operator!=(const Matrix64_Bool& rhs) const;
    const uint8_t& operator[]  (int index) const;
    Matrix64_Bool  operator!   ();
    Matrix64_Bool& operator=   (const Matrix64_Bool& rhs);
    Matrix64_Bool& operator=   (const uint8_t arr[8]);
    Matrix64_Bool& operator>>= (int val);
    Matrix64_Bool& operator<<= (int val);
    Matrix64_Bool& operator&=  (const Matrix64_Bool& rhs);
    Matrix64_Bool& operator|=  (const Matrix64_Bool& rhs);
    Matrix64_Bool& operator^=  (const Matrix64_Bool& rhs);
    Matrix64_Bool  operator~()  const;
    Matrix64_Bool  operator>>  (int val) const;
    Matrix64_Bool  operator<<  (int val) const;
    const Matrix64_Bool operator&  (const Matrix64_Bool& rhs) const;
    const Matrix64_Bool operator|  (const Matrix64_Bool& rhs) const;
    const Matrix64_Bool operator^  (const Matrix64_Bool& rhs) const;
};

#endif
