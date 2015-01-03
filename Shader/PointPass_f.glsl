#version 410

uniform vec2 ScreenSize;

uniform sampler2D PositionMap;
uniform sampler2D ColorMap;
uniform sampler2D NormalMap;

out vec4 OutColor;

void main()
{
	vec2 TexCoord  = gl_fragCoord.xy / ScreenSize;
	vec3 WorldPos = texture( PositionMap, TexCoord ).xyz;
	vec3 ColorM = texture( ColorMap, TexCoord ).xyz;
	vec3 Normal = texture( NormalMap, TexCoord).xyz;
	Normal = normalize( Normal );
	// liczenie swiatla punktowego
	vec3 LightDirection = WorldPos - PointLight.Position;
	float Distance = length( LightDirection );
	LightDirection = normalize( LightDirection );
	
	vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;
    float DiffuseFactor = dot(Normal, -LightDirection);		//N dot L

    vec4 DiffuseColor  = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * DiffuseFactor;

        vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);          // H= E dot L
        SpecularFactor = pow(SpecularFactor, gSpecularPower);
        if (SpecularFactor > 0) {
            SpecularColor = vec4(Light.Color, 1.0f) * gMatSpecularIntensity * SpecularFactor;
        }
    }
	vec4 Color = AmbientColor + DiffuseColor+ SpecularColor;
	float Attenuation =  gPointLight.Atten.Constant +
                         gPointLight.Atten.Linear * Distance +
                         gPointLight.Atten.Exp * Distance * Distance;

    Attenuation = min(1.0, Attenuation);
	Color = Color / Attenaution;
	
	OutColor = vec4( ColorM, 1.0 ) * Color;

}