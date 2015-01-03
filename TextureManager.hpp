#pragma once
#include "Include.hpp"
#include "Singleton.hpp"
#include "Texture2D.hpp"


class TextureManager :
	public Singleton<TextureManager>
{
public:
	Texture2D* GetTexturePtr( const std::string &Name );
	Texture2D& GetTexture( const std::string &Name );
	void LoadTexture( const std::string &Name, const std::string &Path );
	void CreateTexture( uint width, uint height, uint mipmaplvl, FORMAT format, const std::string &name );
	void Parse( const pugi::xml_node &Node );
	TextureManager(void);
	~TextureManager(void);

private:
	std::map< std::string, Texture2D* > mTextures;
};

