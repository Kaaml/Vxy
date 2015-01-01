#version 410

layout( location = 1 ) vec3 inPosition;
uniform mat4 modelViewProjectionMatrix;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( inPosition, 1.0 );
}
