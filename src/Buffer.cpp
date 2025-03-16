#include "gles2pp/Buffer.hpp"

namespace gles2pp
{

Buffer::Buffer()
    : Object{[]() {
          GLuint name{0};
          glGenBuffers(1, &name);
          return name;
      }()}
{
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &get_name());
}

void Buffer::bind(Target t_target)
{
    glBindBuffer(static_cast<GLenum>(t_target), get_name());
}

void Buffer::data(Target t_target, std::uintptr_t t_size, std::span<const std::byte> t_data, DrawUsage t_draw_usage)
{
    glBufferData(static_cast<GLenum>(t_target), static_cast<GLsizeiptr>(t_size), t_data.data(),
                 static_cast<GLenum>(t_draw_usage));
}

void Buffer::subdata(Target t_target, std::span<const std::byte> t_data, std::uintptr_t t_offset)
{
    glBufferSubData(static_cast<GLenum>(t_target), static_cast<GLintptr>(t_offset),
                    static_cast<GLsizeiptr>(t_data.size()), t_data.data());
}

}