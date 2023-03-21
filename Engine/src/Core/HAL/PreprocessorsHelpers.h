#pragma once

#define PREPROCESSOR_EXPAND_MACRO(x) x
#define PREPROCESSOR_STRINGIFY_MACRO(x) #x
#define PREPROCESSOR_JOIN(x, y) x##y

#define PREPROCESSOR_BIT(x) (1 << X)