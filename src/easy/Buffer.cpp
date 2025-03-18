#include "gles2pp/easy/Buffer.hpp"

namespace gles2pp::easy
{

ArrayBuffer::ArrayBuffer(std::size_t t_size) : Buffer{Target::ARRAY, t_size}
{
}

ArrayElementBuffer::ArrayElementBuffer(std::size_t t_size) : Buffer{Target::ELEMENT_ARRAY, t_size}
{
}

void ArrayElementBuffer::draw(Primitive t_primitive)
{
    draw_elements(size(), t_primitive);
}

}