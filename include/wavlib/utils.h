#pragma once
#include <wavlib/config.h>
#include <string>

#define INT24_MAX 8388607;
#define INT24_
namespace wavlib
{
    std::string WAVLIB_PRIVATE word4tos(uint8_t* word)
    {
        std::string result((char*)word, 4);
        return result;
    }
}