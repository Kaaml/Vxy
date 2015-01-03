#include "UniformObject.hpp"


UniformObject::UniformObject()
{
	glGenBuffers( 1, &h_UniformBufferObject );
}


UniformObject::~UniformObject()
{
}
