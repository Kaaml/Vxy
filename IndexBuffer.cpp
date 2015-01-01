#include "IndexBuffer.hpp"


IndexBuffer::IndexBuffer(void)
{
	mUsageType = UT_STATIC_DRAW;
	hIndexBuffer = 0;
	glGenBuffers( 1, &hIndexBuffer );
}

//IndexBuffer::IndexBuffer( const IndexSettings &Settings )
//{
//	glGenBuffers( 1, &hIndexBuffer );
//	mIndexSettings = Settings;
//}

void IndexBuffer::SetIndexData( const std::vector< int > &Data )
{
	mIndices = Data;
}

void IndexBuffer::SetIndexData( const int *Data, size_t Count )
{
	mIndices = std::vector< int > ( *Data,  Count );
}

//void IndexBuffer::SetIndexSettings( const IndexSettings &Settings )
//{
//	mIndexSettings = Settings;
//}

//void IndexBuffer::Init()
//{
//	if( !hIndexBuffer )
//	{
//		glGenBuffers( 1, &hIndexBuffer );
//	}
//}

void IndexBuffer::Prepare()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hIndexBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof( mIndices[0] ), &mIndices[0], mUsageType );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void IndexBuffer::Bind()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, hIndexBuffer );
}


IndexBuffer::~IndexBuffer(void)
{
	if( hIndexBuffer )
	{
		glDeleteBuffers(1, &hIndexBuffer );
		hIndexBuffer = 0;
	}
}		
