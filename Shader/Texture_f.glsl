#version 420


struct PointLight
{
	vec3  Color;
	float AmbientIntensity;               
	float DiffuseIntensity; 
	float SpecularPower;      
	vec3  Position;
	float Radius;                   
	float ConstantAttenuation;  // sta?y wsp?czynnik t?umienia ?wiat?a; oznaczenie kc
	float LinearAttenuation;    // liniowy wsp?czynnik t?umienia ?wiat?a; oznaczenie kl
	float QuadraticAttenuation; // kwadratowy wsp?czynnik t?umienia ?wiat?a; oznaczenie kq
};

uniform sampler2D	texPosition;
uniform sampler2D	texColor;
uniform sampler2D	texNormal;
uniform PointLight	Light;
uniform vec2		ScreenSize;

in vec2 ioTexCoord;


out vec4 OutColor;

//  >>>>>>>>>>>>>>>>>   MAIN FUNC      <<<<<<<<<<<<
void main()
{
	// odbudowa danych
	vec2 TexCoord = gl_FragCoord.xy / ScreenSize;
	vec3 WorldPosition =  texture2D( texPosition, TexCoord ).xyz ;
	vec3 Color = texture2D( texColor, TexCoord ).xyz;
	vec3 Normal = texture2D( texNormal, TexCoord ).xyz;
	Normal = normalize( Normal );
	float Shininess = texture2D( texNormal, TexCoord ).a;


	float radius = Light.Radius;
	vec3 LightDir = Light.Position.xyz - WorldPosition.xyz;
	float d = length( LightDir );
	LightDir /= d;
	vec3 color = vec3( 0.0 );
	float NdotL = max( dot( Normal, LightDir ), 0.0 );		//difuse
	if( NdotL > 0.0 )
	{
		//float attenuation = 1.f /(Light.ConstantAttenuation +
		//					  Light.LinearAttenuation * d +
		//					  Light.QuadraticAttenuation *d *d);
		float att = max( 0, 1- d/ radius );
		float NdotH = max( dot( Normal, LightDir ), 0.0 );		//specular

		//color += att * Color * Light.Color * NdotL + pow( NdotH, 128 ) * Light.Color * Color * 0.8;
		color += att * Light.Color * ( NdotL * Color + Light.SpecularPower*pow(NdotH, Shininess )  * Color + 0.2 * Color ) ;
	}
	OutColor = vec4( color, 1.0 );
	
}





