// MFC_ViewSinhVien.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "MFC_ViewSinhVienDlg.h"
#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"

// MFC_ViewSinhVien dialog

IMPLEMENT_DYNAMIC(MFC_ViewSinhVien, CDialogEx)

MFC_ViewSinhVien::MFC_ViewSinhVien(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWSV_DLG, pParent)
	, m_dobsv_val(COleDateTime::GetCurrentTime())
	, m_emailsv_val(_T(""))
	, m_mssv_val(_T(""))
	, m_pobsv_val(_T(""))
	, m_sdtsv_val(_T(""))
	, m_timkiemdiem_ctrl(_T(""))
	, m_hotensv_val(_T(""))
{

}

MFC_ViewSinhVien::~MFC_ViewSinhVien()
{
}

void MFC_ViewSinhVien::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOA_CBB, m_khoa_ctrl);
	DDX_Control(pDX, IDC_EDITSV_BTN, m_editsv_btn);
	DDX_Control(pDX, IDC_SAVEEDIT_BTN, m_save_editsv_btn);
	DDX_DateTimeCtrl(pDX, IDC_DOBSV_TXT, m_dobsv_val);
	DDX_Text(pDX, IDC_EMAILSV_TXT, m_emailsv_val);
	DDX_Text(pDX, IDC_MSSV_TXT, m_mssv_val);
	DDX_Text(pDX, IDC_POBSV_TXT, m_pobsv_val);
	DDX_Text(pDX, IDC_SDTSV_TXT, m_sdtsv_val);
	DDX_Control(pDX, IDC_THEMDIEM_BTN, m_themdiem_ctrl);
	DDX_Text(pDX, IDC_TIMKIEMDIEM_TXT, m_timkiemdiem_ctrl);
	DDX_Control(pDX, IDC_TIMKIEMMH_BTN, m_timkiemmh_ctrl);
	DDX_Control(pDX, IDC_DIEMSV_LISTCRL, m_danhsachdiemsv_listctrl);
	DDX_Text(pDX, IDC_TENSV_TXT, m_hotensv_val);
	DDX_Control(pDX, IDC_TENSV_TXT, m_hotensv_ctrl);
	DDX_Control(pDX, IDC_DOBSV_TXT, m_dobsv_ctrl);
	DDX_Control(pDX, IDC_EMAILSV_TXT, m_emailsv_ctrl);
	DDX_Control(pDX, IDC_MSSV_TXT, m_mssv_ctrl);
	DDX_Control(pDX, IDC_POBSV_TXT, m_pobsv_ctrl);
	DDX_Control(pDX, IDC_SDTSV_TXT, m_sdtsv_ctrl);
}


BEGIN_MESSAGE_MAP(MFC_ViewSinhVien, CDialogEx)
	ON_BN_CLICKED(IDC_THEMDIEM_BTN, &MFC_ViewSinhVien::OnBnClickedThemdiemBtn)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb)
	ON_BN_CLICKED(IDC_EDITSV_BTN, &MFC_ViewSinhVien::OnBnClickedEditsvBtn)
	ON_BN_CLICKED(IDC_SAVEEDIT_BTN, &MFC_ViewSinhVien::OnBnClickedSaveeditBtn)
END_MESSAGE_MAP()


// MFC_ViewSinhVien message handlers
BOOL MFC_ViewSinhVien::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ListView_SetExtendedListViewStyle(m_danhsachdiemsv_listctrl, LVS_EX_GRIDLINES);
	m_danhsachdiemsv_listctrl.SetExtendedStyle(m_danhsachdiemsv_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//column width and heading
	m_danhsachdiemsv_listctrl.InsertColumn(0, L"Môn học", LVCFMT_CENTER, 150);
	m_danhsachdiemsv_listctrl.InsertColumn(1, L"Mã Lớp", LVCFMT_LEFT, 100);
	m_danhsachdiemsv_listctrl.InsertColumn(2, L"Điểm", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(3, L"Ngày bắt đầu", LVCFMT_LEFT, 100);
	m_danhsachdiemsv_listctrl.InsertColumn(4, L"Ngày kết thúc", LVCFMT_LEFT, 80);
	CString mssv;
	mssv = "4201104001";
	LoadThongTinSinhVien(mssv);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void MFC_ViewSinhVien::LoadThongTinSinhVien(CString mssv) {
	/*has issues: not yet get data from control in groupbox*/
	CDatabase database;
	CString sDsn;
	
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString selectQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strTenKhoa, strEmail, strSDT, strNoiSinh, strNgayBatDau, strNgayKetThuc;
		selectQuery.Format(_T("select MSSV, HOTEN, NGAYSINH, NOISINH, TENKHOA,TENMH, kq.MALOP as MALOP,DIEM,EMAIL,SDT,NGAYBATDAU, NGAYKETTHUC from SinhVien sv inner join Khoa k on sv.makhoa = k.makhoa inner join KetQua kq on sv.mssv = kq.massv inner join(select mh.mamh, TENMH, MALOP, TENLOP, NGAYBATDAU, NGAYKETTHUC from lop lp inner join monhoc mh on mh.mamh = lp.mamh) tmp on kq.malop = tmp.malop where mssv = '%s'"),mssv);
		
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset content of listcontrol
		m_danhsachdiemsv_listctrl.DeleteAllItems();

		int iDiemMonHoc = 0;
		
		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MSSV", strMSSV);
			recset.GetFieldValue(L"HOTEN", strHoTen);
			recset.GetFieldValue(L"NGAYSINH", strNgaySinh);
			recset.GetFieldValue(L"NOISINH", strNoiSinh);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);
			recset.GetFieldValue(L"TENMH", strMonHoc);
			recset.GetFieldValue(L"MALOP", strMaLop);
			recset.GetFieldValue(L"DIEM", diem);
			recset.GetFieldValue(L"EMAIL", strEmail);
			recset.GetFieldValue(L"SDT",strSDT);
			recset.GetFieldValue(L"NGAYBATDAU",strNgayBatDau);
			recset.GetFieldValue(L"NGAYKETTHUC",strNgayKetThuc);

			//insert value into list record
			iDiemMonHoc = m_danhsachdiemsv_listctrl.InsertItem(0, strMonHoc);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 1, strMaLop);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 2, diem);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 3, strNgayBatDau);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 4, strNgayKetThuc);
			//Move next
			recset.MoveNext();

		}
		m_khoa_ctrl.AddString(strTenKhoa);
		m_khoa_ctrl.SetCurSel(0);
		m_hotensv_val = strHoTen;
		m_emailsv_val = strEmail;
		m_dobsv_val.ParseDateTime(strNgaySinh);
		m_mssv_val = strMSSV;
		m_pobsv_val = strNoiSinh;
		m_sdtsv_val = strSDT;
		UpdateData(FALSE);
		recset.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error:danh sach diem sinh vien " + e->m_strError);
	} END_CATCH
}
void MFC_ViewSinhVien::OnBnClickedThemdiemBtn()
{
	
}

void MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb()
{

}





void MFC_ViewSinhVien::OnBnClickedEditsvBtn()
{
	m_khoa_ctrl.EnableWindow(TRUE);
	 m_hotensv_ctrl.EnableWindow(TRUE);
	 m_dobsv_ctrl.EnableWindow(TRUE);
     m_emailsv_ctrl.EnableWindow(TRUE);
	 m_mssv_ctrl.EnableWindow(TRUE);
	 m_pobsv_ctrl.EnableWindow(TRUE);
	 m_sdtsv_ctrl.EnableWindow(TRUE);
}


void MFC_ViewSinhVien::OnBnClickedSaveeditBtn()
{
	UpdateData(TRUE);
	/*has issues: not yet get data from control in groupbox*/
	CDatabase database;
	CString sDsn;

	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString insertQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strTenKhoa, strEmail, strSDT, strNoiSinh, strNgayBatDau, strNgayKetThuc;
		insertQuery.Format();

		CRecordset recset(&database);

		database.Close();

	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error:danh sach diem sinh vien " + e->m_strError);
	} END_CATCH

}
