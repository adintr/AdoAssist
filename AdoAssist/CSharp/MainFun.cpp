
#include "stdafx.h"
#include "../AdoAssistDll/DllExport.h"


const static CString s_strTemplate = _T("\
/*----------------------------------------------------------------------------------------------------------------\n\
Version:	AdoAssist 1.20\n\
   Time:	[TIME]\n\
    SQL:	[SQL]\n\
----------------------------------------------------------------------------------------------------------------*/\n\
using System;\n\
using System.Collections.Generic;\n\
using System.Text;\n\
\n\
namespace Database\n\
{\n\
	public class [CLASSNAME] : Database.IDBOperability\n\
	{\n\
		#region Data and Attr\n\
\n\
[DATAANDATTR]\n\
\n\
		#endregion\n\
\n\
		#region IDBOperability\n\
\n\
		public void DBSetData(System.Data.DataRow datarow, Object oFlag)\n\
		{\n\
			var x = datarow;\n\
\n\
[DBSETDATA]\n\
		}\n\
\n\
		public void DBGetData(System.Data.IDataReader reader, Object oFlag)\n\
		{\n\
			var x = reader;\n\
\n\
[DBGETDATA]\n\
		}\n\
\n\
		#endregion\n\
	}\n\
}\n\
");

const static CString s_strDataAttr = _T("\
		/// <summary>\n\
		/// [REMARK]\n\
		/// </summary>\n\
		protected [DATATYPE] [VARIABLENAME];\n\
\n\
		/// <summary>\n\
		/// [REMARK]\n\
		/// </summary>\n\
		public [DATATYPE] [FIELDNAME]\n\
		{\n\
			get\n\
			{\n\
				return [VARIABLENAME];\n\
			}\n\
			set\n\
			{\n\
				[VARIABLENAME] = value;\n\
			}\n\
		}\n\
	");

CString CreateCode( const  std::vector<CAdoClassData> &lAdoClassData, bool bFeildIndex, LPCTSTR lpszFile, LPCTSTR lpszSql ) 
{

	CString strClassDataMember,strClassDataFun, strAdoCode;
	CString strDbCodes_Name, strDbCodes_Index, strFmt;
	CString strTmp, strRemark;
	CString strDbSetData, strDbGetData, strDataAndAttr;
	CString strDbSetData_Name, strDbSetData_Index;
	CString strDbGetData_Name, strDbGetData_Index;
	CString strDbSetCode_Name, strDbSetCode_Index;
	CString strDbGetCode_Name, strDbGetCode_Index;

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


		strTmp = s_strDataAttr;
		strRemark.Format(_T("%s %s %s"), strIndex, strFieldName, strVariantType);
		strTmp.Replace(_T("[DATATYPE]"), strDataType);
		strTmp.Replace(_T("[REMARK]"), strRemark);
		strTmp.Replace(_T("[VARIABLENAME]"), strVariableName);
		strTmp.Replace(_T("[FIELDNAME]"), strFieldName);
		strDataAndAttr.AppendFormat(_T("%s\n"), strTmp);

		strDbSetData_Name.Format(_T("\t\t\tx[\"%s\"] = %s;\n"),
			strFieldName, strFieldName);
		strDbSetData_Index.Format(_T("\t\t\tx[%s] = %s;\n"),
			strIndex, strFieldName);

		strDbGetData_Name.Format(_T("\t\t\tDBConvert.Convert(out %s, x[\"%s\"]);\n"),
			strVariableName, strFieldName);
		strDbGetData_Index.Format(_T("\t\t\tDBConvert.Convert(out %s, x[%s]);\n"),
			strVariableName, strIndex);


		if (bAutoIncrement)
		{
			strDbSetData_Name.Insert(3, _T("//"));
			strDbSetData_Index.Insert(3, _T("//"));
		}

		strDbSetCode_Name.Append(strDbSetData_Name);
		strDbSetCode_Index.Append(strDbSetData_Index);

		strDbGetCode_Name.Append(strDbGetData_Name);
		strDbGetCode_Index.Append(strDbGetData_Index);

	}

	if (bFeildIndex)
	{
		strDbSetData.Format(_T("%s\n\t\t\t/*\n%s\t\t\t*/\n"), strDbSetCode_Index, strDbSetCode_Name);
		strDbGetData.Format(_T("%s\n\t\t\t/*\n%s\t\t\t*/\n"), strDbGetCode_Index, strDbGetCode_Name);
	}
	else
	{
		strDbSetData.Format(_T("%s\n\t\t\t/*\n%s\t\t\t*/\n"), strDbSetCode_Name, strDbSetCode_Index);
		strDbGetData.Format(_T("%s\n\t\t\t/*\n%s\t\t\t*/\n"), strDbGetCode_Name, strDbGetCode_Index);
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
	strCode.Replace(_T("[CLASSNAME]"), strClassName);

	strCode.Replace(_T("[DBSETDATA]"), strDbSetData);
	strCode.Replace(_T("[DBGETDATA]"), strDbGetData);
	strCode.Replace(_T("[DATAANDATTR]"), strDataAndAttr);


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

const static CString s_strSaveDlgText = _T(".cs\nDBClassName\nCSharp File(*.cs)|*.cs|All File(*.*)|*.*||");
extern "C" AFX_CLASS_EXPORT LPCTSTR SaveDlgText()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return s_strSaveDlgText;
}