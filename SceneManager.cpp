#include "SceneManager.hpp"


SceneManager::SceneManager(void)
{
}

cMesh3d* SceneManager::LoadWaveFrontOBJ( const std::string &FileName )
{
	std::fstream File( FileName.c_str(), std::ios::binary | std::ios::out );
	if( !File.is_open() )
	{
		std::cerr << "ERROR: Nie znaleziono pliku: " << FileName << std::endl;
		return nullptr;
	}
	std::string line;
	while ( File.eof() )
	{
		std::getline( File, line );
		
	}
	return NULL;

}



SceneManager::~SceneManager(void)
{
}
