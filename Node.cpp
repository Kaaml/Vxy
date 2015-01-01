#include "Node.hpp"


Node::Node(void)
{
	mPosition = glm::vec3( 0.f );
	mScale = glm::vec3( 1.f );
	mRotation = glm::vec3( 0.f );
	mQuatRotation = glm::quat( mRotation );
	mLocalMatrix = glm::mat4( 1.f );
	mWorldMatrix = glm::mat4( 1.f );
}

void Node::RotateX( float angle )
{
	mRotation.x = angle;
}

void Node::RotateY( float angle )
{
	mRotation.y = angle;
}

void Node::RotateZ( float angle )
{
	mRotation.z = angle;
}

void Node::Move( glm::vec3 Dir )
{
	mPosition+= Dir;
}
void Node::Move( float x, float y, float z )
{
	mPosition+= glm::vec3( x, y, z );
}

void Node::Scale( float x, float y, float z )
{
	mScale = glm::vec3( x, y, z );
}
void Node::Scale( glm::vec3 Scale )
{
	mScale = Scale;
}

void Node::CalculateLocalMatrix()
{
	mLocalMatrix = glm::mat4( 1.f );
	mLocalMatrix = glm::scale( glm::mat4(1.f), mScale );
	mLocalMatrix = glm::rotate( mLocalMatrix, mRotation.y, glm::vec3( -1.f, 0.f, 0.f )); 
	mLocalMatrix = glm::rotate( mLocalMatrix, mRotation.x, glm::vec3( 0.f, 1.f, 0.f )); 
	mLocalMatrix = glm::rotate( mLocalMatrix, mRotation.z, glm::vec3( 0.f, 0.f, 1.f )); 
	mLocalMatrix = glm::translate( mLocalMatrix, mPosition );
}

void Node::AddChild( Node* pNode )
{
	mChildrens.insert( std::make_pair( "nazwa", pNode ) );
}

void Node::CalculateWorldMatrix()
{
	if( mParent )
	{
		mWorldMatrix = mParent->GetWorldTransformation();
	}else
	{
		mWorldMatrix = glm::mat4( 1.f );
	}
}


void Node::Render()
{
	/*for( auto *i : mSurfaces )
	{
		i->Render();
	}
*/
	for( auto it = mSurfaces.begin(); it != mSurfaces.end(); it++ )
	{
		(*it)->Render();
	}
}

Node::~Node(void)
{
}
