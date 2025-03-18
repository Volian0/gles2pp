#include "gles2pp/easy/Texture2D.hpp"

namespace gles2pp::easy
{

Texture2D::Texture2D(GLuint t_width, GLuint t_height, std::span<const std::byte> t_data, ScaleMode t_scale_mode,
                     Unit t_unit)
{
    active(t_unit);
    bind();
    image(t_width, t_height, t_data);
    if (t_scale_mode == ScaleMode::NEAREST)
    {
        parameter(MagnifyingFilter::NEAREST);
        parameter(MinifyingFilter::NEAREST);
    }
    else
    {
        generate_mipmap();
        parameter(MagnifyingFilter::LINEAR);
        parameter(MinifyingFilter::LINEAR_MIPMAP_LINEAR);
    }
}

}