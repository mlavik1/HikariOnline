#ifndef HIKARI_OBJDEFS_H
#define HIKARI_OBJDEFS_H

#include "Core/Object/class.h"

typedef uint32_t ObjectFlagRegister;

enum class ObjectFlag
{
	Destroyed = 1,
	PendingDestroy = 2
};

// Used in the constructor defined in DEFINE_CLASS_INTERNAL.
// This allows us to create an instance of a class without knowing the calss ( see Class::CreateInstance() ).
struct MingObject_EmptyConstructorParams
{
	
};

struct ObjectInitialiserParams
{

};

// Do not use this directly!
#define DEFINE_CLASS_INTERNAL(name, constructorinitlist, baseclassaccessor) \
private: \
	static Hikari::Class* StaticClass; \
public: \
	static Hikari::Class* GetStaticClass() \
	{ \
		if(StaticClass == nullptr) StaticClass = name##::CreateStaticClass(); \
		return StaticClass; \
	} \
	static Hikari::Class* CreateStaticClass() \
	{ \
		if(StaticClass) return StaticClass; \
		return new Hikari::Class(#name, &##name##::_CreateInstanceFromDefaultConstructor, baseclassaccessor); \
	} \
	virtual Hikari::Class* GetClass() \
	{ \
		return GetStaticClass(); \
	} \
	\
	##name##(MingObject_EmptyConstructorParams params) constructorinitlist  \
	{ \
	} \
	static Hikari::Object* _CreateInstanceFromDefaultConstructor() \
	{ \
		return new name##(MingObject_EmptyConstructorParams()); \
	}

/**
* Define a class, that directly or indirectly inherits from Hikari::Object.
* 
* The class will have Run-Time Type Information available through GetClass() and GetStaticClass().
* This macro will generate a constructor with parameters, so the class will have no implicit default constructor.
* IMPORTANT: You will need to add the IMPLEMENT_CLASS(classname)-macro to your source file.
*/
#define DEFINE_CLASS(classname, baseclassname) \
	DEFINE_CLASS_INTERNAL(classname, : ##baseclassname##(params), ##baseclassname##::GetStaticClass())

/**
* Add this to your source file, if DEFINE_CLASS has been used in the header file.
*/
#define IMPLEMENT_CLASS(classname) \
	Hikari::Class* ##classname##::StaticClass = ##classname##::CreateStaticClass();

#endif
