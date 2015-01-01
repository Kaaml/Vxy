#pragma once
#include "Singleton.hpp"
#include "Include.hpp"
#include "cMesh3d.hpp"
#include "Node.hpp"


class Loader
{
	Loader();
	virtual void Load( std::string Name ) = 0;
	virtual std::vector< Surface*>& GetSurfaces() = 0;
	virtual ~Loader();
};

class SceneManager : public Singleton<SceneManager>
{
private:
	Node *pRoot;
	std::map< std::string, Node > mNodes;
public:
	SceneManager(void);
	template< class T >
	Node* CreateNode( std::string file );
	~SceneManager(void);

	cMesh3d* LoadWaveFrontOBJ( const std::string &FileName );
};


template< class T >
Node* CreateNode( std::string file )
{
	T::Load( file );
	std::vector< Surface*> T::GetSurfaces();
}