// CSharp.h : CSharp DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCSharpApp
// �йش���ʵ�ֵ���Ϣ������� CSharp.cpp
//

class CCSharpApp : public CWinApp
{
public:
	CCSharpApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
