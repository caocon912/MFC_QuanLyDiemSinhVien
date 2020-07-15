// QLSV.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "QLSV.h"
#include "afxdialogex.h"


// QLSV dialog

IMPLEMENT_DYNAMIC(QLSV, CDialogEx)

QLSV::QLSV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSSVDlg, pParent)
{

}

QLSV::~QLSV()
{
}

void QLSV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(QLSV, CDialogEx)
END_MESSAGE_MAP()


// QLSV message handlers
