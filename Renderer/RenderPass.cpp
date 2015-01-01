#include "RenderPass.hpp"


RenderPass::RenderPass(void)
{
	pShader = cShaderManager::GetInstance()->GetProgram( "default" );
}


RenderPass::~RenderPass(void)
{
}

void RenderPass::Bind()
{
	pShader->Bind();	
	for( const auto &texture : mTextures )
	{
		texture->Bind();
	}
}

void RenderPass::Update()
{
	pShader->Update();
}

void RenderPass::AddTexture( TextureSampler *pTexture )
{
	mTextures.push_back( pTexture );
}

void RenderPass::Parse( pugi::xml_node Node )
{
	//parasowanie pass
	for( const auto &Child : Node.children() )
	{
		if( !strcmp( Child.name(), "shader" ) )
		{
			//wyszukaj shader i jak go nie ma ³aduj z pliku itp
			std::string ShaderName = Child.attribute( "name" ).as_string();
			cProgramShader *Shader = cShaderManager::GetInstance()->GetProgram( ShaderName );
			if( Shader == nullptr )
			{
				Shader = cShaderManager::GetInstance()->Parse( Child );
			}
			pShader = Shader;
		}else if( !strcmp( Child.name(), "sampler" ) )
		{
			//sampler z tekstury
			std::string TextureName = Child.attribute( "texture").as_string();
			uint Sampler = Child.attribute( "sampler" ).as_uint();
			TextureManager *TexMgr = TextureManager::GetSingletonPtr();
			Texture2D *Tex = TexMgr->GetTexturePtr( TextureName );
			TextureSampler *TexSampler = new TextureSampler( Tex, Sampler );
			TexSampler->Update();
			mTextures.push_back( TexSampler );
		}
	}

}

void RenderPass::SetShader( cProgramShader *pProgram )
{
	pShader = pProgram;
}