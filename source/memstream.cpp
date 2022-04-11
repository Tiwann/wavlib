#include "memstream.h"
#include <cassert>
wavlib::memstream::memstream(): _buffer(nullptr), _size(0), _pos(0), _open(false)
{
    
}

wavlib::memstream::memstream(void* buf, uint64_t size): _buffer(buf), _size(size), _pos(0), _open(true)
{
    
}

wavlib::memstream::memstream(const char* filename): _buffer(nullptr), _size(0), _pos(0), _open(false)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return;

    file.seekg(0, std::ios::end);
    const size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    _buffer = new uint8_t[file_size];
    file.read(static_cast<char*>(_buffer), (std::streamsize)file_size);
    _size = file_size;
    _open = true;
    file.close();
}

uint32_t wavlib::memstream::read(void* dst_buffer, uint32_t dst_buffer_size, uint32_t elem_size, uint32_t count)
{
    assert(is_open());
    assert(dst_buffer_size >= elem_size * count);

    const uint8_t* src = static_cast<uint8_t*>(_buffer);
    uint32_t copied_elems = 0;

    while (std::memcpy(static_cast<uint8_t*>(dst_buffer) + copied_elems * elem_size, src + _pos, elem_size))
    {
        _pos += elem_size;
        copied_elems++;
        if (copied_elems >= count) break;
    }
    return copied_elems;
}

void wavlib::memstream::seek(uint32_t offset, uint8_t origin)
{
    if (!_open) return;
    switch (origin)
    {
    case SEEK_SET:
        _pos = 0;
        if (_pos + offset <= _size)
            _pos += offset;
        break;
    case SEEK_CUR:
        if (_pos + offset <= _size)
            _pos += offset;
        break;
    case SEEK_END:
        _pos = _size;
        if (_pos + offset <= _size)
            _pos += offset;
        break;
    default: return;
    }

    assert(_pos <= _size);
}

void wavlib::memstream::close()
{
    if (!_open) return;
    _open = false;
    _buffer = nullptr;
    _pos = 0;
    _size = 0;
}

uint64_t wavlib::memstream::tell() const
{
    return _pos;
}
