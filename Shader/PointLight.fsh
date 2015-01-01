#version 420 

in vec4 pFragCoord;

out vec4 OutputColor;

layout ( binding = 0 ) uniform sampler2D iAmbientTex;
layout ( binding = 2 ) uniform sampler2D iPositionTex;		//world space
layout ( binding = 1 ) uniform sampler2D iNormalTex;		
layout ( binding = 3 ) uniform sampler2D iDiffuseTex;
layout ( binding = 4 ) uniform sampler2D iSpecularTex;

uniform vec3  CameraPosition;
uniform vec3  LightPosition;
uniform float LightRadius;
uniform vec3  LightAmbient;
uniform vec3  LightDiffuse;
uniform vec3  LightSpecular;
uniform float LightSpecualrPower;


/*
void main( void )
{
	vec2 f2TexCoord = (vec2(pFragCoord.x, pFragCoord.y) / pFragCoord.w + 1.0) * 0.5;
	OutputColor = texture2D( iAmbientTex, f2TexCoord );
	vec3 Normal = texture2D( iNormalTex, f2TexCoord ).xyz;
	Normal = normalize( Normal );
	
	/*vec3 Position = texture2D( iPositionTex, f2TexCoord );
	vec3 LightDir = vec3( LightPosition - Position );
	float d = length( LightDir );
	LightDir /= LightRadius;
	float Attenuation = clamp( 1.f - dot( LightDir, LightDir ) );
	LightDir = normalize( LightDir );
	

	// stary shader ktory chyba dzialal
	LightDirection = LightPosition - Position;
	float LightDistance = length( LightDirection );
	LightDirection /= LightDistance;
	
	float NdotL = max( dot( Normal, LightDirection ), 0.0 );		// diffuse
	vec4 Color = vec4( 0.0 );
	if( NdotL > 0.0 )
	{
		float Attenuation = max( 0, 1 - LightDistance/ LightRadius );
		
		vec3 halfVec = normalize( LightPosition + normalize( CameraPosition - Position ) );
		float NdotH = max( dot( Normal, halfVec), 0.0 );
		//dla phonga z reflect
		vec3 R = normalize( -reflect( LightDirection, Normal ) );
		
		
		Color =  NdotL * LightDiffuse +
					LightSpecular * pow( NdotH, Shininess );
		OutputColor = Color;
	}	
}*/

void main( void )
{
	vec2 f2TexCoord = (vec2(pFragCoord.x, pFragCoord.y) / pFragCoord.w + 1.0) * 0.5;
	
	OutputColor = texture2D( iAmbientTex, f2TexCoord );
	vec3 Normal = texture2D( iNormalTex, f2TexCoord ).xyz;
	Normal = normalize( Normal );
	float Shininess = texture2D( iNormalTex, f2TexCoord ).a;
	vec3 Position = texture2D( iPositionTex, f2TexCoord ).xyz;

	vec3 LightDirection = LightPosition - Position;
	float LightDistance = length( LightDirection );
	//float Attenuation = clamp( 1.f - dot( LightDir, LightDir ) );
	LightDirection /= LightDistance;
	
	float NdotL = max( dot( Normal, LightDirection ), 0.0 );		// diffuse factor
	vec4 Color = vec4( 0.0 );
	if( NdotL > 0.0 )
	{
		float Attenuation = max( 0, 1 - LightDistance/ LightRadius );	

		vec3 R = normalize( -reflect( LightDirection, Normal ) );
		//vec3 Diffuse = texture2D( iDiffuseTex, f2TexCoord) * NdotL;
		float RdotE = max( dot( R, CameraPosition), 0.0f );		//specular factor
		vec3 Specular = pow( RdotE, Shininess );
		
		
		//Color =  NdotL * LightDiffuse +	LightSpecular;
		
		Color = vec4( Attenuation * LightAmbient *( 0.1 + NdotL + RdotE ), 1.f );
		OutputColor += Color;
	}
}