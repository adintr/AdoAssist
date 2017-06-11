#include "StdAfx.h"
#include "AdoClassData.h"
//#include <comutil.h>
#include "dllExport.h"

CAdoClassData::CAdoClassData(void)
{
	nVariantType = -1;
	bIsAutoIncrement = false;
}

CAdoClassData::~CAdoClassData(void)
{
}


void CAdoClassData::Deserialize(const Json::Value& jsonValue)
{
	strIndex  =  jsonValue["Index"].asCString();
	strFieldName  =  jsonValue["FieldName"].asCString();
	strVariableName  =  jsonValue["VariableName"].asCString();
	strVariantType  =  jsonValue["VariantType"].asCString();
	nVariantType  =  jsonValue["VariantTypeEnum"].asInt();
	strDataType  =  jsonValue["DataType"].asCString();
	bIsAutoIncrement = jsonValue["AutoIncrement"].asBool();

}

void CAdoClassData::Serialize(Json::Value& jsonValue) const
{
	jsonValue["Index"] = Json::Value(CT2CA(strIndex));
	jsonValue["FieldName"] = Json::Value(CT2CA(strFieldName));
	jsonValue["VariableName"] = Json::Value(CT2CA(strVariableName));
	jsonValue["VariantType"] = Json::Value(CT2CA(strVariantType));
	jsonValue["VariantTypeEnum"] = Json::Value(nVariantType);
	jsonValue["DataType"] = Json::Value(CT2CA(strDataType));
	jsonValue["AutoIncrement"] = Json::Value(bIsAutoIncrement);
}


void CAdoClassData::DeserializeEx(std::vector<CAdoClassData>& lAdoClassData, LPCTSTR lpszValue)
{
	lAdoClassData.clear();
	CAdoClassData clsData;

	CStringA bstrValue(lpszValue);

	Json::Reader reader;

	Json::Value json_object;

	const char* json_document = (LPCSTR)bstrValue;

	if (!reader.parse(json_document, json_object)
		&& !json_object.isArray()
		&& !json_object.empty())
	{
		return ;
	}

	Json::Value::iterator it = json_object.begin();
	Json::Value::iterator itEnd = json_object.end();
	UINT nSize = json_object.size();
	lAdoClassData.reserve(nSize);

	for (; it != itEnd; it++)
	{
		clsData.Deserialize(*it);
		lAdoClassData.push_back(clsData);
	}
	
}

void CAdoClassData::SerializeEx(const std::vector<CAdoClassData>& lAdoClassData,CString& strValue)
{

	Json::Value root;  

	Json::Value json_temp;      
	UINT nSize = lAdoClassData.size();

	for (UINT i=0; i<nSize; i++)
	{
		lAdoClassData[i].Serialize(json_temp);
		root.append(json_temp);
	}

	Json::StyledWriter fast_writer;
	//Json::FastWriter fast_writer;

	strValue =  fast_writer.write(root).c_str();
}