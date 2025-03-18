#pragma once

#include "gles2pp/Texture.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

namespace gles2pp::easy
{

class Texture2D : public gles2pp::Texture
{
public:
    enum class ScaleMode : std::uint8_t
    {
        NEAREST,
        LINEAR
    };

    Texture2D(GLuint t_width, GLuint t_height, std::span<const std::byte> t_data, ScaleMode t_scale_mode,
              Unit t_unit = Unit::TEXTURE0);
};

}