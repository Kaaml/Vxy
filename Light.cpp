#include "Light.hpp"


Light::Light(void)
{
	mLightType = LightType::POINT_LIGHT;
	mLightPosition = glm::vec3( 0.f );
	mAmbientColor = glm::vec3( 1.f );
	mDiffuseColor = glm::vec3( 1.f );
	mSpecularColor= glm::vec3( 1.f );
	mDirection = glm::vec3( 0.f, 0.f, 0.f );
	mSpotExponent = 0.f;
	mSpotCutoff	  = 0.f;
	mRadius		  = 0.f;
	mSpecularPower= 0.f;
}

Light::Light( const glm::vec3 Position, const glm::vec3 &Color, LightType Type )
{
	mLightType = Type;
	mLightPosition = Position;
	mAmbientColor = Color;
	mDiffuseColor = glm::vec3( 1.f );
	mSpecularColor= glm::vec3( 1.f );
	mDirection = glm::vec3( 0.f, 0.f, 0.f );
	mSpotExponent = 0.f;
	mSpotCutoff	  = 0.f;
	mRadius		  = 0.f;
	mSpecularPower= 0.f;
}
void Light::SetLightType( LightType Type )
{
	mLightType = Type;
}
void Light::SetPosition( const glm::vec3 &Position )
{
	mLightPosition = Position;
}
void Light::SetAmbient( const glm::vec3 &Ambient )
{
	mAmbientColor = Ambient;
}
void Light::SetDiffuse( const glm::vec3 &Diffuse )
{
	mDiffuseColor = Diffuse;
}
void Light::SetSpecular( const glm::vec3 &Speuclar )
{
	mSpecularColor = Speuclar;
}
void Light::SetDirection( const glm::vec3 &Direction )
{
	mDirection = Direction;
}
void Light::SetSpotDirection( const glm::vec3 &SpotDirection )
{
	mDirection = SpotDirection;
}
void Light::SetSpotExponent( float Exponent )
{ 
	mSpotExponent = Exponent;
}
void Light::SetSpotCutoff( float SpotCutoff )
{
	mSpotCutoff = SpotCutoff;
}
void Light::SetRadiu( float Radius )
{
	mRadius = Radius;
}
void Light::SetSpecularPower( float SpecPower )
{
	mSpecularPower = SpecPower;
}

const glm::vec3& Light::GetPosition() const
{
	return mLightPosition;
}
const glm::vec3& Light::GetAmbient() const
{ 
	return mAmbientColor;
}
const glm::vec3& Light::GetDiffuse() const
{
	return mDiffuseColor;
}
const glm::vec3& Light::GetSpecular() const
{
	return mSpecularColor;
}
float Light::GetRadius() const
{
	return mRadius;
}
float Light::GetSpecularPower() const
{
	return mSpecularPower;
}

LightType Light::GetLightType() const
{
	return mLightType;
}

Material* Light::GetMaterialPtr() const
{
	return pMaterial;
}

Material& Light::GetMaterial() const
{
	return *pMaterial;
}

float Light::GetSpotCutoff() const
{
	return mSpotCutoff;
}

const glm::vec3& Light::GetSpotDirection() const
{
	return mDirection;
}

void Light::SetMaterial( Material *pMat )
{
	pMaterial = pMat;
}

void Light::SetSpotLight( const glm::vec3& Position, const glm::vec3& SpotDirection, float SpotCutoff, const glm::vec3& color )
{
	mLightPosition = Position;
	mDirection = SpotDirection;
	mDiffuseColor = color;
	mSpotCutoff = SpotCutoff;
}
Light::~Light(void)
{
}
