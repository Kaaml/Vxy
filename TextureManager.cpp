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
		std::cout << "ERROR: Texture: " << Name << " not fount!\n";
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

void TextureManager::Parse( const pugi::xml_node &Node )
{
	std::string TexPath = Node.attribute( "file" ).as_string();
	std::string TexName = Node.attribute( "name" ).as_string();
	if( TexPath.length() == 0 )
	{
		//tworz teksture bez wczytywania z obrazka;	
		int width = Node.attribute( "width" ).as_uint();
		int height = Node.attribute( "height" ).as_uint();
		int mipmap = Node.attribute( "mipmap" ).as_uint();
		auto Format = Node.attribute( "format" ).as_string();
		FORMAT FormatEnum;
		if( !strcmp( Format, "RGBA" ) )
		{
			FormatEnum = FORMAT::RGBA;
		} else if( !strcmp( Format, "RGB" ) )
		{
			FormatEnum = FORMAT::RGB;
		} else if( !strcmp( Format, "RGB8" ) )
		{
			FormatEnum = FORMAT::RGB8;
		} else if( !strcmp( Format, "RGB16" ) )
		{
			FormatEnum = FORMAT::RGB16;
		} else if( !strcmp( Format, "RGB16F" ) )
		{
			FormatEnum = FORMAT::RGB16F;
		} else if( !strcmp( Format, "RGB32I" ) )
		{
			FormatEnum = FORMAT::RGB32I;
		} else if( !strcmp( Format, "RGB32F" ) )
		{
			FormatEnum = FORMAT::RGB32F;
		} else if( !strcmp( Format, "RGBA32F" ) )
		{
			FormatEnum = FORMAT::RGBA32F;
		} else if( !strcmp( Format, "DEPTH" ) )
		{
			FormatEnum = FORMAT::DEPTH;
		} else if( !strcmp( Format, "DEPTH24" ) )
		{
			FormatEnum = FORMAT::DEPTH24;
		} else if( !strcmp( Format, "DEPTH32F" ) )
		{
			FormatEnum = FORMAT::DEPTH32F;
		}
		else if( !strcmp( Format, "DEPTH_STENCIL" ) )
		{
			FormatEnum = FORMAT::DEPTH_STENCIL;
		}
		else if( !strcmp( Format, "DEPTH_STENCIL32" ) )
		{
			FormatEnum = FORMAT::DEPTH_STENCIL32;
		}
		else
		{
			FormatEnum = FORMAT::RGB;
		}
		
		Texture2D *Text = new Texture2D( width, height, mipmap, FormatEnum );
		mTextures.insert( std::make_pair( TexName, Text ) );
	} else
	{
		this->LoadTexture( TexName, TexPath );
	}
	
}