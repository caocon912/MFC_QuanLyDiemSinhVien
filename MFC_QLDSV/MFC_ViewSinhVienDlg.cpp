// MFC_ViewSinhVien.cpp : implementation file
//

#include "pch.h"
#include "MFC_QLDSV.h"
#include "MFC_ViewSinhVienDlg.h"
#include "AddNewDiemDlg.h"
#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"
#include <stdio.h>


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
	TRY{
		sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
		//sDsn.Format(L"DRIVER={SQL Server};SERVER=DESKTOP-8RB0FH7;DATABASE=QLDSV");
		database.Open(NULL, false, false, sDsn);
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Lỗi kết nối DB:" + e->m_strError);
	}END_CATCH
}

MFC_ViewSinhVien::~MFC_ViewSinhVien()
{
	database.Close();
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
	DDX_Control(pDX, IDC_SUADIEM_BTN, m_suadiem_ctrl);
	DDX_Control(pDX, IDC_XOADIEM_BTN, m_xoadiem_ctrl);
}


BEGIN_MESSAGE_MAP(MFC_ViewSinhVien, CDialogEx)
	ON_BN_CLICKED(IDC_THEMDIEM_BTN, &MFC_ViewSinhVien::OnBnClickedThemdiemBtn)
	ON_CBN_SELCHANGE(IDC_KHOA_CBB, &MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb)
	ON_BN_CLICKED(IDC_EDITSV_BTN, &MFC_ViewSinhVien::OnBnClickedEditsvBtn)
	ON_BN_CLICKED(IDC_SAVEEDIT_BTN, &MFC_ViewSinhVien::OnBnClickedSaveeditBtn)
	ON_BN_CLICKED(IDC_TIMKIEMMH_BTN, &MFC_ViewSinhVien::OnBnClickedTimkiemmhBtn)
	ON_BN_CLICKED(IDC_SUADIEM_BTN, &MFC_ViewSinhVien::OnBnClickedSuadiemBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &MFC_ViewSinhVien::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_XOADIEM_BTN, &MFC_ViewSinhVien::OnBnClickedXoadiemBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DIEMSV_LISTCRL, &MFC_ViewSinhVien::OnLvnItemchangedDiemsvListcrl)
	ON_EN_CHANGE(IDC_MSSV_TXT, &MFC_ViewSinhVien::OnEnChangeMssvTxt)
END_MESSAGE_MAP()

void MFC_ViewSinhVien::SetMSSV(CString maSoSinhVien) {
	mssv = maSoSinhVien;
}
CString MFC_ViewSinhVien::GetMSSV() {
	return mssv;
}
// MFC_ViewSinhVien message handlers
BOOL MFC_ViewSinhVien::OnInitDialog()
{	
	CDialogEx::OnInitDialog();
	
	
	// TODO:  Add extra initialization here
	ListView_SetExtendedListViewStyle(m_danhsachdiemsv_listctrl, LVS_EX_GRIDLINES);
	m_danhsachdiemsv_listctrl.SetExtendedStyle(m_danhsachdiemsv_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//column width and heading 
	m_danhsachdiemsv_listctrl.InsertColumn(0, L"Môn học", LVCFMT_CENTER, 150);
	m_danhsachdiemsv_listctrl.InsertColumn(1, L"Mã Lớp", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(2, L"Điểm qúa trình", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(3, L"Điểm giữa kì", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(4, L"Điểm cuối kì", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(5, L"Điểm trung bình", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(6, L"Ngày bắt đầu", LVCFMT_LEFT, 80);
	m_danhsachdiemsv_listctrl.InsertColumn(7, L"Ngày kết thúc", LVCFMT_LEFT, 80);
	CString mssv = GetMSSV();

	LoadThongTinSinhVien(mssv);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void MFC_ViewSinhVien::LoadThongTinSinhVien(CString mssv) {
	TRY{
		CString selectQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strTenKhoa, strEmail, strSDT, strNoiSinh, strNgayBatDau, strNgayKetThuc, diemqt, diemgk, diemck;

		selectQuery.Format(_T("select MSSV, HOTEN, NGAYSINH, NOISINH, TENKHOA,TENMH, kq.MALOP as MALOP,DIEM,EMAIL,SDT,NGAYBATDAU, NGAYKETTHUC,DIEMQT,DIEMGK,DIEMCK from SinhVien sv inner join Khoa k on sv.makhoa = k.makhoa inner join KetQua kq on sv.mssv = kq.massv inner join(select mh.mamh, TENMH, MALOP, TENLOP, NGAYBATDAU, NGAYKETTHUC from lop lp inner join monhoc mh on mh.mamh = lp.mamh) tmp on kq.malop = tmp.malop where mssv = '%s'"),mssv);
		
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
			recset.GetFieldValue(L"DIEMQT", diemqt);
			recset.GetFieldValue(L"DIEMGK", diemgk);
			recset.GetFieldValue(L"DIEMCK", diemck);

			//insert value into list record
			iDiemMonHoc = m_danhsachdiemsv_listctrl.InsertItem(0, strMonHoc);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 1, strMaLop);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 2, diemqt);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 3, diemgk);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 4, diemck);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 5, diem);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 6, strNgayBatDau);
			m_danhsachdiemsv_listctrl.SetItemText(iDiemMonHoc, 7, strNgayKetThuc);
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
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error:danh sach diem sinh vien " + e->m_strError);
	} END_CATCH
}
void MFC_ViewSinhVien::OnBnClickedThemdiemBtn()
{
	AddNewDiemDlg dlg;
	dlg.setMSSV(m_mssv_val);
	dlg.DoModal();
	
}

void MFC_ViewSinhVien::OnCbnSelchangeKhoaCbb()
{

}


void MFC_ViewSinhVien::ResetControl() {
	m_khoa_ctrl.EnableWindow(FALSE);
	m_hotensv_ctrl.EnableWindow(FALSE);
	m_dobsv_ctrl.EnableWindow(FALSE);
	m_emailsv_ctrl.EnableWindow(FALSE);
	m_mssv_ctrl.EnableWindow(FALSE);
	m_pobsv_ctrl.EnableWindow(FALSE);
	m_sdtsv_ctrl.EnableWindow(FALSE);
	m_save_editsv_btn.EnableWindow(FALSE);
}


void MFC_ViewSinhVien::OnBnClickedEditsvBtn()
{
	 m_khoa_ctrl.EnableWindow(TRUE);
	 m_hotensv_ctrl.EnableWindow(TRUE);
	 m_dobsv_ctrl.EnableWindow(TRUE);
     m_emailsv_ctrl.EnableWindow(TRUE);
	 m_mssv_ctrl.EnableWindow(FALSE);
	 m_pobsv_ctrl.EnableWindow(TRUE);
	 m_sdtsv_ctrl.EnableWindow(TRUE);
	 m_save_editsv_btn.EnableWindow(TRUE);
}


void MFC_ViewSinhVien::OnBnClickedSaveeditBtn()
{
	UpdateData(TRUE);
	TRY{
		CString updateQuery, selectKhoaQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strMaKhoa, strTenKhoa, strEmail, strSDT, strNoiSinh, strNgayBatDau, strNgayKetThuc;
		
		strMSSV = m_mssv_val;
		strHoTen = m_hotensv_val;
		strNgaySinh = m_dobsv_val.Format(_T("%d/%m/%Y"));
		m_khoa_ctrl.GetLBText(m_khoa_ctrl.GetCurSel(), strTenKhoa);
		strEmail = m_emailsv_val;
		strSDT = m_sdtsv_val;
		strNoiSinh = m_pobsv_val;
		
		selectKhoaQuery.Format(_T("SELECT MAKHOA, TENKHOA FROM KHOA WHERE TENKHOA = N'%s'"),strTenKhoa);
		
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectKhoaQuery, CRecordset::readOnly);
		
		//get first row
		recset.GetFieldValue(L"MAKHOA", strMaKhoa);
		recset.Close();
		
		//cap nhat thay doi thong tin sinh vien, ket qua
		updateQuery.Format(L"UPDATE SinhVien SET makhoa =N'%s' ,hoten =N'%s' , ngaysinh ='%s' , email ='%s' ,noisinh = '%s',sdt = '%s' WHERE MSSV = '%s'", strMaKhoa, strHoTen, strNgaySinh, strEmail, strNoiSinh, strSDT, strMSSV);
		database.ExecuteSQL(updateQuery);
	
		ResetControl();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error:danh sach diem sinh vien " + e->m_strError);
	} END_CATCH

}


void MFC_ViewSinhVien::OnBnClickedTimkiemmhBtn()
{

	UpdateData(TRUE);
	TRY{
	
		CString findQuery;
		CString strMaMonHoc, strTenMonHoc, strMaLop,strTenLop, strNgayBatDau, strNgayKetThuc, diemtb, diemqt, diemgk, diemck;
	
		CRecordset recsetMonHoc(&database);

		findQuery.Format(_T("select TENMH, kq.MALOP as MALOP, TENLOP, DIEM, DIEMQT, DIEMGK, DIEMCK, NGAYBATDAU, NGAYKETTHUC from SinhVien sv inner join KetQua kq on sv.mssv = kq.massv inner join(select mh.mamh, TENMH, MALOP, TENLOP, NGAYBATDAU, NGAYKETTHUC from lop lp inner join monhoc mh on mh.mamh = lp.mamh) tmp on kq.malop = tmp.malop where mssv = '%s' and TENMH LIKE N'%s'"),mssv,m_timkiemdiem_ctrl);

		recsetMonHoc.Open(CRecordset::forwardOnly, findQuery, CRecordset::readOnly);

		int iDiem = 0;
		m_danhsachdiemsv_listctrl.DeleteAllItems();
		//loop all the row result
		while (!recsetMonHoc.IsEOF()) { //EOF: end of file
			recsetMonHoc.GetFieldValue(L"TENMH", strTenMonHoc);
			recsetMonHoc.GetFieldValue(L"MALOP", strMaLop);
			recsetMonHoc.GetFieldValue(L"TENLOP", strTenLop);
			recsetMonHoc.GetFieldValue(L"DIEM", diemtb);
			recsetMonHoc.GetFieldValue(L"DIEMQT", diemqt);
			recsetMonHoc.GetFieldValue(L"DIEMGK", diemgk);
			recsetMonHoc.GetFieldValue(L"DIEMCK", diemck);
			recsetMonHoc.GetFieldValue(L"NGAYBATDAU", strNgayBatDau);
			recsetMonHoc.GetFieldValue(L"NGAYKETTHUC", strNgayKetThuc);

			//insert value into list record
			iDiem = m_danhsachdiemsv_listctrl.InsertItem(0, strTenMonHoc);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 1, strMaLop);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 2, strTenLop);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 3, diemqt);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 4, diemgk);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 5, diemck);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 6, diemtb);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 7, strNgayBatDau);
			m_danhsachdiemsv_listctrl.SetItemText(iDiem, 8, strNgayKetThuc);
			//Move next
			recsetMonHoc.MoveNext();

		}
		recsetMonHoc.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}


void MFC_ViewSinhVien::OnBnClickedSuadiemBtn()
{
	int rowSelected = m_danhsachdiemsv_listctrl.GetSelectionMark();
	CString malop = m_danhsachdiemsv_listctrl.GetItemText(rowSelected, 1);
	AddNewDiemDlg dlg;
	dlg.setMSSV(m_mssv_val);
	dlg.setMaLop(malop);
	dlg.DoModal();
}

void MFC_ViewSinhVien::OnBnClickedXoadiemBtn()
{
	int rowSelected = m_danhsachdiemsv_listctrl.GetSelectionMark();
	CString malop = m_danhsachdiemsv_listctrl.GetItemText(rowSelected, 1);
	AfxMessageBox(L"Xác nhận xoá điểm?", MB_YESNO| MB_ICONWARNING);
	if (IDYES) {
		TRY{
			CString deleteQuery;
			deleteQuery.Format(_T("DELETE FROM KETQUA WHERE MASSV = '%s' AND MALOP = '%s'"),mssv, malop);
			database.ExecuteSQL(deleteQuery);
			LoadThongTinSinhVien(mssv);
		} 
		CATCH(CDBException, e) {
			AfxMessageBox(L"Xảy ra lỗi trong quá trình xoá điểm SV");
		} END_CATCH
	}
	else if (IDNO) {

	}
}


void MFC_ViewSinhVien::OnBnClickedRefreshBtn()
{
	LoadThongTinSinhVien(mssv);
}




void MFC_ViewSinhVien::OnLvnItemchangedDiemsvListcrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_suadiem_ctrl.EnableWindow(TRUE);
	m_xoadiem_ctrl.EnableWindow(TRUE);
}


void MFC_ViewSinhVien::OnEnChangeMssvTxt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
