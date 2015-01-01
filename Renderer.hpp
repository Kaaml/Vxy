#pragma once

#include "Include.hpp"
#include "cShaderManager.hpp"
#include "Surface.hpp"
#include "cCamera.hpp"
#include "Fbo.hpp"
#include "Texture2D.hpp"
#include "Singleton.hpp"
#include "Light.hpp"
#include "TextureManager.hpp"



class Renderer : public Singleton< Renderer >
{
public:
	Renderer( const glm::vec2 &ViewSize );
	void AddToRender( Surface* pSurface );
	void AddLight( Light *pLight );
	void Render();

	void SetActiveMaterial( Material *pMaterial );
	void SetActiveCamera( cCamera *pCamera );
	void SetMVPMatrix( const glm::mat4 &mvp );
	void SetModelMatrix( const glm::mat4 &model );
	void SetViewMatrix( const glm::mat4 &view );
	void SetProjectionMatrix( const glm::mat4 &projection );
	void SetNormalMatrix( const glm::mat3 &normalmat );
	void UpdateMatrix();

	inline Material* GetActiveMaterialPtr() const {
		return pActiveMaterial;
	};
	inline Material& GetActiveMaterial() const {
		return *pActiveMaterial;
	};
	cCamera* GetActiveCameraPtr() const {
		return pActiveCamera;
	};
	Light* GetActiveLightPtr() const{
		return pActiveLight;
	};
	Light& GetActiveLight() {
		return *pActiveLight;
	};
	const glm::mat4& GetMVPMatrix() const;
	const glm::mat4& GetModelMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat3& GetNormalMatrix() const;
	~Renderer(void);

private:
	// Deferred rendering method <-- prezkszta³cic na klasy czy cos normalniejszego
	void InitRendering();
	void GeometryPass();
	void LightPass();
	Fbo *pDeferred;
	std::vector< Texture2D * > mLayers;
	std::vector< Surface* > mSurfaceToRender;
	std::vector< Light* > mLightsToRender;

	// ***  $$$$ *****
	Material *pActiveMaterial;
	cCamera  *pActiveCamera;
	Light	 *pActiveLight;

	Material *pPointLightMaterial;
	Material *pDirectLightMaterial;
	Material *pSpotLightMaterial;

	Surface *ScreenSurface;

	glm::mat4 mModelMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;
	glm::mat4 mModelViewProjection;
	glm::mat3 mNormalMatrix;
	glm::vec2 mViewSize;
	
};

inline const glm::mat4& Renderer::GetMVPMatrix() const {
	return mModelViewProjection;
};

inline const glm::mat4& Renderer::GetModelMatrix() const {
	return mModelMatrix;
};

inline const glm::mat4& Renderer::GetViewMatrix() const {
	return mViewMatrix;
};

inline const glm::mat4& Renderer::GetProjectionMatrix() const {
	return mProjectionMatrix;
};

inline const glm::mat3& Renderer::GetNormalMatrix() const {
	return mNormalMatrix;
};
