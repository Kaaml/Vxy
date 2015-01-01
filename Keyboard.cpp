#include "Keyboard.hpp"

Keyboard *Key = new Keyboard;
Keyboard::Keyboard(void)
{
	for( size_t i = 0; i < GLFW_KEY_LAST; ++i )
	{
		mKeyBuffer[i] = 0;
		mOldKeyBuffer[i] =  0;
	}
}

void Keyboard::Update()
{

	for( int i = 0; i < GLFW_KEY_LAST; ++i )
	{
		if( glfwGetKey( i ) == GLFW_RELEASE ) 
		{
			mKeyBuffer[i] = false;
			mOldKeyBuffer[i] = false;
		}
		if( glfwGetKey( i ) == GLFW_PRESS ) 
		{
			if( mKeyBuffer[i] == true ) mOldKeyBuffer[i] = true;
			mKeyBuffer[i] = true;
		}
	}
}

bool Keyboard::IsKeyDown( int Key )
{
	if( Key > GLFW_KEY_LAST )
		return false;
	return mKeyBuffer[ Key ];
}

bool Keyboard::IsKeyPressed( int Key )
{
	if( Key > GLFW_KEY_LAST )
		return false;
	return mKeyBuffer[Key] && !mOldKeyBuffer[Key];	
}

bool Keyboard::IsKeyRelase( int Key )
{
	return !mKeyBuffer[ Key ];
}

Keyboard::~Keyboard(void)
{
}
