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