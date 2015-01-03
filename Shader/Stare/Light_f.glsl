#version 420


out vec4 OutColor;

//smooth in vec3 vPosition;
//smooth in vec3 vNormal;

//uniform LightSourceParameters
//{
//    vec4 ambient;               // intensywnoœæ œwiat³a otoczenia; oznaczenie La
//    vec4 diffuse;               // intensywnoœæ œwiat³a rozproszonego; oznaczenie Ld
//    vec4 specular;              // intensywnoœæ œwiat³a zwierciadlanego; oznaczenie Ls
//    vec4 position;              // po³o¿enie Ÿród³a œwiat³a punktowego/reflektora
//                                // (position.w = 1.0) lub wektor kierunku œwiat³a
//                                // kierunkowego, skierowany do Ÿród³a (position.w = 0.0)
//    vec3 spotDirection;         // wektor kierunku œwiat³a reflektora; oznaczenie S
//    float spotExponent;         // wyk³adnik œwiat³a reflektora; oznaczenie se;
//                                // zakres wartoœci <0;128>
//    float spotCutoff;           // k¹t obciêcia œwiat³a reflektora; oznaczaczenie sc;
//                                // zakres wartoœci <0;90> oraz 180
//    float constantAttenuation;  // sta³y wspó³czynnik t³umienia œwiat³a; oznaczenie kc
//    float linearAttenuation;    // liniowy wspó³czynnik t³umienia œwiat³a; oznaczenie kl
//    float quadraticAttenuation; // kwadratowy wspó³czynnik t³umienia œwiat³a; oznaczenie kq
//} LightSource[8];
//struct MaterialParameters
//{
//	vec4 mambient;
//    vec4 emission;      // wspó³czynnik emisji œwiat³a; oznaczenie Me
//    vec4 ambient;       // wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
//    vec4 diffuse;       // wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
//    vec4 specular;      // wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
//    float shininess;    // wyk³adnik wspó³czynnika funkcji rozb³ysku;
//                        // zakres wartoœci <0;128>; oznaczenie Msh
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
	//// Dla œwiat³a kierunkowego
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