#include "Transform.hpp"


Transform::Transform(void)
{
	mTranslate = glm::vec3( 0.0f );
	mScale = glm::vec3( 1.f );
	mLocalMatrix = glm::mat4( 1.0f );
	mWorldMatrix = glm::mat4( 1.0f );
	parent = nullptr;
}

Transform::~Transform(void)
{
}

Transform* Transform::Parent()
{
	return parent;
}

void Transform::SetParent( Transform* Parent )
{
	parent = Parent;
}
const glm::mat4& Transform::GetLocalMatrix()
{
	mLocalMatrix = glm::translate( mTranslate ) * glm::scale( mScale );
	return mLocalMatrix;
}
void Transform::Translate( float x, float y, float z )
{
	//SetLocalMatrix( glm::translate( x, y, z ) * GetLocalMatrix() );
	mTranslate = glm::vec3( x, y, z );
}

void Transform::Translate( glm::vec3 t )
{
	//SetLocalMatrix( glm::translate( t ) * GetLocalMatrix() );
	mTranslate = t;
}

void Transform::Rotate( float angle, float x, float y, float z )
{
	SetLocalMatrix( glm::rotate( angle, x, y, z ) * GetLocalMatrix() );
}

void Transform::Rotate( float angle, glm::vec3 axis )
{
	SetLocalMatrix( glm::rotate( angle, axis ) * GetLocalMatrix() );
}

void Transform::Scale( float x, float y, float z )
{
	//SetLocalMatrix( glm::scale( x, y, z ) * GetLocalMatrix() );
	mScale = glm::vec3( x, y, z );
}

void Transform::Scale( glm::vec3 Scale )
{
	mScale = Scale;
	//SetLocalMatrix( glm::scale( Scale ) * GetLocalMatrix() );
}

void Transform::PreMultiply( const glm::mat4 &m )
{
	SetLocalMatrix( m * GetLocalMatrix() );
}

void Transform::PostMultiply( const glm::mat4 &m )
{
	SetLocalMatrix( GetLocalMatrix() * m );
}

void Transform::SetWorldMatrix( const glm::mat4 &m )
{
	mWorldMatrix = m;
}

const glm::mat4& Transform::GetWordlMatrix()
{
	return mWorldMatrix;
}

void Transform::CalculateWordlMatrix()
{
	if( parent )
	{
		SetWorldMatrix( parent->GetWordlMatrix() * GetLocalMatrix() );
	}else
	{
		mWorldMatrix = GetLocalMatrix();
	}
}

glm::mat4 Transform::GetComputedMatrix()
{
	glm::mat4 World = GetLocalMatrix();
	Transform *par = parent;

	while ( par )
	{
		World = parent->GetLocalMatrix() * World;
		par = par->Parent();
	}
	return World;
}