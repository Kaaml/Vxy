#pragma once

#include "Include.hpp"
#include <glm/glm.hpp>
#include "Texture2D.hpp"
#include "cShaderManager.hpp"
#include "RenderPass.hpp"

class RenderPass;
enum TEXTURE_USAGE
{
	TEXTURE_COLOR,
	TEXTURE_NORMAL,
	TEXTUREN_SHININESS
};

class Material
{
public:
	Material(void);
	~Material(void);

	void Bind();
	void SetEmission(  const glm::vec3 &Emission );
	void SetAmbient(  const glm::vec3 &Ambient );
	void SetDiffuse(  const glm::vec3 &Diffuse );
	void SetSpecular(  const glm::vec3 &Specular );
	void Setshininess(  const float &Shininess );
	void SetShaderName( const std::string &ShaderName );
	glm::vec3 GetEmission() const {
		return mEmission;
	};
	glm::vec3 GetAmbient() const {
		return mAmbient;
	};
	glm::vec3 GetDiffuse() const {
		return mDiffuse;
	};
	glm::vec3 GetSpecular() const {
		return mSpecular;
	};
	float GetShininess() const {
		return mShininess;
	};
	const std::string GetShaderName() const {
		return mShaderName;
	};
	const cProgramShader* GetShaderPtr();

	void AddRenderPass( RenderPass *pPass );

	void Parse( pugi::xml_node Node );
	
private:
	glm::vec3 mGlobalAmbient;
	glm::vec3 mEmission;	// wsp emisji swiatla
	glm::vec3 mAmbient;		// wsp odbicia dla swiadtla otoczenia
	glm::vec3 mDiffuse;		// wsp odbicia dla swiadtla rozproszonego
	glm::vec3 mSpecular;	// wsp odbicia dla swiadtla zwierciadlanego

	//std::map< TEXTURE_USAGE, Texture2D* > mMaterialTextures;
	float mShininess;		// wyk³adnik rozblysku <0; 128>
	std::string mShaderName;
	
	RenderPass *pRenderPass;


};

