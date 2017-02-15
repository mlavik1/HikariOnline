#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include "replication_types.h"
//#include "replication_manager.h" // TODO!!!

#define REPLICATION_DATATYPE const char*

#define REPLICATE_VARIABLE(type, name) \
void Replication_Set##name##(REPLICATION_DATATYPE arg_val, int &index) \
{ \
	name = *(reinterpret_cast<type*>((char*)arg_val + index)); \
	index += sizeof(type); \
} \
std::ostringstream Replication_Get##name##() \
{\
	std::ostringstream ss; \
	char * chararr = reinterpret_cast<char *>(&name); \
	for (std::size_t i = 0; i != sizeof(name); ++i) \
		ss << chararr[i]; \
	return ss; \
}

#define REPLICATE_CLASSINSTANCE(classname, name) \
void Replication_Set##name##(REPLICATION_DATATYPE arg_val, int &index) \
{ \
	(name).SetReplicatedData(arg_val, index); \
} \
std::ostringstream Replication_Get##name##() \
{\
	return (name).GetReplicatedData(); \
}


#define REPLICATION_BODY(classname) \
protected: \
std::vector<void(##classname##::*)(REPLICATION_DATATYPE, int&)> Replication_mReplicationModifiers; \
std::vector<std::ostringstream(##classname##::*)()> Replication_mReplicationAccessors; \
public: \
void SetReplicatedData(REPLICATION_DATATYPE data, int& i) \
	{ \
		for (void(##classname##::*currReplMod)(REPLICATION_DATATYPE, int&) : Replication_mReplicationModifiers) \
			(this->*currReplMod)(data, i); \
	} \
std::ostringstream GetReplicatedData() \
{ \
	std::ostringstream oss; \
	for (std::ostringstream(##classname##::*currReplAcc)() : Replication_mReplicationAccessors) \
		oss << (this->*currReplAcc)().str(); \
	return oss; \
}

#define REPLICATION_CONSTRUCTOR() GetReplicableMembers();

#define REPLICATE(classname, name) \
Replication_mReplicationModifiers.push_back(&##classname##::Replication_Set##name##); \
Replication_mReplicationAccessors.push_back(&##classname##::Replication_Get##name##);



class IReplicable
{
protected:
	virtual void GetReplicableMembers() {}
	repid_t mReplicationID = repid_none;
	bool mIsReplicated = false;

public:
	virtual void SetReplicatedData(REPLICATION_DATATYPE data, int& i)
	{
	}

	virtual std::ostringstream GetReplicatedData()
	{
		std::ostringstream oss;
		return oss;
	}

	inline repid_t GetReplicationID()
	{
		return mReplicationID;
	}

	
	inline void SetReplicationID(repid_t arg_id)
	{
		mReplicationID = arg_id;
	}
	
	inline void SetIsReplicated(bool arg_replicate)
	{
		mIsReplicated = arg_replicate;
		//ReplicationManager::Instance()->SetReplicate(this, arg_replicate); // TODO!!!
	}
	
	// This one should not be necessary! TODO: Remove
	inline void SetReplicate(repid_t arg_id)
	{
		mReplicationID = arg_id;
		SetIsReplicated(true);
	}

	


};