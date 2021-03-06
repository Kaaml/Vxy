#pragma once

#include "Include.hpp"
#include "VerticesEnums.hpp"
#include "IndexBuffer.hpp"
#include "VertexDeclaration.hpp"

struct VertexSettings
{
	PRIMITIVE_TYPE PrimitiveMode;
	USAGE_TYPE UsageType;
	IndexBuffer * IndicesBuffer;
	VertexDeclaration *Declaration;
	
	VertexSettings()
		:IndicesBuffer( nullptr ), Declaration( nullptr )
	{	
	};
	VertexSettings( PRIMITIVE_TYPE PT, USAGE_TYPE UT, IndexBuffer* Index, VertexDeclaration* vdesc)
		: PrimitiveMode( PT ), UsageType( UT ), IndicesBuffer( Index ), Declaration( vdesc )
	{
	};
};

class VertexBuffer
{
public:
	VertexBuffer(void);
	VertexBuffer( const VertexSettings& settings );
	void Render();
	// Przesyła dane wierzchołków do sterownika
	void SetVertexData( const std::vector < float > &Vertices );
	// dla innego typu danych etc
	void SetVertexData( float* Data, size_t size );
	void Prepare();
	void Bind();
	void UnBind();
	void Init();
	void Clean();

	const VertexSettings & GetVertexSettings() const {
		return mVertexSettings;
	};

	~VertexBuffer(void);
private:
	std::vector < float > mVertices;
	GLuint hVertexBuffer;
	GLuint hVertexArrayObject;
	VertexSettings mVertexSettings;

};

