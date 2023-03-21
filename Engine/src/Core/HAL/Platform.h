#pragma once
#include "Core/HAL/PlatformDetection.h"

// Define all other platforms to be zero
#if !defined(PLATFORM_WINDOWS)
	#define PLATFORM_WINDOWS 0
#endif
#if !defined(PLATFORM_APPLE)
	#define PLATFORM_APPLE 0
#endif
#if !defined(PLATFORM_LINUX)
	#define PLATFORM_LINUX 0
#endif
#if !defined(PLATFORM_IOS)
	#define PLATFORM_IOS 0
#endif
#if !defined(PLATFORM_ANDROID)
	#define PLATFORM_ANDROID 0
#endif
#if !defined(PLATFORM_SWITCH)
	#define PLATFORM_SWITCH 0
#endif

#if PLATFORM_WINDOWS
	#include "Platform/WindowsPlatform/WindowsPlatform.h"
#endif

#include "Core/HAL/PreprocessorsHelpers.h"

#if PLATFORM_APPLE
	#include <stddef.h> //needed for size_t
#endif

#ifndef LINE_TERMINATOR
	#define LINE_TERMINATOR "\n"
#endif

// Define platform types as global types
#include "Platform/GenericPlatform/GenericPlatform.h"

// Unsigned base types

/// 8-bit unsigned integer
typedef PlatformTypes::uint8 uint8;
/// 16-bit unsigned integer
typedef PlatformTypes::uint16 uint16;
/// 32-bit unsigned integer
typedef PlatformTypes::uint32 uint32;
/// 64-bit unsigned integer
typedef PlatformTypes::uint64 uint64;

// Signed base types

/// 8-bit signed integer
typedef PlatformTypes::int8 int8;
/// 16-bit signed integer
typedef PlatformTypes::int16 int16;
/// 32-bit signed integer
typedef PlatformTypes::int32 int32;
/// 64-bit signed integer
typedef PlatformTypes::int64 int64;


// Character types

/// An unsigned integer same size as a pointer
typedef PlatformTypes::SIZE_T SIZE_T;
/// An integer same size as a pointer
typedef PlatformTypes::SSIZE_T SSIZE_T;

// Test the global types

static_assert(sizeof(uint8) == 1, "uint8 type size test failed.");
static_assert(sizeof(uint16) == 2, "uint16 type size test failed.");
static_assert(sizeof(uint32) == 4, "uint32 type size test failed.");
static_assert(sizeof(uint64) == 8, "uint64 type size test failed.");

static_assert(sizeof(int8) == 1, "int8 type size test failed.");
static_assert(sizeof(int16) == 2, "int16 type size test failed.");
static_assert(sizeof(int32) == 4, "int32 type size test failed.");
static_assert(sizeof(int64) == 8, "int64 type size test failed.");

static_assert(sizeof(SIZE_T) == sizeof(void*), "SIZE_T type size test failed.");
static_assert(sizeof(SSIZE_T) == sizeof(void*), "SSIZE_T type size test failed.");