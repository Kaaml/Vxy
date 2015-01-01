#pragma once

#include "Include.hpp"
#include "VerticesEnums.hpp"


class IndexBuffer
{
public:
	IndexBuffer(void);
	//IndexBuffer( const IndexSettings& Settings );
	void SetIndexData( const std::vector< int > &Data );
	void SetIndexData( const int *Data, size_t Count );
	void SetUsageType( USAGE_TYPE Type )
	{
		mUsageType = Type;
	}
	//void SetIndexSettings( IndexSettings Settings );
	//void SetIndexSettings( const IndexSettings &Settings );
	//void Init();
	void Prepare();
	void Bind();

	// Function return handle to OpenGL buffer : GLuint
	GLuint GetId() const {
		return hIndexBuffer;
	};
	int GetIndexCount() const {
		return mIndices.size();
	};
	uint GetElementSize() const {
		return sizeof( mIndices[0] );
	}
	// Function return const reference to index vector data : const std::vector< int > &
	const std::vector< int > & GetData() const {
		return mIndices;
	};
	USAGE_TYPE GetUsageType() const {
		return mUsageType;
	}
	// Function return const reference to index settings : const IndexSettings &
	/*const IndexSettings & GetIndexSettings() const {
		return mIndexSettings;
	};*/


	~IndexBuffer(void);
private:
	//void *pIndices;		//dane indeksow
	//IndexSettings mIndexSettings;
	USAGE_TYPE mUsageType;
	std::vector< int > mIndices;
	GLuint hIndexBuffer;
};

