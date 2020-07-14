// DanhSachSinhVienTheoKhoa.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "DanhSachSinhVienTheoKhoa.h"
#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"
#include "MFC_ViewSinhVienDlg.h"


// DanhSachSinhVienTheoKhoa dialog

IMPLEMENT_DYNAMIC(DanhSachSinhVienTheoKhoa, CDialogEx)

DanhSachSinhVienTheoKhoa::DanhSachSinhVienTheoKhoa(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSDSV_DLG, pParent)
	, m_newmssv_val(_T(""))
	, m_newdiem_val(_T(""))
	, m_filterkhoa_val(_T(""))
	, m_newtenlop_txt(_T(""))
	, m_newmalop_val(_T(""))
	, m_timkiemsv_txt(_T(""))
	, m_filterMonHoc_val(_T(""))
{

}

DanhSachSinhVienTheoKhoa::~DanhSachSinhVienTheoKhoa()
{
}

BOOL DanhSachSinhVienTheoKhoa::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	FillNewClassControl();
	FillFilterDepartmentControl();
	FillFilterSubjectControl();
	FillFilterClassControl();
	ListView_SetExtendedListViewStyle(m_dssv_listctrl, LVS_EX_GRIDLINES);
	m_dssv_listctrl.SetExtendedStyle(m_dssv_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//column width and heading
	m_dssv_listctrl.InsertColumn(0, L"MSSV", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(1, L"Họ Tên", LVCFMT_CENTER, 100);
	m_dssv_listctrl.InsertColumn(2, L"Ngày sinh", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(3, L"Khoa", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(4, L"Môn học", LVCFMT_CENTER, 150);
	m_dssv_listctrl.InsertColumn(5, L"Mã Lớp", LVCFMT_LEFT, 100);
	m_dssv_listctrl.InsertColumn(6, L"Điểm", LVCFMT_LEFT, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void DanhSachSinhVienTheoKhoa::FillNewClassControl() {
	CDatabase database;
	CString sDsn;//data source name
	CString strMaLop, strTenLop;
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");

	TRY{
		database.Open(NULL,false,false,sDsn);
		
		CString selectQuery;
		selectQuery.Format(_T("SELECT MALOP,TENLOP FROM LOP"));

		CRecordset recsetLop(&database);

		recsetLop.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		while (!recsetLop.IsEOF()) {
			recsetLop.GetFieldValue(L"MALOP",strMaLop);
			m_newmalop_ctrl.AddString(strMaLop);
			recsetLop.MoveNext();
		}
		recsetLop.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox Lop: " + e->m_strError);
	} END_CATCH

}
void DanhSachSinhVienTheoKhoa::FillFilterSubjectControl() {
	//load du lieu len filter combobox subject
	CDatabase database;
	CString sDsn;
	CString strMaMonHoc, strTenMonHoc;
	//	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");

	TRY{
		database.Open(NULL,false,false,sDsn);

		CString selectQuery;
		selectQuery.Format(_T("SELECT MAMH,TENMH FROM MONHOC"));

		CRecordset recsetMonHoc(&database);

		recsetMonHoc.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		while (!recsetMonHoc.IsEOF()) {
			recsetMonHoc.GetFieldValue(L"MAMH",strMaMonHoc);
			recsetMonHoc.GetFieldValue(L"TENMH", strTenMonHoc);
			m_filterMonHoc_ctrl.AddString(strTenMonHoc);
			recsetMonHoc.MoveNext();
		}
		recsetMonHoc.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox mon hoc: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::FillFilterClassControl() {
	//load du lieu len filter combobox subject
	CDatabase database;
	CString sDsn;
	CString strMaLop, strTenLop;
	//	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");

	TRY{
		database.Open(NULL,false,false,sDsn);

		CString selectQuery;
		selectQuery.Format(_T("SELECT MALOP,TENLOP,MAMH FROM LOP"));

		CRecordset recsetLop(&database);

		recsetLop.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		while (!recsetLop.IsEOF()) {
			recsetLop.GetFieldValue(L"MALOP",strMaLop);
			recsetLop.GetFieldValue(L"TENLOP", strTenLop);
			m_filterMaLop_ctrl.AddString(strMaLop +"-"+ strTenLop);
			recsetLop.MoveNext();
		}
		recsetLop.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox lop: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::FillFilterDepartmentControl() {
	//load du lieu len filter combobox khoa
	CDatabase database;
	CString sDsn;
	CString strMaKhoa, strTenKhoa;
	//	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");

	TRY{
		database.Open(NULL,false,false,sDsn);

		CString selectQuery;
		selectQuery.Format(_T("SELECT MAKHOA,TENKHOA FROM KHOA"));

		CRecordset recsetKhoa(&database);

		recsetKhoa.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		while (!recsetKhoa.IsEOF()) {
			recsetKhoa.GetFieldValue(L"MAKHOA",strMaKhoa);
			recsetKhoa.GetFieldValue(L"TENKHOA", strTenKhoa);
			m_filterKhoa_ctrl.AddString(strTenKhoa);
			recsetKhoa.MoveNext();
		}
		recsetKhoa.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox khoa: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEWMSSV_TXT, m_newmssv_val);
	DDX_Text(pDX, IDC_NEWDIEM_TXT, m_newdiem_val);
	DDX_Control(pDX, IDC_NEWMSSV_TXT, m_newmssv_ctrl);
	DDX_CBString(pDX, IDC_KHOA_CBB, m_filterkhoa_val);
	DDX_Control(pDX, IDC_KHOA_CBB, m_filterKhoa_ctrl);
	DDX_Control(pDX, IDC_NEWMALOP_CBB, m_newmalop_ctrl);
	DDX_CBString(pDX, IDC_NEWMALOP_CBB, m_newmalop_val);
	DDX_Text(pDX, IDC_NEWTENLOP_TXT, m_newtenlop_txt);

	DDX_Control(pDX, IDC_MONHOC_CBB, m_filterMonHoc_ctrl);
	DDX_Control(pDX, IDC_MALOP_CBB, m_filterMaLop_ctrl);
	DDX_Control(pDX, IDC_DSDSVTK_LISTCTRL, m_dssv_listctrl);
	DDX_Text(pDX, IDC_TIMKIEMSV_TXT, m_timkiemsv_txt);
	DDX_Control(pDX, IDC_XEMCHITIET_BTN, m_xemchitiet_ctrl);
	DDX_CBString(pDX, IDC_MONHOC_CBB, m_filterMonHoc_val);
}


BEGIN_MESSAGE_MAP(DanhSachSinhVienTheoKhoa, CDialogEx)
	ON_BN_CLICKED(IDC_NHAPDIEM_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedNhapdiemBtn)
	ON_EN_CHANGE(IDC_NEWMSSV_TXT, &DanhSachSinhVienTheoKhoa::OnEnChangeNewmssvTxt)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeKhoaCbb)
	ON_CBN_SELCHANGE(IDC_MONHOC_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeMonhocCbb)
	ON_CBN_SELCHANGE(IDC_NEWMALOP_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeNewmalopCbb)
	ON_BN_CLICKED(IDC_XEMCHITIET_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedXemchitietBtn)
	ON_BN_CLICKED(IDC_XEM_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedXemBtn)
	ON_BN_CLICKED(IDC_TIMKIEMSV_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedTimkiemsvBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DSDSVTK_LISTCTRL, &DanhSachSinhVienTheoKhoa::OnLvnItemchangedDsdsvtkListctrl)
	ON_CBN_SELCHANGE(IDC_MALOP_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeMalopCbb)
END_MESSAGE_MAP()


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
		UpdateData(TRUE);
		strMSSV = m_newmssv_val;
		m_newmalop_ctrl.GetLBText(m_newmalop_ctrl.GetCurSel(), strMaLop);
		float strDiem = _ttof(m_newdiem_val);
		insertQuery.Format(_T("INSERT INTO KETQUA(MASSV,MALOP,DIEM) VALUES ('%s','%s',%f)"), m_newmssv_val, m_newmalop_val, strDiem);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm điểm cho sinh viên MSSV:"+m_newmssv_val);
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error of them moi diem cho sinh vien: " + e->m_strError);
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
	int indexCCB = m_filterKhoa_ctrl.GetCurSel();
	//lay gia tri tai index do
	m_filterKhoa_ctrl.GetLBText(indexCCB,khoa);
	
	//load combobox Môn học và mã lớp
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString selectQuery;
		CString strMaMonHoc, strTenMonHoc, strMaLop, strTenLop;
		selectQuery.Format(_T("select MAMH, TENMH from MONHOC where MAKHOA in (select MAKHOA from KHOA where TENKHOA = N'%s')"),khoa);
	
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset combobox
		m_filterMonHoc_ctrl.ResetContent();
		
		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAMH", strMaMonHoc);
			recset.GetFieldValue(L"TENMH", strTenMonHoc);

			m_filterMonHoc_ctrl.AddString(strTenMonHoc);
			//Move next
			recset.MoveNext();
		}
		m_filterMonHoc_ctrl.SetCurSel(0);
		OnCbnSelchangeMonhocCbb();
		recset.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error of combox mamh,malop: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::OnCbnSelchangeMonhocCbb()
{
	// TODO: Add your control notification handler code here
	CString monHoc;
	monHoc = m_filterMonHoc_val;
	int indexCCB = m_filterMonHoc_ctrl.GetCurSel();
	//lay gia tri tai index do
	m_filterMonHoc_ctrl.GetLBText(indexCCB, monHoc);

	//load combobox mã lớp
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString selectQuery;
		CString strMaLop, strTenLop;
		selectQuery.Format(_T("select MALOP, TENLOP from LOP where MAMH in (select MAMH from MONHOC where TENMH = N'%s')"),monHoc);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset combobox
		m_filterMaLop_ctrl.ResetContent();

		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MALOP", strMaLop);
			recset.GetFieldValue(L"TENLOP", strTenLop);

			m_filterMaLop_ctrl.AddString(strMaLop);
			//Move next
			recset.MoveNext();
		}
		m_filterMaLop_ctrl.SetCurSel(0);
		recset.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error of combox malop: " + e->m_strError);
	} END_CATCH
}


void DanhSachSinhVienTheoKhoa::OnCbnSelchangeMalopCbb()
{
	// TODO: Add your control notification handler code here
}

void DanhSachSinhVienTheoKhoa::OnCbnSelchangeNewmalopCbb()
{
	// TODO: Add your control notification handler code here
	CString maLop;
	m_newmalop_ctrl.GetLBText(m_newmalop_ctrl.GetCurSel(),maLop);
	UpdateData(FALSE);
	m_newtenlop_txt = maLop;
}


void DanhSachSinhVienTheoKhoa::OnBnClickedXemchitietBtn()
{
	MFC_ViewSinhVien viewSVDlg;
	viewSVDlg.DoModal();
}


void DanhSachSinhVienTheoKhoa::OnBnClickedXemBtn()
{
	// TODO: Add your control notification handler code here
	CString maKhoa, maMonHoc, maLop;
	m_filterKhoa_ctrl.GetLBText(m_filterKhoa_ctrl.GetCurSel(), maKhoa);
	//m_filterMonHoc_ctrl.GetLBText(m_filterMonHoc_ctrl.GetCurSel(),maMonHoc);
	//m_filterMaLop_ctrl.GetLBText(m_filterMaLop_ctrl.GetCurSel(),maLop);

	/*has issues: not yet get data from control in groupbox*/
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString selectQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strTenKhoa;
		selectQuery.Format(_T("select MASSV,HOTEN,NGAYSINH,TENKHOA,TENMH,MAMH,tmp1.MALOP,DIEM from ketqua kq inner join (select MSSV, HOTEN, NGAYSINH, TENKHOA, sv.MAKHOA from sinhvien SV inner join Khoa k on sv.makhoa = k.makhoa) sinhvien on kq.massv = sinhvien.mssv inner join (select TENMH, mh.MAMH, MALOP from monhoc mh inner join lop lp on lp.mamh = mh.mamh) tmp1 on tmp1.malop = kq.malop"));
		if (!maKhoa.IsEmpty() || !maMonHoc.IsEmpty() || !maLop.IsEmpty()) {
			selectQuery += " where ";
		}
		BOOL checkAndCondition = FALSE;
		//định dạng chuỗi tìm kiếm : TENKHOA = N''
		if (!maKhoa.IsEmpty()) {
			selectQuery += L"TENKHOA LIKE N'" + maKhoa + L"'";
		}
		if (!maMonHoc.IsEmpty()) {
			selectQuery += L"TENMH LIKE N'" + maMonHoc + L"'";
		}
		if (!maLop.IsEmpty()) {
			selectQuery += L"MALOP LIKE N'" + maLop + L"'";
		}
		CRecordset recsetSV(&database);

		recsetSV.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset content of listcontrol
		m_dssv_listctrl.DeleteAllItems();

		int iSinhVien = 0;
		//loop all the row result
		while (!recsetSV.IsEOF()) { //EOF: end of file
			recsetSV.GetFieldValue(L"MASSV", strMSSV);
			recsetSV.GetFieldValue(L"HOTEN", strHoTen);
			recsetSV.GetFieldValue(L"NGAYSINH", strNgaySinh);
			recsetSV.GetFieldValue(L"TENKHOA", strTenKhoa);
			recsetSV.GetFieldValue(L"TENMH", strMonHoc);
			recsetSV.GetFieldValue(L"MALOP", strMaLop);
			recsetSV.GetFieldValue(L"DIEM", diem);

			//insert value into list record
			iSinhVien = m_dssv_listctrl.InsertItem(0, strMSSV);
			m_dssv_listctrl.SetItemText(iSinhVien, 1, strHoTen);
			m_dssv_listctrl.SetItemText(iSinhVien, 2, strNgaySinh);
			m_dssv_listctrl.SetItemText(iSinhVien, 3, strTenKhoa);
			m_dssv_listctrl.SetItemText(iSinhVien, 4, strMonHoc);
			m_dssv_listctrl.SetItemText(iSinhVien, 5, strMaLop);
			m_dssv_listctrl.SetItemText(iSinhVien, 6, diem);
			//Move next
			recsetSV.MoveNext();

		}
		recsetSV.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}

//tim kiem theo mssv
void DanhSachSinhVienTheoKhoa::OnBnClickedTimkiemsvBtn()
{
	UpdateData(TRUE);
	/*has issues: not yet get data from control in groupbox*/
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		
		CString findQuery;
		CString strMSSV, strHoTen, strNgaySinh, strTenKhoa; 

		CRecordset recsetSV(&database);
		
		findQuery.Format(_T("SELECT MSSV,HOTEN, NGAYSINH, sv.MAKHOA,TENKHOA FROM SINHVIEN  SV INNER JOIN KHOA K ON SV.MAKHOA = K.MAKHOA WHERE MSSV LIKE '%s'"),m_timkiemsv_txt);

		recsetSV.Open(CRecordset::forwardOnly, findQuery, CRecordset::readOnly);
		
		int iSinhVien = 0;
		//loop all the row result
		while (!recsetSV.IsEOF()) { //EOF: end of file
			recsetSV.GetFieldValue(L"MSSV", strMSSV);
			recsetSV.GetFieldValue(L"HOTEN", strHoTen); 
			recsetSV.GetFieldValue(L"NGAYSINH", strNgaySinh);
			recsetSV.GetFieldValue(L"TENKHOA", strTenKhoa);

			//insert value into list record
			iSinhVien = m_dssv_listctrl.InsertItem(0, strMSSV);
			m_dssv_listctrl.SetItemText(iSinhVien, 1, strHoTen);
			m_dssv_listctrl.SetItemText(iSinhVien, 2, strNgaySinh);
			m_dssv_listctrl.SetItemText(iSinhVien, 3, strTenKhoa);
			//Move next
			recsetSV.MoveNext();

		}
		recsetSV.Close();
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}


void DanhSachSinhVienTheoKhoa::OnLvnItemchangedDsdsvtkListctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
}



