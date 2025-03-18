#pragma once

#include "Object.hpp"

#include <GLES2/gl2.h>

#include <string>

namespace gles2pp
{

class ShaderAttachment;

class Shader : Object
{
    friend ShaderAttachment;

public:
    enum class Parameter : GLenum
    {
        TYPE = GL_SHADER_TYPE,
        DELETE_STATUS = GL_DELETE_STATUS,
        COMPILE_STATUS = GL_COMPILE_STATUS,
        INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
        SOURCE_LENGTH = GL_SHADER_SOURCE_LENGTH
    };

    enum class Type : GLenum
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    Shader(Type t_type);
    ~Shader() override;

    Shader(const Shader&) = delete;
    auto operator=(const Shader&) -> Shader& = delete;
    Shader(Shader&&) = delete;
    auto operator=(Shader&&) -> Shader& = delete;

    void compile();
    [[nodiscard]] auto get(Parameter t_parameter) -> GLint;
    void source(const std::string& t_source);
};

}