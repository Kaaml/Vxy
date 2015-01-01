#pragma once
#include "Include.hpp"
#include "Surface.hpp"
class Node
{
private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::quat mQuatRotation;
	glm::vec3 mRotation;
	glm::mat4 mLocalMatrix;
	glm::mat4 mWorldMatrix;

	std::map< std::string, Node* > mChildrens;				//children node
	Node *mParent;											// parent node; for root node nullptr	

	std::vector< Surface* > mSurfaces;

public:
	Node(void);
	void Render();
	void RotateX( float angle );
	void RotateY( float angle );
	void RotateZ( float angle );
	void Move( float x, float y, float z );
	void Move( glm::vec3 Dir );
	void Scale( float x, float y, float z );
	void Scale( glm::vec3 Scale );
	void CalculateTransformation();
	void CalculateLocalMatrix();
	void CalculateWorldMatrix();

	void AddChild( Node* pNode );

	//get methods
	inline glm::mat4& GetLocalTransformation();
	inline glm::mat4& GetWorldTransformation();
	
	virtual ~Node(void);
};

inline glm::mat4 & Node::GetWorldTransformation()
{
	return mWorldMatrix;
}
inline glm::mat4 & Node::GetLocalTransformation()
{
	return mLocalMatrix;
}