// MainWnd.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "MainWnd.h"
#include "afxdialogex.h"
#include "DanhSachSinhVienTheoKhoa.h"
#include "QLSV.h"
// MainWnd dialog

IMPLEMENT_DYNAMIC(MainWnd, CDialogEx)

MainWnd::MainWnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DLG, pParent)
{

}

MainWnd::~MainWnd()
{
}

void MainWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainWnd, CDialogEx)
	ON_BN_CLICKED(IDC_QLSV_BTN, &MainWnd::OnBnClickedQlsvBtn)
	ON_BN_CLICKED(IDC_DSDIEM_BTN, &MainWnd::OnBnClickedDsdiemBtn)
END_MESSAGE_MAP()


// MainWnd message handlers


void MainWnd::OnBnClickedQlsvBtn()
{
	QLSV dlg;
	dlg.DoModal();

}


void MainWnd::OnBnClickedDsdiemBtn()
{
	// TODO: Add your control notification handler code here
	DanhSachSinhVienTheoKhoa dsdDlg;
	dsdDlg.DoModal();
}
