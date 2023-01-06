#pragma once
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define true 1
#define false 0

// https://stackoverflow.com/questions/3407012/rounding-up-to-the-nearest-multiple-of-a-number
int roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}
