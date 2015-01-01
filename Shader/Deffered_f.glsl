#version 420

layout( location = 0 ) out vec3 Position;
layout( location = 1 ) out vec4 Normal;
layout( location = 2 ) out vec3 Ambient;
layout( location = 3 ) out vec3 Diffuse;
layout( location = 4 ) out vec3 Specular;

uniform sampler2D Texture1;
uniform vec3 AmbientIntensity;		
uniform vec3 DiffuseIntensity;	
uniform vec3 SpecularIntenisty;	
uniform float Shininess;

in vec3 wPosition;
in vec3 vNormal;
in vec2 vTex;

void main()
{
	Normal = vec4( normalize( vNormal ), Shininess );
	Position =  wPosition;
	Ambient = texture2D( Texture1, vTex ).rgb * AmbientIntensity;
	Diffuse =  texture2D( Texture1, vTex ).rgb * DiffuseIntensity;
	Specular = texture2D( Texture1, vTex ).rgb * SpecularIntenisty;
	
	
	
}
