// QLSV.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "QLSV.h"
#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"
#include <stdio.h>

// QLSV dialog

IMPLEMENT_DYNAMIC(QLSV, CDialogEx)

QLSV::QLSV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSSVDlg, pParent)
	, m_mssv_val(_T(""))
	, m_hoten_val(_T(""))
	, m_dob_val(COleDateTime::GetCurrentTime())
	, m_address1_val(_T(""))
	, m_sdt_val(_T(""))
	, m_email_val(_T(""))
	, m_pwd_val(_T(""))
	, m_khoa_cbb_val(_T(""))
	, m_cmnd_val(_T(""))
	, m_pob_val(_T(""))
	, m_address2_val(_T(""))
	, m_nienkhoa_val(_T(""))
{
	TRY{
		sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
		database.Open(NULL, false, false, sDsn);
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Lỗi kết nối DB:" + e->m_strError);
	}END_CATCH

}

QLSV::~QLSV()
{
}

void QLSV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MSSV_TXT, m_mssv_val);
	DDX_Text(pDX, IDC_HOTEN_TXT, m_hoten_val);
	DDX_DateTimeCtrl(pDX, IDC_DOB_TXT, m_dob_val);
	DDX_Text(pDX, IDC_ADDRESS1_TXT, m_address1_val);
	DDX_Text(pDX, IDC_SDT_TXT, m_sdt_val);
	DDX_Text(pDX, IDC_EMAIL_TXT, m_email_val);
	DDX_Text(pDX, IDC_PWD_TXT, m_pwd_val);
	DDX_CBString(pDX, IDC_KHOA_CBB, m_khoa_cbb_val);
	DDX_Control(pDX, IDC_KHOA_CBB, m_khoacbb_ctrl);
	DDX_Text(pDX, IDC_CMND_TXT, m_cmnd_val);
	DDX_Control(pDX, IDC_CMND_TXT, m_cmnd_ctrl);
	DDX_Text(pDX, IDC_POB_TXT, m_pob_val);
	DDX_Text(pDX, IDC_ADDESS2_TXT, m_address2_val);
	DDX_Text(pDX, IDC_NIENKHOA_TXT, m_nienkhoa_val);
	DDX_Control(pDX, IDC_DSSV_LISTCTRL, m_dssv_listctrl);
}


BEGIN_MESSAGE_MAP(QLSV, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DSSV_LISTCTRL, &QLSV::OnLvnItemchangedDssvListctrl)
	ON_BN_CLICKED(IDC_XOASV_BTN, &QLSV::OnBnClickedXoasvBtn)
END_MESSAGE_MAP()


// QLSV message handlers


BOOL QLSV::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LoadDanhSachSinhVien();
	ListView_SetExtendedListViewStyle(m_dssv_listctrl, LVS_EX_GRIDLINES);
	m_dssv_listctrl.SetExtendedStyle(m_dssv_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//column width and heading
	m_dssv_listctrl.InsertColumn(0, L"MSSV", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(1, L"Họ Tên", LVCFMT_CENTER, 100);
	m_dssv_listctrl.InsertColumn(2, L"Ngày sinh", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(3, L"Nơi sinh", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(4, L"Khoa", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(5, L"Lớp sv", LVCFMT_CENTER, 150);
	m_dssv_listctrl.InsertColumn(6, L"Email", LVCFMT_LEFT, 100);
	m_dssv_listctrl.InsertColumn(7, L"ĐiểmTB", LVCFMT_LEFT, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX Property Pages should return FALSE
}
void QLSV::LoadDanhSachSinhVien() {
	TRY{
		CString selectQuery;
		CString mssv, hoten, ngaysinh, noisinh, tenkhoa, email, sdt, cmnd, address1, address2, nienkhoa, lopsv, avatar,diemtb;

		selectQuery.Format(_T("select mssv, hoten, ngaysinh, noisinh, tenkhoa, email,"
								"sdt, cmnd, address1, address2, nienkhoa, lopsv, avatar,diemtb " 
								"from sinhvien sv inner join khoa k on sv.makhoa = k.makhoa "));

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset content of listcontrol
		m_dssv_listctrl.DeleteAllItems();

		int iSinhVien = 0;

		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"mssv", mssv);
			recset.GetFieldValue(L"hoten", hoten);
			recset.GetFieldValue(L"ngaysinh", ngaysinh);
			recset.GetFieldValue(L"noisinh", noisinh);
			recset.GetFieldValue(L"tenkhoa", tenkhoa);
			recset.GetFieldValue(L"email", email);
			recset.GetFieldValue(L"sdt",sdt);
			recset.GetFieldValue(L"cmnd", cmnd);
			recset.GetFieldValue(L"address1", address1);
			recset.GetFieldValue(L"address2", address2);
			recset.GetFieldValue(L"nienkhoa", nienkhoa);
			recset.GetFieldValue(L"lopsv", lopsv);
			recset.GetFieldValue(L"avatar", avatar);
			recset.GetFieldValue(L"diemtb", diemtb);
			
			//insert value into list record
			iSinhVien = m_dssv_listctrl.InsertItem(0, mssv);
			m_dssv_listctrl.SetItemText(iSinhVien, 1, hoten);
			m_dssv_listctrl.SetItemText(iSinhVien, 2, ngaysinh);
			m_dssv_listctrl.SetItemText(iSinhVien, 3, noisinh);
			m_dssv_listctrl.SetItemText(iSinhVien, 4, tenkhoa);
			m_dssv_listctrl.SetItemText(iSinhVien, 5, lopsv);
			m_dssv_listctrl.SetItemText(iSinhVien, 6, email);
			m_dssv_listctrl.SetItemText(iSinhVien, 7, diemtb);
			//Move next
			recset.MoveNext();
		}
		UpdateData(FALSE);
		recset.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error:danh sach diem sinh vien " + e->m_strError);
	} END_CATCH
}

void QLSV::OnLvnItemchangedDssvListctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void QLSV::OnBnClickedXoasvBtn()
{
	int rowSelected = m_dssv_listctrl.GetSelectionMark();
	CString massv = m_dssv_listctrl.GetItemText(rowSelected, 0);
	AfxMessageBox(L"Xác nhận xoá sinh viên?", MB_YESNO | MB_ICONWARNING);
	if (IDYES) {
		TRY{
			CString deleteQuery;
			deleteQuery.Format(_T("DELETE FROM SINHVIEN WHERE MSSV = '%s'"), massv);
			database.ExecuteSQL(deleteQuery);
			LoadDanhSachSinhVien();
		}
			CATCH(CDBException, e) {
			AfxMessageBox(L"Xảy ra lỗi trong quá trình xoá Sinh Viên:"+ e->m_strError);
		} END_CATCH
	}
	else if (IDNO) {

	}

}
