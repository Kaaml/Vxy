#include "RenderPass.hpp"
#include <cassert>

TEXTUREFILTER CheckTextureFilter( const char* type )
{
	if( !strcmp( type, "LINEAR" ) )
	{
		return TF_LINEAR;
	} else if( !strcmp( type, "NEAREST" ) )
	{
		return TF_NEAREST;
	} else if( !strcmp( type, "LINEAR_MIPMAP_LINEAR" ) )
	{
		return TF_LINEAR_MIPMAP_LINEAR;
	} else if( !strcmp( type, "LINEAR_MIPMAP_NAREST" ) )
	{
		return TF_LINEAR_MIPMAP_NEAREST;
	} else if( !strcmp(type, "NAREST_MIPMAP_NAREST" ) )
	{
		return TF_NEAREST_MIPMAP_NEAREST;
	} else if( !strcmp( type, "NAREST_MIPMAP_LINEAR" ) )
	{
		return TF_NEAREST_MIPMAP_LINEAR;
	} else
	{
		return TF_LINEAR;
	}
}

WRAPMODE CheckWrapMode( const char* sMode )
{
	if(! strcmp( sMode, "CLAMP" ) )
	{
		return WM_CLAMP;
	} else if( !strcmp( sMode, "CLAMP_TO_EDGE" ) )
	{
		return WM_CLAMP_TO_EDGE;
	} else if( !strcmp( sMode, "MIRRORED_REPEAT" ) )
	{
		return WM_MIRRORED_REPEAT;
	} else if( !strcmp( sMode, "REPEAT" ) )
	{
		return WM_REPEAT;
	} else
	{
		return WM_CLAMP;
	}
}
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
			TEXTUREFILTER TfMin = CheckTextureFilter( Child.attribute( "min_filter" ).as_string() );
			TEXTUREFILTER TfMag = CheckTextureFilter( Child.attribute( "mag_filter" ).as_string( ) );
			WRAPMODE WmS = CheckWrapMode( Child.attribute( "wrap_s" ).as_string() );
			WRAPMODE WmT = CheckWrapMode( Child.attribute( "wrap_t" ).as_string() );			

			TextureManager *TexMgr = TextureManager::GetSingletonPtr();
			Texture2D *Tex = TexMgr->GetTexturePtr( TextureName );
			if( Tex == nullptr )
			{
				std::cerr << "blad";
			}
			TextureSampler *TexSampler = new TextureSampler( Tex, Sampler, TfMin, TfMag, WmS, WmT );
			TexSampler->Update();
			mTextures.push_back( TexSampler );
		}
	}

}

void RenderPass::SetShader( cProgramShader *pProgram )
{
	pShader = pProgram;
}