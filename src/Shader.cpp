#include "gles2pp/Shader.hpp"

namespace gles2pp
{

Shader::Shader(Type t_type) : Object{glCreateShader(static_cast<GLenum>(t_type))}
{
}

Shader::~Shader()
{
    glDeleteShader(get_name());
}

void Shader::compile()
{
    glCompileShader(get_name());
}

auto Shader::get(Parameter& t_parameter) -> GLint
{
    GLint value{0};
    glGetShaderiv(get_name(), static_cast<GLenum>(t_parameter), &value);
    return value;
}

void Shader::source(std::string_view t_source)
{
    const GLchar* source = t_source.data();
    constexpr GLint SIZE{0};
    glShaderSource(get_name(), 1, &source, &SIZE);
}

}