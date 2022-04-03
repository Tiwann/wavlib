#pragma once

#define WAVLIB_IMPLEMENTATION
#include <wavlib.h>
#include <string>
#include <cstring>
#include <vector>

namespace wavlib
{

    struct WAVLIB_API wav_header
    {
        uint8_t     id[4] = { 'R', 'I', 'F', 'F' };
        uint32_t    size{};
        uint8_t     format[4] = { 'W', 'A', 'V', 'E' };
    };

    struct WAVLIB_API wav_fmt
    {
        uint8_t     id[4] = { 'f', 'm', 't', ' ' };
        uint32_t    size{};
        uint16_t    format{};
        uint16_t    channels{};
        uint32_t    sample_rate{};
        uint32_t    byte_rate{};
        uint16_t    block_align{};
        uint16_t    bit_depth{};
    };

    struct WAVLIB_API wav_data
    {
        uint8_t                 id[4] = { 'd', 'a', 't', 'a' };
        uint32_t                size{};
        uint32_t                num_frames{};
        std::vector<char>       raw_frames;
    };
    
    class WAVLIB_API wav
    {
    protected:
        wav_header  header;
        wav_fmt     fmt;
        wav_data    data;

    public:
        const uint16_t& channels()  const { return fmt.channels;    }
        const uint32_t& frequency() const { return fmt.sample_rate; }
        const uint32_t& byterate()  const { return fmt.byte_rate;   }
        const uint16_t& bit_depth() const { return fmt.bit_depth;   }
        const char*     raw_pcm()   const { return data.raw_frames.data(); }
        
        void setdata(const std::vector<float>& pcm)
        {
            data.raw_frames = std::vector<char>();
            data.raw_frames.reserve(pcm.size() * sizeof(float));
            std::memcpy(data.raw_frames.data(), pcm.data(), pcm.size() * sizeof(float));
        }

        void setdata(const std::vector<char>& raw_pcm)
        {
            data.raw_frames = raw_pcm;
        }

        void setformat(const wav_fmt& new_format)
        {
            fmt = new_format;
        }

        wav();
        wav(uint16_t channels, uint32_t frequency, uint16_t depth, const std::vector<char>& raw_audio);
        wav(const std::string& filename);

        bool write_to_file(const char* filename) const;
    };
}
