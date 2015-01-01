#version 420

in vec2 pUv;

layout (location = 0 ) out vec3 OutputColor;
layout (binding = 0 ) uniform sampler2D iTexture;

void main( void )
{
	OutputColor = texture( iTexture, pUv );
	//OutputColor = vec3( pUv.x, pUv.y, 0.f );
}