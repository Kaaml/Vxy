#pragma once

#include "Include.hpp"
#include "Material.hpp"


class MaterialManager : public Singleton <  MaterialManager >
{
private:
	std::map< std::string, Material* > mMaterials;
public:
	void LoadMaterialXML( std::string XmlFile );
	MaterialManager(void);
	~MaterialManager(void);
};

