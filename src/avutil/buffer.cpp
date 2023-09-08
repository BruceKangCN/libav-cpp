#include <cstdint>
#include <new>

#include <libavutil/common.h>

#include <av-cpp/avutil/buffer.hpp>
#include <av-cpp/avutil/common.hpp>

namespace av {

BufferRef::BufferRef(const BufferRef& ref)
    : m_v(av_buffer_ref(ref.m_v))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferRef::BufferRef(std::size_t size, bool init)
    : m_v(init ? av_buffer_allocz(size) : av_buffer_alloc(size))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferRef::BufferRef(AVBufferRef* ref)
    : m_v(ref)
{
    // nothing
}

BufferRef::~BufferRef()
{
    av_buffer_unref(&m_v);
}

BufferRef& BufferRef::operator=(const BufferRef& ref)
{
    if (&ref == this) {
        return *this;
    }

    m_v = av_buffer_ref(ref.m_v);
    if (!m_v) {
        throw std::bad_alloc();
    }

    return *this;
}

void BufferRef::replace(const BufferRef& other)
{
    if (av_buffer_replace(&m_v, other.m_v) != 0) {
        throw std::bad_alloc();
    }
}

BufferRef BufferRef::create(std::vector<std::uint8_t>& data,
    void (*free)(void*, std::uint8_t*), void* opaque, int flags)
{
    auto* ret = av_buffer_create(data.data(), data.size(), free, opaque, flags);
    if (!ret) {
        throw std::bad_alloc();
    }
    return ret;
}

void BufferRef::makeWritable()
{
    throwOnError(av_buffer_make_writable(&m_v));
}

void BufferRef::realloc(std::size_t size)
{
    throwOnError(av_buffer_realloc(&m_v, size));
}

BufferPool::BufferPool(std::size_t size, AVBufferRef* (*alloc)(std::size_t size))
    : m_v(av_buffer_pool_init(size, alloc))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferPool::BufferPool(std::size_t size, void* opaque,
    AVBufferRef* (*alloc)(void*, std::size_t size), void (*free)(void*))
    : m_v(av_buffer_pool_init2(size, opaque, alloc, free))
{
    if (!m_v) {
        throw std::bad_alloc();
    }
}

BufferPool::~BufferPool()
{
    av_buffer_pool_uninit(&m_v);
}

BufferPool::BufferPool(AVBufferPool* pool)
    : m_v(pool)
{
    // nothing
}

BufferRef BufferPool::get()
{
    auto* ret = av_buffer_pool_get(m_v);
    if (!ret) {
        throw std::bad_alloc();
    }
    return ret;
}

} // namespace av
