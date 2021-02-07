#pragma once

#include "Core.h"
#include "Library.h"

namespace Serialization
{
	//Class that performs all save and load operations
	//Call this after creating an object for loading an objects parameters
	class Archive
	{
	public:
		Archive(const std::string& filename, bool binary = true)
			:m_FileName(filename), m_Binary(binary)
		{
			m_FileName.append(s_Extension);

			fs = new std::fstream();
		}

		~Archive()
		{
			delete fs;
		}

		template<class Object>
		void Serialize(const Object& o)
		{
			fs->open(m_FileName, std::ios::out | std::ios::trunc);

			m_Binary ? WriteBinary(*fs, s_FileVersion) : *fs << s_FileVersion << "\n";

			OnSerialize(*this, o, s_FileVersion);

			fs->close();
		}

		template<class Object>
		void DeSerialize(Object& o)
		{
			fs->open(m_FileName, std::ios::in);

			if (fs->good() == false) return;

			unsigned int fileversion = -1;

			m_Binary ? ReadBinary(*fs, fileversion) : *fs >> fileversion;

			OnDeSerialize(*this, o, fileversion);

			fs->close();

		}

		template<class T>
		Archive& operator&(const T& var);

		template<class T>
		Archive& operator&(T& var);

		template<>
		Archive& operator&(std::string& var);

		template<>
		Archive& operator&(const std::string& var);

		template<class T>
		Archive& operator&(std::vector<T>& v);

		template<class T>
		Archive& operator&(const std::vector<T>& v);

	private:
		std::fstream* fs = nullptr;
		
		std::string m_FileName;

		bool m_Binary;

		static unsigned int s_FileVersion;

		static const char* s_Extension;
	};

	template<class T>
	Archive& Archive::operator&(const T& var)
	{
		m_Binary ? WriteBinary(*fs, var) : Write(*fs, var);

		return *this;
	}

	template<class T>
	Archive& Archive::operator&(T& var)
	{	
		m_Binary ? ReadBinary(*fs, var) : Read(*fs, var);

		return *this;
	}

	template<>
	Archive& Archive::operator&(std::string& var)
	{
		m_Binary ? ReadBinary(*fs, var) : Read(*fs, var);

		return *this;
	}

	template<>
	Archive& Archive::operator&(const std::string& var)
	{
		m_Binary ? WriteBinary(*fs, var) : Write(*fs, var);
		
		return *this;
	}

	template<class T>
	Archive& Archive::operator&(const std::vector<T>& v)
	{
		m_Binary ? WriteBinaryVector<T>(*fs, v) : WriteVector<T>(*fs, v);
		
		return *this;
	}

	template<class T>
	Archive& Archive::operator&(std::vector<T>& v)
	{	
		m_Binary ?  ReadBinaryVector<T>(*fs, v) : ReadVector<T>(*fs, v);

		return *this;
	}

	template<typename T>
	auto OnSerialize(Archive& ar, const T& obj, unsigned int version)
		-> decltype(obj.Serialize(ar, version))
	{
		obj.Serialize(ar, version);
	};

	template<typename T>
	auto OnSerialize(Archive& ar, const T& obj, unsigned int version)
		->decltype(Serialize(ar, obj, version))
	{
		Serialize(ar, obj, version);
	};

	template<typename T>
	auto OnDeSerialize(Archive& ar, T& obj, unsigned int version)
		-> decltype(obj.DeSerialize(ar, version))
	{
		obj.DeSerialize(ar, version);
	};

	template<typename T>
	auto OnDeSerialize(Archive& ar, T& obj, unsigned int version)
		->decltype(DeSerialize(ar, obj, version))
	{
		DeSerialize(ar, obj, version);
	};

	template<class BaseClass, class T>
	inline void BaseObjectSerialize(Archive& ar, const T& obj, unsigned int version)
	{
		OnSerialize(ar, (BaseClass)obj, version);
	};

	template<class BaseClass, class T>
	inline void BaseObjectDeSerialize(Archive& ar, T& obj, unsigned int version)
	{
		OnDeSerialize(ar, (BaseClass&)obj, version);
	};

#define SERIALIZEMEMEBER(archive, member) archive & member;
#define SERIALIZEBASECLASS(BaseClass, archive, obj, version) Serialization::BaseObjectSerialize<BaseClass>(archive, obj, version);
#define DESERIALIZEBASECLASS(BaseClass, archive, obj, version) Serialization::BaseObjectDeSerialize<BaseClass>(archive, obj, version);
}