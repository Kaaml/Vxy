#pragma once

#include "Include.hpp"
#include "cShaderManager.hpp"
#include "cMesh3d.hpp"
#include "cCamera.hpp"
#include "Transform.hpp"


extern	cShaderManager *MainShaderManager;

class cModel
{
public:
	cModel(void);
	~cModel(void);
	void Draw();
	void SetMesh( cMesh3d * mesh );
	//void SetCamera( cCamera *Camera ){ pCamera = Camera; };
	void SetUniform();
	void SetShader( const std::string &ShaderName );
	Transform* GetTransform();
	void SetTransform( Transform* transform );

private:
	void LoadToGPU();
	std::string m_Name;
	std::string mShaderName;
	bool m_Loaded;
	float m_Scale;
	cMesh3d *pMesh;
	Transform* mTransform;
			
};

