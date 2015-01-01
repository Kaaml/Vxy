#include "Fbo.hpp"


Fbo::Fbo(  GLuint Width, GLuint Height )
{
	m_Height = Height;
	m_Width = Width;
	glGenFramebuffers( 1, &m_Handle );
	m_DepthBuffer = nullptr;
	m_ReadBuffer = BUFFERTARGET::NONE;
}

Fbo::~Fbo(void)
{
	glDeleteFramebuffers( 1, &m_Handle );
	m_TextureBuffers.clear();
}

void Fbo::BindBuffer( FBOBIND Target )
{
	glBindFramebuffer( Target, m_Handle );
	glViewport( 0, 0, m_Width, m_Height );
	
	if( Target == FBOBIND::FB || Target == FBOBIND::DRAW )
	{
		BindDrawBuffers();
		for( auto i = m_TextureBuffers.begin(); i != m_TextureBuffers.end(); ++i )
		{
			i->second->BindAtachament( this, i->first );
		}
		if( m_DepthBuffer )
		{
			//m_DepthBuffer->BindAtachament( this, BUFFERTARGET::DEPTH_STENCIL_ATACHEMENT );
			m_DepthBuffer->BindAtachament( this, BUFFERTARGET::DEPTH_ATTACHEMENT );
		}
	}
	if( Target == FBOBIND::FB || Target == FBOBIND::READ )
		BindReadBuffers();

}

void Fbo::SetReadBuffer( BUFFERTARGET Target )
{
	m_ReadBuffer = Target;
	glReadBuffer( m_ReadBuffer );
}

void Fbo::SetDrawBuffers( BUFFERTARGET Target )
{
	m_DrawBuffers.clear();
	m_DrawBuffers.push_back( Target );
}

void Fbo::SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2 )
{
	m_DrawBuffers.clear();
	m_DrawBuffers.resize( 2);
	m_DrawBuffers[0] = Target;
	m_DrawBuffers[1] = Target2;
}

void Fbo::SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3 )
{
	m_DrawBuffers.clear();
	m_DrawBuffers.resize( 3 );
	m_DrawBuffers[0] = Target;
	m_DrawBuffers[1] = Target2;
	m_DrawBuffers[2] = Target3;
}

void Fbo::SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3, BUFFERTARGET Target4, BUFFERTARGET Target5 )
{
	m_DrawBuffers.clear();
	m_DrawBuffers.resize( 5 );
	m_DrawBuffers[0] = Target;
	m_DrawBuffers[1] = Target2;
	m_DrawBuffers[2] = Target3;
	m_DrawBuffers[3] = Target4;
	m_DrawBuffers[4] = Target5;
}

void Fbo::SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3, BUFFERTARGET Target4 )
{
	m_DrawBuffers.clear();
	m_DrawBuffers.resize( 4 );
	m_DrawBuffers[0] = Target;
	m_DrawBuffers[1] = Target2;
	m_DrawBuffers[2] = Target3;
	m_DrawBuffers[3] = Target4;
}

void Fbo::SetDrawBuffers( const std::vector< BUFFERTARGET > &Targets )
{
	m_DrawBuffers.clear();
	m_DrawBuffers = Targets;
}

void Fbo::AddTextureAtachament( BUFFERTARGET Atachament, Texture2D *Texture )
{

	// TUTAJ POPRAWIC <===================================================================================
	m_TextureBuffers.insert( std::pair<BUFFERTARGET, AbstractAttachBuffer*>( Atachament, (AbstractAttachBuffer*) Texture ) );

}


void Fbo::AddDepthAtachament( AbstractAttachBuffer* Depth )
{
	m_DepthBuffer = Depth;
}

void Fbo::RemoveTextureAtachaments()
{
	m_TextureBuffers.clear();
}

void Fbo::BindReadBuffers()
{
	glReadBuffer( m_ReadBuffer );
}

void Fbo::BindDrawBuffers()
{
	glDrawBuffers( m_DrawBuffers.size(), (GLenum* ) &m_DrawBuffers[0] );
}

void Fbo::UnBind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

bool Fbo::CheckStatus()
{
	GLenum FBOstatus = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER );
	if( FBOstatus != GL_FRAMEBUFFER_COMPLETE )
	{
		switch (FBOstatus)
		{
		case GL_FRAMEBUFFER_UNDEFINED:			
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
		
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			
			break;
		default:
			break;
		}
	}
	return 0;
	// brak bledu
};

void Fbo::ClearBuffer()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );
}
