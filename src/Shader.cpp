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

auto Shader::get(Parameter t_parameter) -> GLint
{
    GLint value{0};
    glGetShaderiv(get_name(), static_cast<GLenum>(t_parameter), &value);
    return value;
}

void Shader::source(const std::string& t_source)
{
    const auto* const source = t_source.data();
    glShaderSource(get_name(), 1, &source, nullptr);
}

}