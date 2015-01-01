#version 410
layout ( location = 0 ) in vec3 inPosition;

uniform mat4 modelViewProjectionMatrix;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( inPosition, 1.0 );
}