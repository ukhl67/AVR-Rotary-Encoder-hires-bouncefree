/*
* rotaryEncode.h
*
* Created: 2022-05-29
* Author : Uwe Kolz
*/

#ifndef RE_DETENT
# warning "RE_DETENT not defined for rotaryEncode.h"
#define RE_DETENT 1
#endif

#include <avr/io.h>

int8_t rotaryEncode(uint8_t reA, uint8_t reB, uint8_t reNum ) {
    static uint8_t reHist[8] = {0,0,0,0,0,0,0,0}; // Wert historie
    uint8_t reVal         = 0; // Aktueller Wert Bit 1 und 2

    reNum &= 0b111; // Value 0-7

    if (reA != 0) reVal |= 0b01;
    if (reB != 0) reVal |= 0b10;

    if ( ( reHist[reNum] & 0b11 ) == reVal )  return 0; // no change, return

    reHist[reNum] = ( ( reHist[reNum]<<2 ) | reVal ) & 0b00111111 ;

    #if RE_DETENT == 1
    // 1:1 Abtastung
    switch (reHist[reNum]) {
        case 0b100001: return  1; break;
        case 0b010010: return -1; break;
    }

    #elif RE_DETENT == 2
    // 1:2 Abtastung
    switch (reHist[reNum])	{
        case 0b000111: return  1; break;
        case 0b111000: return  1; break;
        case 0b001011: return -1; break;
        case 0b110100: return -1; break;
    }

    #elif RE_DETENT == 4
    // 1:4 Abtastung
    switch (reHist[reNum])	{
        case 0b000111: return  1; break;
        case 0b011110: return  1; break;
        case 0b111000: return  1; break;
        case 0b100001: return  1; break;
        case 0b001011: return -1; break;
        case 0b101101: return -1; break;
        case 0b110100: return -1; break;
        case 0b010010: return -1; break;
    }
    #else
    # error RE_DETENT invalid value (1,2,4)
    #endif

    return 0;
}


