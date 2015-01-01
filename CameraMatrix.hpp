#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class CameraMatrix
{
public:
	CameraMatrix(void);
	CameraMatrix( const glm::vec3 &EyePos, const glm::vec3 &ForwardDir, const glm::vec3 &UpDir, 
		float Fov, float Aspect, float Near, float Far, float Width, float Height );

	void SetProjection( float Fov, float Aspect, float Near, float Far );
	void SetEyePos( const glm::vec3 &EyePos );
	void SetForwardDir( const glm::vec3 &ForwardDir );
	void SetUpDir( const glm::vec3 &UpDir );

	void Update();
	
	const glm::vec3& GetEyePos() const;
	const glm::vec3& GetUpDir() const;
	const glm::vec3& GetForwardDir() const;

	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewProjectionMatrix() const;

	~CameraMatrix(void);

private:
	void UpdateProjectionMatrix();
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mViewProjMatrix;
	glm::vec2 mScreenSize;
	float mNear;
	float mFar;
	float mAspect;
	float mFov;

	// Pozycja oka
	glm::vec3 mEyePosition;
	//kierunek patrzenia
	glm::vec3 mForwardDir;
	//kierunek do gory
	glm::vec3 mUpDir;
	//wektor w prawo
	glm::vec3 mRightDir;
};

inline const glm::mat4& CameraMatrix::GetViewMatrix() const
{
	return mViewMatrix;
}

inline const glm::mat4& CameraMatrix::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}

inline const glm::mat4& CameraMatrix::GetViewProjectionMatrix() const
{
	return mViewProjMatrix;
}