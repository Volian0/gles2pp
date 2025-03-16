#include "gles2pp/Program.hpp"

#include "gles2pp/Exception.hpp"

namespace gles2pp
{

Program::Program() : Object{glCreateProgram()}
{
}

Program::~Program()
{
    glDeleteProgram(get_name());
}

auto Program::get_attribute_location(std::string_view t_name) -> GLint
{
    const auto attribute_location = glGetAttribLocation(get_name(), t_name.data());
    if (attribute_location == -1)
    {
        throw Exception("Failed to get attribute location");
    }
    return attribute_location;
}

auto Program::get(Parameter t_parameter) -> GLint
{
    GLint value{0};
    glGetProgramiv(get_name(), static_cast<GLenum>(t_parameter), &value);
    return value;
}

auto Program::get_uniform_location(std::string_view t_name) -> GLint
{
    const auto uniform_location = glGetUniformLocation(get_name(), t_name.data());
    if (uniform_location == -1)
    {
        throw Exception("Failed to get uniform location");
    }
    return uniform_location;
}

void Program::link()
{
    glLinkProgram(get_name());
}

void Program::use()
{
    glUseProgram(get_name());
}

}