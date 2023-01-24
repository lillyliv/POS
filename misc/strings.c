#pragma once

// https://aticleworld.com/strcmp-in-c/

int strcmp(char *s1, char *s2)
{
    int charCompareStatus = 0;
    while( ( *s1 != '\0' && *s2 != '\0' ) && *s1 == *s2 )
    {
        s1++;
        s2++;
    }
    //compare the mismatching character
    charCompareStatus = (*s1 ==*s2)?0:(*s1 >*s2)?1:-1;
    return !charCompareStatus; // inverting so is true on success
}
