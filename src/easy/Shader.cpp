#include "gles2pp/easy/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace gles2pp::easy
{

Shader::Shader(Type t_type, const std::string& t_path) : gles2pp::Shader{t_type}
{
    const auto source_string = [&]() {
        std::ifstream file{t_path};
        std::ostringstream string_stream;
        string_stream << file.rdbuf();
        return string_stream.str();
    }();
    source(source_string);
    compile();
    if (get(Parameter::COMPILE_STATUS) != GL_TRUE)
    {
        throw std::runtime_error("Failed to compile shader:\n" + source_string);
    }
}

}