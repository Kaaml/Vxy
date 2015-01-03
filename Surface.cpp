#include "Surface.hpp"


Surface::Surface(void)
{
	pVertex = nullptr;
	pMaterial = nullptr;
	
}


Surface::~Surface(void)
{
}


void Surface::Render()
{
	if( pVertex )
	{
		pVertex->Bind();
		pVertex->Render();
		pVertex->UnBind();		
	}else
	{
		std::cerr << "EROR: Rendering obiektu " << /* TUTAJ WSTAWIC COS*/ " nie ustawionow wskaznika na dane\n";
		return;
	}
}

void Surface::SetVertexBuffer( VertexBuffer* Vertex )
{
	pVertex = Vertex;
}

void Surface::SetMaterial( Material* Material )
{
	pMaterial = Material;
}

Material* Surface::GetMaterialPtr()
{
	return pMaterial;
}
Material& Surface::GetMaterial()
{
	return *pMaterial;
}


Surface* PrefabShape::GenerateRectangle()
{
	std::vector< int> Indices;
	Indices.resize( 6 );
	Indices[0] = 0;
	Indices[1] = 1;
	Indices[2] = 2;
	Indices[3] = 0;
	Indices[4] = 2;
	Indices[5] = 3;
	std::vector< float > Vertices;
	Vertices.resize( 4 * 8 );		// 4 verteksy poo 8 wartosc( ozycja, normalna, texx)
	Vertices[0] =  -1.0f; Vertices[1] = 1.0f; Vertices[2] = 0.0f;
	Vertices[8] =   1.0f; Vertices[9] = 1.0f; Vertices[10] = 0.0f;
	Vertices[16] =  1.0f; Vertices[17] = -1.0f; Vertices[18] = 0.0f;
	Vertices[24] =  -1.0f; Vertices[25] = -1.0f; Vertices[26] = 0.0f;
	// normalnce
	Vertices[3] =  0.0f; Vertices[4] =  0.0f; Vertices[5] =  1.0f;
	Vertices[11] = 0.0f; Vertices[12] = 0.0f; Vertices[13] = 1.0f;
	Vertices[19] = 0.0f; Vertices[20] = 0.0f; Vertices[21] = 1.0f;
	Vertices[27] = 0.0f; Vertices[28] = 0.0f; Vertices[29] = 1.0f;

	
	
	Surface* s = new Surface();
	VertexBufferManager &VBOMan = VertexBufferManager::GetSingleton();
	IndexBuffer *pIndex = VBOMan.CreateIndexBuffer();
	pIndex->SetIndexData( Indices );
	pIndex->Prepare();
	VertexDeclaration *pDecl = VBOMan.GetVertexDeclaration( "Default" );
	VertexBuffer *pVertex = VBOMan.CreateVertexBuffer(
		VertexSettings( PT_TRIANGLE, UT_STATIC_DRAW, pIndex, pDecl ) );	
	pVertex->SetVertexData( Vertices );
	pVertex->Prepare();
	s->SetVertexBuffer( pVertex );

	return s;
}

Surface* PrefabShape::GeneratePlane( )
{
	
	ILuint image;
	ilGenImages( 1, &image );
	ilBindImage( image );
	//ilLoadImage( "Data/heightmap.png" );
	ilLoadImage( "Data/hmap10x10.tga" );
	ILenum Error = ilGetError();
	if( Error != IL_NO_ERROR )
	{
		return false;
		std::cerr << "ERROR: Wczytanie tekstury: " << "nie powiodlo sie, plik: " << "Data/hmap1.tga" << " nie zostal wczytany" << std::endl;
	}
	int width, height, depth;
	ILenum type, format;
	width = ilGetInteger( IL_IMAGE_WIDTH );
	height = ilGetInteger( IL_IMAGE_HEIGHT );
	depth = ilGetInteger( IL_IMAGE_DEPTH );
	type = ilGetInteger( IL_IMAGE_TYPE );		//unsigned int etc
	if( type != IL_LUMINANCE )
	{
		std::cerr << "INFO: Height map wrong type. Normal type: LUMINANCE\n";
	}
	format = ilGetInteger( IL_IMAGE_FORMAT );		// rgba, rgb, etc
	ILubyte *pixmap = ilGetData();
	/*for( int i = 0; i < 10; ++i )
	{
		for( int j = 0; j < 10; j ++)
		{
			std::cout << " " << (unsigned short)*(pixmap + i * 10 + j)/255.f;

		}
		std::cout << std::endl;
	}*/
	/*float hMap[]=
	{
		0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 0.1f, 0.1f, 0.1f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 0.1f, 0.2f, 0.2f, 0.1f, 0.1f, 0.1f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.1f, 0.2f, 0.3f, 0.3f, 0.1f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.1f, 0.4f, 0.4f, 0.4f, 0.2f, 0.f, 0.f, 0.f,
		0.f, 0.1f, 0.2f, 0.3f, 0.3f, 0.3f, 0.1f, 0.0f, 0.f, 0.f,
		0.f, 0.f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.0f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f, 0.1f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.f ,
		0.f, 0.f, 0.f, 0.f, 0.1f, 0.1f, 0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,

	};*/
	const int size = 10;
	const int sizex = width;
	const float Precision = 1.f;
	float startW = -size / 2.f + 0.5f;
	//std::vector< float > Vertices;
	std::vector< Vertex_S > Vertices2;
	//Vertices.resize( size*size*3 );
	std::vector< int > Index;
	Index.reserve( size*size + (size - 1)*(size - 1) );

	for( int i = 0; i < size; ++i )
	{
		for( int j = 0; j < size; ++j )
		{
			//std::cout << "( " << startW + j << " ; " << startW + i << ") ";
			//Vertices.push_back( startW + j );		// x
			//Vertices.push_back( (unsigned short )*(pixmap+(i * 10 + j))/-255.f *4.f   ); //y
			//Vertices.push_back( startW + i );		//z
			//for( size_t k = 0; k < 3; k++ )
			//{
			//	Vertices.push_back( 0.f ); // wyrzuc normalne, i texcoordy
			//}
			//// wyrzuæ teexcoord
			//Vertices.push_back( (float)i );
			//Vertices.push_back( (float)j );	
			Vertex_S v{ glm::vec3( (startW + j), (unsigned short)*(pixmap + (i * 10 + j)) / -255.f *4.f, (startW + i) ),
				glm::vec3( 0.f, 0.f, 0.f ),
				glm::vec2( (float)i, (float)j ) };
			Vertices2.emplace_back( v );				
		}
	}

	int i = 0;
	//Index[i++] = size-1; 
	Index.push_back( size - 1 );
	for( int row = 0; row < size - 1; row++ )
	{
		if( (row & 1) == 1 ) //dla nie parzystych wierszy rzêdów
		{
			for( int col = 0; col < size; col++ )
			{
				Index.push_back( col + row * size );
				//Index[i++] = col + row*size;
				Index.push_back( col + (row + 1)*size );
				//Index[i++] = col + (row + 1) *size;
			}

		} else				//dla parzystych
		{
			for( int col = size - 1; col >0; col-- )
			{
				Index.push_back( col + (row + 1)*size );
				//Index[i++] = col + (row + 1)*size;
				Index.push_back( col - 1 + row * size );
				//Index[i++] = col - 1 + row*size;
			}
		}//else

	}
	//Index[i++] = size*size - size;
	Index.push_back( size*size - size );

	//liczenie normalnych
	//for( int i = 0; i < Index.size(); i += 3 )
	//{
		// licz dla 1 trójkata
	//	Vertices2[i].vPosition;
	//}

	for( int i = 0; i < size -1; ++i )		//dla ka¿dego wiersza
	{
		for( int j = 0; j < size-1; ++j )	//dla ka¿dej kolumny
		{
		
			glm::vec3 p1, p2, p3, tmp, v1, v2;
			int v[4];
			v[0] = i*size + j; v[1] = i*size + j + 1;
			v[2] = (i + 1)*size + j; v[3] = (i + 1)*size + j + 1;

			// store the positions of first triangle into 3 usable vertices
			p1 = Vertices2[v[0]].vPosition;
			p2 = Vertices2[v[3]].vPosition;
			p3 = Vertices2[v[2]].vPosition;

			// boki
			v1 = p2 - p1;
			v2 = p3 - p1;
			// calculate normal			
			//tmp = glm::cross( v1, v2 );
			tmp = glm::cross( v2, v1 );
			Vertices2[v[0]].vNormal += tmp;
			Vertices2[v[3]].vNormal += tmp;
			Vertices2[v[2]].vNormal += tmp;

			p1 = Vertices2[v[1]].vPosition;
			p2 = Vertices2[v[3]].vPosition;
			p3 = Vertices2[v[0]].vPosition;

			// boki trojkatow
			v1 = p2 - p1;
			v2 = p3 - p1;
			// normal
			//tmp = glm::cross( v1, v2 );
			tmp = glm::cross( v2, v1 );

			Vertices2[v[1]].vNormal += tmp;
			Vertices2[v[3]].vNormal += tmp;
			Vertices2[v[0]].vNormal += tmp;

		}
	}
	//normalizacja normalnych
	for( auto &x : Vertices2 )
	{
		x.vNormal = glm::normalize( x.vNormal );
	}
	
	//tworzenie surface
	Surface* s = new Surface( );
	VertexBufferManager *VBOMan = VertexBufferManager::GetSingletonPtr();
	IndexBuffer *pIndex = VBOMan->CreateIndexBuffer( );
	pIndex->SetIndexData( Index );
	pIndex->Prepare( );
	VertexDeclaration *pDecl = VBOMan->GetVertexDeclaration( "Default" );
	VertexBuffer *pVertex = VBOMan->CreateVertexBuffer(
		VertexSettings( PT_TRIANGLE_STRIP, UT_STATIC_DRAW, pIndex, pDecl ) );
	//pVertex->SetVertexData( Vertices );
	pVertex->SetVertexData( (float*)Vertices2.data(), Vertices2.size() * sizeof( Vertex_S) );
	pVertex->Prepare( );
	s->SetVertexBuffer( pVertex );
	return s;
}