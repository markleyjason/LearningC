#pragma once
#define INT32_MIN -2147483648
#define INT32_MAX 2147483647

char isDigit(char);

__int32 ctoai(char);

//Assumes all integers in the array are only a single digit (0-9)
char* uint32arraytostring(unsigned __int32 size, unsigned __int32* start);

__int32 stoai(char* input);

__int32 findMin(__int32*, __int32);

__int32 findVolume(__int32, __int32, __int32);
__int32 findVolumeA(__int32*);

