#pragma once

#include "gles2pp/Buffer.hpp"
#include "gles2pp/Miscellaneous.hpp"
#include "gles2pp/Types.hpp"

#include <cstddef>
#include <span>
#include <vector>

namespace gles2pp::easy
{

template <typename Type> class Buffer : public gles2pp::Buffer
{
public:
    Buffer(Target t_target, std::size_t t_size) : m_target{t_target}
    {
        gles2pp::Buffer::bind(t_target);
        data(t_target, t_size * sizeof(Type));
        m_buffer.reserve(t_size);
    }

    constexpr void insert(std::size_t t_size, const Type* t_values)
    {
        m_buffer.insert(m_buffer.end(), t_values, t_values + t_size);
    }

    constexpr void insert(Type t_value)
    {
        m_buffer.emplace_back(t_value);
    }

    constexpr void insert(std::span<const Type> t_data)
    {
        insert(t_data.size(), t_data.data());
    }

    void bind()
    {
        gles2pp::Buffer::bind(m_target);
    }

    void subdata()
    {
        gles2pp::Buffer::subdata(m_target,
                                 {reinterpret_cast<const std::byte*>(m_buffer.data()), m_buffer.size() * sizeof(Type)});
    }

    constexpr void clear()
    {
        m_buffer.clear();
    }

    [[nodiscard]] constexpr auto size() const noexcept
    {
        return m_buffer.size();
    }

private:
    Target m_target;
    std::vector<Type> m_buffer;
};

class ArrayBuffer : public Buffer<Float>
{
public:
    ArrayBuffer(std::size_t t_size);
};

class ArrayElementBuffer : public Buffer<UShort>
{
public:
    ArrayElementBuffer(std::size_t t_size);

    void draw(Primitive t_primitive = Primitive::TRIANGLES);
};

}