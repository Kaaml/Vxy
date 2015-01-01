#include "ShaderFunc.hpp"


void MVP( void *data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::mat4 MVP = Render->GetMVPMatrix();
	//glm::mat4 MVP = glm::perspective( 45.f, 1366.f/768.f, 0.01f, 10000.f );	
	//MVP *= glm::translate( 0.f, 0.f, -10.f );
	//glm::mat4 MVP = glm::mat4( 1.f );
	memcpy( data, (void *) &MVP, size );
}

void ModelMatrix( void *data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::mat4 Model = Render->GetModelMatrix();
	memcpy( data, (void *) &Model, size );
}

void ViewMatrix( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::mat4 View = Render->GetViewMatrix();
	memcpy( data, (void *) &View, size );
}

void ModelViewMatrix( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::mat4 ModelView = Render->GetViewMatrix();
	ModelView *= Render->GetModelMatrix();
	memcpy( data, (void*)&ModelView, size );
}

void NormalMatrix( void *data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::mat3 Normal = Render->GetNormalMatrix();
	memcpy( data, ( void *) &Normal, size );
}

void ProjectionMatrix( void *data, uint size )
{
	Renderer * Render = Renderer::GetSingletonPtr();
	glm::mat4 Projection = Render->GetProjectionMatrix();
	memcpy( data, (void *) &Projection, size );
}

void Emission( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 emision = Render->GetActiveMaterial().GetEmission();
	memcpy( data, (void*)&emision, size );
}

void Shininess( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	float Shinines = Render->GetActiveMaterial().GetShininess();
	memcpy( data, (void*)&Shinines, size );
}

void Ambient( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Ambient = Render->GetActiveMaterial().GetAmbient();
	memcpy( data, (void*) &Ambient, size );
}

void Diffuse( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Diffuse = Render->GetActiveMaterial().GetDiffuse();
	memcpy( data, (void*) &Diffuse, size );
}

void Specular( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Specular = Render->GetActiveMaterial().GetSpecular();
	memcpy( data, (void*) &Specular, size );
}

void LightRadius( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	float r = Render->GetActiveLight().GetRadius();
	memcpy( data, (void*) &r, size );
}

void LightPosition( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Position = Render->GetActiveLight().GetPosition();
	memcpy( data, (void*)&Position, size );
}

void LightAmbient( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Ambient = Render->GetActiveLight().GetAmbient();
	memcpy( data, (void*)&Ambient, size );
}

void LightDiffuse( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Diffuse = Render->GetActiveLight().GetDiffuse();
	memcpy( data, (void*) &Diffuse, size );
}

void LightSpecular( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 Specular = Render->GetActiveLight().GetSpecular();
	memcpy( data, (void*) &Specular, size );
}

void LightSpecularPower( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	float SpecularPower = Render->GetActiveLight().GetSpecularPower();
	memcpy( data, (void*) &SpecularPower, size );
}

void CameraPosition( void* data, uint size )
{
	Renderer *Render = Renderer::GetSingletonPtr();
	glm::vec3 CamPos = Render->GetActiveCameraPtr()->GetCameraPos();
	memcpy( data, (void*) &CamPos, size );
}