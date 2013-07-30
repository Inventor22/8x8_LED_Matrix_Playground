
#include "Matrix64_Bool.h"

Matrix64_Bool::Matrix64_Bool(uint8_t initVal) {
    for (int i = 0; i < 8; i++) {
        row[i] = initVal;
    }
}

Matrix64_Bool::Matrix64_Bool(uint8_t arr[8]) {
    for (int i = 0; i < 8; i++) {
        row[i] = arr[i];
    }
}

Matrix64_Bool::~Matrix64_Bool() {};

Matrix64_Bool& Matrix64_Bool::set(uint8_t x, uint8_t y, bool state) {
    if (state) row[y] |=  (B10000000 >> x);
    else       row[y] &= ~(B10000000 >> x);
    return *this;
}

Matrix64_Bool& Matrix64_Bool::set(Point& p, bool state) {
    set(p.x, p.y, state);
}

bool Matrix64_Bool::get(uint8_t x, uint8_t y) const {
    if (x < 0 || x > 7 || y < 0 || y > 7) return 0;
    return row[y] & (B10000000 >> x);
}

bool Matrix64_Bool::get(Point& p) const {
    return get(p.x, p.y);
}

Matrix64_Bool& Matrix64_Bool::setRow(uint8_t y, uint8_t val) {
    row[y] = val;
    return *this;
}

Matrix64_Bool& Matrix64_Bool::setRow(uint8_t y, uint8_t val, Operator op) {
    switch (op) {
    case AND:  row[y] &=  val; break;
    case NAND: row[y] = ~(row[y] & val); break;
    case OR:   row[y] |=  val; break;
    case NOR:  row[y] = ~(row[y] | val); break;
    case XOR:  row[y] ^=  val; break;
    case XNOR: row[y] ^= ~val; break;
    case NOT:  row[y]  = ~val; break;
    default: return *this;
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::setRows(uint8_t val) {
    for (int i = 0; i < 8; i++) {
        row[i] = val;
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::setRows(uint8_t val, Operator op) {
    for (uint8_t i = 0; i < 8; i++) {
        setRow(i, val, op);
    }
}

Matrix64_Bool& Matrix64_Bool::setCol(uint8_t x, uint8_t val) {
    (*this) = ~(*this);
    setRow(x,val);
    (*this) = ~(*this);
    return *this;
}

Matrix64_Bool& Matrix64_Bool::setCol(uint8_t x, uint8_t val, Operator op) {
    *this = ~(*this);
    *this = ~setRow(x, val, op);
    return *this;
}

uint8_t Matrix64_Bool::getRow(int y) {
    return row[y];
}

uint8_t Matrix64_Bool::getCol(int x) {
    uint8_t val;
    (*this) = ~(*this);
    val = row[x];
    *this = ~(*this);
    return val;
}

void Matrix64_Bool::clear() {
    setRows(0x00);
}

bool Matrix64_Bool::isEmpty() {
    for (int i = 0; i < 8; i++) {
        if (row[i]) return false;
    }
    return true;
}

Matrix64_Bool& Matrix64_Bool::rotate(Rotation rotate) {
    //uint8_t temp[8];
    if (rotate == CW) {
        this->flipHorizontal();
        *this = ~(*this);
    } else {
        this->flip(VERTICAL);
        *this = ~(*this);
        /* for (int i = 0; i < 8; i++) temp[i] = getCol(i);
        for (int i = 0; i < 8; i++) row[i]  = temp[i];*/
    }
    return *this;
}

void Matrix64_Bool::flipHorizontal() {
    uint8_t temp;
    for (int i = 0; i < 4; i++) {
        temp     = row[i];
        row[i]   = row[7-i];
        row[7-i] = temp;
    }
}

Matrix64_Bool& Matrix64_Bool::flip(Orientation orient) {
    if (orient == HORIZONTAL) {
        flipHorizontal();
    } else {
        *this = ~(*this);
        flipHorizontal();
        *this = ~(*this);
    }
    return *this;
}

Matrix64_Bool Matrix64_Bool::identity() {
    *this = Image64::identity;
    return *this;
}

Matrix64_Bool& Matrix64_Bool::shift(Direction dir, uint8_t units) {
    units %= 7;
    if (dir == UP) {
        *this = ~(*this);
        for (int i = 0; i < 8; i++) {
            uint8_t endBits = row[i] >> (8-units);
            row[i] <<= units;
            row[i] |= endBits;
        }
        *this = ~(*this);
    }
    else if (dir == DOWN) {
        *this = ~(*this);
        for (int i = 0; i < 8; i++) {
            uint8_t startBits = row[i] << (8-units);
            row[i] >>= units;
            row[i] |= startBits;
        }
        *this = ~(*this);
    }
    else if (dir == LEFT) {
        for (int i = 0; i < 8; i++) {
            uint8_t endBits = row[i] >> (8-units);
            row[i] <<= units;
            row[i] |= endBits;
        }
    }
    else if (dir == RIGHT) {
        for (int i = 0; i < 8; i++) {
            uint8_t startBits = row[i] << (8-units);
            row[i] >>= units;
            row[i] |= startBits;
        }
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::shiftOff(Direction dir, uint8_t units) {
    if (dir == UP) {
        *this = ~((~(*this)) <<= units); // transpose, shift, transpose
    }
    else if (dir == DOWN) {
        *this = ~((~(*this)) >>= units); // transpose, shift, transpose
    }
    else if (dir == LEFT)  *this <<= units;
    else if (dir == RIGHT) *this >>= units;
    return *this;
}

bool Matrix64_Bool::operator== (const Matrix64_Bool& rhs) const {
    for (int i = 0; i < 8; i++) {
        if (row[i] != rhs.row[i]) return false;
    }
    return true;
}

bool Matrix64_Bool::operator!= (const Matrix64_Bool& rhs) const {
    return !(*this == rhs);
}

const uint8_t& Matrix64_Bool::operator[] (int index) const{
    if (!(index >= 0 && index < 8)) return 0;
    return row[index];
}

Matrix64_Bool Matrix64_Bool::operator! () {
    Matrix64_Bool negated;
    for (int i = 0; i < 8; i++) {
        negated.row[i] = ~(this->row[i]);
    }
    return negated;
}

Matrix64_Bool& Matrix64_Bool::operator= (const Matrix64_Bool& rhs) {
    if (this == &rhs) return *this;
    for (int i = 0; i < 8; i++) {
        row[i] = rhs.row[i];
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator= (const uint8_t arr[8]) {
    for (int i = 0; i < 8; i++) {
        row[i] = arr[i];
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator>>= (int val) {
    for (int i = 0; i < 8; i++) {
        row[i] >>= val;
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator<<= (int val) {
    for (int i = 0; i < 8; i++) {
        row[i] <<= val;
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator&= (const Matrix64_Bool& rhs) {
    if (this == &rhs) return *this;
    for (int i = 0; i < 8; i++) {
        row[i] &= rhs.row[i];
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator|= (const Matrix64_Bool& rhs) {
    for (int i = 0; i < 8; i++) {
        row[i] |= rhs.row[i];
    }
    return *this;
}

Matrix64_Bool& Matrix64_Bool::operator^= (const Matrix64_Bool& rhs) {
    for (int i = 0; i < 8; i++) {
        row[i] ^= rhs.row[i];
    }
    return *this;
}

Matrix64_Bool Matrix64_Bool::operator~() const {
    Matrix64_Bool transpose;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            transpose.row[i] += get(i,j) << (7-j);
        }
    }
    return transpose;
}

Matrix64_Bool Matrix64_Bool::operator>> (int val) const {
    return Matrix64_Bool(*this) >>= val;
}

Matrix64_Bool Matrix64_Bool::operator<< (int val) const {
    return Matrix64_Bool(*this) <<= val;
}

const Matrix64_Bool Matrix64_Bool::operator& (const Matrix64_Bool& rhs) const {
    return Matrix64_Bool(*this) &= rhs;
}

const Matrix64_Bool Matrix64_Bool::operator| (const Matrix64_Bool& rhs) const {
    return Matrix64_Bool(*this) |= rhs;
}

const Matrix64_Bool Matrix64_Bool::operator^ (const Matrix64_Bool& rhs) const {
    return Matrix64_Bool(*this) ^= rhs;
}
