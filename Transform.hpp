#pragma once
#define GLM_FORCE_CXX11
#include <glm\glm.hpp>
#include <glm\ext.hpp>

class Transform
{
public:
	Transform(void);
	~Transform(void);
	void SetLocalMatrix( const glm::mat4 &m )
	{
		mLocalMatrix = m;
	};
	void Translate( float x, float y, float z );
	void Translate( glm::vec3 t );
	void Rotate( float angle, float x, float y, float z );
	// Obraca o angle wokó³ osi wyznaczonej przez x,y,z
	void Rotate( float angle, glm::vec3 axis );

	void Scale( float x, float y, float z );
	void Scale( glm::vec3 Scale );
	void PreMultiply( const glm::mat4 &m );
	void PostMultiply( const glm::mat4 &m );
	const glm::mat4& GetLocalMatrix();
	void SetWorldMatrix( const glm::mat4 &m );
	const glm::mat4& GetWordlMatrix();
	void CalculateWordlMatrix();
	Transform* Parent();
	void SetParent( Transform* Parent );
	//zwraca "rodzica"
	glm::mat4 GetComputedMatrix();
	//liczy macierz ( uwzgledniajac wszystkie nadrzedne transformacje
private:
	glm::mat4 mLocalMatrix;
	glm::mat4 mWorldMatrix;
	// World mat4 po uwzglednieniu przeksztalcen z wyzszego 
	glm::vec3 mTranslate;
	glm::vec3 mScale;
	Transform *parent;
	//nadrzedna transformacja

};

