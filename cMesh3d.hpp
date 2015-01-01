#pragma once
#include "Include.hpp"

class cMesh3d
{
public:
	cMesh3d(void);
	cMesh3d( std::string FileName );
	~cMesh3d(void);
	bool LoadObjMesh( std::string FileName );
	void BindVertexArray();
	void UnbindVertexArray();
	int GetIndicesCout();

	friend cMesh3d* Cube();
	friend cMesh3d* Plane();
	friend cMesh3d* Sphere();
private:
	std::vector< glm::vec3 > m_Vertex;
	std::vector< glm::vec3 > m_Normals;
	std::vector< glm::vec2 > m_TexCoord;
	std::vector< GLuint > Indices;
	//OpenGL
	GLuint h_vao;
	// VAO
	GLuint h_vbo;
	// vertexy normal texcoord	
	GLuint h_ibo;
	// indexy
	void LoadToGpu();
};

