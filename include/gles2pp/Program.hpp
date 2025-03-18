#pragma once

#include "Object.hpp"

#include <GLES2/gl2.h>

#include <string>

namespace gles2pp
{

class ShaderAttachment;

class Program : Object
{
    friend ShaderAttachment;

public:
    enum class Parameter : GLenum
    {
        DELETE_STATUS = GL_DELETE_STATUS,
        LINK_STATUS = GL_LINK_STATUS,
        VALIDATE_STATUS = GL_VALIDATE_STATUS,
        INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
        ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
        ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
        ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
        ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
        ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH
    };

    Program();
    ~Program() override;

    Program(const Program&) = delete;
    auto operator=(const Program&) -> Program& = delete;
    Program(Program&&) = delete;
    auto operator=(Program&&) -> Program& = delete;

    [[nodiscard]] auto get_attribute_location(const std::string& t_name) -> GLint;
    [[nodiscard]] auto get(Parameter t_parameter) -> GLint;
    [[nodiscard]] auto get_uniform_location(const std::string& t_name) -> GLint;
    void link();
    void use();
};

}