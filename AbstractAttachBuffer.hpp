#pragma once

#include "Include.hpp"
//#include "Fbo.hpp"

class Fbo;
enum BUFFERTARGET;
enum FBOBIND;

class AbstractAttachBuffer
{
public:
	AbstractAttachBuffer(void);
	~AbstractAttachBuffer(void);
	GLuint GetHandle() const { return m_BufferHandle; };
	void virtual BindAtachament( Fbo* fbo, BUFFERTARGET Target ) = 0;
protected:
	GLuint m_BufferHandle;
};

