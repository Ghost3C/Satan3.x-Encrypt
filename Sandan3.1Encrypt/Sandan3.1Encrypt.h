// Sandan3.1Encrypt.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSandan31EncryptApp:
// See Sandan3.1Encrypt.cpp for the implementation of this class
//

class CSandan31EncryptApp : public CWinApp
{
public:
	CSandan31EncryptApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSandan31EncryptApp theApp;