#pragma once
#include "Include.hpp"

enum VertexUsage
{
	V_POSITION	= 0,
	V_NORMAL	= 1,
	V_TEXCOORD  = 2,
	V_COLOR		= 3
};
struct VertexPointer
{
	size_t Index;				//Indeks pod jakim dane bed¹ w shaderze
	size_t Size;				// ile typow jest w danym linijce
	GLenum Type;				// Typ danych domyœlny -> float
	size_t Stride;				// liczba bajtów dziel¹ca dwa te same atrybuty
	bool Normalized;			// domyœlne -> false
	void * Pointer;				// Ptr na poczatek danych w buforze, odl w bajtach pierwszego elementu
	VertexUsage Usage;			// Rodzaj danych vertexa ( normalna, texcoord, pozycja itp )
	// Domyœlny konstruktor
	VertexPointer(){
		Index = 0;
		Size  =  3;
		Type = GL_FLOAT;
		Stride = 0;
		Normalized = false;
		Pointer = nullptr;
		Usage = V_POSITION;
	};
	// Stride - co ile B jest ten sam typ, ptr - wskaznik na pierwsyz wyraz w uforze  Normalized -> flase | Type -> GL_FLOAT
	VertexPointer( size_t _index, size_t _size, size_t _stride, VertexUsage _usage, void* ptr, bool _normalized = false, GLenum _type = GL_FLOAT ){
		Index = _index;
		Size  =  _size;
		Type = _type;
		Stride = _stride;
		Normalized = _normalized;
		Pointer = ptr;
		Usage = _usage;
	};
};
class VertexDeclaration
{
public:
	VertexDeclaration(void);
	void AddPointer( const VertexPointer& Element );
	void AddPointers( VertexPointer * Elements, size_t Count );
	void Bind();
	VertexPointer*	GetVertexPointer( VertexUsage Usage );
	VertexPointer*	GetVertexPointer( size_t index );
	~VertexDeclaration(void);
private:
	std::vector< VertexPointer > mVertexPointers;
};



// Vertex pointer -> odniesienie do funkcji glVertexAttribPointer
// przechowywuje potrzebne dane, oraz do tego typ danych jaki jest
// w danym pointerze trzymany. NP Dla danych
// VVVVVVVVVV NNNNNNNNNN TTTTTTTTTTT
// V - vertex, N - normala, T - texxcoordy
// V - vec3	   N - vec3		T - vec2
//VertexPointer( 0, 3, 0, V_POSITION, nullptr )
//VertexPointer( 1, 3, 0, V_NORMAL, size(V))
//VertexPointer( 2, 2, 0, V_TEXCOORD, size(v+N) )