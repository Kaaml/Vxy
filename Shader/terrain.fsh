#version 420


layout( binding = 0 )uniform sampler2D ColorTex;
layout( binding = 1 )uniform sampler2D GrassTex;
//out vec4 OutColor;
in vec3 inOutNormal;
in vec3 inOutPos;
in vec2 inOutTexCoord;

layout (location = 0 ) out vec3 OutputAmbient;
layout (location = 1 ) out vec4 OutputNormal;
layout (location = 2 ) out vec3 OutputPosition;
layout (location = 3 ) out vec3 OutputDiffuse;
layout (location = 4 ) out vec3 OutputSpecular;


void main()
{
	//OutColor = vec4( inOutNormal, 1.f );
	OutputNormal = vec4(  inOutNormal, 1.f );
	OutputPosition = inOutPos;
	OutputAmbient = vec3( 1.f, 1.f, 1.f );
	if( inOutPos.y > -1.f )
	{
		OutputAmbient= texture( GrassTex, inOutTexCoord ).xyz;
		OutputDiffuse= texture( GrassTex, inOutTexCoord ).xyz;
	}
	OutputAmbient *= texture( ColorTex, inOutTexCoord ).xyz;
	OutputSpecular+= texture( ColorTex, inOutTexCoord ).xyz;
	OutputDiffuse *= texture( ColorTex, inOutTexCoord ).xyz;
}