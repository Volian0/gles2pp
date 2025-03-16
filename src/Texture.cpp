#include "gles2pp/Texture.hpp"

#include "gles2pp/Exception.hpp"

namespace gles2pp
{

Texture::Texture()
    : Object{[]() {
          GLuint name{0};
          glGenTextures(1, &name);
          return name;
      }()}
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &get_name());
}

void Texture::bind(BindTarget t_target)
{
    glBindTexture(static_cast<GLenum>(t_target), get_name());
}

void Texture::active(Unit t_unit)
{
    glActiveTexture(static_cast<GLenum>(t_unit));
}

void Texture::generate_mipmap(BindTarget t_target)
{
    glGenerateMipmap(static_cast<GLenum>(t_target));
}

void Texture::image(GLuint t_width, GLuint t_height, std::span<const std::byte> t_data, Format t_format,
                    ImageTarget t_target, GLuint t_lod_level, TexelType t_texel_type)
{
    constexpr GLuint MINIMUM_2D_SIZE{64};
    constexpr GLuint MINIMUM_CUBEMAP_SIZE{16};
    if (t_target == ImageTarget::TEXTURE_2D)
    {
        if (t_width < MINIMUM_2D_SIZE || t_height < MINIMUM_2D_SIZE)
        {
            throw Exception("Invalid 2D texture size");
        }
    }
    else if (t_width < MINIMUM_CUBEMAP_SIZE || t_height < MINIMUM_CUBEMAP_SIZE)
    {
        throw Exception("Invalid cubemap texture size");
    }
    glTexImage2D(static_cast<GLenum>(t_target), static_cast<GLint>(t_lod_level), static_cast<GLint>(t_format),
                 static_cast<GLsizei>(t_width), static_cast<GLsizei>(t_height), 0, static_cast<GLenum>(t_format),
                 static_cast<GLenum>(t_texel_type), t_data.data());
}

void Texture::parameter(MinifyingFilter t_minifying_filter, BindTarget t_target)
{
    glTexParameteri(static_cast<GLenum>(t_target), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(t_minifying_filter));
}

void Texture::parameter(MagnifyingFilter t_magnifying_filter, BindTarget t_target)
{
    glTexParameteri(static_cast<GLenum>(t_target), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(t_magnifying_filter));
}

void Texture::parameter(WrapS t_wrap_s, BindTarget t_target)
{
    glTexParameteri(static_cast<GLenum>(t_target), GL_TEXTURE_WRAP_S, static_cast<GLint>(t_wrap_s));
}

void Texture::parameter(WrapT t_wrap_t, BindTarget t_target)
{
    glTexParameteri(static_cast<GLenum>(t_target), GL_TEXTURE_WRAP_T, static_cast<GLint>(t_wrap_t));
}

}