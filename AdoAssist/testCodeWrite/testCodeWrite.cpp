// testCodeWrite.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "testCodeWrite.h"
#include <locale.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

const LPCTSTR lpszCode = _T("\
[\n\
   {\n\
      \"AutoIncrement\" : true,\n\
      \"DataType\" : \"long\",\n\
      \"FieldName\" : \"ID\",\n\
      \"Index\" : \"0\",\n\
      \"VariableName\" : \"m_lID\",\n\
      \"VariantType\" : \"adInteger\",\n\
      \"VariantTypeEnum\" : 3\n\
   },\n\
   {\n\
      \"AutoIncrement\" : false,\n\
      \"DataType\" : \"CString\",\n\
      \"FieldName\" : \"Guid\",\n\
      \"Index\" : \"1\",\n\
      \"VariableName\" : \"m_strGuid\",\n\
      \"VariantType\" : \"adVarWChar\",\n\
      \"VariantTypeEnum\" : 202\n\
   },\n\
   {\n\
      \"AutoIncrement\" : false,\n\
      \"DataType\" : \"CString\",\n\
      \"FieldName\" : \"Name\",\n\
      \"Index\" : \"2\",\n\
      \"VariableName\" : \"m_strName\",\n\
      \"VariantType\" : \"adVarWChar\",\n\
      \"VariantTypeEnum\" : 202\n\
   },\n\
   {\n\
      \"AutoIncrement\" : false,\n\
      \"DataType\" : \"long\",\n\
      \"FieldName\" : \"Age\",\n\
      \"Index\" : \"3\",\n\
      \"VariableName\" : \"m_lAge\",\n\
      \"VariantType\" : \"adInteger\",\n\
      \"VariantTypeEnum\" : 3\n\
   }\n\
]\n\
");

extern "C" AFX_CLASS_EXPORT bool WriteProgramCode(LPCTSTR lpszFile, LPCTSTR lpszClsData, 
												  LPCTSTR lpszSql, bool bFeildIndex);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		_tsetlocale(LC_ALL, _T("chs"));

		LPCTSTR lpszFile = _T("D:\\DBClassName.cs");
		LPCTSTR lpszSql = _T("SELECT * FROM tbl_Demo");

		WriteProgramCode(lpszFile, lpszCode, lpszSql, false);
	}

	return nRetCode;
}
