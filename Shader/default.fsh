#version 420

//out vec4 OutColor;
in vec3 inOutNormal;
in vec3 inOutPos;


layout (location = 0 ) out vec3 OutputAmbient;
layout (location = 1 ) out vec4 OutputNormal;
layout (location = 2 ) out vec3 OutputPosition;
layout (location = 3 ) out vec3 OutputDiffuse;
layout (location = 4 ) out vec3 OutputSpecular;

void main()
{
	//OutColor = vec4( 1.f, 1.86f, 0.0f, 1.f );
	OutputAmbient = vec3( 1.f, 1.86f, 0.0f);
	OutputNormal = vec4( inOutNormal, 1.f );
	OutputPosition =  inOutPos;
	OutputDiffuse = vec3( 1.f, 1.86f, 0.0f );
	OutputSpecular= vec3( 1.f, 1.86f, 0.0f );
	//OutColor = vec4( inOutPos, 1.f );
}