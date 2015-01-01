#pragma once

#include "../Include.hpp"
#include "../Renderer.hpp"
#include "../cShaderManager.hpp"
#include "../TextureSampler.hpp"


class RenderPass
{
public:
	RenderPass(void);
	~RenderPass(void);
	void Bind();
	void Update();
	void SetShader( cProgramShader *pProgram );
	void AddTexture( TextureSampler *pTexture );

	void Parse( pugi::xml_node Node );
	//napisac ladowanie z pliku xml
private:
	std::string mPassName;
	cProgramShader *pShader;
	//std::map< uint, Texture2D* > mTextures;
	std::vector< TextureSampler* > mTextures;
};

