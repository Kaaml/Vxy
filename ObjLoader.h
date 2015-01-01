#pragma once
#include "Include.hpp"
#include "Surface.hpp"
#include "VBOManager.hpp"

//#include <assimp.h>
#include <aiPostProcess.h>
#include <assimp.hpp>
#include <aiMesh.h>
#include <aiScene.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	bool operator==(const Vertex& other) const
	{
		return ((Position == other.Position) && (Normal == other.Normal) &&
			/*(Color == other.Color) &&*/ (TexCoord == other.TexCoord ));
	}
};

struct fVertex
{
	int Vertex;
	int Normal;
	int TexCoord;
	bool operator==( const fVertex& rhs ) 
	{
		if( Vertex == rhs.Vertex && Normal == rhs.Normal && TexCoord == rhs.TexCoord )
			return true;
		else return false;
	}
};




struct less
{
	bool operator()(const glm::ivec3& lhs, const glm::ivec3& rhs ) const
	{	// apply operator< to operands
		//return (bool)glm::lessThan( _Left, _Right ).x;
		return (lhs.x < rhs.x) || 
			(	( lhs.x == rhs.x) && ( ( lhs.y < rhs.y) || 
				(( lhs.y == rhs.y) && ( lhs.z < rhs.z) )));
	}
};
class ObjLoader
{
public:
	ObjLoader(void);
	static void Load( const std::string &FileName );
	static void LoadAssimp( const std::string &FileName );
	static std::vector< Surface*>& GetSurfaces();
	~ObjLoader(void);
private:
	std::vector< glm::vec3 > mVertex;
	std::vector< glm::vec3 > mNormals;
	std::vector< glm::vec2 > mTexcoords;
	std::vector< float > mGpuBuffer;
	std::vector< int > mGpuIndices;
	std::vector< glm::ivec3 > mFaces;
	std::map< glm::ivec3, int , less> mVertexMap;
	void GetFace( const std::string &line );	
	void GetFace_t( std::string &line );
	void Prepare( void );
	short WordsSize( char* startPtr, char* endPtr );
	bool GetDataFromFaceWord( char* vertexData, int* index, const char* buffEnd );
	char* GetNextWorld( char* startPtr, char* endPtr );
	bool mTriangulated;
	std::vector< Surface* > mSurfaces;

	bool cmp( std::pair< glm::ivec3, int > &lhs,  std::pair< glm::ivec3, int > &rhs ); 
};
