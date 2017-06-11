#pragma once

#include "json/include/json/json.h"
#ifndef ADOASSISTDLLCLASS
#ifdef ADOASSISTDLL
#define ADOASSISTDLLCLASS __declspec(dllexport)
#else
#define ADOASSISTDLLCLASS __declspec(dllimport)
#endif //ADOASSISTDLL
#endif // ADOASSISTDLLCLASS

class ADOASSISTDLLCLASS CAdoClassData
{
public:

	CString			strIndex;
	CString			strFieldName;
	CString			strVariableName;
	CString			strVariantType;
	int			nVariantType;
	CString			strDataType;
	bool			bIsAutoIncrement;

public:
	CAdoClassData(void);
	~CAdoClassData(void);


	void Deserialize(const Json::Value& jsonValue);
	void Serialize(Json::Value& jsonValue) const;

	static void DeserializeEx(std::vector<CAdoClassData>& AdoClassData, LPCTSTR lpszValue);
	static void SerializeEx(const std::vector<CAdoClassData>& AdoClassData,CString& strValue);
};
