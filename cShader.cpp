#include "cShader.hpp"


cShader::cShader(void){}

cShader::cShader( SHADERTYPE Type )
{
	m_shaderType = Type;
	m_compiled = false;
}

bool cShader::LoadShader( const std::string &File )
{
	hShader = glCreateShader( m_shaderType );
	std::ifstream ifile;
	ifile.open( File.c_str(), std::ios::binary );
	if( ifile.is_open() )
	{
		ifile.seekg( 0, std::ios::end );
		int length = (int) ifile.tellg();
		ifile.seekg( 0, std::ios::beg );
		char * buffor = new char[length * sizeof(char)+1];
		ifile.read( buffor, length );
		buffor[length] = '\0';
		//std::cout << buffor <<std::endl;
		m_source = buffor ;
		delete [] buffor;
		ifile.close();

	}else
	{
		return false;
		std::cerr << "ERROR: Nie mozna otworzyc pliku: " << File <<std::endl;
	}
	const char *data = m_source.c_str();
	
	glShaderSource( hShader, 1, &data, NULL );
	return true;	
}

bool cShader::Compile()
{
	if( m_source.size() !=0 )
	{
		glCompileShader( hShader );
		GLint Status;
		glGetShaderiv( hShader, GL_COMPILE_STATUS, &Status );
		if( Status == GL_FALSE )
		{
			GLint length;		
			glGetShaderiv( hShader, GL_INFO_LOG_LENGTH, &length );
			char *log = new char[ length ];
			glGetShaderInfoLog( hShader, length, NULL, log );
			std::cerr << log << "\n";
			delete[] log;
			return false;
		}
		//std::cerr << "Shader: "<</* m_name <<*/ " zostal skompilowany\n"; 
		m_compiled = true;
		return true;
	}else
	{
		std::cerr << "ERROR: Shader: "<< /*m_name <<*/ "nie posiada kodu zrodlowego\n";
		return false;
	}
}

//void cShader::SetName( std::string Name ){	m_name = Name;}

void cShader::SetType( SHADERTYPE Type )
{
	m_shaderType = Type;
}

cShader::~cShader(void)
{
	if( hShader )
	{
		glDeleteShader( hShader );
		hShader = 0 ;
	}
}
