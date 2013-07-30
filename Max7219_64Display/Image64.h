// Images.h

#ifndef IMAGE64_H
#define IMAGE64_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <binary.h>

namespace Image64 {
    extern uint8_t    identity[];
    extern prog_uchar sine[]      PROGMEM;
    extern prog_uchar smiley[]    PROGMEM;
    extern prog_uchar surprised[] PROGMEM;
    extern prog_uchar largeBox[]  PROGMEM;
    extern prog_uchar mediumBox[] PROGMEM;
    extern prog_uchar smallBox[]  PROGMEM;
    extern prog_uchar tinyBox[]   PROGMEM;
    extern prog_uchar wave[]      PROGMEM;
    extern prog_uchar up[]        PROGMEM;
    extern prog_uchar down[]      PROGMEM;
    extern prog_uchar left[]      PROGMEM;
    extern prog_uchar right[]     PROGMEM;
    extern prog_uchar man[]       PROGMEM;
};


#endif