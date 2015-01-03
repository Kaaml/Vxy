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
				////TO DO: ladowanie textury
				//std::string TexName = Child.attribute( "name" ).as_string();
				//std::string TexFile = Child.attribute( "file" ).as_string();
				TextureManager *TexMgr = TextureManager::GetSingletonPtr();	
				TexMgr->Parse( Child );
				//
				//{
				//	TexMgr->LoadTexture( TexName, TexFile );
				//}
				

			}else if( !strcmp( Child.name(), "material" ) )
			{
				//ladowanie materialów
				std::string MaterialName = Child.attribute( "name").as_string();
				Material *Mat = new Material();
				Mat->Parse( Child );
				mMaterials.insert( std::make_pair( MaterialName, Mat ) );
			}
		}

	}


}
Material* MaterialManager::GetMaterialPtr( const std::string &MatName )
{
	auto ItMaterial = mMaterials.find( MatName );
	if( ItMaterial != mMaterials.end() )
	{
		return ItMaterial->second;
	}
	else
	{
		std::cerr << "ERROR: MaterialManager( Nie znaleziono materialu < " << MatName << ".\n";
		return nullptr;
	}
}

Material& MaterialManager::GetMaterial( const std::string &MatName )
{
	auto ItMaterial = mMaterials.find( MatName );
	if( ItMaterial != mMaterials.end( ) )
	{
		return *ItMaterial->second;
	}
	else
	{
		std::cerr << "ERROR: MaterialManager( Nie znaleziono materialu < " << MatName << ".\n";
		return *mMaterials["default"];
	}	
}

MaterialManager::~MaterialManager(void)
{

}