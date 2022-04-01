#define WAVLIB_IMPLEMENTATION
#include "wav.h"

#include <fstream>
#include <algorithm>

namespace wavlib
{
    wav::wav()
        : m_num_channels(0), m_sample_rate(0), m_bits_per_sample(0), m_sound_data(std::vector<float>()),
        m_num_frames(0), m_byte_rate(0), m_block_align(0)
    {

    }

    wav::wav(uint16_t channels, uint32_t frequency, uint16_t depth, const uint8_t* audio, uint32_t frames)
        : m_num_channels(channels), m_sample_rate(frequency), m_bits_per_sample(depth), m_sound_data(std::vector<float>()),
        m_num_frames(frames)
    {
        m_byte_rate = m_sample_rate * m_num_channels * m_bits_per_sample / 8;
        m_block_align = m_num_channels * m_bits_per_sample / 8;
    }

    wav::wav(uint16_t channels, uint32_t frequency, uint16_t depth, uint32_t frames)
        : m_num_channels(channels), m_sample_rate(frequency), m_bits_per_sample(depth), m_sound_data(std::vector<float>()),
        m_num_frames(frames)
    {
        m_byte_rate = m_sample_rate * m_num_channels * m_bits_per_sample / 8;
        m_block_align = m_num_channels * m_bits_per_sample / 8;
    }

    bool wav::write_to_file(const char* filename)
    {
        std::ofstream stream(filename, std::ios::binary);

        if (!stream.is_open())
        {
            return false;
        }

        wav_header  header;
        stream.write((const char*)&header, sizeof(wav_header));

        wav_fmt fmt;
        fmt.bit_depth   = m_bits_per_sample;
        fmt.block_align = m_block_align;
        fmt.byte_rate   = m_byte_rate;
        fmt.channels    = m_num_channels;
        fmt.format      = 1;
        fmt.sample_rate = m_sample_rate;
        fmt.size        = 16;
        stream.write((const char*)&fmt, sizeof(wav_fmt));

        stream.write("data", 4);
        int datasize = m_num_frames * m_num_channels * m_bits_per_sample / 8;
        stream.write((const char*)&datasize, 4);

        for (float sample : m_sound_data)
        {
            int16_t intsample = sample * INT16_MAX;
            intsample = std::clamp(intsample, (int16_t)INT16_MIN, (int16_t)INT16_MAX);
            stream.write((const char*)&intsample, 2);
        }

        stream.seekp(4, std::ios::beg);
        int headersize = 36 + datasize;
        stream.write((const char*)&headersize, 4);

        stream.close();
        return true;
    }

}