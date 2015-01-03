#version 420

uniform mat4 modelViewProjectionMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec2 UV;
layout ( location = 2 ) in vec3 Normal;

smooth out vec3 vPosition;
smooth out vec3 vNormal;


void main( void )
{
	//vPosition = vec3(mvMatrix) * inPosition;

	//vNormal = normalMatrix * Normal;
	gl_Position = modelViewProjectionMatrix * vec4(inPosition, 1.0 );

}