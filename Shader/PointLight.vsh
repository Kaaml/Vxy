#version 420

layout (location = 0 ) in vec3 inPosition;

out vec4 pFragCoord;

uniform mat4 ModelViewProjection;

void main( void )
{
	
	
	pFragCoord = ModelViewProjection * vec4( inPosition, 1.f );
	gl_Position = pFragCoord;

}
