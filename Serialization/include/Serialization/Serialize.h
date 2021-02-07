#pragma once

#include "Core.h"

namespace Serialization
{ 
	//Abstract class for serialization objects
	class ISerializable
	{
	public:
		ISerializable();

		virtual std::string GetName() = 0;
		virtual void Serialize(class Archive& ar, unsigned int version) const = 0;
		virtual void DeSerialize(class Archive& ar, unsigned int version) = 0;
	};
}