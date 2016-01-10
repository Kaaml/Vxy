#version 420

struct DirLight
{
	vec3  Color;
	vec3  Position;   
	float SpecularExponent;               
	//float DiffuseIntensity;                       
	//float ConstantAttenuation;  // sta³y wspó³czynnik t³umienia œwiat³a; oznaczenie kc
	//float LinearAttenuation;    // liniowy wspó³czynnik t³umienia œwiat³a; oznaczenie kl
	//float QuadraticAttenuation; // kwadratowy wspó³czynnik t³umienia œwiat³a; oznaczenie kq
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

	
	//usun¹c w góre
	vec3 WorldPos = texture( texPosition, TexCoord ).xyz;
	vec3 Color = texture( texColor, TexCoord ).xyz;
	vec3 Normal = texture( texNormal, TexCoord).xyz;
	Normal = normalize( Normal );
    
	//liczenie swiatla kierunkowego
	vec4 AmbientColor = vec4( 1.0 );
	vec3 LightDirection = Light.Position.xyz - WorldPos;
	//vec3 LightDirection = Light.Position.xyz;
	float NdotL = max( dot( Normal, normalize( LightDirection ) ), 0.0 );		//diffuse rozproszone œwiat³o
	
	OutColor = 0.1 * vec4(Color, 1.0 ) + vec4( Color * NdotL * Light.Color, 1.0 );		//diffuse light zastosowany
	if( NdotL > 0.0 )
	{
		//vec3 EyeDir = normalize( WorldPos - CameraPosition );		// E - Eye Dir  specular light
		vec3 EyeDir = normalize( CameraPosition - WorldPos );
		//obliczanie wektora po³ówkoewgo H = L + E
		vec3 halfVec = normalize( LightDirection + WorldPos );
		halfVec = normalize( LightDirection + EyeDir );
		//vec3 halfVec = normalize( LightDirection + EyeDir );
		float NdotH = max( 0.0, dot( Normal, halfVec ));	
		vec3 Specular = Color * pow( NdotH, SpecularExponent2 );
		OutColor.xyz += Specular;		
		
	}
		// na chwile tylk
	//OutColor = vec4( Color, 1.f );
	
	
}