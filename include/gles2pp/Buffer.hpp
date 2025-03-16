#pragma once

#include "Object.hpp"

#include <GLES2/gl2.h>

#include <cstddef>
#include <cstdint>
#include <span>

namespace gles2pp
{

class Buffer : Object
{
public:
    /* The expected usage pattern of the data store. */
    enum class DrawUsage : GLenum
    {
        STREAM = GL_STREAM_DRAW,
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };

    enum class Target : GLenum
    {
        ARRAY = GL_ARRAY_BUFFER,
        ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER
    };

    Buffer();
    ~Buffer() override;

    Buffer(const Buffer&) = delete;
    auto operator=(const Buffer&) -> Buffer& = delete;
    Buffer(Buffer&&) = delete;
    auto operator=(Buffer&&) -> Buffer& = delete;

    void bind(Target t_target);

    static void data(Target t_target, std::uintptr_t t_size, std::span<const std::byte> t_data = {},
                     DrawUsage t_draw_usage = DrawUsage::DYNAMIC);
    static void subdata(Target t_target, std::span<const std::byte> t_data, std::uintptr_t t_offset = 0);
};

}