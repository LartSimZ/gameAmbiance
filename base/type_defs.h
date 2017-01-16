#pragma once

#include <string>
#include <cstdlib>

// Integer types
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

#ifndef _swap_int

template <typename T>
void _swap_int(T& a, T& b) { T t(a); a = b; b = t; }

#endif // !_swap_int