#pragma once

#include "Object.hpp"

#include <GLES2/gl2.h>

#include <cstddef>
#include <span>

namespace gles2pp
{

class Texture : Object
{
public:
    enum class BindTarget : GLenum
    {
        TEXTURE_2D = GL_TEXTURE_2D,
        TEXTURE_CUBEMAP = GL_TEXTURE_CUBE_MAP
    };

    enum class Format : GLenum
    {
        ALPHA = GL_ALPHA,
        LUMINANCE = GL_LUMINANCE,
        LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    enum class ImageTarget : GLenum
    {
        TEXTURE_2D = GL_TEXTURE_2D,
        TEXTURE_CUBEMAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        TEXTURE_CUBEMAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        TEXTURE_CUBEMAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        TEXTURE_CUBEMAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        TEXTURE_CUBEMAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        TEXTURE_CUBEMAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    enum class MagnifyingFilter : GLenum
    {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR
    };

    enum class MinifyingFilter : GLenum
    {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,
        NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class Parameter : GLenum
    {
        MINIFYING_FILTER = GL_TEXTURE_MIN_FILTER,
        MAGNIFYING_FILTER = GL_TEXTURE_MAG_FILTER,
        WRAP_S = GL_TEXTURE_WRAP_S,
        WRAP_T = GL_TEXTURE_WRAP_T
    };

    enum class TexelType : GLenum
    {
        UBYTE = GL_UNSIGNED_BYTE,
        USHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
        USHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
        USHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1
    };

    /* Which texture unit to make active. */
    enum class Unit : GLenum
    {
        TEXTURE0 = GL_TEXTURE0,
        TEXTURE1 = GL_TEXTURE1,
        TEXTURE2 = GL_TEXTURE2,
        TEXTURE3 = GL_TEXTURE3,
        TEXTURE4 = GL_TEXTURE4,
        TEXTURE5 = GL_TEXTURE5,
        TEXTURE6 = GL_TEXTURE6,
        TEXTURE7 = GL_TEXTURE7
    };

    enum class WrapS : GLenum
    {
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        REPEAT = GL_REPEAT
    };

    enum class WrapT : GLenum
    {
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        REPEAT = GL_REPEAT
    };

    Texture();
    ~Texture() override;

    Texture(const Texture&) = delete;
    auto operator=(const Texture&) -> Texture& = delete;
    Texture(Texture&&) = delete;
    auto operator=(Texture&&) -> Texture& = delete;

    void bind(BindTarget t_target = BindTarget::TEXTURE_2D);

    static void active(Unit t_unit);
    static void generate_mipmap(BindTarget t_target = BindTarget::TEXTURE_2D);
    static void image(GLuint t_width, GLuint t_height, std::span<const std::byte> t_data,
                      Format t_format = Format::RGBA, ImageTarget t_target = ImageTarget::TEXTURE_2D,
                      GLuint t_lod_level = 0, TexelType t_texel_type = TexelType::UBYTE);
    static void parameter(MinifyingFilter t_minifying_filter, BindTarget t_target = BindTarget::TEXTURE_2D);
    static void parameter(MagnifyingFilter t_magnifying_filter, BindTarget t_target = BindTarget::TEXTURE_2D);
    static void parameter(WrapS t_wrap_s, BindTarget t_target = BindTarget::TEXTURE_2D);
    static void parameter(WrapT t_wrap_t, BindTarget t_target = BindTarget::TEXTURE_2D);
};

}