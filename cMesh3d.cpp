#include "cMesh3d.hpp"


cMesh3d::cMesh3d(void)
{
	h_vao = 0;
	h_vbo = 0;
	h_ibo = 0;
}
cMesh3d::cMesh3d( std::string FileName )
{
	h_vao = 0;
	h_vbo = 0;
	h_ibo = 0;
	LoadObjMesh( FileName );
}
cMesh3d::~cMesh3d(void){}


bool cMesh3d::LoadObjMesh( std::string FileName )
{
	std::fstream File;
	File.open( FileName.c_str(), std::ios::binary | std::ios::in );
	if( !File.is_open() )
	{
		std::cerr << "ERROR: Nie otworzono poprawnie pliku: " << FileName << std::endl;
		File.close();
		return false;
	}
	std::string buffer;
	std::stringstream ssbuffer;
	//bool Tex, Normal;
	float x, y, z;
	std::stringstream buff2;
	std::vector< glm::ivec3 > Faces;
	std::vector< glm::vec3 > Vertex;
	std::vector< glm::vec3 > Normals;
	std::vector< glm::vec2 > TexCoord;

	while( !File.eof() )
	{
		std::getline( File, buffer );

		if( !buffer.compare( 0, 2, "v " ) )
		{
			// #################################################### VERTEX #########################			
			buff2 << buffer.substr(2, buffer.length() );	
			buff2 >> x >> y>> z;
			Vertex.push_back( glm::vec3( x, y, z ) );
		}
		if( !buffer.compare( 0, 2, "vt") )
		{
			// #################################################### TEXT COORDS #########################			
			buff2 << buffer.substr(2, buffer.length() );
			buff2 >> x >> y ;
			TexCoord.push_back( glm::vec2( x, y )); 

		}
		if( !buffer.compare( 0, 2, "vn") )
		{
			// #################################################### NORMALS #########################			
			buff2 << buffer.substr(2, buffer.length() );
			buff2 >> x >> y >> z ;
			Normals.push_back( glm::vec3( x, y, z ) );		
		}
		if( !buffer.compare( 0, 1, "f" ) )
		{
			// #################################################### FACES #########################
			buff2 << buffer.substr(2, buffer.length() );
			glm::ivec3 tmpVertex[3];
			char space;
			if( Normals.size() > 0 && TexCoord.size() > 0 )
			{
				buff2 >> tmpVertex[0].x >> space >> tmpVertex[0].y >> space >> tmpVertex[0].z >>
					tmpVertex[1].x >> space >> tmpVertex[1].y >> space >> tmpVertex[1].z >>
					tmpVertex[2].x >> space >> tmpVertex[2].y >> space >> tmpVertex[2].z;
				Faces.push_back( tmpVertex[0] );
				Faces.push_back( tmpVertex[1] );
				Faces.push_back( tmpVertex[2] );
			}else
			{
				if( Normals.size() > 0 )
				{
					buff2 >> tmpVertex[0].x >> space >> space >> tmpVertex[0].y
						>> tmpVertex[1].x >> space >> space >> tmpVertex[1].y
						>> tmpVertex[2].x >> space >> space >> tmpVertex[2].y;
					Faces.push_back( tmpVertex[0] );
					Faces.push_back( tmpVertex[1] );
					Faces.push_back( tmpVertex[2] );
				//std::cout << "ERROR: Plik: " << FileName << " musi zawierac normalne i texcoordy\n";				
				}

					//TUTAJ POPRAWIC!
			}			

		}
		buff2.clear();
	}// end of while( !File.eof() )
	// przetworzenie danych na dane z indeksami

	
		struct CMP
		{
			bool operator() ( const glm::ivec3 &a, const glm::ivec3 &b ) const
			{
				return (a.x < b.x) || (	(a.x == b.x) && ( (a.y < b.y) || ((a.y == b.y) && (a.z < b.z))));
			}
			
		};
			

		std::map< glm::ivec3, int, CMP > UniqueVertex;
		std::map< glm::ivec3, int, CMP >::iterator it;		
		for( unsigned i = 0; i < Faces.size() ; ++i )
		{			
			UniqueVertex.insert( std::make_pair< glm::ivec3, int > ( (glm::ivec3)Faces[i],(int) UniqueVertex.size() ) );
			//std::cout << Faces[i].x << Faces[i].y  << Faces[i].z <<std::endl;
			Indices.push_back( UniqueVertex[ Faces[i] ] );
			//std::cout << Indices.back() << std::endl;
			
		}		
		/*for( it = UniqueVertex.begin(); it != UniqueVertex.end(); it++ )
		{
			std::cout << "V: " << it->first.x <<" VN: " << it->first.y <<" VT: " << it->first.z << " I: " << it->second << std::endl;
		}*/

		std::map< int, glm::ivec3 > result;
		std::map< int, glm::ivec3 >::iterator it2;
		for(it = UniqueVertex.begin() ; it != UniqueVertex.end(); ++it )
			result.insert( std::make_pair( it->second, it->first ) );

		for( it2 = result.begin(); it2 != result.end(); it2++ )
		{
			//std::cout << "V: " << it2->second.x <<" VN: " << it2->second.y <<" VT: " << it2->second.z << " I: " << it2->first << std::endl;
			m_Vertex.push_back( Vertex[ it2->second.x-1] );
			if( TexCoord.size() > 0 )
				m_TexCoord.push_back( TexCoord[ it2->second.y-1] );
			if( Normals.size() > 0 )
				if(  TexCoord.size() > 0 )
					m_Normals.push_back( Normals[ it2->second.z-1] );
				else
					m_Normals.push_back( Normals[ it2->second.y-1] );
		}
		LoadToGpu();

	return true;

}

void cMesh3d::LoadToGpu()
{
	glGenVertexArrays( 1, &h_vao );
	glBindVertexArray( h_vao );
	glGenBuffers( 1, &h_vbo );
	glGenBuffers( 1, &h_ibo );
	glBindBuffer( GL_ARRAY_BUFFER, h_vbo );
	glBufferData( GL_ARRAY_BUFFER,  m_Vertex.size() * sizeof(glm::vec3)
								+ m_TexCoord.size() * sizeof(glm::vec2)
								+ m_Normals.size() * sizeof( glm::vec3 ), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER, NULL, m_Vertex.size() * sizeof( glm::vec3 ), &m_Vertex[0] );
	if( m_TexCoord.size() > 0 )
		glBufferSubData( GL_ARRAY_BUFFER, m_Vertex.size() * sizeof( glm::vec3 ), m_TexCoord.size() * sizeof( glm::vec2 ), &m_TexCoord[0] );
	if( m_Normals.size() > 0 )
	glBufferSubData( GL_ARRAY_BUFFER, m_Vertex.size() * sizeof( glm::vec3 ) + m_TexCoord.size() * sizeof( glm::vec2 ),
		m_Normals.size() * sizeof( glm::vec3 ), &m_Normals[0] );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (m_Vertex.size() * sizeof( glm::vec3 ) ) );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) (m_Vertex.size() * sizeof( glm::vec3 ) +
		m_TexCoord.size() * sizeof( glm::vec2) ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, h_ibo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof( GLuint ), &Indices[0], GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	glBindVertexArray( 0 );
}

void cMesh3d::BindVertexArray()
{
	glBindVertexArray( h_vao );	
}

void cMesh3d::UnbindVertexArray()
{
	glBindVertexArray( 0 );
}

int cMesh3d::GetIndicesCout()
{
	return (int)Indices.size();
}




cMesh3d* Cube()
{
	cMesh3d* geom = new cMesh3d();
	geom->m_Vertex.resize( 24 );	
	geom->m_Vertex[0] = glm::vec3(  1, -1, -1 );
	geom->m_Vertex[1] = glm::vec3(  1, -1,  1 );
	geom->m_Vertex[2] = glm::vec3( -1, -1,  1 );
	geom->m_Vertex[3] = glm::vec3( -1, -1, -1 );
	geom->m_Vertex[4] = glm::vec3(  1,  1, -1 );
	geom->m_Vertex[5] = glm::vec3( -1,  1, -1 );
	geom->m_Vertex[6] = glm::vec3( -1,  1, 1  );
	geom->m_Vertex[7] = glm::vec3(  1,  1, 1  );
	geom->m_Vertex[8] = glm::vec3(  1, -1, -1 );
	geom->m_Vertex[9] = glm::vec3(  1,  1, -1 );
	geom->m_Vertex[10] = glm::vec3(  1,  1, 1  );
	geom->m_Vertex[11] = glm::vec3(  1, -1, 1  );
	geom->m_Vertex[12] = glm::vec3(  1, -1, 1  );
	geom->m_Vertex[13] = glm::vec3(  1,  1, 1  );
	geom->m_Vertex[14] = glm::vec3( -1,  1, 1  );
	geom->m_Vertex[15] = glm::vec3( -1, -1, 1  );
	geom->m_Vertex[16] = glm::vec3( -1, -1, 1  );
	geom->m_Vertex[17] = glm::vec3( -1,  1, 1  );
	geom->m_Vertex[18] = glm::vec3( -1,  1, -1 );
	geom->m_Vertex[19] = glm::vec3( -1, -1, -1 );
	geom->m_Vertex[20] = glm::vec3(  1,  1, -1 );
	geom->m_Vertex[21] = glm::vec3(  1, -1, -1 );
	geom->m_Vertex[22] = glm::vec3( -1, -1, -1 );
	geom->m_Vertex[23] = glm::vec3( -1,  1, -1 );

	geom->Indices.resize( 36 );
	geom->Indices[0]  = 0 ;
	geom->Indices[1]  = 1 ;
	geom->Indices[2]  = 2 ;
	geom->Indices[3]  = 0 ;
	geom->Indices[4]  = 2 ;
	geom->Indices[5]  = 3 ;
	geom->Indices[6]  = 4 ;
	geom->Indices[7]  = 5 ;
	geom->Indices[8]  = 6 ;
	geom->Indices[9]  = 4 ;
	geom->Indices[10] = 6 ;
	geom->Indices[11] = 7 ;
	geom->Indices[12] = 8 ;
	geom->Indices[13] = 9 ;
	geom->Indices[14] = 10;
	geom->Indices[15] = 8 ;
	geom->Indices[16] = 10;
	geom->Indices[17] = 11;
	geom->Indices[18] = 12;
	geom->Indices[19] = 13;
	geom->Indices[20] = 14;
	geom->Indices[21] = 12;
	geom->Indices[22] = 14;
	geom->Indices[23] = 15;
	geom->Indices[24] = 16;
	geom->Indices[25] = 17;
	geom->Indices[26] = 18;
	geom->Indices[27] = 16;
	geom->Indices[28] = 18;
	geom->Indices[29] = 19;
	geom->Indices[30] = 20;
	geom->Indices[31] = 21;
	geom->Indices[32] = 22;
	geom->Indices[33] = 20;
	geom->Indices[34] = 22;
	geom->Indices[35] = 23;

	geom->m_TexCoord.resize(24);
	geom->m_TexCoord[0] = glm::vec2( 0.25, 0.5 ); 
	geom->m_TexCoord[1] = glm::vec2(0.25, 0.25 );
	geom->m_TexCoord[2] = glm::vec2(0.5 , 0.25 );
	geom->m_TexCoord[3] = glm::vec2(0.5 , 0.5  );
	geom->m_TexCoord[4] = glm::vec2(1   , 0.5  );
	geom->m_TexCoord[5] = glm::vec2(0.75, 0.5  );
	geom->m_TexCoord[6] = glm::vec2(0.75, 0.25 );
	geom->m_TexCoord[7] = glm::vec2(1   , 0.25 );
	geom->m_TexCoord[8] = glm::vec2(0.25, 0.5  );
	geom->m_TexCoord[9] = glm::vec2(1e-006, 0.5);
	geom->m_TexCoord[10] = glm::vec2(0   , 0.250);
	geom->m_TexCoord[11] = glm::vec2(0.25, 0.250);
	geom->m_TexCoord[12] = glm::vec2(0.25, 0.250);
	geom->m_TexCoord[13] = glm::vec2(0.25, 1e-006 );
	geom->m_TexCoord[14] = glm::vec2(0.50, 0 );
	geom->m_TexCoord[15] = glm::vec2(0.5 , 0.25 );
	geom->m_TexCoord[16] = glm::vec2(0.5 , 0.25 );
	geom->m_TexCoord[17] = glm::vec2(0.75, 0.25 );
	geom->m_TexCoord[18] = glm::vec2(0.75, 0.5  );
	geom->m_TexCoord[19] = glm::vec2(0.5 , 0.5  );
	geom->m_TexCoord[20] = glm::vec2(0.25, 0.75 );
	geom->m_TexCoord[21] = glm::vec2(0.25, 0.5  );
	geom->m_TexCoord[22] = glm::vec2(0.5 , 0.5  );
	geom->m_TexCoord[23] = glm::vec2(0.50, 0.75 );
			
	geom->m_Normals.resize(24);
	geom->m_Normals [0] = glm::vec3( 0, -1, 0  );
	geom->m_Normals [1] = glm::vec3( 0, -1, 0  );
	geom->m_Normals [2] = glm::vec3( 0, -1, 0  );
	geom->m_Normals [3] = glm::vec3( 0, -1, 0  );
	geom->m_Normals [4] = glm::vec3( 0, 1 ,0   );
	geom->m_Normals [5] = glm::vec3( 0, 1 ,0   );
	geom->m_Normals [6] = glm::vec3( 0, 1 ,0   );
	geom->m_Normals [7] = glm::vec3( 0, 1 ,0   );
	geom->m_Normals [8] = glm::vec3( 1, 0 ,0   );
	geom->m_Normals [9] = glm::vec3( 1, 0 ,0   );
	geom->m_Normals [10] = glm::vec3(1, 0 ,0   );
	geom->m_Normals [11] = glm::vec3(1, 0 ,0   );
	geom->m_Normals [12] = glm::vec3(0, -0, 1  );
	geom->m_Normals [13] = glm::vec3(0, -0, 1  );
	geom->m_Normals [14] = glm::vec3(0, -0, 1  );
	geom->m_Normals [15] = glm::vec3(0, -0, 1  );
	geom->m_Normals [16] = glm::vec3(1, -0, -0 );
	geom->m_Normals [17] = glm::vec3(1, -0, -0 );
	geom->m_Normals [18] = glm::vec3(1, -0, -0 );
	geom->m_Normals [19] = glm::vec3(1, -0, -0 );
	geom->m_Normals [20] = glm::vec3(0, 0 ,-1  );
	geom->m_Normals [21] = glm::vec3(0, 0 ,-1  );
	geom->m_Normals [22] = glm::vec3(0, 0 ,-1  );
	geom->m_Normals [23] = glm::vec3(0, 0 ,-1  );   
	geom->LoadToGpu();
    
	return geom;
}

cMesh3d* Plane()
{
	cMesh3d* geom = new cMesh3d();
	geom->m_Vertex.resize(4 );
	geom->m_Vertex[0] = glm::vec3( -1.0f, 1.0f, 0.0f);
	geom->m_Vertex[1] = glm::vec3(  1.0f, 1.0f, 0.0f );
	geom->m_Vertex[2] = glm::vec3(  1.0f, -1.f, 0.0f );
	geom->m_Vertex[3] = glm::vec3( -1.0f, -1.0f, 0.0f );	

	geom->Indices.resize( 6 );
	geom->Indices[0] = 0;
	geom->Indices[1] = 1;
	geom->Indices[2] = 2;
	geom->Indices[3] = 0;
	geom->Indices[4] = 2;
	geom->Indices[5] = 3;

	geom->m_TexCoord.resize(4);
	geom->m_TexCoord[0] = glm::vec2( 0.0f, 1.0f );
	geom->m_TexCoord[1] = glm::vec2( 1.0f, 1.0f );
	geom->m_TexCoord[2] = glm::vec2( 1.0f, 0.0f );
	geom->m_TexCoord[3] = glm::vec2( 0.0f, 0.0f );

	geom->m_Normals.resize(4);
	geom->m_Normals [0] = glm::vec3( 0.0f, 0.0f, 1.0f );
	geom->m_Normals [1] = glm::vec3( 0.0f, 0.0f, 1.0f );
	geom->m_Normals [2] = glm::vec3( 0.0f, 0.0f, 1.0f );
	geom->m_Normals [3] = glm::vec3( 0.0f, 0.0f, 1.0f );
	geom->LoadToGpu();
	return geom;

}				  

cMesh3d* Sphere()
{
	cMesh3d* geom = new cMesh3d();
	geom->m_Vertex.resize( 162 );
	geom->m_Vertex[0] = glm::vec3(  0.850651f, 0.525731f, 0.000000f );
    geom->m_Vertex[1] = glm::vec3( -0.850651f, 0.525731f, 0.000000f  );
    geom->m_Vertex[2] = glm::vec3( -0.850651f, -0.525731f, 0.000000f );
    geom->m_Vertex[3] = glm::vec3( 0.850651f, -0.525731f, 0.000000f  );
    geom->m_Vertex[4] = glm::vec3( 0.525731f, 0.000000f, 0.850651f   );
    geom->m_Vertex[5] = glm::vec3( 0.525731f, 0.000000f, -0.850651f  );
    geom->m_Vertex[6] = glm::vec3( -0.525731f, 0.000000f, -0.850651f );
    geom->m_Vertex[7] = glm::vec3( -0.525731f, 0.000000f, 0.850651f  );
    geom->m_Vertex[8] = glm::vec3( 0.000000f, 0.850651f, 0.525731f   );
    geom->m_Vertex[9] = glm::vec3( 0.000000f, -0.850651f, 0.525731f  );
    geom->m_Vertex[10] = glm::vec3( 0.000000f, -0.850651f, -0.525731f );
    geom->m_Vertex[11] = glm::vec3( 0.000000f, 0.850651f, -0.525731f  );
    geom->m_Vertex[12] = glm::vec3( 0.309017f, 0.500000f, 0.809017f	);
    geom->m_Vertex[13] = glm::vec3( -0.309017f, 0.500000f, 0.809017f	);
    geom->m_Vertex[14] = glm::vec3( 0.000000f, 0.000000f, 1.000000f	);
    geom->m_Vertex[15] = glm::vec3( -0.309017f, -0.500000f, 0.809017f );
    geom->m_Vertex[16] = glm::vec3( 0.309017f, -0.500000f, 0.809017f	);
    geom->m_Vertex[17] = glm::vec3( 0.000000f, 0.000000f, -1.000000f  );
    geom->m_Vertex[18] = glm::vec3( -0.309017f, 0.500000f, -0.809017f );
    geom->m_Vertex[19] = glm::vec3( 0.309017f, 0.500000f, -0.809017f	);
    geom->m_Vertex[20] = glm::vec3( 0.309017f, -0.500000f, -0.809017f );
    geom->m_Vertex[21] = glm::vec3( -0.309017f, -0.500000f, -0.809017f);
    geom->m_Vertex[22] = glm::vec3( 0.809017f, 0.309017f, 0.500000f	);
    geom->m_Vertex[23] = glm::vec3( 0.809017f, -0.309017f, 0.500000f	);
    geom->m_Vertex[24] = glm::vec3( 1.000000f, 0.000000f, 0.000000f	);
    geom->m_Vertex[25] = glm::vec3( 0.809017f, -0.309017f, -0.500000f	);
    geom->m_Vertex[26] = glm::vec3( 0.809017f, 0.309017f, -0.500000f	);
    geom->m_Vertex[27] = glm::vec3( -0.809017f, -0.309017f, 0.500000f	);
    geom->m_Vertex[28] = glm::vec3( -0.809017f, 0.309017f, 0.500000f	);
    geom->m_Vertex[29] = glm::vec3( -1.000000f, 0.000000f, 0.000000f	);
    geom->m_Vertex[30] = glm::vec3( -0.809017f, 0.309017f, -0.500000f	);
    geom->m_Vertex[31] = glm::vec3( -0.809017f, -0.309017f, -0.500000f);
    geom->m_Vertex[32] = glm::vec3( 0.500000f, 0.809017f, 0.309017f	);
    geom->m_Vertex[33] = glm::vec3( 0.500000f, 0.809017f, -0.309017f	);
    geom->m_Vertex[34] = glm::vec3( 0.000000f, 1.000000f, 0.000000f	);
    geom->m_Vertex[35] = glm::vec3( -0.500000f, 0.809017f, -0.309017f	);
    geom->m_Vertex[36] = glm::vec3( -0.500000f, 0.809017f, 0.309017f	);
    geom->m_Vertex[37] = glm::vec3( 0.000000f, -1.000000f, 0.000000f	);
    geom->m_Vertex[38] = glm::vec3( 0.500000f, -0.809017f, -0.309017f	);
    geom->m_Vertex[39] = glm::vec3( 0.500000f, -0.809017f, 0.309017f	);
    geom->m_Vertex[40] = glm::vec3( -0.500000f, -0.809017f, 0.309017f	);
    geom->m_Vertex[41] = glm::vec3( -0.500000f, -0.809017f, -0.309017f);
    geom->m_Vertex[42] = glm::vec3( 0.433889f, 0.259892f, 0.862669f	);
    geom->m_Vertex[43] = glm::vec3( 0.162460f, 0.262866f, 0.951057f	);
    geom->m_Vertex[44] = glm::vec3( 0.273267f, 0.000000f, 0.961938f	);
    geom->m_Vertex[45] = glm::vec3( 0.000000f, 0.525731f, 0.850651f	);
    geom->m_Vertex[46] = glm::vec3( -0.162460f, 0.262866f, 0.951057f	);
    geom->m_Vertex[47] = glm::vec3( -0.433889f, 0.259892f, 0.862669f	);
    geom->m_Vertex[48] = glm::vec3( -0.273267f, 0.000000f, 0.961938f	);
    geom->m_Vertex[49] = glm::vec3( 0.160622f, 0.702046f, 0.693780f	);
    geom->m_Vertex[50] = glm::vec3( -0.160622f, 0.702046f, 0.693780f	);
    geom->m_Vertex[51] = glm::vec3( 0.162460f, -0.262866f, 0.951057f	);
    geom->m_Vertex[52] = glm::vec3( 0.433889f, -0.259892f, 0.862669f	);
    geom->m_Vertex[53] = glm::vec3( -0.162460f, -0.262866f, 0.951057f	);
    geom->m_Vertex[54] = glm::vec3( 0.000000f, -0.525731f, 0.850651f	);
    geom->m_Vertex[55] = glm::vec3( -0.160622f, -0.702046f, 0.693780f );
    geom->m_Vertex[56] = glm::vec3( 0.160622f, -0.702046f, 0.693780f	);
    geom->m_Vertex[57] = glm::vec3( -0.433889f, -0.259892f, 0.862669f	);
    geom->m_Vertex[58] = glm::vec3( 0.273267f, 0.000000f, -0.961938f	);
    geom->m_Vertex[59] = glm::vec3( 0.162460f, 0.262866f, -0.951057f	);
    geom->m_Vertex[60] = glm::vec3( 0.433889f, 0.259892f, -0.862669f	);
    geom->m_Vertex[61] = glm::vec3( -0.162460f, 0.262866f, -0.951057f	);
    geom->m_Vertex[62] = glm::vec3( 0.000000f, 0.525731f, -0.850651f	);
    geom->m_Vertex[63] = glm::vec3( -0.160622f, 0.702046f, -0.693780f	);
    geom->m_Vertex[64] = glm::vec3( 0.160622f, 0.702046f, -0.693780f	);
    geom->m_Vertex[65] = glm::vec3( -0.273267f, 0.000000f, -0.961938f	);
    geom->m_Vertex[66] = glm::vec3( -0.433889f, 0.259892f, -0.862669f	);
    geom->m_Vertex[67] = glm::vec3( 0.433889f, -0.259892f, -0.862669f	);
    geom->m_Vertex[68] = glm::vec3( 0.162460f, -0.262866f, -0.951057f	);
    geom->m_Vertex[69] = glm::vec3( 0.000000f, -0.525731f, -0.850651f	);
    geom->m_Vertex[70] = glm::vec3( -0.162460f, -0.262866f, -0.951057f);
    geom->m_Vertex[71] = glm::vec3( -0.433889f, -0.259892f, -0.862669f);
    geom->m_Vertex[72] = glm::vec3( 0.160622f, -0.702046f, -0.693780f );
    geom->m_Vertex[73] = glm::vec3( -0.160622f, -0.702046f, -0.693780f);
    geom->m_Vertex[74] = glm::vec3( 0.862669f, 0.433889f, 0.259892f	);
    geom->m_Vertex[75] = glm::vec3( 0.951057f, 0.162460f, 0.262866f	);
    geom->m_Vertex[76] = glm::vec3( 0.961938f, 0.273267f, 0.000000f	);
    geom->m_Vertex[77] = glm::vec3( 0.850651f, 0.000000f, 0.525731f	);
    geom->m_Vertex[78] = glm::vec3( 0.951057f, -0.162460f, 0.262866f	);
    geom->m_Vertex[79] = glm::vec3( 0.862669f, -0.433889f, 0.259892f	);
    geom->m_Vertex[80] = glm::vec3( 0.961938f, -0.273267f, 0.000000f	);
    geom->m_Vertex[81] = glm::vec3( 0.693780f, 0.160622f, 0.702046f	);
    geom->m_Vertex[82] = glm::vec3( 0.693780f, -0.160622f, 0.702046f	);
    geom->m_Vertex[83] = glm::vec3( 0.951057f, 0.162460f, -0.262866f	);
    geom->m_Vertex[84] = glm::vec3( 0.862669f, 0.433889f, -0.259892f	);
    geom->m_Vertex[85] = glm::vec3( 0.951057f, -0.162460f, -0.262866f	);
    geom->m_Vertex[86] = glm::vec3( 0.850651f, 0.000000f, -0.525731f	);
    geom->m_Vertex[87] = glm::vec3( 0.693780f, -0.160622f, -0.702046f	);
    geom->m_Vertex[88] = glm::vec3( 0.693780f, 0.160622f, -0.702046f	);
    geom->m_Vertex[89] = glm::vec3( 0.862669f, -0.433889f, -0.259892f	);
    geom->m_Vertex[90] = glm::vec3( -0.862669f, -0.433889f, 0.259892f	);
    geom->m_Vertex[91] = glm::vec3( -0.951057f, -0.162460f, 0.262866f	);
    geom->m_Vertex[92] = glm::vec3( -0.961938f, -0.273267f, 0.000000f	);
    geom->m_Vertex[93] = glm::vec3( -0.850651f, 0.000000f, 0.525731f	);
    geom->m_Vertex[94] = glm::vec3( -0.951057f, 0.162460f, 0.262866f	);
    geom->m_Vertex[95] = glm::vec3( -0.862669f, 0.433889f, 0.259892f	);
    geom->m_Vertex[96] = glm::vec3( -0.961938f, 0.273267f, 0.000000f	);
    geom->m_Vertex[97] = glm::vec3( -0.693780f, -0.160622f, 0.702046f	);
    geom->m_Vertex[98] = glm::vec3( -0.693780f, 0.160622f, 0.702046f	);
    geom->m_Vertex[99] = glm::vec3( -0.951057f, -0.162460f, -0.262866f);
    geom->m_Vertex[100] = glm::vec3( -0.862669f, -0.433889f, -0.259892f);
    geom->m_Vertex[101] = glm::vec3( -0.951057f, 0.162460f, -0.262866f );
    geom->m_Vertex[102] = glm::vec3( -0.850651f, 0.000000f, -0.525731f );
    geom->m_Vertex[103] = glm::vec3( -0.693780f, 0.160622f, -0.702046f );
    geom->m_Vertex[104] = glm::vec3( -0.693780f, -0.160622f, -0.702046f);
    geom->m_Vertex[105] = glm::vec3( -0.862669f, 0.433889f, -0.259892f );
    geom->m_Vertex[106] = glm::vec3( 0.259892f, 0.862669f, 0.433889f	);
    geom->m_Vertex[107] = glm::vec3( 0.262866f, 0.951057f, 0.162460f	);
    geom->m_Vertex[108] = glm::vec3( 0.000000f, 0.961938f, 0.273267f	);
    geom->m_Vertex[109] = glm::vec3( 0.525731f, 0.850651f, 0.000000f	);
    geom->m_Vertex[110] = glm::vec3( 0.262866f, 0.951057f, -0.162460f	);
    geom->m_Vertex[111] = glm::vec3( 0.259892f, 0.862669f, -0.433889f	);
    geom->m_Vertex[112] = glm::vec3( 0.000000f, 0.961938f, -0.273267f	);
    geom->m_Vertex[113] = glm::vec3( 0.702046f, 0.693780f, 0.160622f	);
    geom->m_Vertex[114] = glm::vec3( 0.702046f, 0.693780f, -0.160622f	);
    geom->m_Vertex[115] = glm::vec3( -0.262866f, 0.951057f, 0.162460f	);
    geom->m_Vertex[116] = glm::vec3( -0.259892f, 0.862669f, 0.433889f	);
    geom->m_Vertex[117] = glm::vec3( -0.262866f, 0.951057f, -0.162460f	);
    geom->m_Vertex[118] = glm::vec3( -0.525731f, 0.850651f, 0.000000f	);
    geom->m_Vertex[119] = glm::vec3( -0.702046f, 0.693780f, -0.160622f	);
    geom->m_Vertex[120] = glm::vec3( -0.702046f, 0.693780f, 0.160622f	);
    geom->m_Vertex[121] = glm::vec3( -0.259892f, 0.862669f, -0.433889f	);
    geom->m_Vertex[122] = glm::vec3( 0.000000f, -0.961938f, 0.273267f	);
    geom->m_Vertex[123] = glm::vec3( 0.262866f, -0.951057f, 0.162460f	);
    geom->m_Vertex[124] = glm::vec3( 0.259892f, -0.862669f, 0.433889f	);
    geom->m_Vertex[125] = glm::vec3( 0.262866f, -0.951057f, -0.162460f	);
    geom->m_Vertex[126] = glm::vec3( 0.525731f, -0.850651f, 0.000000f	);
    geom->m_Vertex[127] = glm::vec3( 0.702046f, -0.693780f, -0.160622f	);
    geom->m_Vertex[128] = glm::vec3( 0.702046f, -0.693780f, 0.160622f	);
    geom->m_Vertex[129] = glm::vec3( 0.000000f, -0.961938f, -0.273267f	);	
    geom->m_Vertex[130] = glm::vec3( 0.259892f, -0.862669f, -0.433889f	);
    geom->m_Vertex[131] = glm::vec3( -0.259892f, -0.862669f, 0.433889f	);
    geom->m_Vertex[132] = glm::vec3( -0.262866f, -0.951057f, 0.162460f	);
    geom->m_Vertex[133] = glm::vec3( -0.525731f, -0.850651f, 0.000000f	);
    geom->m_Vertex[134] = glm::vec3( -0.262866f, -0.951057f, -0.162460f);
    geom->m_Vertex[135] = glm::vec3( -0.259892f, -0.862669f, -0.433889f);
    geom->m_Vertex[136] = glm::vec3( -0.702046f, -0.693780f, 0.160622f	);
    geom->m_Vertex[137] = glm::vec3( -0.702046f, -0.693780f, -0.160622f);
    geom->m_Vertex[138] = glm::vec3( 0.425325f, 0.688191f, 0.587785f	);
    geom->m_Vertex[139] = glm::vec3( 0.587785f, 0.425325f, 0.688191f	);
    geom->m_Vertex[140] = glm::vec3( 0.688191f, 0.587785f, 0.425325f	);
    geom->m_Vertex[141] = glm::vec3( 0.425325f, 0.688191f, -0.587785f	);
    geom->m_Vertex[142] = glm::vec3( 0.688191f, 0.587785f, -0.425325f	);
    geom->m_Vertex[143] = glm::vec3( 0.587785f, 0.425325f, -0.688191f	);
    geom->m_Vertex[144] = glm::vec3( 0.587785f, -0.425325f, 0.688191f	);
    geom->m_Vertex[145] = glm::vec3( 0.425325f, -0.688191f, 0.587785f	);
    geom->m_Vertex[146] = glm::vec3( 0.688191f, -0.587785f, 0.425325f	);
    geom->m_Vertex[147] = glm::vec3( 0.587785f, -0.425325f, -0.688191f	);
    geom->m_Vertex[148] = glm::vec3( 0.688191f, -0.587785f, -0.425325f	);
    geom->m_Vertex[149] = glm::vec3( 0.425325f, -0.688191f, -0.587785f	);
    geom->m_Vertex[150] = glm::vec3( -0.587785f, 0.425325f, 0.688191f	);
    geom->m_Vertex[151] = glm::vec3( -0.425325f, 0.688191f, 0.587785f	);
    geom->m_Vertex[152] = glm::vec3( -0.688191f, 0.587785f, 0.425325f	);
    geom->m_Vertex[153] = glm::vec3( -0.587785f, 0.425325f, -0.688191f	);
    geom->m_Vertex[154] = glm::vec3( -0.688191f, 0.587785f, -0.425325f	);
    geom->m_Vertex[155] = glm::vec3( -0.425325f, 0.688191f, -0.587785f	);
    geom->m_Vertex[156] = glm::vec3( -0.587785f, -0.425325f, 0.688191f	);
    geom->m_Vertex[157] = glm::vec3( -0.688191f, -0.587785f, 0.425325f	);
    geom->m_Vertex[158] = glm::vec3( -0.425325f, -0.688191f, 0.587785f	);
    geom->m_Vertex[159] = glm::vec3( -0.587785f, -0.425325f, -0.688191f);
    geom->m_Vertex[160] = glm::vec3( -0.425325f, -0.688191f, -0.587785f);
    geom->m_Vertex[161] = glm::vec3( -0.688191f, -0.587785f, -0.425325f);

	geom->m_Normals.resize( 162 );
	geom->m_Normals[0] = glm::vec3(  0.850651f, 0.525731f, 0.000000f );
    geom->m_Normals[1] = glm::vec3( -0.850651f, 0.525731f, 0.000000f  );
    geom->m_Normals[2] = glm::vec3( -0.850651f, -0.525731f, 0.000000f );
    geom->m_Normals[3] = glm::vec3( 0.850651f, -0.525731f, 0.000000f  );
    geom->m_Normals[4] = glm::vec3( 0.525731f, 0.000000f, 0.850651f   );
    geom->m_Normals[5] = glm::vec3( 0.525731f, 0.000000f, -0.850651f  );
    geom->m_Normals[6] = glm::vec3( -0.525731f, 0.000000f, -0.850651f );
    geom->m_Normals[7] = glm::vec3( -0.525731f, 0.000000f, 0.850651f  );
    geom->m_Normals[8] = glm::vec3( 0.000000f, 0.850651f, 0.525731f   );
    geom->m_Normals[9] = glm::vec3( 0.000000f, -0.850651f, 0.525731f  );
    geom->m_Normals[10] = glm::vec3( 0.000000f, -0.850651f, -0.525731f );
    geom->m_Normals[11] = glm::vec3( 0.000000f, 0.850651f, -0.525731f  );
    geom->m_Normals[12] = glm::vec3( 0.309017f, 0.500000f, 0.809017f	);
    geom->m_Normals[13] = glm::vec3( -0.309017f, 0.500000f, 0.809017f	);
    geom->m_Normals[14] = glm::vec3( 0.000000f, 0.000000f, 1.000000f	);
    geom->m_Normals[15] = glm::vec3( -0.309017f, -0.500000f, 0.809017f );
    geom->m_Normals[16] = glm::vec3( 0.309017f, -0.500000f, 0.809017f	);
    geom->m_Normals[17] = glm::vec3( 0.000000f, 0.000000f, -1.000000f  );
    geom->m_Normals[18] = glm::vec3( -0.309017f, 0.500000f, -0.809017f );
    geom->m_Normals[19] = glm::vec3( 0.309017f, 0.500000f, -0.809017f	);
    geom->m_Normals[20] = glm::vec3( 0.309017f, -0.500000f, -0.809017f );
    geom->m_Normals[21] = glm::vec3( -0.309017f, -0.500000f, -0.809017f);
    geom->m_Normals[22] = glm::vec3( 0.809017f, 0.309017f, 0.500000f	);
    geom->m_Normals[23] = glm::vec3( 0.809017f, -0.309017f, 0.500000f	);
    geom->m_Normals[24] = glm::vec3( 1.000000f, 0.000000f, 0.000000f	);
    geom->m_Normals[25] = glm::vec3( 0.809017f, -0.309017f, -0.500000f	);
    geom->m_Normals[26] = glm::vec3( 0.809017f, 0.309017f, -0.500000f	);
    geom->m_Normals[27] = glm::vec3( -0.809017f, -0.309017f, 0.500000f	);
    geom->m_Normals[28] = glm::vec3( -0.809017f, 0.309017f, 0.500000f	);
    geom->m_Normals[29] = glm::vec3( -1.000000f, 0.000000f, 0.000000f	);
    geom->m_Normals[30] = glm::vec3( -0.809017f, 0.309017f, -0.500000f	);
    geom->m_Normals[31] = glm::vec3( -0.809017f, -0.309017f, -0.500000f);
    geom->m_Normals[32] = glm::vec3( 0.500000f, 0.809017f, 0.309017f	);
    geom->m_Normals[33] = glm::vec3( 0.500000f, 0.809017f, -0.309017f	);
    geom->m_Normals[34] = glm::vec3( 0.000000f, 1.000000f, 0.000000f	);
    geom->m_Normals[35] = glm::vec3( -0.500000f, 0.809017f, -0.309017f	);
    geom->m_Normals[36] = glm::vec3( -0.500000f, 0.809017f, 0.309017f	);
    geom->m_Normals[37] = glm::vec3( 0.000000f, -1.000000f, 0.000000f	);
    geom->m_Normals[38] = glm::vec3( 0.500000f, -0.809017f, -0.309017f	);
    geom->m_Normals[39] = glm::vec3( 0.500000f, -0.809017f, 0.309017f	);
    geom->m_Normals[40] = glm::vec3( -0.500000f, -0.809017f, 0.309017f	);
    geom->m_Normals[41] = glm::vec3( -0.500000f, -0.809017f, -0.309017f);
    geom->m_Normals[42] = glm::vec3( 0.433889f, 0.259892f, 0.862669f	);
    geom->m_Normals[43] = glm::vec3( 0.162460f, 0.262866f, 0.951057f	);
    geom->m_Normals[44] = glm::vec3( 0.273267f, 0.000000f, 0.961938f	);
    geom->m_Normals[45] = glm::vec3( 0.000000f, 0.525731f, 0.850651f	);
    geom->m_Normals[46] = glm::vec3( -0.162460f, 0.262866f, 0.951057f	);
    geom->m_Normals[47] = glm::vec3( -0.433889f, 0.259892f, 0.862669f	);
    geom->m_Normals[48] = glm::vec3( -0.273267f, 0.000000f, 0.961938f	);
    geom->m_Normals[49] = glm::vec3( 0.160622f, 0.702046f, 0.693780f	);
    geom->m_Normals[50] = glm::vec3( -0.160622f, 0.702046f, 0.693780f	);
    geom->m_Normals[51] = glm::vec3( 0.162460f, -0.262866f, 0.951057f	);
    geom->m_Normals[52] = glm::vec3( 0.433889f, -0.259892f, 0.862669f	);
    geom->m_Normals[53] = glm::vec3( -0.162460f, -0.262866f, 0.951057f	);
    geom->m_Normals[54] = glm::vec3( 0.000000f, -0.525731f, 0.850651f	);
    geom->m_Normals[55] = glm::vec3( -0.160622f, -0.702046f, 0.693780f );
    geom->m_Normals[56] = glm::vec3( 0.160622f, -0.702046f, 0.693780f	);
    geom->m_Normals[57] = glm::vec3( -0.433889f, -0.259892f, 0.862669f	);
    geom->m_Normals[58] = glm::vec3( 0.273267f, 0.000000f, -0.961938f	);
    geom->m_Normals[59] = glm::vec3( 0.162460f, 0.262866f, -0.951057f	);
    geom->m_Normals[60] = glm::vec3( 0.433889f, 0.259892f, -0.862669f	);
    geom->m_Normals[61] = glm::vec3( -0.162460f, 0.262866f, -0.951057f	);
    geom->m_Normals[62] = glm::vec3( 0.000000f, 0.525731f, -0.850651f	);
    geom->m_Normals[63] = glm::vec3( -0.160622f, 0.702046f, -0.693780f	);
    geom->m_Normals[64] = glm::vec3( 0.160622f, 0.702046f, -0.693780f	);
    geom->m_Normals[65] = glm::vec3( -0.273267f, 0.000000f, -0.961938f	);
    geom->m_Normals[66] = glm::vec3( -0.433889f, 0.259892f, -0.862669f	);
    geom->m_Normals[67] = glm::vec3( 0.433889f, -0.259892f, -0.862669f	);
    geom->m_Normals[68] = glm::vec3( 0.162460f, -0.262866f, -0.951057f	);
    geom->m_Normals[69] = glm::vec3( 0.000000f, -0.525731f, -0.850651f	);
    geom->m_Normals[70] = glm::vec3( -0.162460f, -0.262866f, -0.951057f);
    geom->m_Normals[71] = glm::vec3( -0.433889f, -0.259892f, -0.862669f);
    geom->m_Normals[72] = glm::vec3( 0.160622f, -0.702046f, -0.693780f );
    geom->m_Normals[73] = glm::vec3( -0.160622f, -0.702046f, -0.693780f);
    geom->m_Normals[74] = glm::vec3( 0.862669f, 0.433889f, 0.259892f	);
    geom->m_Normals[75] = glm::vec3( 0.951057f, 0.162460f, 0.262866f	);
    geom->m_Normals[76] = glm::vec3( 0.961938f, 0.273267f, 0.000000f	);
    geom->m_Normals[77] = glm::vec3( 0.850651f, 0.000000f, 0.525731f	);
    geom->m_Normals[78] = glm::vec3( 0.951057f, -0.162460f, 0.262866f	);
    geom->m_Normals[79] = glm::vec3( 0.862669f, -0.433889f, 0.259892f	);
    geom->m_Normals[80] = glm::vec3( 0.961938f, -0.273267f, 0.000000f	);
    geom->m_Normals[81] = glm::vec3( 0.693780f, 0.160622f, 0.702046f	);
    geom->m_Normals[82] = glm::vec3( 0.693780f, -0.160622f, 0.702046f	);
    geom->m_Normals[83] = glm::vec3( 0.951057f, 0.162460f, -0.262866f	);
    geom->m_Normals[84] = glm::vec3( 0.862669f, 0.433889f, -0.259892f	);
    geom->m_Normals[85] = glm::vec3( 0.951057f, -0.162460f, -0.262866f	);
    geom->m_Normals[86] = glm::vec3( 0.850651f, 0.000000f, -0.525731f	);
    geom->m_Normals[87] = glm::vec3( 0.693780f, -0.160622f, -0.702046f	);
    geom->m_Normals[88] = glm::vec3( 0.693780f, 0.160622f, -0.702046f	);
    geom->m_Normals[89] = glm::vec3( 0.862669f, -0.433889f, -0.259892f	);
    geom->m_Normals[90] = glm::vec3( -0.862669f, -0.433889f, 0.259892f	);
    geom->m_Normals[91] = glm::vec3( -0.951057f, -0.162460f, 0.262866f	);
    geom->m_Normals[92] = glm::vec3( -0.961938f, -0.273267f, 0.000000f	);
    geom->m_Normals[93] = glm::vec3( -0.850651f, 0.000000f, 0.525731f	);
    geom->m_Normals[94] = glm::vec3( -0.951057f, 0.162460f, 0.262866f	);
    geom->m_Normals[95] = glm::vec3( -0.862669f, 0.433889f, 0.259892f	);
    geom->m_Normals[96] = glm::vec3( -0.961938f, 0.273267f, 0.000000f	);
    geom->m_Normals[97] = glm::vec3( -0.693780f, -0.160622f, 0.702046f	);
    geom->m_Normals[98] = glm::vec3( -0.693780f, 0.160622f, 0.702046f	);
    geom->m_Normals[99] = glm::vec3( -0.951057f, -0.162460f, -0.262866f);
    geom->m_Normals[100] = glm::vec3( -0.862669f, -0.433889f, -0.259892f);
    geom->m_Normals[101] = glm::vec3( -0.951057f, 0.162460f, -0.262866f );
    geom->m_Normals[102] = glm::vec3( -0.850651f, 0.000000f, -0.525731f );
    geom->m_Normals[103] = glm::vec3( -0.693780f, 0.160622f, -0.702046f );
    geom->m_Normals[104] = glm::vec3( -0.693780f, -0.160622f, -0.702046f);
    geom->m_Normals[105] = glm::vec3( -0.862669f, 0.433889f, -0.259892f );
    geom->m_Normals[106] = glm::vec3( 0.259892f, 0.862669f, 0.433889f	);
    geom->m_Normals[107] = glm::vec3( 0.262866f, 0.951057f, 0.162460f	);
    geom->m_Normals[108] = glm::vec3( 0.000000f, 0.961938f, 0.273267f	);
    geom->m_Normals[109] = glm::vec3( 0.525731f, 0.850651f, 0.000000f	);
    geom->m_Normals[110] = glm::vec3( 0.262866f, 0.951057f, -0.162460f	);
    geom->m_Normals[111] = glm::vec3( 0.259892f, 0.862669f, -0.433889f	);
    geom->m_Normals[112] = glm::vec3( 0.000000f, 0.961938f, -0.273267f	);
    geom->m_Normals[113] = glm::vec3( 0.702046f, 0.693780f, 0.160622f	);
    geom->m_Normals[114] = glm::vec3( 0.702046f, 0.693780f, -0.160622f	);
    geom->m_Normals[115] = glm::vec3( -0.262866f, 0.951057f, 0.162460f	);
    geom->m_Normals[116] = glm::vec3( -0.259892f, 0.862669f, 0.433889f	);
    geom->m_Normals[117] = glm::vec3( -0.262866f, 0.951057f, -0.162460f	);
    geom->m_Normals[118] = glm::vec3( -0.525731f, 0.850651f, 0.000000f	);
    geom->m_Normals[119] = glm::vec3( -0.702046f, 0.693780f, -0.160622f	);
    geom->m_Normals[120] = glm::vec3( -0.702046f, 0.693780f, 0.160622f	);
    geom->m_Normals[121] = glm::vec3( -0.259892f, 0.862669f, -0.433889f	);
    geom->m_Normals[122] = glm::vec3( 0.000000f, -0.961938f, 0.273267f	);
    geom->m_Normals[123] = glm::vec3( 0.262866f, -0.951057f, 0.162460f	);
    geom->m_Normals[124] = glm::vec3( 0.259892f, -0.862669f, 0.433889f	);
    geom->m_Normals[125] = glm::vec3( 0.262866f, -0.951057f, -0.162460f	);
    geom->m_Normals[126] = glm::vec3( 0.525731f, -0.850651f, 0.000000f	);
    geom->m_Normals[127] = glm::vec3( 0.702046f, -0.693780f, -0.160622f	);
    geom->m_Normals[128] = glm::vec3( 0.702046f, -0.693780f, 0.160622f	);
    geom->m_Normals[129] = glm::vec3( 0.000000f, -0.961938f, -0.273267f	);	
    geom->m_Normals[130] = glm::vec3( 0.259892f, -0.862669f, -0.433889f	);
    geom->m_Normals[131] = glm::vec3( -0.259892f, -0.862669f, 0.433889f	);
    geom->m_Normals[132] = glm::vec3( -0.262866f, -0.951057f, 0.162460f	);
    geom->m_Normals[133] = glm::vec3( -0.525731f, -0.850651f, 0.000000f	);
    geom->m_Normals[134] = glm::vec3( -0.262866f, -0.951057f, -0.162460f);
    geom->m_Normals[135] = glm::vec3( -0.259892f, -0.862669f, -0.433889f);
    geom->m_Normals[136] = glm::vec3( -0.702046f, -0.693780f, 0.160622f	);
    geom->m_Normals[137] = glm::vec3( -0.702046f, -0.693780f, -0.160622f);
    geom->m_Normals[138] = glm::vec3( 0.425325f, 0.688191f, 0.587785f	);
    geom->m_Normals[139] = glm::vec3( 0.587785f, 0.425325f, 0.688191f	);
    geom->m_Normals[140] = glm::vec3( 0.688191f, 0.587785f, 0.425325f	);
    geom->m_Normals[141] = glm::vec3( 0.425325f, 0.688191f, -0.587785f	);
    geom->m_Normals[142] = glm::vec3( 0.688191f, 0.587785f, -0.425325f	);
    geom->m_Normals[143] = glm::vec3( 0.587785f, 0.425325f, -0.688191f	);
    geom->m_Normals[144] = glm::vec3( 0.587785f, -0.425325f, 0.688191f	);
    geom->m_Normals[145] = glm::vec3( 0.425325f, -0.688191f, 0.587785f	);
    geom->m_Normals[146] = glm::vec3( 0.688191f, -0.587785f, 0.425325f	);
    geom->m_Normals[147] = glm::vec3( 0.587785f, -0.425325f, -0.688191f	);
    geom->m_Normals[148] = glm::vec3( 0.688191f, -0.587785f, -0.425325f	);
    geom->m_Normals[149] = glm::vec3( 0.425325f, -0.688191f, -0.587785f	);
    geom->m_Normals[150] = glm::vec3( -0.587785f, 0.425325f, 0.688191f	);
    geom->m_Normals[151] = glm::vec3( -0.425325f, 0.688191f, 0.587785f	);
    geom->m_Normals[152] = glm::vec3( -0.688191f, 0.587785f, 0.425325f	);
    geom->m_Normals[153] = glm::vec3( -0.587785f, 0.425325f, -0.688191f	);
    geom->m_Normals[154] = glm::vec3( -0.688191f, 0.587785f, -0.425325f	);
    geom->m_Normals[155] = glm::vec3( -0.425325f, 0.688191f, -0.587785f	);
    geom->m_Normals[156] = glm::vec3( -0.587785f, -0.425325f, 0.688191f	);
    geom->m_Normals[157] = glm::vec3( -0.688191f, -0.587785f, 0.425325f	);
    geom->m_Normals[158] = glm::vec3( -0.425325f, -0.688191f, 0.587785f	);
    geom->m_Normals[159] = glm::vec3( -0.587785f, -0.425325f, -0.688191f);
    geom->m_Normals[160] = glm::vec3( -0.425325f, -0.688191f, -0.587785f);
    geom->m_Normals[161] = glm::vec3( -0.688191f, -0.587785f, -0.425325f);

	std::vector< GLuint> a;
#pragma region Indices
	// INDEXY WIERZCHOLKOW
	GLuint ind[] = { 4, 42, 44,
    44, 42, 43,    44, 43, 14,
    42, 12, 43,    14, 43, 46,
    46, 43, 45,    46, 45, 13,
    43, 12, 45,    14, 46, 48,
    48, 46, 47,    48, 47, 7,
    46, 13, 47,    12, 49, 45,
    45, 49, 50,    45, 50, 13,
    49, 8, 50,	   4, 44, 52,
    52, 44, 51,    52, 51, 16,
    44, 14, 51,    16, 51, 54,
    54, 51, 53,    54, 53, 15,
    51, 14, 53,    16, 54, 56,
    56, 54, 55,    56, 55, 9,
    54, 15, 55,    14, 48, 53,
    53, 48, 57,    53, 57, 15,
    48, 7, 57,     5, 58, 60,
    60, 58, 59,    60, 59, 19,
    58, 17, 59,    19, 59, 62,
    62, 59, 61,    62, 61, 18,
    59, 17, 61,    19, 62, 64,
    64, 62, 63,    64, 63, 11,
    62, 18, 63,    17, 65, 61,
    61, 65, 66,    61, 66, 18,
    65, 6 , 66,    5, 67, 58,
    58, 67, 68,    58, 68, 17,
    67, 20, 68,    17, 68, 70,
    70, 68, 69,    70, 69, 21,
    68, 20, 69,    17, 70, 65,
    65, 70, 71,    65, 71, 6,
    70, 21, 71,    20, 72, 69,
    69, 72, 73,    69, 73, 21,
    72, 10, 73,    0, 74, 76,
    76, 74, 75,    76, 75, 24,
    74, 22, 75,    24, 75, 78,
    78, 75, 77,    78, 77, 23,
    75, 22, 77,    24, 78, 80,
    80, 78, 79,    80, 79, 3,
    78, 23, 79,    22, 81, 77,
    77, 81, 82,    77, 82, 23,
    81, 4 , 82,     0, 76, 84,
    84, 76, 83,    84, 83, 26,
    76, 24, 83,    26, 83, 86,
    86, 83, 85,    86, 85, 25,
    83, 24, 85,    26, 86, 88,
    88, 86, 87,    88, 87, 5,
    86, 25, 87,    24, 80, 85,
    85, 80, 89,    85, 89, 25,
    80, 3 , 89,    2, 90, 92,
    92, 90, 91,    92, 91, 29,
    90, 27, 91,    29, 91, 94,
    94, 91, 93,    94, 93, 28,
    91, 27, 93,    29, 94, 96,
    96, 94, 95,    96, 95, 1,
    94, 28, 95,    27, 97, 93,
    93, 97, 98,    93, 98, 28,
    97, 7, 98,     2, 92, 100,
    100, 92, 99,   100, 99, 31,
    92, 29, 99,    31, 99, 102,
    102, 99, 101,   102, 101, 30,
    99, 29, 101,    31, 102, 104,
    104, 102, 103,  104, 103, 6,
    102, 30, 103,   29, 96, 101,
    101, 96, 105,   101, 105, 30,
    96, 1, 105,		8, 106, 108,
    108, 106, 107,  108, 107, 34,
    106, 32, 107,   34, 107, 110,
    110, 107, 109,  110, 109, 33,
    107, 32, 109,   34, 110, 112,
    112, 110, 111,  112, 111, 11,
    110, 33, 111,   32, 113, 109,
    109, 113, 114,  109, 114, 33,
    113, 0, 114,    8, 108, 116,
    116, 108, 115,  116, 115, 36,
    108, 34, 115,   36, 115, 118,
    118, 115, 117,  118, 117, 35,
    115, 34, 117,   36, 118, 120,
    120, 118, 119,  120, 119, 1,
    118, 35, 119,   34, 112, 117,
    117, 112, 121,  117, 121, 35,
    112, 11, 121,   9, 122, 124,
    124, 122, 123,  124, 123, 39,
    122, 37, 123,   39, 123, 126,
    126, 123, 125,  126, 125, 38,
    123, 37, 125,   39, 126, 128,
    128, 126, 127,  128, 127, 3,
    126, 38, 127,   37, 129, 125,
    125, 129, 130,  125, 130, 38,
    129, 10, 130,   9, 131, 122,
    122, 131, 132,  122, 132, 37,
    131, 40, 132,   37, 132, 134,
    134, 132, 133,  134, 133, 41,
    132, 40, 133,   37, 134, 129,
    129, 134, 135,  129, 135, 10,
    134, 41, 135,
    40, 136, 133,   133, 136, 137,
    133, 137, 41,   136, 2, 137,
    8, 49, 106,		106, 49, 138,
    106, 138, 32,   49, 12, 138,
    32, 138, 140,   140, 138, 139,
    140, 139, 22,   138, 12, 139,
    32, 140, 113,   113, 140, 74,
    113, 74, 0,		140, 22, 74,
    12, 42, 139,    139, 42, 81,
    139, 81, 22,    42, 4, 81,
    11, 111, 64,    64, 111, 141,
    64, 141, 19,    111, 33, 141,
    19, 141, 143,   143, 141, 142,
    143, 142, 26,   141, 33, 142,
    19, 143, 60,    60, 143, 88,
    60, 88, 5,		143, 26, 88,
    33, 114, 142,   142, 114, 84,
    142, 84, 26,    114, 0, 84,
    4, 52, 82,		82, 52, 144,
    82, 144, 23,    52, 16, 144,
    23, 144, 146,   146, 144, 145,
    146, 145, 39,   144, 16, 145,
    23, 146, 79,    79, 146, 128,
    79, 128, 3,		146, 39, 128,
    16, 56, 145,    145, 56, 124,
    145, 124, 39,   56, 9, 124,
    5, 87, 67,		67, 87, 147,
    67, 147, 20,	87, 25, 147,
    20, 147, 149,	149, 147, 148,
    149, 148, 38,   147, 25, 148,
    20, 149, 72,    72, 149, 130,
    72, 130, 10,    149, 38, 130,
    25, 89, 148,    148, 89, 127,
    148, 127, 38,   89, 3, 127,
    7, 47, 98,		98, 47, 150,
    98, 150, 28,    47, 13, 150,
    28, 150, 152,   152, 150, 151,
    152, 151, 36,   150, 13, 151,
    28, 152, 95,    95, 152, 120,
    95, 120, 1,		152, 36, 120,
    13, 50, 151,    151, 50, 116,
    151, 116, 36,   50, 8, 116,
    6, 103, 66,		66, 103, 153,
    66, 153, 18,    103, 30, 153,
    18, 153, 155,   155, 153, 154,
    155, 154, 35,   153, 30, 154,
    18, 155, 63,    63, 155, 121,
    63, 121, 11,    155, 35, 121,
    30, 105, 154,   154, 105, 119,
    154, 119, 35,   105, 1, 119,
    7, 97, 57,		57, 97, 156,
    57, 156, 15,    97, 27, 156,
    15, 156, 158,   158, 156, 157,
    158, 157, 40,   156, 27, 157,
    15, 158, 55,    55, 158, 131,
    55, 131, 9,		158, 40, 131,
    27, 90, 157,	157, 90, 136,
    157, 136, 40,	90, 2, 136,
    6, 71, 104,		104, 71, 159,
    104, 159, 31,   71, 21, 159,
    31, 159, 161,   161, 159, 160,
    161, 160, 41,   159, 21, 160,
    31, 161, 100,   100, 161, 137,
    100, 137, 2,	161, 41, 137,    
	21, 73, 160,	160, 73, 135,
    160, 135, 41,	73, 10, 135 };
#pragma endregion
	geom->Indices.resize( sizeof( ind )/ sizeof( int ) );
	std::copy( ind, ind + sizeof(ind)/sizeof( int ), geom->Indices.begin() ); 
	geom->LoadToGpu();
	return geom;
}