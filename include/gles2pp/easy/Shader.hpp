#pragma once

#include "gles2pp/Shader.hpp"

#include <string>

namespace gles2pp::easy
{

class Shader : public gles2pp::Shader
{
public:
    Shader(Type t_type, const std::string& t_path);
};

class VertexShader : public Shader
{
public:
    VertexShader(const std::string& t_path);
};

class FragmentShader : public Shader
{
public:
    FragmentShader(const std::string& t_path);
};

}