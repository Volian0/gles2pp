#pragma once

#include <GLES2/gl2.h>

#include <array>
#include <cstddef>
#include <string>
#include <utility>

namespace gles2pp::easy
{

class Program;

class Uniform
{
    friend Program;

public:
    constexpr Uniform(std::string t_name) : m_name{std::move(t_name)}
    {
    }

    [[nodiscard]] constexpr auto get_location() const noexcept
    {
        return m_location;
    }

private:
    std::string m_name;
    GLint m_location{-1};
};

template <std::size_t Size> using Uniforms = std::array<Uniform, Size>;

}