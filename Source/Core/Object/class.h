#ifndef HIKARI_CLASS_H
#define HIKARI_CLASS_H

/*=============================================================================================
							A Class structure for Hikari::Object

Contains RunTime Type Information and some basic reflection-like functionalities.
Use DEFINE_CLASS and IMPLEMENT_CLASS, and inherit from Hikari::Object to generate a Hikari::Class.
See objdefs.h
==============================================================================================*/

#include <string>
#include <vector>
#include <unordered_map>

namespace Hikari
{
	// Forward declarations:
	class Object;
	class Function;

	class Class
	{
		friend class Object;

		typedef Hikari::Class*(*staticclassaccessor_t)();
		typedef Hikari::Object*(*staticconstructor_t)();

	private:
		std::string mClassName;					// Name of this class
		Hikari::Class* mBaseClass;				// Pointer to base class
		std::vector<Hikari::Class*> mChildClasses;
		staticconstructor_t mStaticConstructor; // Static functions that calls an empty constructor
		unsigned int mCreatedInstanceCount;		// Number of created instances (destroyed isntances are also counted)
		std::unordered_map<std::string, Function*> mMemberFunctions;

	public:
		Class(const char* arg_name, staticconstructor_t constructor = 0, Hikari::Class* superclass = 0);

		void AddMemberFunction(Function* arg_function);

		/**
		* Gets the full name of the class, with namespace.
		*
		*/
		const std::string &GetFullName() const;

		/**
		* Gets the simple name of the class, without namespace.
		*
		*/
		std::string GetName() const;

		/**
		* Returns a pointer to the base class of this class.
		*
		*/
		const Class* GetBaseClass() const;

		/**
		* Checks if this class is an subclass of the specified class.
		*
		*/
		bool IsSubclassOf(Class* arg_other) const;

		/**
		* Checks if this class is the same as, or inherits from, the specified class.
		*
		*/
		bool IsA(Class* arg_other) const;

		/**
		* Creates an instances of the class.
		*
		*/
		Object* CreateInstance();
		
		/**
		* Recursively searches through the children searching for class by given name.
		*
		* @param arg_name				The name of the class to search for.
		* @param arg_fullname			Use full name (with namespace) when comparing class names.
		*/
		Class* GetChildClassByName(const char* arg_name, bool arg_fullname);

		Function* GetFunctionByName(const char* arg_name);

		/**
		* Returns a pointer to the static Class-instance of a class by the given name (if it exists).
		*
		* @param arg_name				The name of the class to search for.
		* @param arg_fullname			Use full name (with namespace) when comparing class names.
		*/
		static Class* GetClassByName(const char* arg_name, bool arg_fullname);

	};
}

#endif
