#version 330

//uniformy

uniform mat4 modelViewProjectionMatrix;
uniform vec3 lightPosition;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec2 UV;
layout ( location = 2 ) in vec3 Normal;


smooth out vec3 inoutNormal;
smooth out vec3 inoutLightDir;


void main( void )
{
	inoutNormal = normalMatrix * Normal;

	vec4 Position4 = mvMatrix * vec4(inPosition, 1.0 );
	vec3 Position =  Position4.xyz / Position4.w ;
	inoutLightDir = normalize( lightPosition - Position );

	gl_Position = modelViewProjectionMatrix * vec4(inPosition, 1.0 );

}