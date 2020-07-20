// AddNewDiemDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "AddNewDiemDlg.h"
#include "afxdialogex.h"
#include "MFC_ViewSinhVienDlg.h"


// AddNewDiemDlg dialog

IMPLEMENT_DYNAMIC(AddNewDiemDlg, CDialogEx)

AddNewDiemDlg::AddNewDiemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THEMDIEM_DLG, pParent)
	, m_malop_val(_T(""))
	, m_diemqt_val(_T(""))
	, m_diemgk_val(_T(""))
	, m_diemck_val(_T(""))

{
	TRY{
		sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
		database.Open(NULL, false, false, sDsn);
		} CATCH(CDBException, e) {
			AfxMessageBox(L"Lỗi kết nối DB:" + e->m_strError);
		}END_CATCH
}

AddNewDiemDlg::~AddNewDiemDlg()
{
}

void AddNewDiemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MALOP_TXT, m_malop_val);
	DDX_Text(pDX, IDC_DIEMQT_TXT, m_diemqt_val);
	DDX_Text(pDX, IDC_DIEMGK_TXT, m_diemgk_val);
	DDX_Text(pDX, IDC_DIEMCK_TXT, m_diemck_val);
	DDX_Text(pDX, IDC_EDIT1, m_malop_val);
}


BEGIN_MESSAGE_MAP(AddNewDiemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NHAPDIEM_BTN, &AddNewDiemDlg::OnBnClickedNhapdiemBtn)
END_MESSAGE_MAP()


// AddNewDiemDlg message handlers

void AddNewDiemDlg::setMSSV(CString maSoSV) {
	mssv = maSoSV;
}
CString AddNewDiemDlg::getMSSV() {
	return mssv;
}
void AddNewDiemDlg::OnBnClickedNhapdiemBtn()
{
	UpdateData(TRUE);
	CString insertQuery;
	float diemqt, diemgk, diemck, diemtb;
	diemqt = _ttof(m_diemqt_val);
	diemgk = _ttof(m_diemgk_val);
	diemck = _ttof(m_diemck_val);
	diemtb = (diemqt * 0.1 + diemgk * 0.3 + diemck * 0.6);
	insertQuery.Format(_T("INSERT INTO KETQUA(MASSV,MALOP,DIEM,DIEMQT,DIEMGK,DIEMCK) VALUES ('%s','%s',%f,%f,%f,%f)"), mssv, m_malop_val, diemtb, diemqt, diemgk, diemck);
	database.ExecuteSQL(insertQuery);
	AfxMessageBox(L"Đã thêm điểm cho sinh viên MSSV:" + mssv);
	
	EndDialog(0);
}
