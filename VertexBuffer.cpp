#include "VertexBuffer.hpp"


VertexBuffer::VertexBuffer(void)
{
	//pVertices = nullptr;
	hVertexBuffer = NULL;
	mVertexSettings.PrimitiveMode = PT_UNKOWN;
	mVertexSettings.UsageType = UT_STATIC_DRAW;
}

VertexBuffer::VertexBuffer( const VertexSettings& settings )
{
	//pVertices = nullptr;
	hVertexBuffer = NULL;
	mVertexSettings = settings;
}

void VertexBuffer::Init()
{
	glGenBuffers( 1, &hVertexBuffer );
	glGenVertexArrays( 1, &hVertexArrayObject );
}

void VertexBuffer::SetVertexData( const std::vector< float > &Vertices )
{
	mVertices = Vertices;
}

void VertexBuffer::SetVertexData( float* data, size_t size )
{
	mVertices.resize( size );
	memcpy( &mVertices[0], data, size );
}
void VertexBuffer::Render()
{
	if( mVertexSettings.PrimitiveMode == PT_UNKOWN )		// jezeli nie ustawiony typ do renderowania wyjdz
		return;

	if( !mVertexSettings.IndicesBuffer )
	{
		glDrawArrays( mVertexSettings.PrimitiveMode, 0, mVertices.size() );
	}
	else
	{
		glDrawElements( mVertexSettings.PrimitiveMode, mVertexSettings.IndicesBuffer->GetIndexCount(), GL_UNSIGNED_INT, 0 );
	}
}

void VertexBuffer::Prepare()
{
	
	if( mVertexSettings.PrimitiveMode !=  PRIMITIVE_TYPE::PT_UNKOWN )
	{
		glBindVertexArray( hVertexArrayObject );
		glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer );
		glBufferData( GL_ARRAY_BUFFER, mVertices.size() * sizeof( &mVertices[0] ), mVertices.data(), mVertexSettings.UsageType );
		//std::cout << "BUfer data size: " << mVertices.size() * sizeof( &mVertices[0]) << std::endl;
		mVertexSettings.Declaration->Bind();

		if( mVertexSettings.IndicesBuffer )
			mVertexSettings.IndicesBuffer->Bind();
		glBindVertexArray( 0 );
	}else
		std::cerr << "EROR: VertexBufffer::Prepare() -> Primitiv UsageType is invalid\n";
}

void VertexBuffer::Bind()
{
	//glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer );
	glBindVertexArray( hVertexArrayObject );
	glBindBuffer( GL_ARRAY_BUFFER, hVertexBuffer );
	if( mVertexSettings.IndicesBuffer )
		mVertexSettings.IndicesBuffer->Bind();
	
}
void VertexBuffer::UnBind()
{

	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	if( mVertexSettings.IndicesBuffer )
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}
VertexBuffer::~VertexBuffer(void)
{
	if( hVertexBuffer )
	{
		glDeleteBuffers( 1, &hVertexBuffer );
		hVertexBuffer = NULL;
	}
	if ( hVertexArrayObject )
	{
		glDeleteVertexArrays( 1, &hVertexArrayObject );
		hVertexArrayObject = NULL;
	}

}


// Tworzenie VAO, VBO, IBO
// Przypisanie do VAO <- IBO i VBO
// Vao.SetVBO 
// Vao.set ibo
//	
// Rysowanie za pomoca VAO
	

// W VBO NIE PRZECHOWYWAC POINTERA DO IBO
// W VAO BEDA ROBIONE WSZYSTKIE OPERACJE NA VBO I IBO 