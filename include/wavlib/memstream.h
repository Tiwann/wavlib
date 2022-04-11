#pragma once

#include <wavlib/config.h>
#include <fstream>


namespace wavlib
{
    class WAVLIB_API memstream
    {
    public:
        uint64_t size() const { return _size; }
        uint64_t pos() const { return _pos; }
        bool is_open() const { return _open; }

    protected:
        void* _buffer;
        uint64_t _size;
        uint64_t _pos;
        bool _open;

    public:
        memstream();
        memstream(void* buf, uint64_t size);
        memstream(const char* filename);
        uint32_t read(void* dst_buffer, uint32_t dst_buffer_size, uint32_t elem_size, uint32_t count);
        void seek(uint32_t offset, uint8_t origin);
        void close();
        uint64_t tell() const;
    };
}