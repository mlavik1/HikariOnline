#ifndef HIKARI_OBJDEFS_H
#define HIKARI_OBJDEFS_H

#include "Core/Common/macros.h"
#include "Core/Object/class.h"
#include "Core/Object/function.h"

typedef uint32_t NetGUID;
typedef uint32_t ObjectFlagRegister;

#define NetGUIDNone 0

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
	static bool ClassPropertiesRegistered; \
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
	static Hikari::Object* _CreateInstanceFromDefaultConstructor() \
	{ \
		return new name##(); \
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

#define BEGIN_REGISTER_CLASSPROPERTIES(classname) \
	static bool RegisterClassProperties() \
	{ \
		Hikari::Class* myClass = ##classname##::GetStaticClass(); \

#define END_REGISTER_CLASSPROPERTIES(classname) \
	return 0; \
	}

#define REGISTER_CLASS_FUNCTION(classname, functionname) \
	myClass->AddMemberFunction(new Hikari::Function(#functionname, (void(Hikari::Object::*)(Hikari::FunctionArgContainer))(&##classname##::call_##functionname##) ));

#define REGISTER_CLASSPROPERTIES(classname) \
	bool classname##::ClassPropertiesRegistered = ##classname##::RegisterClassProperties();
	
#define CALL_FUNCTION(objectptr, functionname, ...) \
	objectptr->CallFunction(objectptr->GetClass()->GetFunctionByName(#functionname), getargs_##functionname##(__VA_ARGS__));

/**
* Define a function.
* This will enable RTTI and simple Reflection - and is required for RPC calls.
*/
#define DEFINE_FUNCTION(functionname, ...) \
FunctionArgContainer BOOST_PP_CAT(getargs_, functionname) BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__),(),GetDargs(Bogus, __VA_ARGS__)) \
{ \
	FunctionArgContainer args; \
	BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,args.TemplateConstruct<) __VA_ARGS__ BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,>) BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,GetCargs(Bogus, __VA_ARGS__);) \
	return args; \
} \
void BOOST_PP_CAT(call_, functionname) (FunctionArgContainer args) \
{ \
	BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), , \
		MakeVars(Bogus,__VA_ARGS__) )\
	BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,args.TemplateAccess<) __VA_ARGS__ BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,>) BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), ,GetCargs(Bogus, __VA_ARGS__);) \
	functionname GetCargs(Bogus, __VA_ARGS__); \
}
