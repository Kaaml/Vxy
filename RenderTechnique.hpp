#pragma once

#include "Include.hpp"
#include "cShaderManager.hpp"

class RenderTechnique
{
public:
	RenderTechnique(void);
	void SetShader( cProgramShader* Program );

	void Bind();
	~RenderTechnique(void);

private:
	cProgramShader* pProgramShader;
};

