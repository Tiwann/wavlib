#include "wav.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "utils.h"

namespace wavlib
{
    
    wav::wav() : header({}), fmt({}), data({})
    {
        
    }

    wav::wav(uint16_t channels, uint32_t frequency, uint16_t depth, const std::vector<char>& raw_audio) : header({}), fmt({}), data({})
    {
        fmt.channels = channels;
        fmt.sample_rate = frequency;
        fmt.bit_depth = depth;
        fmt.byte_rate = fmt.sample_rate * fmt.channels * fmt.bit_depth / 8;
        fmt.block_align = fmt.channels * fmt.bit_depth / 8;
        data.raw_frames = raw_audio;
        data.num_frames = raw_audio.size() / fmt.channels * fmt.bit_depth / 8;
        data.size = data.num_frames * fmt.channels * fmt.bit_depth / 8;
        header.size = 36 + data.size;
    }

    wav::wav(uint16_t channels, uint32_t frequency, uint16_t depth, uint32_t num_frames, const std::vector<char>& raw_audio) : header({}), fmt({}), data({})
    {
        fmt.channels = channels;
        fmt.sample_rate = frequency;
        fmt.bit_depth = depth;
        fmt.byte_rate = fmt.sample_rate * fmt.channels * fmt.bit_depth / 8;
        fmt.block_align = fmt.channels * fmt.bit_depth / 8;
        data.raw_frames = raw_audio;
        data.num_frames = num_frames;
        data.size = num_frames * fmt.channels * fmt.bit_depth / 8;
        header.size = 36 + data.size;
    }

    wav::wav(const std::string& filename) : header({}), fmt({}), data({})
    {
        std::ifstream stream(filename, std::ios::binary);
        if(!stream.is_open())
        {
            std::cerr << "Failed to open file: File doesn't exist!" << std::endl;
            return;
        }
        
        stream.read(reinterpret_cast<char*>(&header), sizeof(wav_header));
        if(word4tos(header.id) != "RIFF" || word4tos(header.format) != "WAVE")
        {
            std::cout << "Failed to read file: ID is not correct!" << std::endl;
            return;
        }
        
        stream.read(reinterpret_cast<char*>(&fmt), sizeof(wav_fmt));
        if(fmt.format != 1)
        {
            std::cerr << "WAV file doesn't contain uncompressed PCM data!" << std::endl;
            return;
        }
        
        stream.read(reinterpret_cast<char*>(&data), 8);
        data.raw_frames.resize(data.size);
        data.num_frames = static_cast<int>(8.0f * static_cast<float>(data.size) / static_cast<float>(fmt.channels * fmt.bit_depth));
        stream.read(data.raw_frames.data(), data.size);
    }

    bool wav::write_to_file(const char* filename) const
    {
        std::ofstream stream(filename, std::ios::binary);
        if (!stream.is_open())
        {
            return false;
        }
        
        stream.write(reinterpret_cast<const char*>(&header), sizeof(wav_header));
        stream.write(reinterpret_cast<const char*>(&fmt), sizeof(wav_fmt));
        stream.write(reinterpret_cast<const char*>(&data), 8);
        stream.write(data.raw_frames.data(), (std::streamsize)data.raw_frames.size());
        
        stream.close();
        return true;
    }

}
