#version 420

in vec3 pPosition;
in vec3 pNormal;
in vec2 pUv;

layout (location = 2 ) out vec3 OutputPosition;
layout (location = 1 ) out vec4 OutputNormal;
layout (location = 0 ) out vec3 OutputAmbient;
layout (location = 3 ) out vec3 OutputDiffuse;
layout (location = 4 ) out vec3 OutputSpecular;

layout( binding = 0 ) uniform sampler2D iTexture;

uniform float Shininess;
uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;



void main( void )
{
	
	OutputPosition = pPosition;
	OutputNormal = vec4( pNormal, Shininess );
	//OutputNormal = vec4( pNormal, 1.f );
	OutputAmbient =  texture( iTexture, pUv ).xyz;
	OutputDiffuse = Diffuse * texture( iTexture, pUv ).xyz;
	OutputSpecular = Specular * texture( iTexture, pUv ).xyz;
}