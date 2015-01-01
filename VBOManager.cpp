#include "VBOManager.hpp"

VertexBufferManager* VAOmo = new VertexBufferManager();
VertexBufferManager::VertexBufferManager(void)
{
	std::cerr << "Konstukto klasy VBOManager \n";
	mVboCount = 0;
	mIboCount = 0;
	InitDefaultDeclarations();
}

void VertexBufferManager::InitDefaultDeclarations()
{
	/*struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
	};*/
	VertexPointer Pointer[3] =	{
		VertexPointer( 0, 3, 8 * sizeof( float ), V_POSITION,	(void*) NULL ),							// wskaŸnik na pozycje
		VertexPointer( 1, 3, 8 * sizeof( float ), V_NORMAL,		(void*) (sizeof( float ) *3 ) ),		// wskaŸnik na normalna
		VertexPointer( 2, 2, 8 * sizeof( float ), V_TEXCOORD,	(void*) (sizeof( float ) *6 ) )			// wskaxnik na tex coordy
	};
	CreateVertexDeclaration( "Default", Pointer, 3 );
	
}

VertexDeclaration* VertexBufferManager::CreateVertexDeclaration( const std::string &name, VertexPointer *pointers, size_t count )
{
	VertexDeclaration *pDecl = new VertexDeclaration();
	pDecl->AddPointers( pointers, count );
	mVertexDeclarations[ name ] = pDecl;
	return pDecl;
}

VertexBuffer* VertexBufferManager::CreateVertexBuffer( const VertexSettings& Settings )
{
	VertexBuffer* pVertex = new VertexBuffer( Settings );
	pVertex->Init();
	mVBOs[ mVboCount++ ] = pVertex;
	return pVertex;
}

IndexBuffer* VertexBufferManager::CreateIndexBuffer()
{
	IndexBuffer* pIndex = new IndexBuffer();
	mIBOs[ mIboCount++ ] = pIndex;
	//pIndex->Init();
	return pIndex;
}

VertexDeclaration* VertexBufferManager::GetVertexDeclaration( const std::string &Name )
{
	if( mVertexDeclarations.find( Name ) == mVertexDeclarations.end() )
	{
		//wypluj blad
		std::cerr << "ERORO: Nie znaleziono deklaracji ( " << Name << " ) return default value" << std::endl;
		return mVertexDeclarations[ "Defualt" ];
	}
	else
	{
		return mVertexDeclarations[ Name ];
	}
}
VertexBufferManager::~VertexBufferManager(void)
{
	for( std::map< unsigned, VertexBuffer* >::iterator it = mVBOs.begin(); it != mVBOs.end(); ++it )
	{
		delete it->second;
	}
	for( std::map< unsigned, IndexBuffer* >::iterator it = mIBOs.begin(); it != mIBOs.end(); ++it )
	{
		delete it->second;
	}
	for( std::map< std::string, VertexDeclaration* >::iterator it = mVertexDeclarations.begin(); it != mVertexDeclarations.end(); ++it )
	{
		delete it->second;
	}



}
