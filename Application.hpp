#pragma once
#include "Include.hpp"
#include "Singleton.hpp"
#include "Uniform.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "cShaderManager.hpp"
#include "cProgramShader.hpp"
#include "ObjLoader.h"
#include "cMesh3d.hpp"
#include "Renderer.hpp"
#include "cModel.hpp"
#include "TextureManager.hpp"
#include "MaterialManager.hpp"
#include <memory>

class Application : public Singleton < Application >
{
public:
	void Init();
	void Run();
	void CleanUp();
	Application(void);
	Application( float Width, float Height );
	~Application(void);
private:
	float mWidth;
	float mHeight;
	bool mRun;

	double mTime;
	double DeltaTime;
	void InitUtilities();
	void Timer();

	glm::dvec2 mMousePosition;
	VertexBuffer* Vertex;
	IndexBuffer* Indices;
	VertexDeclaration vdec;
	std::vector< Surface* > Surfaces;
	GLuint hVAO;
	GLuint hVBO;
	GLuint hIBO;
	std::unique_ptr< Material> pMaterial;
	std::unique_ptr< cCamera > pCamera;

	GLFWwindow *mWindow;

};

