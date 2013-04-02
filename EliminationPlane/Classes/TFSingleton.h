//
//  Singleton.h
//  TheForce
//
//  Created by Ray M on 13-1-28.
//
//

#ifndef TheForce_Singleton_h
#define TheForce_Singleton_h
#include <iostream>

template<class T> class TFSingleton
{
protected:
	static T* m_pObj;
	TFSingleton(){}

public:
	virtual ~TFSingleton(){}
	static T* GetObj()
	{
		if (m_pObj==NULL)
		{
			m_pObj = new T;
		}
		return m_pObj;
	}
};

//#define DECLARE_SINGLETON(__c)	static __c* m_pObj;
//#define IMPLEMENT_SINGLETON(__c) __c* __c::m_pObj = NULL;

#endif
