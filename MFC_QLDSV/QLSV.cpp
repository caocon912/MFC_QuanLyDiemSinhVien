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
END_MESSAGE_MAP()


// QLSV message handlers


BOOL QLSV::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CDatabase database;
	CString sDsn;

	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLDSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CString selectQuery;
		CString strMSSV, strMaLop, strHoTen, strNgaySinh,strMonHoc,diem, strTenKhoa, strEmail, strSDT, strNoiSinh, strNgayBatDau, strNgayKetThuc, diemqt, diemgk, diemck;

		selectQuery.Format(_T("select MSSV, HOTEN, NGAYSINH, NOISINH, TENKHOA,TENMH, kq.MALOP as MALOP,DIEM,EMAIL,SDT,NGAYBATDAU, NGAYKETTHUC,DIEMQT,DIEMGK,DIEMCK from SinhVien sv inner join Khoa k on sv.makhoa = k.makhoa inner join KetQua kq on sv.mssv = kq.massv inner join(select mh.mamh, TENMH, MALOP, TENLOP, NGAYBATDAU, NGAYKETTHUC from lop lp inner join monhoc mh on mh.mamh = lp.mamh) tmp on kq.malop = tmp.malop where mssv = '%s'"),mssv);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset content of listcontrol
		m_dssv_listctrl.DeleteAllItems();

		int iDiemMonHoc = 0;

		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MSSV", strMSSV);
			recset.GetFieldValue(L"HOTEN", strHoTen);
			recset.GetFieldValue(L"NGAYSINH", strNgaySinh);
			recset.GetFieldValue(L"NOISINH", strNoiSinh);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);
			recset.GetFieldValue(L"LOP", strMonHoc);
			recset.GetFieldValue(L"NIENKHOA", strMaLop);
			recset.GetFieldValue(L"EMAIL", strEmail);
			recset.GetFieldValue(L"SDT",strSDT);
			recset.GetFieldValue(L"DTB", strSDT);

			//insert value into list record
			iDiemMonHoc = m_dssv_listctrl.InsertItem(0, strMonHoc);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 1, strMaLop);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 2, diemqt);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 3, diemgk);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 4, diemck);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 5, diem);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 6, strNgayBatDau);
			m_dssv_listctrl.SetItemText(iDiemMonHoc, 7, strNgayKetThuc);
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
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
