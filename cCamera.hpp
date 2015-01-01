#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Renderer.hpp"
#include "Include.hpp"

class cCamera
{
public:
	cCamera(void);
	// inicjalizuje kamere perspektywiczn¹
	void InitPerspectiv( float Width, float Height, float fov = 45.f,
		float Near = 0.01f, float Far = 10000.f );
	// inicjuje kamere ortogonalna 
	void InitOrtogonal( float Width, float Height);
	~cCamera(void);
	glm::mat4 GetVPmatrix();
	void Move( glm::vec3 delta );
	void AddToYaw( float angle );
	void AddToPitch( float angle );
	void AddToRoll( float angle );
	glm::mat3 GetNormalMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetCameraPos();
	void Update();

private:
	glm::mat4 Projection;
	glm::mat4 View;
	glm::vec3 PositionCamera;
	// obroty w radianach
	float Yaw;
	float Pitch;
	float Roll;

};