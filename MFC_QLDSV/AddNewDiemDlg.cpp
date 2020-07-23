// AddNewDiemDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "AddNewDiemDlg.h"
#include "afxdialogex.h"
#include "MFC_ViewSinhVienDlg.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"
#include "MFC_ViewSinhVienDlg.h"
#include < wchar.h >
#include <stdio.h>

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
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
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
	DDX_Text(pDX, IDC_MALOP_TXT, m_malop_val);
}


BEGIN_MESSAGE_MAP(AddNewDiemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NHAPDIEM_BTN, &AddNewDiemDlg::OnBnClickedNhapdiemBtn)
END_MESSAGE_MAP()

BOOL AddNewDiemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString diemqt, diemgk, diemck;
	if (maLop != "") {
		TRY{
			CString selectQuery;
			selectQuery.Format(L"SELECT MASSV,MALOP,DIEMQT,DIEMGK,DIEMCK,DIEM FROM KETQUA WHERE MASSV='%s' AND MALOP = '%s'", this->getMSSV(), this->getMaLop());
			CRecordset recset(&database);
			recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

			recset.GetFieldValue(L"DIEMQT", diemqt);
			recset.GetFieldValue(L"DIEMGK", diemgk);
			recset.GetFieldValue(L"DIEMCK", diemck);

			m_malop_val = this->getMaLop();
			m_diemqt_val = diemqt;
			m_diemgk_val = diemgk;
			m_diemck_val = diemck;
			UpdateData(FALSE);
		} 
		CATCH(CDBException ,e){
			AfxMessageBox(e->m_strError);
			return FALSE;
		}END_CATCH
	}
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
// AddNewDiemDlg message handlers

void AddNewDiemDlg::setMSSV(CString maSoSV) {
	mssv = maSoSV;
}

CString AddNewDiemDlg::getMSSV() {
	return mssv;
}

void AddNewDiemDlg::setMaLop(CString maLop) {
	this->maLop = maLop;
}

CString AddNewDiemDlg::getMaLop() {
	return maLop;
}

void AddNewDiemDlg::OnBnClickedNhapdiemBtn()
{
	UpdateData(TRUE);
	CString query;
	float diemqt, diemgk, diemck, diemtb;
	diemqt = _ttof(m_diemqt_val);
	diemgk = _ttof(m_diemgk_val);
	diemck = _ttof(m_diemck_val);
	diemtb = (diemqt * 0.1 + diemgk * 0.3 + diemck * 0.6);
	if (this->maLop != "") {
		query.Format(_T("UPDATE KETQUA SET DIEM = %f,DIEMQT = %f,DIEMGK = %f,DIEMCK =%f WHERE MASSV='%s' AND MALOP='%s'"), diemtb, diemqt, diemgk, diemck, mssv,maLop);
	}
	else {
		query.Format(_T("INSERT INTO KETQUA(MASSV,MALOP,DIEM,DIEMQT,DIEMGK,DIEMCK) VALUES ('%s','%s',%f,%f,%f,%f)"), mssv, m_malop_val, diemtb, diemqt, diemgk, diemck);
	}
	database.ExecuteSQL(query);
	AfxMessageBox(L"Đã thêm điểm cho sinh viên MSSV:" + mssv);
	
	EndDialog(0);
}



