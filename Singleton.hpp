#pragma once

#include <cassert>
 
template <typename T> class Singleton
{
private:
    static T* pInstance;
 
public:
    Singleton()
    {
        assert(!pInstance);
        //int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
        //pInstance = (T*)((int)this + offset);
		pInstance = static_cast< T* > ( this );
    }
    ~Singleton()
	{
		assert(pInstance);
		pInstance = 0;
	}
    static T& GetSingleton()
	{ 
		assert(pInstance); 
		return (*pInstance);
	}
    static T* GetSingletonPtr()
    {
		return pInstance;
	}
};
 
template <typename T> T* Singleton <T>::pInstance = 0;


