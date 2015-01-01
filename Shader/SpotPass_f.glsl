#version 410

struct SpotLight
{
	vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	vec3 Position;
	vec3 SpotDirection;
	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;
	float SpotCutoff;		//promien swiatla
	float SpotExponent;
};

uniform sampler2D texPosition;
uniform sampler2D texColor;
uniform sampler2D texNormal;
uniform SpotLight Light;
uniform vec2 ScreenSize;

out vec4 OutColor;



void main()
{
	vec2 TexCoord = gl_FragCoord.xy / ScreenSize;
	vec3 WorldPosition = texture2D( texPosition, TexCoord ).xyz;
	vec3 Color = texture2D( texColor, TexCoord ).xyz;
	vec3 Normal = texture2D( texNormal, TexCoord ).xyz;
	Normal = normalize( Normal );
	
	
	// SWIATLO WLASCIWE
	vec3 LightColor;
	vec3 LightVec = Light.Position.xyz - WorldPosition.xyz;
	float d = length( LightVec );			// distance
	LightVec = normalize( LightVec );
	float NdotL = max( dot( Normal, LightVec ), 0.0 );
	if( NdotL > 0.0 )
	{
		float spot = dot( Light.SpotDirection, -LightVec );
		
		if( spot > cos( radians( Light.SpotCutoff ) )  )
		{
			float Attenuation = pow( spot, Light.SpotExponent ) / ( Light.ConstantAttenuation + Light.LinearAttenuation * d + Light.QuadraticAttenuation * d * d );
			
			float NdotH = max( dot( Normal, LightVec ), 0.0 );
			
			//wyliczenie 
			LightColor = NdotL * Light.DiffuseIntensity * Attenuation * Light.Color;
		}	
	}
	else
		LightColor = vec3( 0.0 );


}
