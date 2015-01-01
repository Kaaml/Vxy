#pragma once

#include "Texture2D.hpp"
#include "AbstractAttachBuffer.hpp"
#include "Include.hpp"

enum BUFFERTARGET;
enum FBOBIND;
class Texture2D;
class AbstractAttachBuffer;

class Fbo
{
public:
	Fbo( GLuint Height, GLuint Width );


	void AddDepthAtachament( AbstractAttachBuffer* Depth );
	void AddTextureAtachament( BUFFERTARGET Atachament, Texture2D *Texture );
	void RemoveTextureAtachaments();
	void SetReadBuffer( BUFFERTARGET Target );
	void BindReadBuffers();
	void BindDrawBuffers();
	void SetDrawBuffers( BUFFERTARGET Target );
	void SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2 );
	void SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3 );
	void SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3, BUFFERTARGET Target4 );
	void SetDrawBuffers( BUFFERTARGET Target, BUFFERTARGET Target2, BUFFERTARGET Target3, BUFFERTARGET Target4, BUFFERTARGET Target5 );
	void SetDrawBuffers( const std::vector< BUFFERTARGET > &Targets );
	bool CheckStatus();
	void ClearBuffer();
	void BindBuffer( FBOBIND Target );
	void UnBind();
	void EnableDepth(){ m_DepthTest = true; };
	void DisableDepth() { m_DepthTest = false; };
	~Fbo(void);

private:
	GLuint m_Width;
	GLuint m_Height;
	GLuint m_Handle;
	std::vector< BUFFERTARGET > m_DrawBuffers;
	std::map< BUFFERTARGET, AbstractAttachBuffer* > m_TextureBuffers;
	AbstractAttachBuffer* m_DepthBuffer;

	BUFFERTARGET m_ReadBuffer;
	bool m_DepthTest;

};

enum BUFFERTARGET
{
	NONE 			   = GL_NONE, 			  
	FRONT_LEFT 		   = GL_FRONT_LEFT, 		  
	FRONT_RIGHT 	   = GL_FRONT_RIGHT, 	  
	BACK_LEFT 		   = GL_BACK_LEFT, 		  
	BACK_RIGHT 		   = GL_BACK_RIGHT,		  
	AUX0 			   = GL_AUX0, 			  
	AUX1 			   = GL_AUX1, 			  
	AUX2 			   = GL_AUX2, 			  
	AUX3 			   = GL_AUX3, 			  
	COLOR_ATTACHMENT0  = GL_COLOR_ATTACHMENT0, 
	COLOR_ATTACHMENT1  = GL_COLOR_ATTACHMENT1, 
	COLOR_ATTACHMENT2  = GL_COLOR_ATTACHMENT2, 
	COLOR_ATTACHMENT3  = GL_COLOR_ATTACHMENT3, 
	COLOR_ATTACHMENT4  = GL_COLOR_ATTACHMENT4, 
	COLOR_ATTACHMENT5  = GL_COLOR_ATTACHMENT5, 
	COLOR_ATTACHMENT6  = GL_COLOR_ATTACHMENT6, 
	COLOR_ATTACHMENT7  = GL_COLOR_ATTACHMENT7, 
	COLOR_ATTACHMENT8  = GL_COLOR_ATTACHMENT8, 
	COLOR_ATTACHMENT9  = GL_COLOR_ATTACHMENT9, 
	COLOR_ATTACHMENT10 = GL_COLOR_ATTACHMENT10,	
	COLOR_ATTACHMENT11 = GL_COLOR_ATTACHMENT11,	
	COLOR_ATTACHMENT12 = GL_COLOR_ATTACHMENT12,	
	COLOR_ATTACHMENT13 = GL_COLOR_ATTACHMENT13,	
	COLOR_ATTACHMENT14 = GL_COLOR_ATTACHMENT14,	
	COLOR_ATTACHMENT15 = GL_COLOR_ATTACHMENT15,
	DEPTH_ATTACHEMENT  = GL_DEPTH_ATTACHMENT,
	DEPTH_STENCIL_ATACHEMENT = GL_DEPTH_STENCIL_ATTACHMENT,
	STENCIL			   = GL_STENCIL_ATTACHMENT
};
enum FBOBIND
{
	READ = GL_READ_FRAMEBUFFER,
	DRAW = GL_DRAW_FRAMEBUFFER,
	FB   = GL_FRAMEBUFFER
};