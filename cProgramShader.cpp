#include "cProgramShader.hpp"


cProgramShader::cProgramShader(std::string name)
{
	if( name.compare( "NULL") )
	{
		h_Program = glCreateProgram();
	}else
	{
		h_Program = 0;
	}
	m_programName = name;
	m_linked = false;
	m_active = false;

}

void cProgramShader::AttachShader( cShader * shader)
{
	m_Shaders.push_back( shader );
	glAttachShader( h_Program, shader->GetShaderHandle() );
}

void cProgramShader::Link()
{
	glLinkProgram( h_Program );
	std::cerr << "INFO: Link shader: " << m_programName << std::endl;
	GLint Length;

	glGetProgramiv( h_Program, GL_LINK_STATUS, &Length );
	if( Length  != GL_TRUE )
	{
		glGetProgramiv( h_Program, GL_INFO_LOG_LENGTH, &Length );
		char * Log = new char[Length];
		glGetProgramInfoLog( h_Program, Length, 0, Log );
		std::cerr << Log <<std::endl;
		delete[] Log;
	}
	glValidateProgram( h_Program );
	GLint val;
	glGetProgramiv( h_Program, GL_VALIDATE_STATUS, &val );
	m_linked = true;
}

//bool cProgramShader::VertexAttribPointer( const char * name, GLuint size,  GLenum type, bool normalise, GLsizei stride, GLvoid* data )
//{
//	std::map<std::string, GLuint >::const_iterator attrib  = m_Attribs.find( name );
//
//	if( attrib != m_Attribs.end() )
//	{
//		glVertexAttribPointer( attrib->second, size, type, normalise, stride, data );
//		return true;
//	}else
//	{
//		return false;
//	}
//
//}

void cProgramShader::UpdateUniforms()
{
	for( const auto &i : mUniform )
	{
		i.second->SetDataFunc( cShaderManager::GetInstance()->GetUniformDataFunc( i.first ) );
		i.second->SetLocation( GetUniformLocation( i.first.c_str() ) );
	}
}

GLint cProgramShader::GetUniformLocation( const char* name )
{
	GLint  loc;
	loc = glGetUniformLocation( h_Program, name );
	//( loc == -1 )
		//std::cerr << "ERROR : Not found " << name << " uniform in program: " << m_programName <<std::endl;
	return loc;
}

void cProgramShader::BindAttrib(GLuint index, std::string attribName )
{
	if( m_linked != true )
	{
		 std::cerr<<"Warning binding attribute after link\n";
	}else
	{
		m_Attribs[ attribName ] = index;
		glBindAttribLocation( h_Program, index, attribName.c_str() );
		std::cerr << "INFO: BindAttribLocation : " << attribName << " in program " << m_programName << std::endl;
	}
}

void cProgramShader::Bind()
{
	glUseProgram( h_Program );
}

void cProgramShader::Unbind()
{
	glUseProgram( 0 );
}

void cProgramShader::EnableAttribArray( const char * name )
{
	glEnableVertexAttribArray( m_Attribs[ name ] );
}
void cProgramShader::DisableAttribArray( const char * name )
{
	glDisableVertexAttribArray( m_Attribs[ name ] );
}

void cProgramShader::AddUniform( Uniform * pUniform )
{
	mUniform.insert( std::pair< std::string, Uniform* >( pUniform->GetName(), pUniform ) );
}

void cProgramShader::SetUniform( std::string name, Type type, void * data )
{
	std::map< std::string, Uniform >::iterator it = mUniforms.find( name );
	if( it != mUniforms.end() )
	{
		//it->second.SetData(type, data );
		//it->second.SetUniform();
	}else
	{
		Uniform u;
		//u.SetData( type, data );
		int loc = GetUniformLocation( name.c_str() );
		if( loc == -1 )
			std::cerr << "ERROR: Nie znaleziono: " << name << " uniformu w shaderze: " << m_programName << std::endl;
		//u.SetLocation( loc );
		//u.SetUniform();
		//mUniforms.insert( std::pair<std::string, Uniform>( name, u));
	}

}

void cProgramShader::Update()
{
	for( auto &Uniform : mUniform )
	{
		Uniform.second->Update();
		//Uniform.second->Bind();
	}

}

cProgramShader::~cProgramShader(void)
{
	if( h_Program )
		glDeleteProgram( h_Program );
}
