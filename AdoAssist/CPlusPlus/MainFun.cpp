
#include "stdafx.h"
#include "../AdoAssistDll/DllExport.h"


const static CString s_strTemplate = _T("\
/*----------------------------------------------------------------------------------------------------------------\n\
Version:	AdoAssist 1.20\n\
   Time:	[TIME]\n\
    SQL:	[SQL]\n\
----------------------------------------------------------------------------------------------------------------*/\n\
#pragma once\n\
\n\
class C[CLASSNAME]\n\
{\n\
public:\n\
[MEMBERVARIABLES]\n\
public:\n\
[MEMBERVARIABLESFUN]\n\
public:\n\
	// Database Interface\n\
	bool AdoGetRecord(const CAdoRecordset& rs, DWORD dwFlag = 0);\n\
	bool AdoSetRecord(const CAdoRecordset& rs, DWORD dwFlag = 0) const;\n\
};\n\
\n\
#pragma warning(disable:4100)\
// Database Interface\n\
inline bool C[CLASSNAME]::AdoGetRecord(const CAdoRecordset& rs, DWORD dwFlag)\n\
{\n\
[DBGETINTERFACE]\n\
	return true;\n\
}\n\
\n\
// Database Interface\n\
inline bool C[CLASSNAME]::AdoSetRecord(const CAdoRecordset& rs, DWORD dwFlag) const\n\
{\n\
[DBSETINTERFACE]\n\
	return true;\n\
}\n\
#pragma warning(default:4100)\
\n\
\n\
");

const static CString s_strMemFun = _T("\
	[DATATYPE] Get[FIELDNAME]() const\n\
	{\n\
		return this->[VARIABLENAME];\n\
	}\n\
\n\
	void Get[FIELDNAME]([DATATYPE]& t[FIELDNAME]) const\n\
	{\n\
		t[FIELDNAME] = this->[VARIABLENAME];\n\
	}\n\
\n\
	void Set[FIELDNAME](const [DATATYPE]& t[FIELDNAME])\n\
	{\n\
		this->[VARIABLENAME] = t[FIELDNAME];\n\
	}\n"\
	);

CString CreateCode( const  std::vector<CAdoClassData> &lAdoClassData, bool bFeildIndex, LPCTSTR lpszFile, LPCTSTR lpszSql ) 
{

	CString strClassDataMember,strClassDataFun, strAdoCode;
	CString strDbCodes_Set, strDbCodes_Get, strFmt;
	CString strTmp;
	CString strAdoSetRecord, strAdoGetRecord;
	CString strDbCode_NameSet, strDbCode_IndexSet; 
	CString strDbCode_NameGet, strDbCode_IndexGet;
	CString strDbCodes_NameSet, strDbCodes_IndexSet; 
	CString strDbCodes_NameGet, strDbCodes_IndexGet;

	UINT nSize = lAdoClassData.size();
	for (UINT i=0; i<nSize; i++)
	{
		const CAdoClassData& clsData = lAdoClassData[i];
		const CString& strIndex			= clsData.strIndex;
		const CString& strFieldName		= clsData.strFieldName;
		const CString& strVariableName	= clsData.strVariableName;
		const CString& strVariantType	= clsData.strVariantType;
		const CString& strDataType		= clsData.strDataType;
		bool bAutoIncrement				= clsData.bIsAutoIncrement;

		strClassDataMember.AppendFormat(_T("\t%s\t\t\t%s;\t//%s\t%s\t%s\n"), 
			strDataType, strVariableName, 
			strIndex, strFieldName, strVariantType);

		strTmp = s_strMemFun;
		strTmp.Replace(_T("[DATATYPE]"), strDataType);
		strTmp.Replace(_T("[FIELDNAME]"), strFieldName);
		strTmp.Replace(_T("[VARIABLENAME]"), strVariableName);
		strClassDataFun.AppendFormat(_T("%s\n"), strTmp);


		strDbCode_NameGet.Format(_T("\tADO_GETFIELDVALUE(_T(\"%s\"), %s);\t//%s\n"), 
			strFieldName, strVariableName, strIndex);

		strDbCode_IndexGet.Format(_T("\tADO_GETFIELDVALUE((long)%s, %s);\t//%s\n"), 
			strIndex, strVariableName, strFieldName);


		if (bAutoIncrement)
		{
			strDbCode_NameSet.Format(_T("\t//ADO_SETFIELDVALUE(_T(\"%s\"), %s);\t//%s\n"), 
				strFieldName, strVariableName, strIndex);

			strDbCode_IndexSet.Format(_T("\t//ADO_SETFIELDVALUE((long)%s, %s);\t//%s\n"), 
				strIndex, strVariableName, strFieldName);
		}
		else
		{
			strDbCode_NameSet.Format(_T("\tADO_SETFIELDVALUE(_T(\"%s\"), %s);\t//%s\n"), 
				strFieldName, strVariableName, strIndex);

			strDbCode_IndexSet.Format(_T("\tADO_SETFIELDVALUE((long)%s, %s);\t//%s\n"), 
				strIndex, strVariableName, strFieldName);
		}

		strDbCodes_NameSet.Append(strDbCode_NameSet);
		strDbCodes_IndexSet.Append(strDbCode_IndexSet);
		strDbCodes_NameGet.Append(strDbCode_NameGet);
		strDbCodes_IndexGet.Append(strDbCode_IndexGet);

	}

	if (bFeildIndex)
	{
		strDbCodes_Set.Format(_T("%s\n\t/*\n%s\t*/\n"), strDbCodes_IndexSet, strDbCodes_NameSet);
		strDbCodes_Get.Format(_T("%s\n\t/*\n%s\t*/\n"), strDbCodes_IndexGet, strDbCodes_NameGet);
	}
	else
	{
		strDbCodes_Set.Format(_T("%s\n\t/*\n%s\t*/\n"), strDbCodes_NameSet, strDbCodes_IndexSet);
		strDbCodes_Get.Format(_T("%s\n\t/*\n%s\t*/\n"), strDbCodes_NameGet, strDbCodes_IndexGet);
	}


	CString strClassName(lpszFile) /*= _T("DBClassName")*/;
	CString strFile(lpszFile);
	int nPos = strFile.ReverseFind('\\')+1;
	if (nPos > -1)
	{
		strClassName = strFile.Right(strFile.GetLength() - nPos);		
		nPos = strClassName.ReverseFind('.');
		if (nPos > -1)
		{
			strClassName = strClassName.Left( nPos );
		}
	}


	COleDateTime ot = COleDateTime::GetCurrentTime();
	CString strCode(s_strTemplate);
	strCode.Replace(_T("[TIME]"), ot.Format(_T("%Y-%m-%d %H:%M:%S")));
	strCode.Replace(_T("[SQL]"), lpszSql);
	strCode.Replace(_T("[MEMBERVARIABLES]"), strClassDataMember);
	strCode.Replace(_T("[MEMBERVARIABLESFUN]"), strClassDataFun);
	strCode.Replace(_T("[DBSETINTERFACE]"), strDbCodes_Set);
	strCode.Replace(_T("[DBGETINTERFACE]"), strDbCodes_Get);
	strCode.Replace(_T("[CLASSNAME]"), strClassName);

	return strCode;
}

extern "C" AFX_CLASS_EXPORT bool WriteProgramCode(LPCTSTR lpszFile, LPCTSTR lpszClsData, 
					  LPCTSTR lpszSql, bool bFeildIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bool bRet = false;
	std::vector<CAdoClassData> lAdoClassData;

	CAdoClassData::DeserializeEx(lAdoClassData, lpszClsData);

	CString strCode  = CreateCode(lAdoClassData, bFeildIndex, lpszFile, lpszSql);

	CStdioFile file;
	if (file.Open(lpszFile,
		CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		file.WriteString(strCode);
		file.Flush();
		file.Close();
		bRet = true;
	}

	return bRet;
}

const static CString s_strSaveDlgText = _T(".h\nDBClassName\nC++ Head File(*.h)|*.h|All File(*.*)|*.*||");
extern "C" AFX_CLASS_EXPORT LPCTSTR SaveDlgText()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return s_strSaveDlgText;
}