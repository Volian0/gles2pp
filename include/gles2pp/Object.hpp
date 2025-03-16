#pragma once

#include "Exception.hpp"

#include <GLES2/gl2.h>

namespace gles2pp
{

class Object
{
public:
    constexpr Object(GLuint t_name) : m_name{t_name}
    {
        if (m_name == 0)
        {
            throw Exception("Failed to create OpenGL object");
        }
    }

    virtual ~Object() = default;

    Object(const Object&) = delete;
    auto operator=(const Object&) -> Object& = delete;
    Object(Object&&) = delete;
    auto operator=(Object&&) -> Object& = delete;

    [[nodiscard]] constexpr auto get_name() const noexcept -> const auto&
    {
        return m_name;
    }

private:
    GLuint m_name;
};

}