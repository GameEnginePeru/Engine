#pragma once

#define PREPROCESSOR_EXPAND_MACRO(x) x
#define PREPROCESSOR_STRINGIFY_MACRO(x) #x
#define PREPROCESSOR_JOIN(x, y) x##y

#define PREPROCESSOR_BIT(x) (1 << x)

#define PREPROCESSOR_MAKE_SINGLETON(type) \
inline static type& Get() \
{ \
    static type instance; \
    return instance; \
} \


template <size_t S>
struct PREPROCESSOR_ENUM_FLAG_INTEGER_FOR_SIZE;

template <>
struct PREPROCESSOR_ENUM_FLAG_INTEGER_FOR_SIZE<1>
{
    typedef int type;
};

template <>
struct PREPROCESSOR_ENUM_FLAG_INTEGER_FOR_SIZE<2>
{
    typedef int type;
};

template <>
struct PREPROCESSOR_ENUM_FLAG_INTEGER_FOR_SIZE<4>
{
    typedef int type;
};

template <>
struct PREPROCESSOR_ENUM_FLAG_INTEGER_FOR_SIZE<8>
{
    typedef int type;
};

template <typename T>
struct PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER
{
    typedef typename _ENUM_FLAG_INTEGER_FOR_SIZE<sizeof(T)>::type type;
};

#define PREPROCESSOR_DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
inline constexpr ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) throw() { return ENUMTYPE(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) | ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }\
inline ENUMTYPE& operator |= (ENUMTYPE& a, ENUMTYPE b) throw() { return (ENUMTYPE&)(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type&)a) |= ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }\
inline constexpr ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) throw() { return ENUMTYPE(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) & ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }\
inline ENUMTYPE& operator &= (ENUMTYPE& a, ENUMTYPE b) throw() { return (ENUMTYPE&)(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type&)a) &= ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }\
inline constexpr ENUMTYPE operator ~ (ENUMTYPE a) throw() { return ENUMTYPE(~((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a)); }\
inline constexpr ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) throw() { return ENUMTYPE(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)a) ^ ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }\
inline ENUMTYPE& operator ^= (ENUMTYPE& a, ENUMTYPE b) throw() { return (ENUMTYPE&)(((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type&)a) ^= ((PREPROCESSOR_ENUM_FLAG_SIZED_INTEGER<ENUMTYPE>::type)b)); }