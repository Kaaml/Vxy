#pragma once
#include "Include.hpp"
#include "AbstractAttachBuffer.hpp"
#include <il/il.h>


enum FORMAT
{
	RGBA = GL_RGBA,
	RGB = GL_RGB,
	RGB8 = GL_RGB8,
	RGB16 = GL_RGB16,
	RGB16F = GL_RGB16F,
	RGBA16F = GL_RGBA16F,
	RGB32I = GL_RGB32I,
	RGB32F = GL_RGB32F,
	RGBA32F = GL_RGBA32F,
	DEPTH = GL_DEPTH_COMPONENT, 
	DEPTH24 = GL_DEPTH_COMPONENT24,
	DEPTH32F = GL_DEPTH_COMPONENT32,
	DEPTH_STENCIL = GL_DEPTH_STENCIL,
	DEPTH_STENCIL32 = GL_DEPTH24_STENCIL8
};
//class Fbo;
//enum BUFFERTARGET;

class Texture2D
	: public AbstractAttachBuffer
{
public:
	Texture2D( void );
	Texture2D( const std::string &ImageName );
	Texture2D( GLuint Width, GLuint Height, int MipmapLvl, const FORMAT Format = FORMAT::RGBA );
	~Texture2D(void);
	bool LoadWithFile(const std::string &ImageName );
	void Bind( int location );
	void UnBind();
	void SetName( const std::string &TextureName );
	//void GenerateHandle();
	void SetWrap( GLenum WrapS, GLenum WrapT );
	void SetWrapS( GLenum WrapS );
	void SetWrapT( GLenum WrapT );
	void SetMinFilter( GLenum MinFilter );
	void SetMagFilter( GLenum MagFilter );

	void BindAtachament( Fbo* fbo, BUFFERTARGET Target );


private:
	GLenum m_WrapT;
	GLenum m_WrapS;
	GLenum m_MinFilter;
	GLenum m_MagFilter;
	GLuint m_MipmapLvl;
	
};

