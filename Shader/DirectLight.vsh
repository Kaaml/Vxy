#version 420

layout ( location = 0 ) in vec3 inPosition;

uniform mat4 ModelViewProjection;

void main()
{
	gl_Position = ModelViewProjection * vec4( inPosition, 1.0 );
}