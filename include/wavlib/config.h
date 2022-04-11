#pragma once

#if defined _WIN32 || defined __CYGWIN__
    #define WAVLIB_DLL_IMPORT   __declspec(dllimport)
    #define WAVLIB_DLL_EXPORT   __declspec(dllexport)
    #define WAVLIB_DLL_PRIVATE  static

#ifdef _MSC_VER
    #pragma warning( disable : 4251 )
#endif
#else
    #if defined __GNUC__ >= 4
        #define WAVLIB_DLL_IMPORT   __attribute__ ((visibility ("default")))
        #define WAVLIB_DLL_EXPORT   __attribute__ ((visibility ("default")))
        #define WAVLIB_DLL_PRIVATE  __attribute__ ((visibility ("hidden")))
    #else
        #define WAVLIB_DLL_IMPORT
        #define WAVLIB_DLL_EXPORT
        #define WAVLIB_DLL_PRIVATE
    #endif
#endif

#ifdef WAVLIB_DLL 
  #ifdef WAVLIB_EXPORTS 
    #define WAVLIB_API WAVLIB_DLL_EXPORT
  #else
    #define WAVLIB_API WAVLIB_DLL_IMPORT
  #endif 
  #define WAVLIB_PRIVATE WAVLIB_DLL_PRIVATE
#else 
  #define WAVLIB_API
  #define WAVLIB_PRIVATE
#endif 
