// ChuongTrinhDaoTao.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "ChuongTrinhDaoTao.h"
#include "afxdialogex.h"


// ChuongTrinhDaoTao dialog

IMPLEMENT_DYNAMIC(ChuongTrinhDaoTao, CDialogEx)

ChuongTrinhDaoTao::ChuongTrinhDaoTao(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTDT_DLG, pParent)
	, m_makhoa_val(_T(""))
	, m_tenkhoa_val(_T(""))
	, m_khoacbb_val(_T(""))
	, m_mamh_val(_T(""))
	, m_tenmh_val(_T(""))
	, m_malop_val(_T(""))
	, m_tenlop_val(_T(""))
{
	makhoa = "";
	tenkhoa = "";
	tenmh = "";
	mamh = "";
	malop = "";
	tenlop = "";
	TRY{
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
		database.Open(NULL, false, false, sDsn);
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Lỗi kết nối DB:" + e->m_strError);
	}END_CATCH
}

ChuongTrinhDaoTao::~ChuongTrinhDaoTao()
{
}

void ChuongTrinhDaoTao::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAKHOA_TXT, m_makhoa_val);
	DDX_Text(pDX, IDC_TENKHOA_TXT, m_tenkhoa_val);
	DDX_Control(pDX, IDC_KHOAMON_CBB, m_khoacbb_ctrl);
	DDX_CBString(pDX, IDC_KHOAMON_CBB, m_khoacbb_val);
	DDX_Control(pDX, IDC_MAMH_TXT, m_mamh_ctrl);
	DDX_Text(pDX, IDC_MAMH_TXT, m_mamh_val);
	DDX_Control(pDX, IDC_TENMH_TXT, m_tenmh_ctrl);
	DDX_Text(pDX, IDC_TENMH_TXT, m_tenmh_val);
	DDX_Control(pDX, IDC_LOPKHOA_CBB, m_lopkhoacbb_Ctrl);
	DDX_Control(pDX, IDC_LOPMH_CBB, m_lopmhcbb_ctrl);
	DDX_Text(pDX, IDC_MALOP, m_malop_val);
	DDX_Control(pDX, IDC_MALOP, m_malop_ctrl);
	DDX_Control(pDX, IDC_TENLOP_TXT, m_tenlop_ctrl);
	DDX_Text(pDX, IDC_TENLOP_TXT, m_tenlop_val);
	DDX_Control(pDX, IDC_SAVELOP_BTN, m_savelop_ctrl);
	DDX_Control(pDX, IDC_SAVEMH_BTN, m_savemh_ctrl);
	DDX_Control(pDX, IDC_SAVEKHOA_BTN, m_savekhoa_ctrl);
	DDX_Control(pDX, IDC_FIELD1_CBB, m_field1cbb_ctrl);
	DDX_Control(pDX, IDC_FIELD2_CBB, m_field2cbb_ctrl);
	DDX_Control(pDX, IDC_FILTER_BTN, m_filter_ctrl);
	DDX_Control(pDX, IDC_LISTCTRL, m_listctrl);
}


BEGIN_MESSAGE_MAP(ChuongTrinhDaoTao, CDialogEx)
	ON_BN_CLICKED(IDC_ADDKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedAddkhoaBtn)
	ON_BN_CLICKED(IDC_EDITKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedEditkhoaBtn)
	ON_BN_CLICKED(IDC_SAVEKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedSavekhoaBtn)
	ON_BN_CLICKED(IDC_DELETEKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedDeletekhoaBtn)
	ON_BN_CLICKED(IDC_ADDMH_BTN, &ChuongTrinhDaoTao::OnBnClickedAddmhBtn)
END_MESSAGE_MAP()


// ChuongTrinhDaoTao message handlers


void ChuongTrinhDaoTao::OnBnClickedAddkhoaBtn()
{
	TRY{
		CString insertQuery;
		UpdateData(TRUE);
		insertQuery.Format(_T("INSERT INTO KHOA(MAKHOA, TENKHOA) VALUES ('%s','%s')"),m_makhoa_val, m_tenkhoa_val);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm khoa");
	} CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
		return;
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedEditkhoaBtn()
{
	int rowSelected = m_listctrl.GetSelectionMark();
	CString maKhoaSelected = m_listctrl.GetItemText(rowSelected, 0);
	CString tenKhoaSelected = m_listctrl.GetItemText(rowSelected, 1);
	m_makhoa_val = maKhoaSelected;
	m_savekhoa_ctrl.EnableWindow(TRUE);
	m_tenkhoa_val = tenKhoaSelected;
	UpdateData(FALSE);
}


void ChuongTrinhDaoTao::OnBnClickedSavekhoaBtn()
{
	UpdateData(TRUE);
	CString tenKhoaEdit;
	tenKhoaEdit = m_tenkhoa_val;
	CString updateQuery;
	TRY{
		updateQuery.Format(L"UPDATE KHOA SET MAKHOA= N'%s' where MAKHOA = N'%s'", m_tenkhoa_val, m_makhoa_val);
	}CATCH(CDBException, e) {
		AfxMessageBox(L"Đã update thông tin khoa");
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedDeletekhoaBtn()
{
	int rowSelected = m_listctrl.GetSelectionMark();
	CString maKhoaSelected = m_listctrl.GetItemText(rowSelected, 0);
	CString deleteQuery;
	deleteQuery.Format(L"DELETE FROM KHOA WHERE MAKHOA = '%s'", maKhoaSelected);
	TRY{
		database.ExecuteSQL(deleteQuery);
		AfxMessageBox(L"Đã xóa thông tin khoa");
	} CATCH(CDBException ,e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedAddmhBtn()
	TRY{
		CString insertQuery,makhoa;
		UpdateData(TRUE);
		CString selectQuery;
		CString tenkhoa;
		m_khoacbb_ctrl.GetLBText(m_khoacbb_ctrl.GetCurSel(), tenkhoa);
		
		CRecordset recsetKhoa(&database);

		recsetKhoa.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);
		
		recsetKhoa.GetFieldValue(L"MAKHOA", makhoa);

		recsetKhoa.Close();
		
		CString insertQuery;
		insertQuery.Format(L"INSERT INTO MONHOC(MAMH, TENMH, MAKHOA) VALUES (N'%s',N'%s',N'%s')",m_mamh_val,m_tenmh_val,makhoa);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm thông tin môn học");
	} CATCH(CDBException ,e) {
		AfxMessageBox(e->m_strError);
	} END_CATCH
}
