#include "TextureManager.hpp"

std::string GetName( std::string Path )
{
	std::string name = Path;
	int slash = name.find_last_of( '/' );
	int point = name.find_last_of( '.' );
	if( slash != -1 )
	{
		return name.substr( slash+1, point-(slash+1));
	}else
	{
		return name.substr( 0, point );
	}
}
TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

Texture2D* TextureManager::GetTexturePtr( const std::string &Name )
{
	std::map< std::string, Texture2D* >::iterator it = mTextures.find( Name );
	if( it != mTextures.end() )
	{
		return it->second ;
	}else
	{
		//wywal null pointer albo texture zerowa
		return nullptr;
	}
}

Texture2D& TextureManager::GetTexture( const std::string &Name )
{

	std::map< std::string, Texture2D* >::iterator it = mTextures.find( Name );
	if( it != mTextures.end() )
	{
		return *it->second;
	}else
	{
		// waywalic informacje
		return Texture2D();
	}
}

void TextureManager::LoadTexture( const std::string &Name, const std::string &Path )
{
	Texture2D* txt = new Texture2D( Path );
	mTextures.insert( std::pair< std::string, Texture2D* >(  Name, txt ) );

}

void TextureManager::CreateTexture( uint width, uint height, uint mipmaplvl, FORMAT format, const std::string &name )
{
	Texture2D *txt = new Texture2D( width, height, mipmaplvl, format );
	mTextures.insert( std::make_pair( name, txt ) );
}

void TextureManager::Parse( pugi::xml_node &Node )
{
	std::string TexPath = Node.attribute( "file" ).as_string();
	std::string TexName = Node.attribute( "name" ).as_string();
	Texture2D *Tex = new Texture2D( TexPath );
	mTextures.insert( std::pair< std::string, Texture2D* >( TexName, Tex ) );
}