#version 410

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 UV;
layout (location = 2) in vec3 Normal;

uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	gl_Position = modelViewProjectionMatrix * vec4( inPosition, 1.0 );
}