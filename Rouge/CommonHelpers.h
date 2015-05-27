#pragma once

#include "Config.h"
#include "LowLevel/Logger.h"


extern char threadIDs;
extern thread_local char curThreadID;

#define BYTES(x) x
#define KB(x) (1024 * x)
#define MB(x) (1024 * KB(x))
#define GB(x) (1024 * MB(x))

template<typename T> inline bool CHECK_BIT(T var, T pos) { return ((var)& (((T)1) << (pos))) == 1; }
template<typename T> inline T SET_BIT(T var, T pos) { return var | (((T)1) << pos); }
template<typename T> inline T CLEAR_BIT(T var, T pos) { return var & ~(((T)1) << pos); }
template<typename T> inline T TOGGLE_BIT(T var, T pos) { return var ^ (((T)1) << pos); }

typedef unsigned char u_int8;
typedef unsigned char* PTR_u_int8;

typedef signed char s_int8;
typedef signed char* PTR_s_int8;

typedef unsigned short u_int16;
typedef signed short s_int16;

typedef unsigned short* PTR_u_int16;
typedef signed short* PTR_s_int16;

typedef unsigned int u_int32;
typedef signed int s_int32;

typedef unsigned int* PTR_u_int32;
typedef signed int* PTR_s_int32;

typedef unsigned long long u_int64;
typedef signed long long s_int64;

typedef unsigned long long* PTR_u_int64;
typedef signed long long* PTR_s_int64;

typedef wchar_t character;

u_int32 uPoT(u_int32 v);

#define LOG__INFO(...) el::Loggers::getLogger(std::to_string(curThreadID))->info(__VA_ARGS__)
#define LOG__WARN(...) el::Loggers::getLogger(std::to_string(curThreadID))->warn(__VA_ARGS__)
#define LOG__ERROR(...) el::Loggers::getLogger(std::to_string(curThreadID))->error(__VA_ARGS__)
#define LOG__DEBUG(...) el::Loggers::getLogger(std::to_string(curThreadID))->debug(__VA_ARGS__)
#define LOG__FATAL(...) el::Loggers::getLogger(std::to_string(curThreadID))->fatal(__VA_ARGS__)
#define LOG__TRACE(...) el::Loggers::getLogger(std::to_string(curThreadID))->trace(__VA_ARGS__)
#define LOG__VERBOSE(...) el::Loggers::getLogger(std::to_string(curThreadID))->verbose(__VA_ARGS__)

#pragma region Enum flags
#define USE_ENUM_FLAGS_FUNCTION 1
#define ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) \
friend inline constexpr T    operator    &   (T x, T y)      {   return static_cast<T>   (static_cast<INT_T>(x) & static_cast<INT_T>(y));    }; \
friend inline constexpr T    operator    |   (T x, T y)      {   return static_cast<T>   (static_cast<INT_T>(x) | static_cast<INT_T>(y));    }; \
friend inline constexpr T    operator    ^   (T x, T y)      {   return static_cast<T>   (static_cast<INT_T>(x) ^ static_cast<INT_T>(y));    }; \
friend inline constexpr T    operator    ~   (T x)           {   return static_cast<T>   (~static_cast<INT_T>(x));                           }; \
friend inline T&   operator    &=  (T& x, T y)     {   x = x & y;  return x;   }; \
friend inline T&   operator    |=  (T& x, T y)     {   x = x | y;  return x;   }; \
friend inline T&   operator    ^=  (T& x, T y)     {   x = x ^ y;  return x;   };

#if(USE_ENUM_FLAGS_FUNCTION)

#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) \
    static inline bool         flags(T x)          {   return static_cast<INT_T>(x) != 0;};

#else

#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) 

#endif

#define ENUM_FLAGS(T) ENUM_FLAGS_EX(T,int)
#pragma endregion