#pragma once

#include <GL/glfw.h>
#include <Windows.h>
#include "Singleton.hpp"

class Keyboard : public Singleton< Keyboard >
{
public:
	Keyboard(void);
	~Keyboard(void);
	// nacisniecie klawisza
	bool IsKeyDown( int Key );
	// klikniecie
	bool IsKeyPressed( int Key );
	// klawisz swobodny
	bool IsKeyRelase( int Key );

	void Update();

private:
	char mKeyBuffer[ GLFW_KEY_LAST ];
	char mOldKeyBuffer[ GLFW_KEY_LAST ];
};

