
// MFC_QLDSV.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"

// CMFCQLDSVApp:
// See MFC_QLDSV.cpp for the implementation of this class
//

class CMFCQLDSVApp : public CWinApp
{
public:
	CMFCQLDSVApp();
	~CMFCQLDSVApp();
	/*CString GetsDsn();
	void SetsDsn(CString dataNameSource);
	CDatabase database;
	CString sDsn;*/
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCQLDSVApp theApp;
