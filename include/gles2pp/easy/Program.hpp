#pragma once

#include "Uniform.hpp"
#include "VertexAttribute.hpp"
#include "gles2pp/Program.hpp"
#include "gles2pp/ShaderAttachment.hpp"
#include "gles2pp/easy/Shader.hpp"

#include <stdexcept>

namespace gles2pp::easy
{

class Program : public gles2pp::Program
{
public:
    template <std::size_t VertexAttributeSize, std::size_t UniformSize>
    Program(const VertexShader& t_vertex_shader, const FragmentShader& t_fragment_shader,
            VertexAttributes<VertexAttributeSize>& t_vertex_attributes, Uniforms<UniformSize>& t_uniforms)
    {
        gles2pp::ShaderAttachment vertex_attachment(*this, t_vertex_shader);
        gles2pp::ShaderAttachment fragment_attachment(*this, t_fragment_shader);
        link();
        if (get(Parameter::LINK_STATUS) != GL_TRUE)
        {
            throw std::runtime_error("Failed to link program");
        }
        use();
        for (auto& vertex_attribute : t_vertex_attributes.get_vertex_attrubutes())
        {
            vertex_attribute.m_location = get_attribute_location(vertex_attribute.get_name());
        }
        for (auto& uniform : t_uniforms)
        {
            uniform.m_location = get_uniform_location(uniform.m_name);
        }
    }
};

}