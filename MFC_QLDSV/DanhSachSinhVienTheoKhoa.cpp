// DanhSachSinhVienTheoKhoa.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "DanhSachSinhVienTheoKhoa.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"


// DanhSachSinhVienTheoKhoa dialog

IMPLEMENT_DYNAMIC(DanhSachSinhVienTheoKhoa, CDialogEx)

DanhSachSinhVienTheoKhoa::DanhSachSinhVienTheoKhoa(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSDSV_DLG, pParent)
	, m_newmssv_val(_T(""))
	, m_newmalop_val(_T(""))
	, m_newdiem_val(_T(""))
	, m_filterkhoa_val(_T(""))
{

}

DanhSachSinhVienTheoKhoa::~DanhSachSinhVienTheoKhoa()
{
}

void DanhSachSinhVienTheoKhoa::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEWMSSV_TXT, m_newmssv_val);
	DDX_CBString(pDX, IDC_MALOP_CBB2, m_newmalop_val);
	DDX_Text(pDX, IDC_NEWDIEM_TXT, m_newdiem_val);
	DDX_Control(pDX, IDC_NEWMSSV_TXT, m_newmssv_ctrl);
	DDX_CBString(pDX, IDC_KHOA_CBB, m_filterkhoa_val);
	DDX_Control(pDX, IDC_MONHOC_CBB, m_filterKhoa_ctrl);
	DDX_Control(pDX, IDC_KHOA_CBB, m_filterKhoa_ctrl);
}


BEGIN_MESSAGE_MAP(DanhSachSinhVienTheoKhoa, CDialogEx)
	ON_BN_CLICKED(IDC_NHAPDIEM_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedNhapdiemBtn)
	ON_EN_CHANGE(IDC_NEWMSSV_TXT, &DanhSachSinhVienTheoKhoa::OnEnChangeNewmssvTxt)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeKhoaCbb)
	ON_CBN_SELCHANGE(IDC_MONHOC_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeMonhocCbb)
END_MESSAGE_MAP()


// DanhSachSinhVienTheoKhoa message handlers
BOOL DanhSachSinhVienTheoKhoa::OnInitDialog() {
	CDialogEx::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//load du lieu len filter combobox khoa
	CDatabase database;
	CString sDsn;
	CString maKhoa,strMaKhoa,tenKhoa, strTenKhoa;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		
		CString selectQuery;
		selectQuery.Format(_T("SELECT MAKHOA, TENKHOA FROM KHOA"));
		
		CRecordset recsetKhoa(&database);

		recsetKhoa.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);
	
		while (!recsetKhoa.IsEOF()) {
			recsetKhoa.GetFieldValue(_T("MAKHOA"),maKhoa);
			recsetKhoa.GetFieldValue(_T("TENKHOA"), strTenKhoa);
			strMaKhoa += maKhoa;
		}

		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
		return TRUE;
}

//Thực hiện lưu thông tin điểm mới nhập vào bảng kết quả
void DanhSachSinhVienTheoKhoa::OnBnClickedNhapdiemBtn()
{
	/*has issues: not yet get data from control in groupbox*/
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CRecordset recset(&database);
		CString insertQuery;
		CString strMSSV, strMaLop;
		strMSSV = m_newmssv_val;
		strMaLop = m_newmalop_val;
		float strDiem = _ttof(m_newdiem_val);
		insertQuery.Format(_T("INSERT INTO KETQUA(MASSV,MALOP,DIEM) VALUES ('%s','%s',%f)"), m_newmssv_val, m_newmalop_val, strDiem);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm điểm cho sinh viên MSSV:"+m_newmssv_val);
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}


void DanhSachSinhVienTheoKhoa::OnEnChangeNewmssvTxt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void DanhSachSinhVienTheoKhoa::OnCbnSelchangeKhoaCbb()
{
	// TODO: Add your control notification handler code here
	CString khoa;
	khoa = m_filterkhoa_val;
}


void DanhSachSinhVienTheoKhoa::OnCbnSelchangeMonhocCbb()
{
	// TODO: Add your control notification handler code here
}
