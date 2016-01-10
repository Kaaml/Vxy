#version 420

struct DirLight
{
	vec3  Color;
	vec3  Position;   
	float SpecularExponent;
	vec3  SpotDirection;
	float SpotCutoff;
	//float DiffuseIntensity;                       
	//float ConstantAttenuation;  // stały współczynnik tłumienia światła; oznaczenie kc
	//float LinearAttenuation;    // liniowy współczynnik tłumienia światła; oznaczenie kl
	//float QuadraticAttenuation; // kwadratowy współczynnik tłumienia światła; oznaczenie kq
};
uniform vec3 CameraPosition;			//in world space coordinates
uniform vec2 ScreenSize;
uniform DirLight Light;
layout ( binding = 2 ) uniform sampler2D texPosition;
layout ( binding = 0 ) uniform sampler2D texColor;
layout ( binding = 1 ) uniform sampler2D texNormal;

layout ( location = 0 ) out vec4 OutColor;

void main()
{
	float DiffuseIntensity = 1.f;
	float SpecularExponent2 = 1.f;
	
	vec2 TexCoord  = gl_FragCoord.xy / ScreenSize;

	
	//usunąc w góre
	vec3 WorldPos = texture( texPosition, TexCoord ).xyz;
	vec3 Color = texture( texColor, TexCoord ).xyz;
	vec3 Normal = texture( texNormal, TexCoord).xyz;
	Normal = normalize( Normal );
    
	//liczenie swiatla kierunkowego
	vec4 AmbientColor = vec4( 1.0 );
	vec3 LightDirection = Light.Position.xyz - WorldPos;
	float DistanceToLight = length( LightDirection );
	float NdotL = max( dot( Normal, normalize( Light.Position.xyz ) ), 0.0 );		//diffuse rozproszone światło
	

	if( NdotL > 0.0 )
	{
		vec3 EyeDir = normalize( CameraPosition - WorldPos);		// E - Eye Dir  specular light
		//obliczanie wektora połówkoewgo H = L + E
		//vec3 halfVec = normalize( LightDirection + WorldPos );
		vec3 halfVec = normalize( LightDirection + EyeDir );
		float Spot = dot( normalize( Light.SpotDirection ), - LightDirection );
		float attenaution = 1.0;
		if( Spot > cos( radians( Light.SpotCutoff ) ) )
		{
			attenaution = pow( Spot, 1 / (1 + DistanceToLight * DistanceToLight ) );
		}
		float NdotH = max( 0.0, dot( Normal, halfVec ));	
		vec3 Specular = Color * pow( NdotH, SpecularExponent2 );
		
		OutColor.xyz =  Color * 0.2 * attenaution +  Color * NdotL * Light.Color;		//diffuse light zastosowany
		OutColor.xyz += Specular;
		OutColor.a = 1.0;
	}

	//natężenie światlłą dla SPOT LIGHT WAŻNE !!!
	
	// kolor = attenaution *ambient + ndotl * diff  + specular * pow( ndoth, shininess );
		// na chwile tylk
	//OutColor = texture2D( texNormal, TexCoord );
	
	//wyjsciowy_kolor = Kolor_swiatla * ( NdotL + NdotH * 0.f ) * 0.66?
	
	
}