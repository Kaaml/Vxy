#include "cCamera.hpp"

cCamera::~cCamera(void){}

cCamera::cCamera(void)
{
	PositionCamera = glm::vec3( 0.0f, 0.0f, 0.f );
	View = glm::mat4( 1.0f );
	Projection = glm::mat4( 1.0f );
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
}

glm::mat4 cCamera::GetVPmatrix()
{
	return ( Projection*View );
}

void cCamera::Move( glm::vec3 delta )
{
	glm::vec3 a = delta;
	a = glm::mat3( glm::yawPitchRoll( Yaw, Pitch, Roll ) )*a;
	PositionCamera += a;
}

void cCamera::AddToPitch( float angle )
{
	Pitch += angle;
}
void cCamera::AddToRoll( float angle )
{
	Roll += angle;
}
void cCamera::AddToYaw( float angle )
{
	Yaw += angle;
}

void cCamera::Update()
{
	if( Yaw > 90 )
		Yaw = 90;
	if( Pitch >90 )
		Pitch = 90;
	glm::mat4 Euler = glm::yawPitchRoll( Yaw, Pitch, Roll );
	View = glm::mat4( 1.0f );
	//View *= glm::inverse(glm::translate( PositionCamera ));
	//View *= glm::inverse( Euler );
	//View *= glm::inverse( Euler * glm::translate( PositionCamera) );
	View = glm::inverse(  glm::translate( PositionCamera) * Euler);
	//if( glfwGetKey( GLFW_KEY_TAB ) == GLFW_PRESS  )
	//	std::cout << "Yaw: " << Yaw << " Pitch: " << Pitch << " Roll: " << Roll << " Position: X " << PositionCamera.x << " Y: " << PositionCamera.y << " Z: " << PositionCamera.z << std::endl;
	Renderer *render = Renderer::GetSingletonPtr();
	render->SetProjectionMatrix( this->GetProjectionMatrix() );
	render->SetViewMatrix( this->GetViewMatrix() );
	render->SetNormalMatrix( this->GetNormalMatrix() );

}

void cCamera::InitPerspectiv( float Width, float Height, float fov,
		float Near, float Far )
{
	Projection = glm::perspective( fov, Width/Height, Near, Far );
	//Projection = glm::perspective( 45.0f, 1366.f/768.f, 0.1f, 1000.f );
	glm::mat4 Euler = glm::inverse(glm::yawPitchRoll( Yaw, Pitch, Roll ));
	View *= glm::inverse(glm::translate( PositionCamera ));
	View *= Euler;
}

void cCamera::InitOrtogonal( float Width, float Height)
{
	Projection = glm::ortho( -1.0f, 1.0f, -1.f, 1.0f );
}


glm::mat4 cCamera::GetProjectionMatrix()
{
	return Projection;
}

glm::mat3 cCamera::GetNormalMatrix()
{
	return glm::mat3( glm::inverse( glm::yawPitchRoll( Yaw, Pitch, Roll ) ) );
}
glm::mat4 cCamera::GetViewMatrix()
{
	return View;
	//return glm::inverse( glm::yawPitchRoll( Yaw, Pitch, Roll )) * glm::inverse( glm::translate( PositionCamera )  );	
	//return glm::inverse( glm::inverse( glm::translate( PositionCamera ) * glm::yawPitchRoll( Yaw, Pitch, Roll ))  );	
}

glm::vec3 cCamera::GetCameraPos()
{
	return PositionCamera;
}
