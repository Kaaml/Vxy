#include "Texture2D.hpp"


Texture2D::Texture2D(void)
	:m_MipmapLvl( 0 ), AbstractAttachBuffer()
{
	glGenTextures(1, &m_BufferHandle );
	m_WrapS = GL_CLAMP;
	m_WrapT = GL_CLAMP;
	m_MagFilter = GL_LINEAR;
	m_MinFilter = GL_LINEAR;
	
}

Texture2D::Texture2D(const std::string &ImageName )
{
	m_WrapS = GL_CLAMP;
	m_WrapT = GL_CLAMP;
	m_MagFilter = GL_LINEAR;
	m_MinFilter = GL_LINEAR;
	glGenTextures(1, &m_BufferHandle );	
	LoadWithFile( ImageName );
}
Texture2D::Texture2D( GLuint Width, GLuint Height, int MipmapLvl, const FORMAT Format )
{
	m_WrapS = GL_CLAMP;
	m_WrapT = GL_CLAMP;
	m_MagFilter = GL_LINEAR;
	m_MinFilter = GL_LINEAR;
	m_MipmapLvl = MipmapLvl;
	glGenTextures( 1, &m_BufferHandle );
	glBindTexture( GL_TEXTURE_2D, m_BufferHandle );
	switch( Format )
	{
	case FORMAT::DEPTH :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr );
		break;
	case FORMAT::DEPTH24 :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr );
		break;
	case FORMAT::DEPTH32F :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );
		break;
	case FORMAT::DEPTH_STENCIL32 :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr );
		break;
	case FORMAT::DEPTH_STENCIL :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, nullptr );
		break;
	case FORMAT::RGBA32F:
	case FORMAT::RGBA16F:
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGBA, GL_FLOAT, nullptr );
		break;
	case FORMAT::RGB32F :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGB, GL_FLOAT, nullptr );
		break;
	case FORMAT::RGB32I :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGB_INTEGER, GL_INT, nullptr );
		break;
	case FORMAT::RGB16 :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr );
		break;
	case FORMAT::RGB16F :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGB, GL_FLOAT, nullptr );
		break;
	case FORMAT::RGBA :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
		break;
	case FORMAT::RGB :
		glTexImage2D( GL_TEXTURE_2D, 0, Format, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr );
		break;


	};


	glBindTexture( GL_TEXTURE_2D, 0 );
}

bool Texture2D::LoadWithFile( const std::string &ImageName )
{
	//wczytanie obrazka
	ILuint image;
	ilGenImages( 1, &image );
	ilBindImage( image );
	ilLoadImage( ImageName.c_str() );
	ILenum Error = ilGetError();
	if( Error != IL_NO_ERROR )
	{
		std::cerr << "ERROR: Wczytanie tekstury: "<< "nie powiodlo sie, plik: " << ImageName << " nie zostal wczytany" << std::endl;
		return false;
	}
	int width, height, depth;
	ILenum type, format;
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	depth = ilGetInteger( IL_IMAGE_DEPTH );
	type = ilGetInteger( IL_IMAGE_TYPE ); 
	format = ilGetInteger( IL_IMAGE_FORMAT );
	ILubyte *pixmap = ilGetData();
	glBindTexture( GL_TEXTURE_2D, m_BufferHandle );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixmap );
	UnBind();
	ilDeleteImage( image );
	return true;
}

void Texture2D::Bind( int location )
{
	glActiveTexture( GL_TEXTURE0 + location );
	glBindTexture( GL_TEXTURE_2D, m_BufferHandle );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapT );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MinFilter );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MagFilter );
}

void Texture2D::UnBind()
{
	glBindTexture( GL_TEXTURE_2D, NULL );
}
void Texture2D::SetWrap( GLenum WrapS, GLenum WrapT )
{
	m_WrapS = WrapS;
	m_WrapT = WrapT;
}
void Texture2D::SetWrapS( GLenum WrapS )
{
	m_WrapS = WrapS;
}
void Texture2D::SetWrapT( GLenum WrapT )
{
	m_WrapT = WrapT;
}
void Texture2D::SetMagFilter( GLenum MagFilter )
{
	m_MagFilter = MagFilter;
}
void Texture2D::SetMinFilter( GLenum MinFilter )
{
	m_MinFilter = MinFilter;
}
Texture2D::~Texture2D(void)
{
	glDeleteTextures(1, &m_BufferHandle );
}

void Texture2D::BindAtachament( Fbo* fbo, BUFFERTARGET Target )
{
	glFramebufferTexture2D( GL_FRAMEBUFFER, Target, GL_TEXTURE_2D, m_BufferHandle, m_MipmapLvl );
}
