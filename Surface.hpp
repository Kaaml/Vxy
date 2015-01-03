#pragma once

#include "Include.hpp"
#include "VertexBuffer.hpp"
#include "Material.hpp"
#include "VBOManager.hpp"

struct Vertex_S
{
	glm::vec3 vPosition;
	glm::vec3 vNormal;
	glm::vec2 vTexCoord;
};


class Surface
{
public:
	Surface(void);

	void Render();
	void SetVertexBuffer( VertexBuffer* Vertex );
	void SetMaterial( Material* Material );

	Material* GetMaterialPtr();
	Material& GetMaterial();

	~Surface(void);

private:
	VertexBuffer *pVertex;
	Material* pMaterial;


};

class PrefabShape
{
public:
	PrefabShape(void );
	static Surface* GenerateRectangle();
	static Surface* GeneratePlane( );
	//static Surface* GenerateSphere();
};