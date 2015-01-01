#include "CameraMatrix.hpp"


CameraMatrix::CameraMatrix(void)
{
	mEyePosition= glm::vec3( 0.f, 1.f, -1.f );
	mForwardDir = glm::vec3( 0.f, 0.f, 0.f );
	mUpDir		= glm::vec3( 0.f, 1.f, 0.f );
	mFov		= 0.0f;
	mAspect		= 0.0f;
	mNear		= 0.0f;
	mFar		= 0.0f;
}

CameraMatrix::CameraMatrix( const glm::vec3 &EyePos, const glm::vec3 &ForwardDir, const glm::vec3 &UpDir, 
		float Fov, float Aspect, float Near, float Far, float Width, float Height )
{
	mEyePosition= EyePos;
	mForwardDir = ForwardDir;
	mUpDir		= UpDir;
	mFov		= Fov;
	mAspect		= Aspect;
	mNear		= Near;
	mFar		= Far;
	mScreenSize = glm::vec2( Width, Height );	
	UpdateProjectionMatrix();
}

void CameraMatrix::SetEyePos( const glm::vec3 &EyePos )
{
	mEyePosition = EyePos;
}

void CameraMatrix::SetForwardDir( const glm::vec3 &ForwardDir )
{
	mForwardDir = ForwardDir;
}

void CameraMatrix::SetUpDir( const glm::vec3 &UpDir )
{
	mUpDir = UpDir;
}

void CameraMatrix::Update()
{
	// calculate view matrix
	mViewMatrix = glm::lookAt( mEyePosition, mEyePosition + mForwardDir, mUpDir );
}

void CameraMatrix::UpdateProjectionMatrix()
{
	mProjectionMatrix = glm::perspectiveFov( mFov, mScreenSize.x, mScreenSize.y, mNear, mFar );
}

CameraMatrix::~CameraMatrix(void)
{
}
