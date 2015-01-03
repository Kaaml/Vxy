#version 420

layout (location = 0 ) in vec3 inPosition;
layout (location = 1 ) in vec3 inNormal;
layout (location = 2 ) in vec2 inUv;

out vec2 pUv;

uniform mat4 ModelViewProjection;

void main()
{
	pUv = inUv;
	gl_Position = ModelViewProjection * vec4( inPosition, 1.f );

}