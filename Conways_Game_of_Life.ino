
#include <ImageManager.h>
#include <CGoL_Shapes.h>
#include <Max7219_64Display.h>
#include <Image64.h>
#include <CharactersFont.h>
#include <Matrix64_Bool.h>
#include <Point.h>

#define SCROLL_SPEED 40
#define LETTERS    true
#define PATTERN    false
#define CELL_KILL  false
#define CELL_SPAWN true
#define CELL_KEEP  true
const char FIRST_LETTER = 'A';
const char LAST_LETTER  = 'Z';

Max7219       display;
Matrix64_Bool prev2, prev1, current, next ;
ImageManager  manager;

uint32_t
    now             = 0, 
    then            = 0,
    then2           = 0;
uint16_t
    update          = 500, 
    dirUpdate       = 10000;
int      generation      = 0;
int      maxGenerations  = 75;
char     letter          = 'A';
int      patternIndex    = 0;
int      maxPatternIndex = 19;
bool     mode            = LETTERS;
bool     steadyState     = false;

Point dir[]   = { UP, DOWN, LEFT, RIGHT, UP+RIGHT, UP+LEFT, DOWN+LEFT, DOWN+RIGHT };
int neighbors = 0;

const bool rndRotate  = false;
bool wrapMode = false;

void setup() {
    Serial.begin(9600);
    display.init(A3, A4, A5, 0x01);
    display.clear();

    display.write("Hello World!", SCROLL_SPEED);
    delay(1000);
    display.write("Welcome to Conway's Game of Life!", SCROLL_SPEED);
    delay(1000);

    //displayWrapMode(wrapMode);
    //display.write("Letters", 40);
    current = manager.loadImage(letter);
    display.write(current);
    delay(500);

}

void loop() {
    now = millis();
    if (now - then > update) {
        then = now;
        update = map(analogRead(0), 0, 1023, 1, 500);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    Point base(i,j);
                    base.shift(dir[k]);
                    if(wrapMode) {
                        if (base.x < 0) base.x = 7;
                        if (base.x > 7) base.x = 0;
                        if (base.y < 0) base.y = 7;
                        if (base.y > 7) base.y = 0;
                    }
                    if (current.get(base)) { neighbors++; }
                }
                if (current.get(i,j)) {
                    if (neighbors < 2 ||
                        neighbors > 3)   next.set(i, j, CELL_KILL);
                    else                 next.set(i, j, CELL_KEEP);
                }
                else if (neighbors == 3) next.set(i, j, CELL_SPAWN);
                neighbors = 0;
            }
        }
        if (rndRotate) {
            if (now - then2 > dirUpdate) {
                then2 = now;
                next.rotate((Rotation)random(0,2));
            }
        }
        generation++;
        current = next;
        next.clear();
        if (!steadyState) {
            if (current == prev2) {
                generation = maxGenerations - 10;
                steadyState = true;
            }
            else if (current == prev1 || current.isEmpty()) {
                generation = maxGenerations - 5;
                steadyState = true;
            } else {
                prev2 = prev1;
                prev1 = current;
            }
        }

        display.write(current);

        if (generation >= maxGenerations) {
            current.clear();
            display.clear();
            if (mode == LETTERS) {
                if (letter == 'Z') {
                    mode = PATTERN;
                    patternIndex = 0;
                    current = manager.loadImage(patternIndex);
                    display.write("Patterns", SCROLL_SPEED);
                } else {
                    letter++;
                    current = manager.loadImage(letter);
                }
            } else {
                if (patternIndex >= maxPatternIndex) {
                    letter = 'A';
                    current = manager.loadImage(letter);
                    mode = LETTERS;
                    wrapMode = !wrapMode;
                    displayWrapMode(wrapMode);
                    display.write("Letters", SCROLL_SPEED);
                } else { 
                    patternIndex++;
                    current = manager.loadImage(patternIndex);
                }
            }
            display.write(current);
            delay(500);
            steadyState = false;
            generation = 0;
        }
    }
}

void displayWrapMode(bool mode) {
    if (wrapMode) {
        display.write("XY Wrapping: ", SCROLL_SPEED);
        maxGenerations = 130;
    } else {
        display.write("Enclosed: ", SCROLL_SPEED);
        maxGenerations = 65;
    }
}

void printMatrix(Matrix64_Bool& matrix) {
    for (int i = 0; i < 8; i++) {
        Serial.println(matrix.getRow(i), BIN);
    }
    Serial.println();
}

//int freeRam () {
//    extern int __heap_start, *__brkval; 
//    int v; 
//    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
//}

// Cool patterns:

/* current = Max7219()
.loadImage(CGol_Shapes::Oscillator::beacon)
.shift(LEFT,2)
.shift(UP,  2)
^  // XORs the two images together
Max7219().loadImage(CGol_Shapes::Oscillator::beacon)
.shift(LEFT, 2)
.shift(UP,   6);*/

//current.set(4,4,1);
//current.set(4,5,1);
//current.set(4,6,1);

//current = loadImage(flashImage[9]) ^ Matrix64_Bool(Image64::identity) & Matrix64_Bool(Image64::identity).flip(VERTICAL);

//current = manager.loadImage(Image::GLIDER).shift(DOWN, 3);
//display.write('R'); //E,H,I,K,K*,M,M*s,Ns,P**,Q**,R,R***,S,T,T*,V_,V*,W,W*,Y_,Y*,Z