#include "Material.hpp"


Material::Material(void)
{
	mShininess = 16.f;
	mEmission = glm::vec3( 1.f );
	mAmbient = glm::vec3( 0.5f );
	mDiffuse = glm::vec3( 0.5f );
	mSpecular = glm::vec3( 0.1f );
}

void Material::SetShaderName( const std::string &ShaderName )
{
	mShaderName = ShaderName;
};

void Material::SetEmission( const glm::vec3 &Emission )
{
	mEmission = Emission;
};
void Material::SetAmbient( const glm::vec3 &Ambient )
{
	mAmbient = Ambient;
};
void Material::SetDiffuse( const glm::vec3 &Diffuse )
{
	mDiffuse = Diffuse;
};
void Material::SetSpecular( const glm::vec3 &Specular )
{
	mSpecular = Specular;
};
void Material::Setshininess( const float &Shininess )
{
	mShininess = Shininess;
};

const cProgramShader* Material::GetShaderPtr()
{
	return cShaderManager::GetInstance()->GetProgram( mShaderName );
}

void Material::Bind()
{
	pRenderPass->Bind();	
	pRenderPass->Update();
	
	//cShaderManager::GetInstance()->GetProgram( mShaderName )->Update();
	//cShaderManager::GetInstance()->Use( mShaderName );	
}

void Material::Parse( pugi::xml_node Node )
{
	//Node -> <material name="Nazwa_Mat" >
	for( const auto &Child : Node.children() )
	{
		if( !strcmp( Child.name(), "pass" ) )
		{
			// tworz nowy pass
			RenderPass *Pass = new RenderPass();
			Pass->Parse( Child );
			pRenderPass = Pass;
		}
	}


}

void Material::AddRenderPass( RenderPass *pPass )
{
	pRenderPass = pPass;
}

Material::~Material(void)
{
}
