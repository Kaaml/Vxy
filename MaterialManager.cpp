#include "MaterialManager.hpp"

MaterialManager *MaterialManage = new MaterialManager();
MaterialManager::MaterialManager(void)
{
}

void MaterialManager::LoadMaterialXML( std::string XmlFile )
{
	pugi::xml_document Doc;
	Doc.load_file( XmlFile.c_str() );
	pugi::xml_node root = Doc.first_child();
	if( !strcmp( root.name(), "materials" ) )
	{
		//pugi::xml_node Child = root.first_child();
		for( const auto &Child : root.children() )
		{
			if( !strcmp( Child.name(), "texture" ) )
			{
				//TO DO: ladowanie textury
				std::string TexName = Child.attribute( "name" ).as_string();
				std::string TexFile = Child.attribute( "file" ).as_string();
				TextureManager *TexMgr = TextureManager::GetSingletonPtr();
				TexMgr->LoadTexture( TexName, TexFile );
			}else if( !strcmp( Child.name(), "material" ) )
			{
				//ladowanie material�w
				std::string MaterialName = Child.attribute( "name").as_string();
				Material *Mat = new Material();
				Mat->Parse( Child );
				mMaterials.insert(
					std::make_pair( MaterialName, Mat ) );
			}
		}

	}


}

MaterialManager::~MaterialManager(void)
{
}