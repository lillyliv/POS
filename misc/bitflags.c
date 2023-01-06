#pragma once

// https://dietertack.medium.com/using-bit-flags-in-c-d39ec6e30f08
// code edited slightly

#define FLAG1 (1 << 0)
#define FLAG2 (1 << 1)
#define FLAG3 (1 << 2)
#define FLAG4 (1 << 3)
#define FLAG5 (1 << 4)
#define FLAG6 (1 << 5)
#define FLAG7 (1 << 6)
#define FLAG8 (1 << 7)

unsigned char SetFlag(unsigned char myflag, unsigned char flag)
{
    return myflag | (int)flag;
}
unsigned char UnsetFlag(unsigned char myflag, unsigned char flag)
{
    return myflag & ~(int)flag;
}
unsigned char FlipFlag(unsigned char myflag, unsigned char flag)
{
    return myflag ^ (int)flag;
}
unsigned char HasFlag(unsigned char myflag, unsigned char flag)
{
   return myflag & (int)flag == (int)flag;
}
