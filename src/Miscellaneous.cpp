#include "gles2pp/Miscellaneous.hpp"

#include <cstddef>

namespace gles2pp
{

void clear_color(GLclampf t_red, GLclampf t_green, GLclampf t_blue, GLclampf t_alpha)
{
    glClearColor(t_red, t_green, t_blue, t_alpha);
}

void disable(Capability t_capability)
{
    glDisable(static_cast<GLenum>(t_capability));
}

void disable_vertex_attribute_array(GLuint t_index)
{
    glDisableVertexAttribArray(t_index);
}

void draw_elements(GLuint t_size, Primitive t_primitive, std::uintptr_t t_indices, IndexType t_index_type)
{

    glDrawElements(static_cast<GLenum>(t_primitive), static_cast<GLsizei>(t_size), static_cast<GLenum>(t_index_type),
                   reinterpret_cast<const void*>(t_indices));
}

void enable(Capability t_capability)
{
    glEnable(static_cast<GLenum>(t_capability));
}

void enable_vertex_attribute_array(GLuint t_index)
{
    glEnableVertexAttribArray(t_index);
}

void blend_function(SourceBlendFactor t_source_factor, DestinationBlendFactor t_destination_factor)
{
    glBlendFunc(static_cast<GLenum>(t_source_factor), static_cast<GLenum>(t_destination_factor));
}

void uniform(GLint t_location, GLfloat t_value)
{
    glUniform1f(t_location, t_value);
}

void uniform(GLint t_location, const std::array<GLfloat, 2>& t_values)
{
    glUniform2f(t_location, t_values[0], t_values[1]);
}

void uniform(GLint t_location, const std::array<GLfloat, 3>& t_values)
{
    glUniform3f(t_location, t_values[0], t_values[1], t_values[2]);
}

void uniform(GLint t_location, const std::array<GLfloat, 4>& t_values)
{
    glUniform4f(t_location, t_values[0], t_values[1], t_values[2], t_values[3]);
}

void uniform(GLint t_location, GLint t_value)
{
    glUniform1i(t_location, t_value);
}

void uniform(GLint t_location, const std::array<GLint, 2>& t_values)
{
    glUniform2i(t_location, t_values[0], t_values[1]);
}

void uniform(GLint t_location, const std::array<GLint, 3>& t_values)
{
    glUniform3i(t_location, t_values[0], t_values[1], t_values[2]);
}

void uniform(GLint t_location, const std::array<GLint, 4>& t_values)
{
    glUniform4i(t_location, t_values[0], t_values[1], t_values[2], t_values[3]);
}

void uniform1(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniform1fv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform2(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniform2fv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform3(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniform3fv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform4(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniform4fv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform1(GLint t_location, GLuint t_count, std::span<const GLint> t_data)
{
    glUniform1iv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform2(GLint t_location, GLuint t_count, std::span<const GLint> t_data)
{
    glUniform2iv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform3(GLint t_location, GLuint t_count, std::span<const GLint> t_data)
{
    glUniform3iv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform4(GLint t_location, GLuint t_count, std::span<const GLint> t_data)
{
    glUniform4iv(t_location, static_cast<GLsizei>(t_count), t_data.data());
}

void uniform_Matrix2(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniformMatrix2fv(t_location, static_cast<GLsizei>(t_count), GL_FALSE, t_data.data());
}

void uniform_Matrix3(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniformMatrix3fv(t_location, static_cast<GLsizei>(t_count), GL_FALSE, t_data.data());
}

void uniform_Matrix4(GLint t_location, GLuint t_count, std::span<const GLfloat> t_data)
{
    glUniformMatrix4fv(t_location, static_cast<GLsizei>(t_count), GL_FALSE, t_data.data());
}

void vertex_attribute_pointer(GLuint t_index, ComponentSize t_component_size, GLuint t_stride,
                              std::uintptr_t t_first_component, ComponentType t_component_type, bool t_normalized)
{
    glVertexAttribPointer(t_index, static_cast<GLint>(t_component_size), static_cast<GLenum>(t_component_type),
                          t_normalized ? GL_TRUE : GL_FALSE, static_cast<GLsizei>(t_stride),
                          reinterpret_cast<const void*>(t_first_component));
}

void viewport(GLuint t_width, GLuint t_height, GLint t_x, GLint t_y)
{
    glViewport(t_x, t_y, static_cast<GLsizei>(t_width), static_cast<GLsizei>(t_height));
}

}