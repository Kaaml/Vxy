#pragma once

#include "Include.hpp"
#include "cShader.hpp"
#include "Uniform.hpp"
#include "cShaderManager.hpp"
#include <glm/ext.hpp>

class cProgramShader
{
public:
	cProgramShader( void );
	cProgramShader( std::string name );
	void Link();
	void Bind();
	void Unbind();
	void Update();
	void AttachShader( cShader* shader );
	void BindAttrib(GLuint index, std::string attribName );
	void SetUniform( std::string name, Type type, void *data );
	void AddUniform( Uniform *Uniform );
	void UpdateUniforms();
	//void SetUniformMatrix( const char * name, )
	GLuint GetID() const {
		return h_Program;
	};
	GLint GetUniformLocation( const char* name );
	void EnableAttribArray( const char * name );
	void DisableAttribArray(const char * );		
	~cProgramShader(void);
private:
	bool m_linked;
	std::vector < cShader* > m_Shaders;
	GLuint h_Program;
	std::string m_programName;
	bool m_active;
	std::map < std::string, GLuint > m_Attribs;
	std::map < std::string, Uniform > mUniforms;
	std::map < std::string, Uniform* > mUniform;
	
};

// Program.SetUniform( typ, void * data );


// PROGRAM UPDATE
// cos for uniform in mUniforms.Update();