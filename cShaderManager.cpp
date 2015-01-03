#include "cShaderManager.hpp"

cShaderManager* cShaderManager::pInstance = NULL;
const std::string cShaderManager::GetName( std::string Path )
{
	int slash = Path.find_last_of( '/' );
	int point = Path.find_last_of( '.' );
	if( slash != -1 )
	{
		return Path.substr( slash+1, point-(slash+1));
	}else
	{
		return Path.substr( 0, point );
	}
}

cShaderManager::cShaderManager(void)
{
	//m_ActiveProgram = NULL;
	m_Shaders.clear();
	
	//ptr na fuknkcje shaderow
	AddUniformDataFunc( "ModelMatrix", &ModelMatrix );
	AddUniformDataFunc( "ViewMatrix", &ViewMatrix );
	AddUniformDataFunc( "ModelViewMatrix", &ModelViewMatrix );
	AddUniformDataFunc( "ProjectionMatrix", &ProjectionMatrix );
	AddUniformDataFunc( "ModelViewProjection", &MVP );
	AddUniformDataFunc( "NormalMatrix", &NormalMatrix );
	AddUniformDataFunc( "Emission", &Emission );
	AddUniformDataFunc( "Shininess" , &Shininess );
	AddUniformDataFunc( "Ambient"   , &Ambient );
	AddUniformDataFunc( "Diffuse"  , &Diffuse );
	AddUniformDataFunc( "Specular" , &Specular );
	AddUniformDataFunc( "LightRadius"		, &LightRadius );
	AddUniformDataFunc( "Light.Position"	   , &LightPosition );
	AddUniformDataFunc( "Light.Color"	   , &LightAmbient );
	AddUniformDataFunc( "LightDiffuse"	   , &LightDiffuse );
	AddUniformDataFunc( "LightSpecular"	   , &LightSpecular );
	AddUniformDataFunc( "Light.SpecularExponent" , &LightSpecularPower );
	AddUniformDataFunc( "Light.SpotDirection", &LightSpotDirection );
	AddUniformDataFunc( "Light.SpotCutoff", &LightSpotCutoff );
	AddUniformDataFunc( "CameraPosition", &CameraPosition );
	AddUniformDataFunc( "ScreenSize", &ScreenResolution );

}

cShaderManager::~cShaderManager(void){}

cProgramShader* cShaderManager::CreateProgram( const std::string &ProgramName )
{
	cProgramShader* Program = new cProgramShader( ProgramName );
	m_Programs.insert( std::pair< std::string, cProgramShader * >( ProgramName, Program ) );
	return Program;
}

cShader* cShaderManager::CreateShader( const std::string &ShaderName, SHADERTYPE Type )
{
	cShader* Shader = new cShader( Type );
	m_Shaders.insert( std::pair< std::string, cShader*>( ShaderName, Shader ) );
	return Shader;
}

cShader* cShaderManager::CreateShader( const std::string &ShaderName, SHADERTYPE Type, const std::string &FileName )
{
	cShader *Shader = new cShader( Type );
	if( !Shader->LoadShader( FileName ) )
	{
		std::cerr << "ERROR: Shader " << ShaderName <<" nie mozna wczytac z pliku: " << FileName << std::endl;
	}else
	{
		if( !Shader->Compile() )
			std::cerr << "ERROR: Blad kompilacji shadera: " << ShaderName << std::endl;
	}
	m_Shaders.insert( std::pair< std::string, cShader*>( ShaderName, Shader ) );
	return Shader;
}

//void cShaderManager::SetActiveShader( std::string ProgramName )
//{
//	std::map< std::string, cProgramShader*>::const_iterator it = m_Programs.find( ProgramName );
//	if( it != m_Programs.end() )
//	{
//		m_ActiveProgram = it->second;
//	} else
//	{
//		m_ActiveProgram = NULL;
//		std::cerr << "ERROR: Not set active program" << std::endl;
//	}
//}

void cShaderManager::CreateProgramWithFile( const std::string ShaderName )
{
	std::fstream File;
	File.open( ShaderName, std::ios::in );
	if( !File.is_open() )
	{
		std::cerr << "ERROR: Blad wczytywania shaderow z pliku: " << ShaderName << std::endl;
		return;
	}
	std::string buffor;
	std::string name;
	std::vector< std::string > Shaders;
	//std::vector< std::string > Fragment;
	while( !File.eof() )
	{
		File >> buffor;
		switch (buffor[0])
		{
			case 'v':
				File >> buffor;
				name = GetName( buffor );
				Shaders.push_back( name );
				CreateShader( name, SHADERTYPE::VertexShader, buffor );
				break;
			case 'f':
				File >> buffor;
				name = GetName( buffor );
				Shaders.push_back( name );
				CreateShader( name, SHADERTYPE::FragmentShader, buffor );
				break;
		default:
			break;
		}
	}
	File.close();
	std::string ProgramName =  GetName( ShaderName );
	CreateProgram( ProgramName );
	cProgramShader* Program = GetProgram( ProgramName );
	for( unsigned i = 0; i < Shaders.size(); i++ )
	{
		Program->AttachShader( GetShader( Shaders[i] ) );
	}
	Program->Link();

}

void cShaderManager::LoadXmlFile( const std::string &Name )
{
	pugi::xml_document Doc;
	Doc.load_file( Name.c_str() );
	pugi::xml_node node = Doc.first_child();		// node wskazuje na shader <--
	std::string ShaderName;
	std::vector < cShader* > Shaders;
	std::map < std::string, Uniform* > Uniforms;
	if( !strcmp( node.name(), "shader" ) )
	{
		ShaderName = node.attribute( "name" ).as_string();
		cProgramShader * Program = nullptr;
		for( const auto &nodeShader : node.children() )		// dla kazdego wezla w "shader"
		{			
			if( !strcmp( nodeShader.name(), "source" )  )
			{
				for( const auto &SourceNode : nodeShader.children() )
				{
					std::string ShaderFile =  SourceNode.attribute( "file").as_string();
					if( !strcmp( SourceNode.name(), "vertex" ) )
					{					
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::VertexShader, ShaderFile ) );
					}else if( !strcmp( SourceNode.name(), "fragment" ) )
					{
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::FragmentShader, ShaderFile ) );
					}else if( !strcmp( SourceNode.name(), "geometry" ) )
					{
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::GeometryShader, ShaderFile ) );
					}else
					{
						std::cerr << "ERROR: Shader type: " << SourceNode.name() << " is not supported!" << std::endl;
					}
				}	// end for( const auto SourceNode : nodeShader.children() )

				/* **** Utworzenie shadera z shaderow ( vertex/fragment/geometry etc **** */
				Program = CreateProgram( ShaderName );
				for( const auto &i : Shaders )
				{
					i->Compile();				
					Program->AttachShader( i );
				}
				Program->Link();

			}else if( !strcmp( nodeShader.name(), "uniform" ) )
			{
				//wczytanie uniformow dla danego shadera				
				Type typ = Type::TVOID;
				if( !strcmp( nodeShader.attribute( "type" ).as_string(), "float" ) )
				{
					typ = TFLOAT;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "int" ) )
				{
					typ = TINT;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "vec2" ) )
				{
					typ = Type::VEC2;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "vec3" ) )
				{
					typ = Type::VEC3;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "vec4" ) )
				{
					typ = Type::VEC4;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "mat3" ) 
						|| !strcmp( nodeShader.attribute( "type" ).as_string(), "mat3x3" ) )
				{
					typ = Type::MAT3;
				}else if( !strcmp( nodeShader.attribute( "type" ).as_string(), "mat4" ) 
					|| !strcmp( nodeShader.attribute( "type" ).as_string(), "mat4x4" ) )
				{
					typ = Type::MAT4;
				}
					
				//Uniforms.insert( std::pair<std::string, Uniform*>( UniformName, uniform ) );
				std::string UniformName = nodeShader.attribute( "name" ).as_string();
				Uniform *uniform = new Uniform( typ, UniformName );	
				uniform->SetLocation( Program->GetUniformLocation( UniformName.c_str() ) );
				uniform->SetDataFunc( cShaderManager::GetInstance()->GetUniformDataFunc( UniformName ));
				Program->AddUniform( uniform );
			}
	
		}
	}
	

}

cProgramShader* cShaderManager::Parse( pugi::xml_node Node )
{
	std::string ShaderName;
	std::vector < cShader* > Shaders;
	std::map < std::string, Uniform* > Uniforms;
	if( !strcmp( Node.name(), "shader" ) )
	{
		ShaderName = Node.attribute( "name" ).as_string();
		cProgramShader * Program = nullptr;
		for( const auto &NodeShader : Node.children() )		// dla kazdego wezla w "shader"
		{			
			if( !strcmp( NodeShader.name(), "source" )  )
			{
				for( const auto &SourceNode : NodeShader.children() )
				{
					std::string ShaderFile =  SourceNode.attribute( "file").as_string();
					if( !strcmp( SourceNode.name(), "vertex" ) )
					{					
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::VertexShader, ShaderFile ) );
					}else if( !strcmp( SourceNode.name(), "fragment" ) )
					{
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::FragmentShader, ShaderFile ) );
					}else if( !strcmp( SourceNode.name(), "geometry" ) )
					{
						Shaders.push_back(
							CreateShader( GetName( ShaderFile), SHADERTYPE::GeometryShader, ShaderFile ) );
					}else
					{
						std::cerr << "ERROR: Shader type: " << SourceNode.name() << " is not supported!" << std::endl;
					}
				}	// end for( const auto SourceNode : NodeShader.children() )

				/* **** Utworzenie shadera(programu) z shaderow ( vertex/fragment/geometry etc **** */
				Program = CreateProgram( ShaderName );
				for( const auto &i : Shaders )
				{
					i->Compile();				
					Program->AttachShader( i );
				}
				Program->Link();

			}else if( !strcmp( NodeShader.name(), "uniform" ) )
			{
				//wczytanie uniformow dla danego shadera				
				Type typ = Type::TVOID;
				if( !strcmp( NodeShader.attribute( "type" ).as_string(), "float" ) )
				{
					typ = TFLOAT;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "int" ) )
				{
					typ = TINT;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "vec2" ) )
				{
					typ = Type::VEC2;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "vec3" ) )
				{
					typ = Type::VEC3;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "vec4" ) )
				{
					typ = Type::VEC4;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "mat3" ) 
						|| !strcmp( NodeShader.attribute( "type" ).as_string(), "mat3x3" ) )
				{
					typ = Type::MAT3;
				}else if( !strcmp( NodeShader.attribute( "type" ).as_string(), "mat4" ) 
					|| !strcmp( NodeShader.attribute( "type" ).as_string(), "mat4x4" ) )
				{
					typ = Type::MAT4;
				}
					
				//Uniforms.insert( std::pair<std::string, Uniform*>( UniformName, uniform ) );
				std::string UniformName = NodeShader.attribute( "name" ).as_string();
				Uniform *uniform = new Uniform( typ, UniformName );	
				uniform->SetLocation( Program->GetUniformLocation( UniformName.c_str() ) );
				uniform->SetDataFunc( cShaderManager::GetInstance()->GetUniformDataFunc( UniformName ));
				Program->AddUniform( uniform );
			}
	
		}
		return Program;
	}
	// jeœli wezel nie wskazuje na shadery
	return nullptr;
}

//void cShaderManager::AttachShaderToActive( std::string ShaderName )
//{
//	if( !m_ActiveProgram )
//		std::cerr << "ERROR: Ative shader isn't set" << std::endl;
//	}else
//	{
//		std::map< std::string, cShader*>::const_iterator it = m_Shaders.find( ShaderName );
//		if( it!= m_Shaders.end() )
//		{
//			m_ActiveProgram->AttachShader( it->second );
//		}else
//		{
//			std::cerr << "ERROR: Not found shader: " << ShaderName << std::endl;
//		}
//
//	}
//}

void cShaderManager::AddUniformDataFunc( const std::string &UniformName, DataFunc pDataFunc )
{
	mUniformDataFunc.insert(
		std::pair< std::string, DataFunc >( UniformName, pDataFunc ) );
}

DataFunc cShaderManager::GetUniformDataFunc( const std::string &UniformName )
{
	std::map< std::string, DataFunc >::const_iterator it = mUniformDataFunc.find( UniformName );
	if( it != mUniformDataFunc.end() )
	{
		return it->second;
	}else
	{
		std::cerr << "ERROR: Nie znaleziono funkcji: " << UniformName << std::endl;
		return nullptr;
	}
}

void cShaderManager::Use( const std::string &ProgramName )
{
	std::map< std::string, cProgramShader*>::const_iterator it = m_Programs.find( ProgramName );
	if( it != m_Programs.end() )
	{
		it->second->Bind();
		//m_ActiveProgram = it->second ;
	}else
	{
		std::cerr << "ERROR: Not find program: " << ProgramName << std::endl;
	}
}

void cShaderManager::UnUse( )
{
	//m_ActiveProgram = NULL;
	glUseProgram( 0 );
}
cProgramShader* cShaderManager::operator[]( const std::string &ProgramName ) 
{
	std::string name( ProgramName );
	std::map< std::string, cProgramShader*>::const_iterator it = m_Programs.find( name );
	if( it != m_Programs.end() )
	{
		return it->second;
	}else
	{
		std::cerr << "ERROR: Not find program: " << ProgramName << std::endl;
		return NULL;
	}
}


cShader* cShaderManager::GetShader( const std::string &ShaderName )
{
	std::map< std::string, cShader*>::const_iterator it = m_Shaders.find( ShaderName );
	if( it!= m_Shaders.end() )
	{
		return it->second;
	}else
	{
		//std::cerr << "ERROR: Not found shader: " << ShaderName << std::endl;
		return nullptr;
	}
}
cProgramShader* cShaderManager::GetProgram( const std::string &ProgramName )
{
	std::map< std::string, cProgramShader*>::const_iterator it = m_Programs.find( ProgramName );
	if( it!= m_Programs.end() )
	{
		return it->second;
	}else
	{
		//std::cerr << "ERROR: Not found program: " << ProgramName << std::endl;
		return nullptr;
	}
}

cShaderManager *MainShaderManager = cShaderManager::GetInstance();