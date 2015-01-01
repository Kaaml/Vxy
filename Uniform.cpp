#include "Uniform.hpp"


Uniform::Uniform(void)
	:mType( TVOID), mData( nullptr ), mSize( 0 )
{
}

Uniform::Uniform( Type type, const std::string &Name, bool dynamic )
	:mType( type )
{
	mName = Name;
	mDynamic = dynamic;
	switch ( type)
	{
	case TVOID:
		mSize = 0;
		break;
	case TINT:
		mData = new int();
		mSize = sizeof( int );
		break;
	case TFLOAT:
		mData = new float();
		mSize = sizeof( float );
		break;
	case TDOUBLE:
		mData = new double();
		mSize = sizeof( float );
		break;
	case VEC2:
		mData = new glm::vec2();
		mSize = sizeof( glm::vec2 );
		break;
	case VEC3:
		mData = new glm::vec3();
		mSize = sizeof( glm::vec3 );
		break;
	case VEC4:
		mData = new glm::vec4();
		mSize = sizeof( glm::vec4 );
		break;
	case MAT3:
		mData = new glm::mat3();
		mSize = sizeof( glm::mat3 );
		break;
	case MAT4:
		mData = new glm::mat4();
		mSize = sizeof( glm::mat4 );
		break;
	default:
		std::cerr << "Error: Undefined type of Uniform: " << mName << std::endl;
		break;
	}
	
}
Uniform::Uniform( Type type, const std::string &Name, uint location, uint data_size, void *pData, bool dynamic )
	:mType( type ),
	mSize( data_size ),
	mName( Name )
{
	mDynamic = dynamic;
	memcpy( pDefaultData, pData, data_size );
	memcpy( mData, pData, data_size );
}

Uniform::Uniform( Type type, const std::string &Name, uint location, std::function< void( void*, uint )> Func, bool dynamic)
{
	mName = Name;
	switch( type )
	{
	case TVOID:
		mSize = 0;
		break;
	case TINT:
		mData = new int();
		pDefaultData = new int();
		mSize = sizeof( int );
		break;
	case TFLOAT:
		mData = new float();
		pDefaultData = new float();
		mSize = sizeof( float );
		break;
	case TDOUBLE:
		mData = new double();
		pDefaultData = new double();
		mSize = sizeof( double );
		break;
	case VEC2:
		mData = new glm::vec2();
		pDefaultData = new glm::vec2();
		mSize = sizeof( glm::vec2 );
		break;
	case VEC3:
		mData = new glm::vec3();
		pDefaultData = new glm::vec3();
		mSize = sizeof( glm::vec3 );
		break;
	case VEC4:
		mData = new glm::vec4();
		pDefaultData = new glm::vec4();
		mSize = sizeof( glm::vec4 );
		break;
	case MAT3:
		mData = new glm::mat3();
		pDefaultData = new glm::mat3();
		mSize = sizeof( glm::mat3 );
		break;
	case MAT4:
		mData = new glm::mat4();
		pDefaultData = new glm::mat4();
		mSize = sizeof( glm::mat4 );
		break;
	default:
		std::cerr << "Error: Undefined type of Uniform: " << mName << std::endl;
		break;
	}
	fGetData = Func;
	mLocation = location;
	mDynamic = dynamic;
}

void Uniform::SetLocation( int loc )
{
	mLocation = loc;
}

void Uniform::SetUniform()
{
	if( mDynamic )
	{
		switch (mType)
		{
		case TINT:
			glUniform1iv( mLocation, 1, (int*)mData );
			break;
		case TFLOAT:
			glUniform1fv( mLocation, 1, (float*)mData );
			break;
		case TDOUBLE:
			glUniform1dv( mLocation, 1, (double*)mData );
			break;
		case VEC2:
			glUniform2fv( mLocation, 1, (float*)mData );
			break;
		case VEC3:
			glUniform3fv( mLocation, 1, (float*)mData );
			break;
		case VEC4:
			glUniform4fv( mLocation, 1, (float*)mData );
			break;
		case MAT3:
			glUniformMatrix3fv( mLocation, 1, GL_FALSE, (float*)mData );
			break;
		case MAT4:
			glUniformMatrix4fv( mLocation, 1, GL_FALSE, (float*)mData );
			break;
		default:
			break;
		}
	}else
	{
		switch (mType)
		{
		case TINT:
			glUniform1iv( mLocation, 1, (int*)pDefaultData );
			break;
		case TFLOAT:
			glUniform1fv( mLocation, 1, (float*)pDefaultData );
			break;
		case TDOUBLE:
			glUniform1dv( mLocation, 1, (double*)pDefaultData );
			break;
		case VEC2:
			glUniform2fv( mLocation, 1, (float*)pDefaultData );
			break;
		case VEC3:
			glUniform3fv( mLocation, 1, (float*)pDefaultData );
			break;
		case VEC4:
			glUniform4fv( mLocation, 1, (float*)pDefaultData );
			break;
		case MAT3:
			glUniformMatrix3fv( mLocation, 1, GL_FALSE, (float*)pDefaultData );
			break;
		case MAT4:
			glUniformMatrix4fv( mLocation, 1, GL_FALSE, (float*)pDefaultData );
			break;
		default:
			break;
		}
	}
}

void Uniform::Update()
{
	if( mDynamic )
	{
		if( fGetData && mSize )
		{
			fGetData( mData, mSize );
		}
	}
	SetUniform();
	
}

void Uniform::SetDataFunc( std::function< void( void*, uint )> Func )
{
	fGetData = Func;
}

Uniform::~Uniform(void)
{
	delete mData;
	delete pDefaultData;
}
