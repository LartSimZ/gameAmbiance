#pragma once

#include <string>
#include <cstdlib>

// Integer types
#ifdef int8_t
typedef char int8_t;
#endif // !int8_t

#ifdef uint8_t
typedef unsigned char uint8_t;
#endif // !uint8_t

#ifdef int16_t
typedef short int16_t;
#endif // !int16_t

#ifdef uint16_t
typedef unsigned short uint16_t;
#endif // !uint16_t

#ifdef int32_t
typedef long int32_t;
#endif // !int32_t

#ifdef uint32_t
typedef unsigned long uint32_t;
#endif // !uint32_t

#ifdef int64_t
typedef long long int64_t;
#endif // !int64_t

#ifdef uint64_t
typedef unsigned long long uint64_t;
#endif // !uint64_t

#ifndef _swap_int

template <typename T>
void _swap_int(T& a, T& b) { T t(a); a = b; b = t; }

#endif // !_swap_int