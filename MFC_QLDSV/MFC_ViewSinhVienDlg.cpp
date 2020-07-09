// MFC_ViewSinhVien.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "MFC_ViewSinhVienDlg.h"
#include "afxdialogex.h"


// MFC_ViewSinhVien dialog

IMPLEMENT_DYNAMIC(MFC_ViewSinhVien, CDialogEx)

MFC_ViewSinhVien::MFC_ViewSinhVien(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWSV_DLG, pParent)
{

}

MFC_ViewSinhVien::~MFC_ViewSinhVien()
{
}

void MFC_ViewSinhVien::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFC_ViewSinhVien, CDialogEx)
	ON_BN_CLICKED(IDC_THEMDIEM_BTN, &MFC_ViewSinhVien::OnBnClickedThemdiemBtn)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb)
END_MESSAGE_MAP()


// MFC_ViewSinhVien message handlers


void MFC_ViewSinhVien::OnBnClickedThemdiemBtn()
{
	// TODO: Add your control notification handler code here
}


void MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb()
{

}
