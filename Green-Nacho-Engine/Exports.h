#pragma once

#if ENGINE_EXPORT
#define ENGINE_DECL_SPEC __declspec(dllexport)
#else
#define ENGINE_DECL_SPEC __declspec(dllimport)
#endif

