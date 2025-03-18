#pragma once

#include "gles2pp/Miscellaneous.hpp"
#include "gles2pp/Types.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

namespace gles2pp::easy
{

class Program;

class VertexAttribute
{
    friend Program;
    template <std::size_t Size> friend class VertexAttributes;

public:
    constexpr VertexAttribute(std::string t_name, ComponentSize t_component_size, ComponentType t_component_type)
        : m_name{std::move(t_name)}, m_component_size{t_component_size}, m_component_type{t_component_type}
    {
    }

    [[nodiscard]] constexpr auto get_name() const noexcept -> const auto&
    {
        return m_name;
    }

    [[nodiscard]] constexpr auto get_component_size() const noexcept
    {
        return m_component_size;
    }

    [[nodiscard]] constexpr auto get_component_type() const noexcept
    {
        return m_component_type;
    }

    [[nodiscard]] constexpr auto get_offset() const noexcept
    {
        return m_offset;
    }

    [[nodiscard]] constexpr auto get_location() const noexcept
    {
        return m_location;
    }

private:
    std::string m_name;
    ComponentSize m_component_size;
    ComponentType m_component_type;
    std::uintptr_t m_offset{0};
    GLint m_location{-1};
};

template <std::size_t Size> class VertexAttributes
{
public:
    constexpr VertexAttributes(const std::array<VertexAttribute, Size>& t_vertex_attributes)
        : m_vertex_attributes{t_vertex_attributes}
    {
        GLuint offset{0};
        for (auto& vertex_attribute : m_vertex_attributes)
        {
            vertex_attribute.m_offset = offset;
            GLuint byte_size{static_cast<GLuint>(vertex_attribute.get_component_size())};
            switch (vertex_attribute.get_component_type())
            {
            case ComponentType::BYTE:
                byte_size *= sizeof(Byte);
                break;
            case ComponentType::UBYTE:
                byte_size *= sizeof(UByte);
                break;
            case ComponentType::SHORT:
                byte_size *= sizeof(Short);
                break;
            case ComponentType::USHORT:
                byte_size *= sizeof(UShort);
                break;
            case ComponentType::FIXED:
                byte_size *= sizeof(Fixed);
                break;
            case ComponentType::FLOAT:
                byte_size *= sizeof(Float);
            }
            offset += byte_size;
        }
        m_stride = offset;
    }

    void enable()
    {
        for (const auto& vertex_attribute : m_vertex_attributes)
        {
            enable_vertex_attribute_array(vertex_attribute.get_location());
        }
    }

    void disable()
    {
        for (const auto& vertex_attribute : m_vertex_attributes)
        {
            disable_vertex_attribute_array(vertex_attribute.get_location());
        }
    }

    void pointer()
    {
        for (const auto& vertex_attribute : m_vertex_attributes)
        {
            vertex_attribute_pointer(vertex_attribute.get_location(), vertex_attribute.get_component_size(), m_stride,
                                     vertex_attribute.get_offset(), vertex_attribute.get_component_type());
        }
    }

    [[nodiscard]] auto get_vertex_attrubutes() noexcept -> auto&
    {
        return m_vertex_attributes;
    }

    [[nodiscard]] constexpr auto get_stride() const noexcept
    {
        return m_stride;
    }

private:
    std::array<VertexAttribute, Size> m_vertex_attributes;
    GLuint m_stride{0};
};

}