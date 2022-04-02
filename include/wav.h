#pragma once

#define WAVLIB_IMPLEMENTATION
#include <wavlib.h>
#include <memory>
#include <vector>

namespace wavlib
{

    struct WAVLIB_API wav_header
    {
        uint8_t     id[4] = { 'R', 'I', 'F', 'F' };
        uint32_t    size;
        uint8_t     format[4] = { 'W', 'A', 'V', 'E' };
    };

    struct WAVLIB_API wav_fmt
    {
        uint8_t     id[4] = { 'f', 'm', 't', ' ' };
        uint32_t    size;
        uint16_t    format;
        uint16_t    channels;
        uint32_t    sample_rate;
        uint32_t    byte_rate;
        uint16_t    block_align;
        uint16_t    bit_depth;
    };


    class WAVLIB_API wav
    {
    protected:
        uint16_t m_num_channels;
        uint32_t m_sample_rate;
        uint32_t m_byte_rate;
        uint16_t m_block_align;
        uint16_t m_bits_per_sample;
        std::vector<float>   m_sound_data;
        uint32_t m_num_frames;

    public:
        const uint16_t& channels()  const { return m_num_channels;        }
        const uint32_t& frequency() const { return m_sample_rate;         }
        const uint32_t& byterate()  const { return m_byte_rate;           }
        const uint16_t& bit_depth() const { return m_bits_per_sample;     }
        const float*    data()      const { return m_sound_data.data(); }

        void setdata(float* data, size_t size)
        {
            m_sound_data = std::vector<float>(data, data + size);
        }

        void setdata(const std::vector<float>& data)
        {
            m_sound_data = data;
        }

        wav();
        wav(uint16_t channels, uint32_t frequency, uint16_t depth, const uint8_t* audio, uint32_t frames);
        wav(uint16_t channels, uint32_t frequency, uint16_t depth, uint32_t frames);

        bool write_to_file(const char* filename);
    };
}
