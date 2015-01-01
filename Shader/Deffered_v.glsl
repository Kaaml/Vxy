#version 420

uniform mat4 modelViewProjectionMatrix;
uniform mat4 mMatrix;
uniform mat3 normalMatrix;

layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec2 UV;
layout ( location = 2 ) in vec3 Normal;

out vec3 wPosition;		// pozycja w orientacji swiata
out vec3 vNormal;
out vec2 vTex;


void main( void )
{
	wPosition = (mMatrix * vec4( inPosition, 1.0 )).xyz;

	vTex = UV;
	vNormal = normalMatrix * Normal;
	gl_Position = modelViewProjectionMatrix * vec4(inPosition, 1.0 );

}