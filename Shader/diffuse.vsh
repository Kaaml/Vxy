#version 420

layout (location = 0 ) in vec3 inPosition;
layout (location = 1 ) in vec3 inNormal;
layout (location = 2 ) in vec2 inUv;

out vec3 pPosition;
out vec3 pNormal;
out vec2 pUv;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

void main()
{
	pPosition = ( ModelMatrix * vec4( inPosition, 1.f )).xyz;		//world space
	pNormal = NormalMatrix *inNormal;
	//pNormal = inNormal ;
	pUv = inUv;
	gl_Position = ModelViewProjection * vec4( inPosition, 1.f );

}