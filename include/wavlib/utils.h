#pragma once
#include "wavlib.h"
#include <string>
namespace wavlib
{
    std::string WAVLIB_PRIVATE word4tos(uint8_t* word)
    {
        std::string result((char*)word, 4);
        return result;
    }

}