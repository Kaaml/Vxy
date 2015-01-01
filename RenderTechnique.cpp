#include "RenderTechnique.hpp"


RenderTechnique::RenderTechnique(void)
{
	pProgramShader = nullptr;
}


RenderTechnique::~RenderTechnique(void)
{
}

void RenderTechnique::Bind()
{
	pProgramShader->Bind();
	
}