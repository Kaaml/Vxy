#pragma once
#include "Include.hpp"
#include "singleton.hpp"
#include "VertexBuffer.hpp"
#include "VertexDeclaration.hpp"

class VertexBufferManager : public Singleton < VertexBufferManager >
{
public:
	VertexBufferManager(void);
	virtual ~VertexBufferManager(void);
	VertexDeclaration* CreateVertexDeclaration( const std::string &Name, VertexPointer *Pointers, size_t Count );
	VertexBuffer* CreateVertexBuffer( const VertexSettings& Settings );
	IndexBuffer* CreateIndexBuffer();

	VertexDeclaration* GetVertexDeclaration( const std::string &Name );
private:
	void InitDefaultDeclarations();
	uint mVboCount;
	uint mIboCount;
	std::map< std::string, VertexDeclaration* > mVertexDeclarations;
	std::map< unsigned, VertexBuffer* > mVBOs;
	std::map< unsigned, IndexBuffer* > mIBOs;
							
};

