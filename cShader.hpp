#pragma once
#ifndef CSHADER_HPP
#define CSHADER_HPP

#include "Include.hpp"

enum SHADERTYPE{ VertexShader = GL_VERTEX_SHADER, GeometryShader = GL_GEOMETRY_SHADER, TesslationShader = GL_TESS_CONTROL_SHADER, FragmentShader = GL_FRAGMENT_SHADER};

class cShader
{
public:
	cShader(void);
	cShader( SHADERTYPE Type );	
	bool LoadShader( const std::string &File );
	bool Compile();
	void SetType( SHADERTYPE type );
	GLuint GetShaderHandle() const { 
		return hShader; 
	};

	~cShader(void);
private:
	std::string m_source;
	SHADERTYPE m_shaderType;
	bool m_compiled;
	GLuint hShader;
};

#endif