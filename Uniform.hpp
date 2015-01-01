#pragma once

#include "Include.hpp"
#include <gl/glew.h>
#include <glm/glm.hpp>

enum Type
{
	 TVOID, TINT, TFLOAT, TDOUBLE, VEC2, VEC3, VEC4, MAT3, MAT4
};

typedef std::function< void (void*, uint) > DataFunc;
class Uniform
{
public:
	Uniform(void);
	Uniform( Type type, const std::string &Name, bool dynamic = true );
	Uniform( Type type, const std::string &Name, uint location, std::function< void( void*, uint )> Func, bool dynamic = true );
	Uniform( Type type, const std::string &Name, uint location, uint data_size, void *pData, bool dynamic = false );
	void SetLocation( int loc );	
	// The function update the value of uniform and sets her in shader
	void Update();
	// set pointer to function GetData 
	void SetDataFunc( std::function<void (void*, uint)> Func );
	
	const std::string & GetName() const {
		return mName;
	};
	~Uniform(void);
private:
	Type mType;
	GLint mLocation;
	uint mSize;
	std::string mName;
	void *mData;
	void *pDefaultData;
	bool mDynamic;		// jeøeli tru wywo≥uje funkcje inaczej przypisuje wartoúÊ domyúlnπ
	// ptr na funkcje do pobierania danych ( void Func( void *ptr_dane, uint data_size )
	DataFunc fGetData;
	void SetUniform();

};


// Update()
//{
//	Data = ShaderManager->GetUniformFunc( nazwa_uniformu )->(void);
//  Data -> wskaünik lub pole z danymi
//
//
//	dalej w shaderze przy bindowaniu
//	Shader.Bind()
//	{
//		for Uniform : Uniforms
//			Uniform.Update();
//			Uniform.Bind();
//	}

//_____________________________
//|			UNIFORM		     |
//|---------------------------|
//|@	 Lokacja w shaderze		 |
//|@		dane Shadera		 |
//|@	wartosc domyslna
//|@	
//|@	
//|@	
