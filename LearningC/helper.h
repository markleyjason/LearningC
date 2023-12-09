#pragma once
#include <stdint.h>

char isDigit(const char digit);

int32_t stringIsDigit(const char* string, size_t index);

int32_t ctoai(const char digit);

char* uint32arraytostring(const int32_t size, const int32_t* start);

int32_t stoai(const char* input);
uint32_t stoaui(const char* input);

__int64 stoai64(const char* input);

int32_t writtenstoad(const char* input);

int32_t findMin(const int32_t*, const int32_t);

int32_t findVolume(const int32_t, const int32_t, const int32_t);
int32_t findVolumeA(const int32_t*);

