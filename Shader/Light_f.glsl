#version 420


out vec4 OutColor;

//smooth in vec3 vPosition;
//smooth in vec3 vNormal;

//uniform LightSourceParameters
//{
//    vec4 ambient;               // intensywno�� �wiat�a otoczenia; oznaczenie La
//    vec4 diffuse;               // intensywno�� �wiat�a rozproszonego; oznaczenie Ld
//    vec4 specular;              // intensywno�� �wiat�a zwierciadlanego; oznaczenie Ls
//    vec4 position;              // po�o�enie �r�d�a �wiat�a punktowego/reflektora
//                                // (position.w = 1.0) lub wektor kierunku �wiat�a
//                                // kierunkowego, skierowany do �r�d�a (position.w = 0.0)
//    vec3 spotDirection;         // wektor kierunku �wiat�a reflektora; oznaczenie S
//    float spotExponent;         // wyk�adnik �wiat�a reflektora; oznaczenie se;
//                                // zakres warto�ci <0;128>
//    float spotCutoff;           // k�t obci�cia �wiat�a reflektora; oznaczaczenie sc;
//                                // zakres warto�ci <0;90> oraz 180
//    float constantAttenuation;  // sta�y wsp�czynnik t�umienia �wiat�a; oznaczenie kc
//    float linearAttenuation;    // liniowy wsp�czynnik t�umienia �wiat�a; oznaczenie kl
//    float quadraticAttenuation; // kwadratowy wsp�czynnik t�umienia �wiat�a; oznaczenie kq
//} LightSource[8];
//struct MaterialParameters
//{
//	vec4 mambient;
//    vec4 emission;      // wsp�czynnik emisji �wiat�a; oznaczenie Me
//    vec4 ambient;       // wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
//    vec4 diffuse;       // wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
//    vec4 specular;      // wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
//    float shininess;    // wyk�adnik wsp�czynnika funkcji rozb�ysku;
//                        // zakres warto�ci <0;128>; oznaczenie Msh
//};

//uniform MaterialParameters FrontMaterial =
//    MaterialParameters( vec4( 0.1, 0.1, 0.1, 1.0 ),
//						vec4( 0.0, 0.0, 0.0, 1.0 ),
//                        vec4( 0.2, 0.2, 0.2, 1.0 ),
//                        vec4( 0.8, 0.8, 0.8, 1.0 ),
//                        vec4( 0.0, 0.0, 0.0, 1.0 ),
//                        0.0 );




void main( void )
{


	//vec3 Normal = normalize( vNormal);
	////OutColor = vec4( 1.0, 0.0, 0.0, 1.0 );
	//// Dla �wiat�a kierunkowego
	//float NdotL = max( dot( Normal,  LightSource[0].position.xyz ), 0.0 );
	//if( NdotL > 0.0 )
	//{
	//	vec3 halfVec = normalize( LightSource[0].position.xyz - normalize( vPosition ) );
	//	float NdotH = max( dot(Normal, halfVec), 0.0 );
	////							Material.diffuse
	//	OutColor +=  NdotL * vec4( 0.8, 0.8, 0.8, 1.0) * LightSource[0].diffuse
	//	 + vec4( 0.1, 0.1, 0.1, 1.0 )* LightSource[0].specular * pow( NdotH, 28.0 );
	////	Material.specular														shiness
	//}
	//else 
	//{
	//	OutColor += vec4( 0.0 );
	//}
	//// END direct light

	//// START POINT LIGHT
	////vec3 LightVec = LightSource[0].position.xyz - vPosition;
	////float Distance = length( LightVec );
	////float NdotL = max( dot( Normal, LightVec), 0.0 );
	////if( NdotL > 0.0 )
	////{
	////	float att = 1.0/ ( LightSource[0].constantAttenuation + 
	////						LightSource[0].linearAttenuation * Distance +
	////						LightSource[0].quadraticAttenuation * Distance * Distance);
	////	float NdotH = max( dot( Normal, LightVec), 0.0 );
	////	//											Material.ambbient				
	////	OutColor += att * LightSource[0].ambient * vec4( 0.5, 0.5, 0.5, 1.0 )
	////		 + NdotL * vec4( 0.8, 0.8, 0.8, 1.0 ) + vec4( 0.1, 0.1, 0.1, 1.0 )* LightSource[0].specular * pow( NdotH, 28 ) );
	////	//				material.diffuse			material.specular
	////}
	
	//// END POINT LIGHT
	

	//OutColor += LightSource[0].ambient * vec4( 1.0, 1.0, 1.0, 1.0 );// + vec4( 0.2, 0.2, 0.2, 0.2 );
	//// koncowe swiatlo = Light.ambient * Material.ambient + Material.emmision

	

	
	OutColor = vec4( 0.0, 1.0, 1.0 ,1.0 );
	


}