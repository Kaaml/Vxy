#version 420

uniform mat4 modelViewProjectionMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec2 UV;
layout ( location = 2 ) in vec3 inNormal;


//smooth out vec3 ioNormal;
out vec2 ioTexCoord;

void main()
{
	//ioNormal = normalMatrix * inNormal;
	ioTexCoord = UV;
	gl_Position = modelViewProjectionMatrix * vec4( inPosition, 1.0 );
	
}