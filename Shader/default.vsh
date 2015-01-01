#version 420

uniform mat4 ModelViewProjection;
layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec3 inNormal;

out vec3 inOutNormal;

void main()
{
	inOutNormal = inNormal;
	gl_Position =  ModelViewProjection * vec4( inPosition, 1.0 );
}