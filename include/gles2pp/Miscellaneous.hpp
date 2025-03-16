#pragma once

#include <GLES2/gl2.h>

#include <array>
#include <cstdint>
#include <span>

namespace gles2pp
{

/* Symbolic constant indicating a GL capability. */
enum class Capability : GLenum
{
    BLEND = GL_BLEND,
    CULL_FACE = GL_CULL_FACE,
    DEPTH_TEST = GL_DEPTH_TEST,
    DITHER = GL_DITHER,
    POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
    SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
    SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,
    SCISSOR_TEST = GL_SCISSOR_TEST,
    STENCIL_TEST = GL_STENCIL_TEST
};

/* Number of components per generic vertex attribute. */
enum class ComponentSize : std::uint_fast8_t
{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
};

/* Data type of each component in the array. */
enum class ComponentType : GLenum
{
    BYTE = GL_BYTE,
    UBYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    USHORT = GL_UNSIGNED_SHORT,
    FIXED = GL_FIXED,
    FLOAT = GL_FLOAT
};

/* How the red, green, blue, and alpha source blending factors are computed. */
enum class DestinationBlendFactor : GLenum
{
    ZERO = GL_ZERO,
    ONE = GL_ONE,
    SOURCE_COLOR = GL_SRC_COLOR,
    ONE_MINUS_SOURCE_COLOR = GL_ONE_MINUS_SRC_COLOR,
    DESTINATION_COLOR = GL_DST_COLOR,
    ONE_MINUS_DESTINATION_COLOR = GL_ONE_MINUS_DST_COLOR,
    SOURCE_ALPHA = GL_SRC_ALPHA,
    ONE_MINUS_SOURCE_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
    DESTINATION_ALPHA = GL_DST_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA = GL_ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR = GL_CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA
};

/* Type of the values in indices. */
enum class IndexType : GLenum
{
    UBYTE = GL_UNSIGNED_BYTE,
    USHORT = GL_UNSIGNED_SHORT
};

/* What kind of primitives to render. */
enum class Primitive : GLenum
{
    POINTS = GL_POINTS,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    LINES = GL_LINES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
    TRIANGLES = GL_TRIANGLES
};

/* How the red, green, blue, and alpha destination blending factors are computed. */
enum class SourceBlendFactor : GLenum
{
    ZERO = GL_ZERO,
    ONE = GL_ONE,
    SOURCE_COLOR = GL_SRC_COLOR,
    ONE_MINUS_SOURCE_COLOR = GL_ONE_MINUS_SRC_COLOR,
    DESTINATION_COLOR = GL_DST_COLOR,
    ONE_MINUS_DESTINATION_COLOR = GL_ONE_MINUS_DST_COLOR,
    SOURCE_ALPHA = GL_SRC_ALPHA,
    ONE_MINUS_SOURCE_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
    DESTINATION_ALPHA = GL_DST_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA = GL_ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR = GL_CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
    SOURCE_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
};

/* Bitwise OR of masks that indicate the buffers to be cleared. */
namespace BufferBitmask
{
inline constexpr auto COLOR{GL_COLOR_BUFFER_BIT};
inline constexpr auto DEPTH{GL_DEPTH_BUFFER_BIT};
inline constexpr auto STENCIL{GL_STENCIL_BUFFER_BIT};
}

void clear_color(GLclampf t_red, GLclampf t_green, GLclampf t_blue, GLclampf t_alpha = 1);
void disable(Capability t_capability);
void disable_vertex_attribute_array(GLuint t_index);
void draw_elements(GLuint t_size, Primitive t_primitive = Primitive::TRIANGLES, std::uintptr_t t_indices = 0,
                   IndexType t_index_type = IndexType::USHORT);
void enable(Capability t_capability);
void enable_vertex_attribute_array(GLuint t_index);
void blend_function(SourceBlendFactor t_source_factor, DestinationBlendFactor t_destination_factor);
void uniform(GLint t_location, GLfloat t_value);
void uniform(GLint t_location, const std::array<GLfloat, 2>& t_values);
void uniform(GLint t_location, const std::array<GLfloat, 3>& t_values);
void uniform(GLint t_location, const std::array<GLfloat, 4>& t_values);
void uniform(GLint t_location, GLint t_value);
void uniform(GLint t_location, const std::array<GLint, 2>& t_values);
void uniform(GLint t_location, const std::array<GLint, 3>& t_values);
void uniform(GLint t_location, const std::array<GLint, 4>& t_values);
void uniform1(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform2(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform3(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform4(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform1(GLint t_location, GLuint t_size, std::span<const GLint> t_data);
void uniform2(GLint t_location, GLuint t_size, std::span<const GLint> t_data);
void uniform3(GLint t_location, GLuint t_size, std::span<const GLint> t_data);
void uniform4(GLint t_location, GLuint t_size, std::span<const GLint> t_data);
void uniform_Matrix2(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform_Matrix3(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void uniform_Matrix4(GLint t_location, GLuint t_size, std::span<const GLfloat> t_data);
void vertex_attribute_pointer(GLuint t_index, ComponentSize t_component_size, GLuint t_stride,
                              std::uintptr_t t_first_component, ComponentType t_component_type = ComponentType::FLOAT,
                              bool t_normalized = false);
void viewport(GLuint t_width, GLuint t_height, GLint t_x = 0, GLint t_y = 0);

}