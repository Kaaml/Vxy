#pragma once

#include "Include.hpp"
#include "Texture2D.hpp"

enum TEXTUREFILTER
{
	TF_NEAREST = GL_NEAREST,
	TF_LINEAR = GL_LINEAR,
	TF_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	TF_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	TF_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	TF_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

enum WRAPMODE
{
	WM_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	WM_CLAMP = GL_CLAMP,
	WM_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	WM_REPEAT = GL_REPEAT
};


class TextureSampler
{
public:
	TextureSampler(void);
	TextureSampler( Texture2D *ptexture, uint sampler = 0, TEXTUREFILTER MinFilter = TF_NEAREST_MIPMAP_LINEAR,
		TEXTUREFILTER MagFilter = TF_LINEAR, WRAPMODE WrapS = WM_REPEAT, WRAPMODE WrapT = WM_REPEAT );
	void Bind();
	void SetWrapMode( WRAPMODE WrapS, WRAPMODE WrapT );
	void SetWrapS( WRAPMODE WrapS );
	void SetWrapT( WRAPMODE WrapT );
	void SetMinFilter( TEXTUREFILTER MinFilter );
	void SetMagFilter( TEXTUREFILTER MagFilter );
	void SetMinMagFilters( TEXTUREFILTER MinFilter , TEXTUREFILTER MagFilter  );
	void SetTexturePointer( Texture2D *Texture );
	void SetSamplerUnit( uint sampler );
	void Update();
	~TextureSampler(void);
private:
	Texture2D *pTexture;
	WRAPMODE mWrapT;
	WRAPMODE mWrapS;
	TEXTUREFILTER mMinFilter;
	TEXTUREFILTER mMagFilter;
	uint mSampler;		//na który slot ma byæ textura bindowana
	GLuint hSampler;

};

