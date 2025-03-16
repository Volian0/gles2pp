#pragma once

#include "Object.hpp"

namespace gles2pp
{

class Program;
class Shader;

class ShaderAttachment
{
public:
    ShaderAttachment(Program& t_program, Shader& t_shader);
    ~ShaderAttachment();

    ShaderAttachment(const ShaderAttachment&) = delete;
    auto operator=(const ShaderAttachment&) -> ShaderAttachment& = delete;
    ShaderAttachment(ShaderAttachment&&) = delete;
    auto operator=(ShaderAttachment&&) -> ShaderAttachment& = delete;

private:
    Object m_program;
    Object m_shader;
};

}