#version 410

struct DirLight
{
	vec3  Color;
	vec3  Direction;
	float AmbientIntensity;               
	float DiffuseIntensity;       
	vec3  Position;                   
	float ConstantAttenuation;  // sta³y wspó³czynnik t³umienia œwiat³a; oznaczenie kc
	float LinearAttenuation;    // liniowy wspó³czynnik t³umienia œwiat³a; oznaczenie kl
	float QuadraticAttenuation; // kwadratowy wspó³czynnik t³umienia œwiat³a; oznaczenie kq
};

uniform vec2 ScreenSize;
uniform vec3 EyeWorldPosition;
uniform DirLight Light;
uniform sampler2D texPosition;
uniform sampler2D texColor;
uniform sampler2D texNormal;

out vec4 OutColor;

void main()
{
	vec2 TexCoord  = gl_FragCoord.xy / ScreenSize;
	vec3 WorldPos = texture( texPosition, TexCoord ).xyz;
	vec3 Color = texture( texColor, TexCoord ).xyz;
	vec3 Normal = texture( texNormal, TexCoord).xyz;
	Normal = normalize( Normal );

	//liczenie swiatla kierunkowego
	vec4 AmbientColor = vec4( 1.0 );// vec4( DirLight.Color , 1.0 ) * DirLight.AmbientIntensity;
	vec4 DiffuseColor = vec4( 0.0 );
	vec4 SpecularColor = vec4( 0.0 );
	vec3 color = vec3( 0.0 );
	float NdotL = max( dot( Normal, normalize( Light.Position.xyz ) ), 0.0 );
	if( NdotL > 0.0 )
	{
		//obliczanie wektora po³ówkoewgo
		vec3 halfVec = normalize( normalize(Light.Position.xyz) - normalize( WorldPos ) );
		float NdotH = max( dot( Normal, halfVec ), 0.0 );
		color = NdotL * Light.Color * Light.DiffuseIntensity * Color;
		
	}
	OutColor = vec4( color, 1.0 ); 



}