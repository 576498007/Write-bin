// NewTransformation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNewTransformationApp:
// �йش����ʵ�֣������ NewTransformation.cpp
//

class CNewTransformationApp : public CWinApp
{
public:
	CNewTransformationApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNewTransformationApp theApp;