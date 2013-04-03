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
public:
	virtual ~TFSingleton(){spInstance_=NULL;}
	static T* getInstance()
	{
		if (spInstance_==NULL)
		{
			spInstance_ = new T;
		}
		return spInstance_;
	}
    
protected:
	TFSingleton(){}
    
private:
    static T* spInstance_;
};

#define IMPLEMENT_SINGLETON(__c) template<> __c* TFSingleton<__c>::spInstance_ = NULL;

#endif
