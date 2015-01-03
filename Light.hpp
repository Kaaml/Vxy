#pragma once
#include "Include.hpp"
#include "Material.hpp"

enum LightType
{
	POINT_LIGHT = 1, SPOT = 2, DIRECTION = 3
};
class Light
{
public:
	Light(void);
	Light( const glm::vec3 Position, const glm::vec3 &Color, LightType Type = POINT_LIGHT );
	~Light(void);

	void SetLightType( LightType Type );
	void SetPosition( const glm::vec3 &Position );
	void SetAmbient( const glm::vec3 &Ambient );
	void SetDiffuse( const glm::vec3 &Diffuse );
	void SetSpecular( const glm::vec3 &Speuclar );

	void SetDirection( const glm::vec3 &Direction );
	void SetSpotDirection( const glm::vec3 &SpotDirection );
	void SetSpotExponent( float Exponent );
	void SetSpotCutoff( float SpotCutoff );
	void SetRadiu( float Radius );
	void SetSpecularPower( float SpecPower );
	void SetMaterial( Material *pMat );
	// SPOT LIGHT SET UP FUNCTION
	void SetSpotLight( const glm::vec3& Position, const glm::vec3& SpotDirection, float SpotCutoff, const glm::vec3& color = glm::vec3( 1.f ) );

	Material* GetMaterialPtr() const;
	Material& GetMaterial() const;

	const glm::vec3& GetPosition() const;
	const glm::vec3& GetAmbient() const;
	const glm::vec3& GetDiffuse() const;
	const glm::vec3& GetSpecular() const;
	const glm::vec3& GetSpotDirection() const;
	float GetRadius() const;
	float GetSpecularPower() const;
	float GetSpotCutoff() const;
	LightType GetLightType() const;
private:
	LightType mLightType;
	glm::vec3 mLightPosition;
	glm::vec3 mAmbientColor;
	glm::vec3 mDiffuseColor;
	glm::vec3 mSpecularColor;
	
	glm::vec3 mDirection;							//wektor kierunerku swiatla reflektorowego lub kierunek w œwietle kierunkowym			
	float mSpotExponent;							//wykladnik swiatla reflektora <0;128>
	float mSpotCutoff;								//k¹t obciêcia œwiat³a reflektora, zakres wartoœci <0;90> oraz 180 - punktowe

	float mRadius;
	float mSpecularPower;

	Material *pMaterial;					// pointer na material dla dee
	//float mConstantAttenuation;		// sta³y wspó³czynnik t³umienia œwiat³a; 
	//float mLinearAttenuation;		// liniowy wspó³czynnik t³umienia œwiat³a; 
	//float mQuadraticAttenuation;	// kwadratowy wspó³czynnik t³umienia œwiat³a;
};

