#include "gles2pp/easy/Buffer.hpp"

namespace gles2pp::easy
{

ArrayBuffer::ArrayBuffer(std::size_t t_size) : Buffer{Target::ARRAY, t_size}
{
}

void ArrayBuffer::bind()
{
    Buffer::bind(Target::ARRAY);
}

void ArrayBuffer::subdata()
{
    Buffer::subdata(Target::ARRAY);
}

ArrayElementBuffer::ArrayElementBuffer(std::size_t t_size) : Buffer{Target::ELEMENT_ARRAY, t_size}
{
}

void ArrayElementBuffer::bind()
{
    Buffer::bind(Target::ELEMENT_ARRAY);
}

void ArrayElementBuffer::subdata()
{
    Buffer::subdata(Target::ELEMENT_ARRAY);
}

void ArrayElementBuffer::draw(Primitive t_primitive)
{
    draw_elements(size(), t_primitive);
}

}