#version 420

out vec4 OutColor;
in vec3 inOutNormal;

void main()
{
	OutColor = vec4( 0.86f, 0.86f, 0.86f, 1.f );
	//OutColor = vec4( inOutNormal, 1.f );
}