#pragma once

#ifndef WAVLIB_API
	#ifdef _WIN32
		#define WAVLIB_DLL_EXPORT	__declspec(dllexport)
		#define WAVLIB_DLL_IMPORT	__declspec(dllimport)
		#define WAVLIB_DLL_PRIVATE	static
	#else
		#ifdef __GNUC__ && __GNUC__ >= 4
			#define WAVLIB_DLL_EXPORT	__attribute__((visibility("default")))
			#define WAVLIB_DLL_IMPORT	__attribute__((visibility("default")))
			#define WAVLIB_DLL_PRIVATE	__attribute__((visibility("hidden")))
		#else
			#define WAVLIB_DLL_EXPORT	
			#define WAVLIB_DLL_IMPORT	
			#define WAVLIB_DLL_PRIVATE	static
		#endif
	#endif

	#ifdef WAVLIB_IMPLEMENTATION
		#define WAVLIB_API WAVLIB_DLL_EXPORT
	#else
		#define WAVLIB_API WAVLIB_DLL_IMPORT
	#endif

	#define WAVLIB_PRIVATE WAVLIB_DLL_PRIVATE
#endif

#include <cstdint>