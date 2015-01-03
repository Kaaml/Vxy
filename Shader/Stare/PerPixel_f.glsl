#version 330

//uniformy

uniform mat4 modelViewProjectionMatrix;
uniform vec4 diffuseColor;
uniform vec3 lightPosition;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

out vec4 FragColor;

smooth in vec3 inoutNormal;
smooth in vec3 inoutLightDir;
	

void main( void )
{
	vec4 AmbientColor = vec4( 1.0, 1.0, 1.0, 1.0 );
	//vec4 DiffuseColor = vec4( 1.0, 1.0, 1.0, 1.0 );
	vec4 SpecularColor = vec4( 0.0, 0.0, 1.0, 1.0 );

	float diff = max( 0.0, dot( normalize( inoutNormal ), normalize( inoutLightDir ) ) );

	FragColor = diff * diffuseColor;
	FragColor += AmbientColor;
	FragColor *= vec4( 1.0, 0.0, 0.0, 1.0 );
	
	 vec3 Reflection = normalize( reflect( -normalize(inoutLightDir ), normalize( inoutNormal ) ) ); 

	 float spec = max( 0.0, dot( normalize( inoutNormal ), Reflection ) );
	 if( diff != 0 )
	{
		float fSpec = pow( spec, 128.0 );
		FragColor.rgb += vec3( fSpec, fSpec, fSpec );
	}
}