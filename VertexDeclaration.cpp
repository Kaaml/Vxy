#include "VertexDeclaration.hpp"


VertexDeclaration::VertexDeclaration(void)
{
}

void VertexDeclaration::AddPointer( const VertexPointer& Element )
{
	mVertexPointers.push_back( Element );
}

void VertexDeclaration::AddPointers( VertexPointer * Elements, size_t Count )
{
	for( size_t i = 0; i < Count; ++i )
	{
		mVertexPointers.push_back( Elements[i] );
	}
}

void VertexDeclaration::Bind()
{
	for( std::vector< VertexPointer >::iterator it = mVertexPointers.begin(); it != mVertexPointers.end(); ++it )
	{
		glVertexAttribPointer( it->Index, it->Size, it->Type, it->Normalized, it->Stride, it->Pointer );
		glEnableVertexAttribArray( it->Index );
	}
}

VertexPointer* VertexDeclaration::GetVertexPointer( VertexUsage Usage )
{
	for( std::vector< VertexPointer >::iterator it = mVertexPointers.begin(); it != mVertexPointers.end(); ++it )
	{
		if( it->Usage == Usage )
			return &(*it);
	}
	return nullptr;
}

VertexPointer* VertexDeclaration::GetVertexPointer( size_t index )
{
	if( index < mVertexPointers.size() )
		return &mVertexPointers[ index ];
	else
		return nullptr;
}

VertexDeclaration::~VertexDeclaration(void)
{
}

