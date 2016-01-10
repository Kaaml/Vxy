#version 420

uniform mat4 ModelViewProjection;
//uniform mat3 NormalMatrix;

layout ( location = 0 ) in vec3 inPosition;
layout ( location = 1 ) in vec3 inNormal;
layout ( location = 2 ) in vec2 inTexCoord;

out vec3 inOutNormal;
out vec3 inOutPos;
out vec2 inOutTexCoord;

void main()
{
	inOutNormal = inNormal;
	inOutPos = inPosition;
	inOutTexCoord = inTexCoord;
	gl_Position =  ModelViewProjection * vec4( inPosition, 1.0 );
}