#include "TextureSampler.hpp"

TextureSampler::TextureSampler()
{
	glGenSamplers( 1, &hSampler );
	mMinFilter = TF_NEAREST_MIPMAP_LINEAR;
	mMagFilter = TF_LINEAR;
	mWrapS = WM_REPEAT;
	mWrapT = WM_REPEAT;
	mSampler = 0;
	this->Update();
}
TextureSampler::TextureSampler( Texture2D *ptexture, uint sampler, TEXTUREFILTER MinFilter,
		TEXTUREFILTER MagFilter, WRAPMODE WrapS, WRAPMODE WrapT )
		:
	mMinFilter( MinFilter ),
	mMagFilter( MagFilter ),
	mWrapS( WrapS ),
	mWrapT( WrapT ),
	mSampler( sampler ),
	pTexture( ptexture )
{
	glGenSamplers( 1, &hSampler );
	this->Update();
}

TextureSampler::~TextureSampler()
{
	glDeleteSamplers( 1, &hSampler );
}

void TextureSampler::Bind()
{
	pTexture->Bind( mSampler );
	glBindSampler( mSampler, hSampler );

}



void TextureSampler::SetWrapMode( WRAPMODE WrapS, WRAPMODE WrapT )
{
	mWrapS = WrapS;
	mWrapT = WrapT;
}

void TextureSampler::SetWrapS( WRAPMODE WrapS )
{
	mWrapS = WrapS;
}
void TextureSampler::SetWrapT( WRAPMODE WrapT )
{
	mWrapT = WrapT;
}
void TextureSampler::SetMagFilter( TEXTUREFILTER MagFilter )
{
	mMagFilter = MagFilter;
}
void TextureSampler::SetMinFilter( TEXTUREFILTER MinFilter )
{
	mMinFilter = MinFilter;
}

void TextureSampler::SetMinMagFilters( TEXTUREFILTER MinFilter , TEXTUREFILTER MagFilter  )
{
	mMinFilter = MinFilter;
	mMagFilter = MagFilter;
}

void TextureSampler::SetTexturePointer( Texture2D *Texture )
{
	pTexture = Texture;
}

void TextureSampler::SetSamplerUnit( uint Sampler )
{
	mSampler = Sampler;
}

void TextureSampler::Update()
{
	glSamplerParameteri( hSampler, GL_TEXTURE_MIN_FILTER, mMinFilter );
	glSamplerParameteri( hSampler, GL_TEXTURE_MAG_FILTER, mMagFilter );
	glSamplerParameteri( hSampler, GL_TEXTURE_WRAP_S, mWrapS );
	glSamplerParameteri( hSampler, GL_TEXTURE_WRAP_T, mWrapT );
}