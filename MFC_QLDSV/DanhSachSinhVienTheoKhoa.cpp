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
#include < wchar.h >
#include <stdio.h>
#include <vector> 
using namespace std;
// DanhSachSinhVienTheoKhoa dialog

IMPLEMENT_DYNAMIC(DanhSachSinhVienTheoKhoa, CDialogEx)

DanhSachSinhVienTheoKhoa::DanhSachSinhVienTheoKhoa(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSDSV_DLG, pParent)
	, m_newmssv_val(_T(""))
	, m_newdiem_val(_T(""))
	, m_filterkhoa_val(_T(""))
	, m_newmalop_val(_T(""))
	, m_timkiemsv_txt(_T(""))
	, m_filterMonHoc_val(_T(""))
	, m_newdiemck_val(_T(""))
	, m_newdiemgk_val(_T(""))
	, m_pathfile_val(_T(""))
{
	TRY{
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
		database.Open(NULL, false, false, sDsn);
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Lỗi kết nối DB:" + e->m_strError);
	}END_CATCH
}

DanhSachSinhVienTheoKhoa::~DanhSachSinhVienTheoKhoa()
{
	database.Close();
}

BOOL DanhSachSinhVienTheoKhoa::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	FillNewClassControl();
	FillFilterDepartmentControl();
	FillFilterSubjectControl();
	FillFilterClassControl();

	m_filterKhoa_ctrl.SetCurSel(0);
	m_filterMonHoc_ctrl.SetCurSel(0);
	m_filterMaLop_ctrl.SetCurSel(0);

	ListView_SetExtendedListViewStyle(m_dssv_listctrl, LVS_EX_GRIDLINES);
	m_dssv_listctrl.SetExtendedStyle(m_dssv_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//column width and heading
	m_dssv_listctrl.InsertColumn(0, L"MSSV", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(1, L"Họ Tên", LVCFMT_CENTER, 100);
	m_dssv_listctrl.InsertColumn(2, L"Ngày sinh", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(3, L"Khoa", LVCFMT_CENTER, 80);
	m_dssv_listctrl.InsertColumn(4,	L"Môn học", LVCFMT_CENTER, 150);
	m_dssv_listctrl.InsertColumn(5, L"Mã Lớp", LVCFMT_LEFT, 100);
	m_dssv_listctrl.InsertColumn(6, L"ĐiểmTB", LVCFMT_LEFT, 80);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void DanhSachSinhVienTheoKhoa::FillNewClassControl() {
	CString strMaLop, strTenLop;
	CString selectQuery;
	selectQuery.Format(_T("SELECT MALOP,TENLOP FROM LOP"));
	TRY{
	CRecordset recsetLop(&database);

		recsetLop.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		while (!recsetLop.IsEOF()) {
			recsetLop.GetFieldValue(L"MALOP",strMaLop);
			m_newmalop_ctrl.AddString(strMaLop);
			recsetLop.MoveNext();
		}
		recsetLop.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox Lop: " + e->m_strError);
	} END_CATCH

}
void DanhSachSinhVienTheoKhoa::FillFilterSubjectControl() {
	//load du lieu len filter combobox subject
	CString strMaMonHoc, strTenMonHoc;
	TRY{
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
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox mon hoc: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::FillFilterClassControl() {
	//load du lieu len filter combobox subject
	CString strMaLop, strTenLop;
	TRY{
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
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox lop: " + e->m_strError);
	} END_CATCH
}

void DanhSachSinhVienTheoKhoa::FillFilterDepartmentControl() {
	//load du lieu len filter combobox khoa
	CString strMaKhoa, strTenKhoa;
	TRY{
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

	DDX_Control(pDX, IDC_MONHOC_CBB, m_filterMonHoc_ctrl);
	DDX_Control(pDX, IDC_MALOP_CBB, m_filterMaLop_ctrl);
	DDX_Control(pDX, IDC_DSDSVTK_LISTCTRL, m_dssv_listctrl);
	DDX_Text(pDX, IDC_TIMKIEMSV_TXT, m_timkiemsv_txt);
	DDX_Control(pDX, IDC_XEMCHITIET_BTN, m_xemchitiet_ctrl);
	DDX_CBString(pDX, IDC_MONHOC_CBB, m_filterMonHoc_val);
	DDX_Control(pDX, IDC_NEWDIEMGK_TXT, m_newdiemgk_txt);
	DDX_Text(pDX, IDC_NEWDIEMCK_TXT, m_newdiemck_val);
	DDX_Text(pDX, IDC_NEWDIEMGK_TXT, m_newdiemgk_val);
	DDX_Text(pDX, IDC_TENFILE_TXT, m_pathfile_val);
	DDX_Control(pDX, IDC_UPLOADFILE_BTN, m_uploadfile_ctrl);
}


BEGIN_MESSAGE_MAP(DanhSachSinhVienTheoKhoa, CDialogEx)
	ON_BN_CLICKED(IDC_NHAPDIEM_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedNhapdiemBtn)
	ON_EN_CHANGE(IDC_NEWMSSV_TXT, &DanhSachSinhVienTheoKhoa::OnEnChangeNewmssvTxt)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeKhoaCbb)
	ON_CBN_SELCHANGE(IDC_MONHOC_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeMonhocCbb)
	ON_BN_CLICKED(IDC_XEMCHITIET_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedXemchitietBtn)
	ON_BN_CLICKED(IDC_XEM_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedXemBtn)
	ON_BN_CLICKED(IDC_TIMKIEMSV_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedTimkiemsvBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DSDSVTK_LISTCTRL, &DanhSachSinhVienTheoKhoa::OnLvnItemchangedDsdsvtkListctrl)
	ON_CBN_SELCHANGE(IDC_MALOP_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeMalopCbb)
	ON_BN_CLICKED(IDC_IMPORTFILE_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedImportfileBtn)
	ON_CBN_SELCHANGE(IDC_NEWMALOP_CBB, &DanhSachSinhVienTheoKhoa::OnCbnSelchangeNewmalopCbb)
	ON_BN_CLICKED(IDC_UPLOADFILE_BTN, &DanhSachSinhVienTheoKhoa::OnBnClickedUploadfileBtn)
END_MESSAGE_MAP()


//Thực hiện lưu thông tin điểm mới nhập vào bảng kết quả
void DanhSachSinhVienTheoKhoa::OnBnClickedNhapdiemBtn()
{
	TRY{
		CRecordset recset(&database);
		CString insertQuery;
		CString strMSSV, strMaLop;
		UpdateData(TRUE);
		strMSSV = m_newmssv_val;
		m_newmalop_ctrl.GetLBText(m_newmalop_ctrl.GetCurSel(), strMaLop);
		float diemQT = _ttof(m_newdiem_val);
		float diemGK = _ttof(m_newdiemgk_val);
		float diemCK = _ttof(m_newdiemck_val);
		float diemTB = (diemQT*0.1 + diemGK*0.3 + diemCK*0.6);
		insertQuery.Format(_T("INSERT INTO KETQUA(MASSV,MALOP,DIEM,DIEMQT,DIEMGK,DIEMCK) VALUES ('%s','%s',%f,%f,%f,%f)"), m_newmssv_val, m_newmalop_val, diemTB,diemQT,diemGK,diemCK);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm điểm cho sinh viên MSSV:"+m_newmssv_val);
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
	
	TRY{
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
		m_filterMonHoc_ctrl.EnableWindow(TRUE);
		
		OnCbnSelchangeMonhocCbb();
		
		recset.Close();
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

	TRY{
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
		m_filterMaLop_ctrl.EnableWindow();
		recset.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error of combox malop: " + e->m_strError);
	} END_CATCH
}


void DanhSachSinhVienTheoKhoa::OnCbnSelchangeMalopCbb()
{
	// TODO: Add your control notification handler code here
}


void DanhSachSinhVienTheoKhoa::OnBnClickedXemchitietBtn()
{
	MFC_ViewSinhVien viewSVDlg;
	//get select row
	int rowSelected = m_dssv_listctrl.GetSelectionMark();
	CString mssv = m_dssv_listctrl.GetItemText(rowSelected, 0);
	viewSVDlg.SetMSSV(mssv);
	viewSVDlg.DoModal();

}


void DanhSachSinhVienTheoKhoa::OnBnClickedXemBtn()
{
	// TODO: Add your control notification handler code here
	CString maKhoa, maMonHoc, maLop;
	m_filterKhoa_ctrl.GetLBText(m_filterKhoa_ctrl.GetCurSel(), maKhoa);
	m_filterMonHoc_ctrl.GetLBText(m_filterMonHoc_ctrl.GetCurSel(),maMonHoc);
	m_filterMaLop_ctrl.GetLBText(m_filterMaLop_ctrl.GetCurSel(),maLop);

	TRY{
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
			selectQuery += L"and TENMH LIKE N'" + maMonHoc + L"'";
		}
		if (!maLop.IsEmpty()) {
			selectQuery += L"AND kq.MALOP LIKE N'" + maLop + L"'";
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
		m_xemchitiet_ctrl.EnableWindow(TRUE);
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}

//tim kiem theo mssv
void DanhSachSinhVienTheoKhoa::OnBnClickedTimkiemsvBtn()
{	
	m_dssv_listctrl.DeleteAllItems();
	UpdateData(TRUE);
	TRY{
		//database.Open(NULL,false,false,sDsn);
		
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
		m_xemchitiet_ctrl.EnableWindow(TRUE);
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


void DanhSachSinhVienTheoKhoa::OnBnClickedImportfileBtn()
{
	//import file excel danh sách điểm theo lớp 
	CFileDialog l_fDlg(TRUE);
	int fileDlg = l_fDlg.DoModal();
	CString strFile;
	
	if (fileDlg == IDOK) {
		strFile = l_fDlg.GetPathName();
		
		m_pathfile_val = strFile;
		UpdateData(FALSE);

		m_uploadfile_ctrl.EnableWindow(TRUE);
	} 
	if (strFile.IsEmpty()) {
		AfxMessageBox(L"File chưa hợp lệ!Thử lại");
		return;
	}
}

void DanhSachSinhVienTheoKhoa::OnBnClickedUploadfileBtn()
{
	//read file using ODBC
	UpdateData(TRUE);
	
	CString sDriver;
	CString sFile = m_pathfile_val;
	vector<CString> insertQueryVector;
	sDriver = GetExcelDriver();

	if (sDriver.IsEmpty()) {
		AfxMessageBox(L"Không tìm thấy Driver Excel");
		return;
	}
	CDatabase excelDB;
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	TRY{
		excelDB.Open(NULL, false, false, sDsn);

		CString sqlQuery,insertQuery;
		sqlQuery = "SELECT MSSV, MALOP, DIEMQT, DIEMGK, DIEMCK, DIEM "
					"FROM KETQUA";
		float diemtb, diemqt, diemgk, diemck;
		
		CString strMSSV, strMaLop, strDiemQT, strDiemGK, strDiemCK, strDiem;

		CRecordset recsetKQ(&excelDB);

		recsetKQ.Open(CRecordset::forwardOnly, sqlQuery, CRecordset::readOnly);

		int iSinhVien = 0;
		//loop all the row result
		while (!recsetKQ.IsEOF()) { //EOF: end of file
			recsetKQ.GetFieldValue(L"MSSV", strMSSV);
			recsetKQ.GetFieldValue(L"MALOP", strMaLop);
			recsetKQ.GetFieldValue(L"DIEMQT", strDiemQT);
			recsetKQ.GetFieldValue(L"DIEMGK", strDiemGK);
			recsetKQ.GetFieldValue(L"DIEMCK", strDiemCK);
			recsetKQ.GetFieldValue(L"DIEM", strDiem);

			//insert value into list record
			/*iSinhVien = m_dssv_listctrl.InsertItem(0, strMSSV);
			m_dssv_listctrl.SetItemText(iSinhVien, 1, strMaLop);
			m_dssv_listctrl.SetItemText(iSinhVien, 2, strDiemQT);
			m_dssv_listctrl.SetItemText(iSinhVien, 3, strDiemGK);
			m_dssv_listctrl.SetItemText(iSinhVien, 2, strDiemCK);
			m_dssv_listctrl.SetItemText(iSinhVien, 3, strDiem);*/
			//Move next
			
			diemqt = _ttof(strDiemQT);
			diemgk = _ttof(strDiemGK);
			diemck = _ttof(strDiemCK);
			diemtb = _ttof(strDiem);
			
			insertQuery.Format(_T("INSERT INTO KETQUA (massv, malop,diem, diemqt,diemgk,diemck) VALUES ('%s','%s','%f','%f','%f','%f')"), strMSSV, strMaLop, diemtb,diemqt,diemgk,diemck);
			insertQueryVector.push_back(insertQuery);

			recsetKQ.MoveNext();
		}
		recsetKQ.Close();
		//luu thong tin doc tu vector sang db
		for (auto i = insertQueryVector.begin(); i != insertQueryVector.end(); ++i) {
			database.ExecuteSQL(*i);
		}
		database.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		return;
	} END_CATCH

}
CString DanhSachSinhVienTheoKhoa::GetExcelDriver()
{
	TCHAR szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	TCHAR* pszBuf = szBuf;
	CString sDriver;

	// Get the names of the installed drivers ("odbcinst.h" has to be included )
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return L"";
	
	// Search for the driver...
	do
	{
		if (_tcsstr(pszBuf,_T("Excel")) != 0)//_tcssstr: tìm kiếm 1 chuỗi con trong chuỗi đích, dùng cho KDL TCHAR
		{
			// Found !
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf = wcschr(pszBuf, _T('\0')) + 1; //wcschar: tìm kiếm 1 kí tự kiểu char trong chuỗi kiểu wchar
	} while (pszBuf[1] != _T('\0'));
	return sDriver;
}
void DanhSachSinhVienTheoKhoa::OnCbnSelchangeNewmalopCbb()
{
	// TODO: Add your control notification handler code here
}


