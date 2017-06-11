#pragma once
#include "afxcmn.h"
#include "EditList.h"
#include <vector>

#include "xMfcBtn.h"
#include "../AdoAssistDll/DllExport.h"

using namespace std;



// CTableDataDlg 对话框


class CTableDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CTableDataDlg)

public:
	CTableDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTableDataDlg();

// 对话框数据
	enum { IDD = IDD_TABLEDATA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	struct CVarTypeInfo
	{
		int			nEnumValue;
		CString		strEnumName;
		CString		strDataType;
		CString		strPrefix;
	};

	typedef bool (__cdecl *pWriteProgramCode)(LPCTSTR lpszFile, LPCTSTR lpszClsData, 
		LPCTSTR lpszSql, bool bFeildIndex);
	typedef LPCTSTR (__cdecl *pSaveDlgText)();

	struct CPluginsDllInfo
	{
		HINSTANCE	hInstance;
		CString		strFileName;
		CString		strDllName;
		pWriteProgramCode pCodeWriter;
		CString		strSaveDlgText;
	};

	static const CVarTypeInfo Info_VarType[];
	std::vector<CVarTypeInfo> m_vectVarType;
	std::vector<CPluginsDllInfo> m_vectDllInfo;

private:
	CString			m_strSql;
	std::vector<CAdoClassData> m_lAdoClassData;

public:
	void InitTableData(_RecordsetPtr& pRs, LPCTSTR lpszSql);
	virtual BOOL OnInitDialog();

	void RefreshIniCfg();
	
	UINT GetVarTypeIndex(int nEnumValue);
	UINT GetVarTypeIndex(LPCTSTR lpszEnumName);

public:
	//CListCtrl m_wndDataList;
	CEditList m_wndDataList;
	afx_msg void OnBnClickedWritecode();

private:
	CBrush				m_oDlgBrush;

	_RecordsetPtr			m_pRecordset;
	CxMfcBtn				m_wndBtn[2];


	void RefreshDataList();
	void GetFieldTypeIni();
	void GetFieldTypeIni(LPCTSTR lpszAppName);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_strCodeType;
	afx_msg void OnCbnSelchangeCodetype();
	afx_msg void OnClose();
	BOOL m_bCheckIndex;
	afx_msg void OnBnClickedNextrecordset();
	CString m_strConfigType;
	// 获取当前的配置文件
	CString GetCurrentCfgFile(void);
	afx_msg void OnCbnSelchangeConfigtype();
	// 初始化代码生成插件
	void InitPlugin(void);

	void FindPlusin(const CString& strFinder);
	

};
