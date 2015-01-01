#pragma once
#ifndef CSHADERMANAGER_HPP
#define CSHADERMANAGER_HPP

#include "Include.hpp"
#include "cProgramShader.hpp"
#include "ShaderFunc.hpp"

#define ShaderManager (*MainShaderManager)

class cShaderManager
{
public:

	//###############  SINGLETON  ################
	static cShaderManager* GetInstance()
	{
		if( !pInstance )
		{
			pInstance = new cShaderManager();
			std::cout << "Crate class ShaderManager\n";
		}
		return pInstance;
	}
	cProgramShader* CreateProgram( const std::string &ProgramName );
	cShader* CreateShader( const std::string &ShaderName, SHADERTYPE Type );
	cShader* CreateShader( const std::string &ShaderName, SHADERTYPE Type, const std::string &FileName );
	//void SetActiveShader( std::string ProgramName );
	void AttachShaderToActive( std::string ShaderName );
	// laduje plik *.shad, w nim sa linijki [v][f][g] (vertex)(fragment)(geomatry)[nazwaPliku.shad], NazwaPliku sluzy jako nazwa programu.
	void CreateProgramWithFile( const std::string FileName );
	// ladowanie shadera z pliku XML 
	void LoadXmlFile( const std::string &Name );
	// laduje pliki z materialu od <shader>
	cProgramShader* Parse( pugi::xml_node Node );
	// ########### Return pointer to active program ##############
	void AddUniformDataFunc( const std::string &UniformName, DataFunc pDataFunc );
	// function return pointer to function to get uniform data
	DataFunc GetUniformDataFunc( const std::string &UniformName );
	void Use( const std::string &ProgramName );
	void UnUse();
	cShader* GetShader( const std::string &ShaderName );
	cProgramShader* GetProgram( const std::string &ProgramName );
	cProgramShader* operator[]( const std::string &ProgramName );
	
private:
	const std::string GetName( std::string Path );
	cShaderManager(void);
	~cShaderManager(void);
	static cShaderManager *pInstance;
	// ###### NAZWA ##### SHADER PROGRAM #######
	std::map< std::string, cProgramShader* > m_Programs;
	// ###### NAZWA ##### SHADER  #######
	std::map< std::string, cShader* > m_Shaders;

	std::map< std::string, DataFunc > mUniformDataFunc;

	//cProgramShader* m_ActiveProgram;
};

#endif