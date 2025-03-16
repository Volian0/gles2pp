#include "gles2pp/ShaderAttachment.hpp"

#include "gles2pp/Program.hpp"
#include "gles2pp/Shader.hpp"

namespace gles2pp
{

ShaderAttachment::ShaderAttachment(Program& t_program, Shader& t_shader)
    : m_program{t_program.get_name()}, m_shader{t_shader.get_name()}
{
    glAttachShader(m_program.get_name(), m_shader.get_name());
}

ShaderAttachment::~ShaderAttachment()
{
    glDetachShader(m_program.get_name(), m_shader.get_name());
}

}