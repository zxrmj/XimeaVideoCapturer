
// mfc_captureVideoNew.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_captureVideoNewApp: 
// �йش����ʵ�֣������ mfc_captureVideoNew.cpp
//

class Cmfc_captureVideoNewApp : public CWinApp
{
public:
	Cmfc_captureVideoNewApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_captureVideoNewApp theApp;