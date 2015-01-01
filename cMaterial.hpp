#pragma once
#include "Include.hpp"
#include <IL/il.h>
#include "Texture2D.hpp"

class cMaterial
{
public:
	//cMaterial(void);
	cMaterial();
	void Use();
	void SetShader();
	void SetShiness( float shiness );
	void SetImage( std::string ImageName );
	~cMaterial(void);
private:
	std::string mShaderName;
	float mShiness;
	Texture2D *mTexture;
};

