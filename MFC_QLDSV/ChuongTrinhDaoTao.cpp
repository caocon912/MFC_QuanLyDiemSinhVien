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
	, m_soluong_val(_T(""))
	, m_startdate_val(COleDateTime::GetCurrentTime())
	, m_enddate_val(COleDateTime::GetCurrentTime())
	, m_fieldsearch_val(_T(""))
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
	DDX_Control(pDX, IDC_FILTER_BTN, m_filter_ctrl);
	DDX_Control(pDX, IDC_LISTCTRL, m_listctrl);
	DDX_Text(pDX, IDC_SOLUONG_TXT, m_soluong_val);
	DDX_DateTimeCtrl(pDX, IDC_STARTDATE_PICKER, m_startdate_val);
	DDX_DateTimeCtrl(pDX, IDC_ENDDATE_PICKER, m_enddate_val);
	DDX_Text(pDX, IDC_FIELD_SEARCH_TXT, m_fieldsearch_val);
	DDX_Control(pDX, IDC_MAKHOA_TXT, m_makhoa_ctrl);
	DDX_Control(pDX, IDC_EDITKHOA_BTN, m_editkhoa_ctrl);
	DDX_Control(pDX, IDC_DELETEKHOA_BTN, m_deletekhoa_ctrl);
	DDX_Control(pDX, IDC_EDITMH_BTN, m_editmh_ctrl);
	DDX_Control(pDX, IDC_DELETEMH_BTN, m_deletemh_ctrl);
	DDX_Control(pDX, IDC_EDITLOP_BTN, m_editlop_ctrl);
	DDX_Control(pDX, IDC_DELETELOP_BTN, m_deletelop_ctrl);
}


BEGIN_MESSAGE_MAP(ChuongTrinhDaoTao, CDialogEx)
	ON_BN_CLICKED(IDC_ADDKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedAddkhoaBtn)
	ON_BN_CLICKED(IDC_EDITKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedEditkhoaBtn)
	ON_BN_CLICKED(IDC_SAVEKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedSavekhoaBtn)
	ON_BN_CLICKED(IDC_DELETEKHOA_BTN, &ChuongTrinhDaoTao::OnBnClickedDeletekhoaBtn)
	ON_BN_CLICKED(IDC_ADDMH_BTN, &ChuongTrinhDaoTao::OnBnClickedAddmhBtn)
	ON_BN_CLICKED(IDC_EDITMH_BTN, &ChuongTrinhDaoTao::OnBnClickedEditmhBtn)
	ON_BN_CLICKED(IDC_DELETEMH_BTN, &ChuongTrinhDaoTao::OnBnClickedDeletemhBtn)
	ON_BN_CLICKED(IDC_SAVEMH_BTN, &ChuongTrinhDaoTao::OnBnClickedSavemhBtn)
	ON_BN_CLICKED(IDC_ADDLOP_BTN, &ChuongTrinhDaoTao::OnBnClickedAddlopBtn)
	ON_BN_CLICKED(IDC_EDITLOP_BTN, &ChuongTrinhDaoTao::OnBnClickedEditlopBtn)
	ON_BN_CLICKED(IDC_SAVELOP_BTN, &ChuongTrinhDaoTao::OnBnClickedSavelopBtn)
	ON_BN_CLICKED(IDC_DELETELOP_BTN, &ChuongTrinhDaoTao::OnBnClickedDeletelopBtn)
	ON_CBN_SELCHANGE(IDC_LOPKHOA_CBB, &ChuongTrinhDaoTao::OnCbnSelchangeLopkhoaCbb)
	ON_CBN_SELCHANGE(IDC_FIELD1_CBB, &ChuongTrinhDaoTao::OnCbnSelchangeField1Cbb)
	ON_BN_CLICKED(IDC_FILTER_BTN, &ChuongTrinhDaoTao::OnBnClickedFilterBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &ChuongTrinhDaoTao::OnBnClickedRefreshBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, &ChuongTrinhDaoTao::OnLvnItemchangedListctrl)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ENDDATE_PICKER, &ChuongTrinhDaoTao::OnDtnDatetimechangeEnddatePicker)
END_MESSAGE_MAP()


// ChuongTrinhDaoTao message handlers


void ChuongTrinhDaoTao::OnBnClickedAddkhoaBtn()
{
	TRY{
		CString insertQuery;
		UpdateData(TRUE);
		insertQuery.Format(_T("INSERT INTO KHOA(MAKHOA, TENKHOA) VALUES (N'%s',N'%s')"),m_makhoa_val, m_tenkhoa_val);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm khoa");
		FillDepartMentControl();
	} CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
		return;
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedEditkhoaBtn()
{
	m_makhoa_ctrl.EnableWindow(FALSE);
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
		database.ExecuteSQL(updateQuery);
		AfxMessageBox(L"Đã update thông tin khoa");
		FillDepartMentControl();
	}CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
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
		FillDepartMentControl();
	} CATCH(CDBException ,e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedAddmhBtn(){
	TRY{
		UpdateData(TRUE);
		CString insertQuery;
		CString selectQuery;
		CString tenkhoa, makhoa;
		m_khoacbb_ctrl.GetLBText(m_khoacbb_ctrl.GetCurSel(), tenkhoa);
		
		selectQuery.Format(_T("SELECT MAKHOA FROM KHOA WHERE TENKHOA = '%s'"), tenkhoa);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//get first row
		recset.GetFieldValue(L"MAKHOA", makhoa);
		
		recset.Close();
		
		insertQuery.Format(L"INSERT INTO MONHOC(MAMH, TENMH, MAKHOA) VALUES (N'%s',N'%s',N'%s')",m_mamh_val,m_tenmh_val,makhoa);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm thông tin môn học");
	} CATCH(CDBException ,e) {
		AfxMessageBox(e->m_strError);
	} END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedEditmhBtn()
{
	m_mamh_ctrl.EnableWindow(FALSE);
	m_savemh_ctrl.EnableWindow(TRUE);
	int rowSelected = m_listctrl.GetSelectionMark();
	CString maMonHoc = m_listctrl.GetItemText(rowSelected, 0);
	CString tenMonHoc = m_listctrl.GetItemText(rowSelected, 1);
	CString tenKhoa = m_listctrl.GetItemText(rowSelected, 2);

	int x = m_khoacbb_ctrl.SelectString(0, tenKhoa);
	m_mamh_val = maMonHoc;
	m_tenmh_val = tenMonHoc;
	m_savemh_ctrl.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void ChuongTrinhDaoTao::OnBnClickedDeletemhBtn()
{
	int rowSelected = m_listctrl.GetSelectionMark();
	CString maMonHocSelected = m_listctrl.GetItemText(rowSelected, 0);
	CString deleteQuery;
	deleteQuery.Format(L"DELETE FROM MONHOC WHERE MAMH = '%s'", maMonHocSelected);
	TRY{
		database.ExecuteSQL(deleteQuery);
		AfxMessageBox(L"Đã xóa thông tin môn học");
	} CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedSavemhBtn()
{
	UpdateData(TRUE);
	CString tenMonHocEdit, strMaKhoa, strTenKhoa;
	tenMonHocEdit = m_tenmh_val;
	CString updateQuery;
	m_khoacbb_ctrl.GetLBText(m_khoacbb_ctrl.GetCurSel(), strTenKhoa);
	TRY{
		CString selectKhoaQuery;
		selectKhoaQuery.Format(_T("SELECT MAKHOA, TENKHOA FROM KHOA WHERE TENKHOA = N'%s'"),strTenKhoa);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectKhoaQuery, CRecordset::readOnly);

		//get first row
		recset.GetFieldValue(L"MAKHOA", strMaKhoa);
		
		recset.Close();

		updateQuery.Format(L"UPDATE MONHOC SET MAKHOA= N'%s', TENMH = N'%s 'where MAMH = N'%s'", strMaKhoa,m_tenmh_val, m_mamh_val);
		database.ExecuteSQL(updateQuery);
		AfxMessageBox(L"Đã sửa thông tin môn học");
		m_savemh_ctrl.EnableWindow(FALSE);
		m_mamh_ctrl.EnableWindow(TRUE);
	}CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedAddlopBtn()
{
	TRY{
		CString insertQuery,maMH;
		UpdateData(TRUE);
		CString selectQuery;
		CString tenMonHoc;
		m_lopmhcbb_ctrl.GetLBText(m_lopmhcbb_ctrl.GetCurSel(), tenMonHoc);

		selectQuery.Format(_T("select MAMH from MONHOC where TENMH = N'%s'"), tenMonHoc);

		CRecordset recsetMonHoc(&database);

		recsetMonHoc.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		recsetMonHoc.GetFieldValue(L"MAMH", maMH);

		recsetMonHoc.Close();

		CString ngaybatdau, ngayketthuc;
		ngaybatdau = m_startdate_val.Format(_T("%d/%m/%Y"));
		ngayketthuc = m_enddate_val.Format(_T("%d/%m/%Y"));
		insertQuery.Format(L"INSERT INTO LOP(MALOP, TENLOP, MAMH, SOLUONG, NGAYBATDAU, NGAYKETTHUC,GHICHU) VALUES (N'%s',N'%s',N'%s',%d, N'%s',N'%s','')",m_malop_val,m_tenlop_val, maMH, _ttoi(m_soluong_val), ngaybatdau, ngayketthuc);
		database.ExecuteSQL(insertQuery);
		AfxMessageBox(L"Đã thêm thông tin lớp học");
	} CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
	} END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedEditlopBtn()
{
	int rowSelected = m_listctrl.GetSelectionMark();
	m_malop_ctrl.EnableWindow(FALSE);
	m_malop_val = m_listctrl.GetItemText(rowSelected, 0);
	m_tenlop_val = m_listctrl.GetItemText(rowSelected, 1);
	CString tenMonHoc = m_listctrl.GetItemText(rowSelected, 2);
	int iMonHoc = m_lopmhcbb_ctrl.SelectString(0, tenMonHoc);
	m_khoacbb_ctrl.SetCurSel(iMonHoc);
	CString tenKhoa = m_listctrl.GetItemText(rowSelected, 3);
	int iKhoa = m_lopkhoacbb_Ctrl.SelectString(0, tenKhoa);
	m_khoacbb_ctrl.SetCurSel(iKhoa);
	m_soluong_val = m_listctrl.GetItemText(rowSelected, 4);
	CString ngayBatDau = m_listctrl.GetItemText(rowSelected, 5);
	CString ngayKetThuc = m_listctrl.GetItemText(rowSelected, 6);
	
	if (ngayBatDau == "") {
		ngayBatDau = "13/07/1968";
	}
	if (ngayKetThuc == "") {
		ngayKetThuc = "13/07/1968";
	}
	m_startdate_val.ParseDateTime(ngayBatDau);
	m_enddate_val.ParseDateTime(ngayKetThuc);

	m_savelop_ctrl.EnableWindow(TRUE);
	UpdateData(FALSE);
}



void ChuongTrinhDaoTao::OnBnClickedSavelopBtn()
{
	UpdateData(TRUE);
	CString tenMonHocEdit,maMH,tenKhoaEdit,makhoa;
	m_lopmhcbb_ctrl.GetLBText(m_lopmhcbb_ctrl.GetCurSel(), tenMonHocEdit);
	m_lopkhoacbb_Ctrl.GetLBText(m_lopkhoacbb_Ctrl.GetCurSel(), tenKhoaEdit);
	CString updateQuery;
	
	TRY{
		CString selectKhoaQuery;
		selectKhoaQuery.Format(_T("SELECT MAMH FROM MONHOC WHERE TENMH = N'%s'"), tenMonHocEdit);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectKhoaQuery, CRecordset::readOnly);

		//get first row
		recset.GetFieldValue(L"MAMH", maMH);
		recset.Close();

		updateQuery.Format(L"UPDATE LOP SET TENLOP= N'%s', MAMH = N'%s',SOLUONG = %d, NGAYBATDAU = '%s', NGAYKETTHUC = '%s',GHICHU=' ' where MALOP = N'%s'", m_tenlop_val, maMH, _ttoi(m_soluong_val), m_startdate_val.Format(_T("%d/%m/%Y")), m_enddate_val.Format(_T("%d/%m/%Y")),m_malop_val);
	/*CString maLop = m_listctrl.GetItemText(rowSelected, 0);
	CString tenLop = m_listctrl.GetItemText(rowSelected, 1);
	CString tenMonHoc = m_listctrl.GetItemText(rowSelected, 2);
	CString tenKhoa = m_listctrl.GetItemText(rowSelected, 3);
	CString soLuong = m_listctrl.GetItemText(rowSelected, 4);
	CString ngayBatDau = m_listctrl.GetItemText(rowSelected, 5);
	CString ngayKetThuc = m_listctrl.GetItemText(rowSelected, 6);*/
		database.ExecuteSQL(updateQuery);
		AfxMessageBox(L"Đã thêm sửa thông tin lớp học");
		m_savelop_ctrl.EnableWindow(FALSE);
	}CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnBnClickedDeletelopBtn()
{
	int rowSelected = m_listctrl.GetSelectionMark();
	CString maLopSelected = m_listctrl.GetItemText(rowSelected, 0);
	CString deleteQuery;
	deleteQuery.Format(L"DELETE FROM LOP WHERE MALOP = '%s'", maLopSelected);
	TRY{
		database.ExecuteSQL(deleteQuery);
		AfxMessageBox(L"Đã xóa thông tin Lớp học");
	} CATCH(CDBException, e) {
		AfxMessageBox(e->m_strError);
	}END_CATCH
}


void ChuongTrinhDaoTao::OnCbnSelchangeLopkhoaCbb()
{
	// TODO: Add your control notification handler code here
	CString khoa;
	int indexCCB = m_lopkhoacbb_Ctrl.GetCurSel();
	//lay gia tri tai index do
	m_lopkhoacbb_Ctrl.GetLBText(indexCCB, khoa);

	TRY{
		CString selectQuery;
		CString strMaMonHoc, strTenMonHoc, strMaLop, strTenLop;
		selectQuery.Format(_T("select MAMH, TENMH from MONHOC where MAKHOA in (select MAKHOA from KHOA where TENKHOA = N'%s')"),khoa);

		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		//reset combobox
		m_lopmhcbb_ctrl.ResetContent();

		//loop all the row result
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAMH", strMaMonHoc);
			recset.GetFieldValue(L"TENMH", strTenMonHoc);

			m_lopmhcbb_ctrl.AddString(strTenMonHoc);
			//Move next
			recset.MoveNext();
		}
		m_lopmhcbb_ctrl.SetCurSel(0);
		m_lopmhcbb_ctrl.EnableWindow(TRUE);

		recset.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error of combox mamh,malop: " + e->m_strError);
	} END_CATCH
}


BOOL ChuongTrinhDaoTao::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_lopmhcbb_ctrl.EnableWindow(FALSE);
	m_field1cbb_ctrl.AddString(L"Khoa");
	m_field1cbb_ctrl.AddString(L"Môn Học");
	m_field1cbb_ctrl.AddString(L"Lớp Học");
	FillDepartMentControl();
	FillSubjectControl();

	m_khoacbb_ctrl.SetCurSel(0);
	m_lopkhoacbb_Ctrl.SetCurSel(0);
	ListView_SetExtendedListViewStyle(m_listctrl, LVS_EX_GRIDLINES);
	m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void ChuongTrinhDaoTao::OnBnClickedFilterBtn()
{
	int nColumnCount = m_listctrl.GetHeaderCtrl()->GetItemCount();
	UpdateData(TRUE);
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_listctrl.DeleteColumn(0);
	}
	m_listctrl.DeleteAllItems();
	CString field1, field2;
	int indexOfField1 = m_field1cbb_ctrl.GetCurSel();
	//lay gia tri tai index do
	m_field1cbb_ctrl.GetLBText(indexOfField1, field1);
	CString query1,query2,selectQuery;
	bool flag = true;
	CEdit* editField = (CEdit*)GetDlgItem(IDC_FIELD_SEARCH_TXT);

	if (editField == NULL)
		return;
	CString str;

	editField->GetWindowTextW(str);

	if (str.IsEmpty())
	{
		flag = false;
	}
	if (field1 == "Khoa") {
		query1 = "SELECT MAKHOA, TENKHOA FROM KHOA";
		if (flag == true) {
			query2.Format(L" WHERE TENKHOA = N'%s'", m_fieldsearch_val);
		}
		TRY{
		selectQuery = query1 + query2;
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaKhoa,strTenKhoa;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã Khoa", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên Khoa", LVCFMT_CENTER, 100);

		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAKHOA", strMaKhoa);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);
			i = m_listctrl.InsertItem(0, strMaKhoa);
			m_listctrl.SetItemText(i, 1, strTenKhoa);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}
	else if (field1 == L"Môn Học") {
		query1 = "SELECT MAMH, TENMH,TENKHOA FROM MONHOC MH INNER JOIN KHOA K ON K.MAKHOA = MH.MAKHOA";
		if (flag == true) {
			query2.Format(L" WHERE TENMH = N'%s'", m_fieldsearch_val);
		}
		TRY{
		selectQuery = query1 + query2 + L" ORDER BY TENKHOA";
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaMH,strTenMH, strTenKhoa;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã môn học", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên môn học", LVCFMT_CENTER, 120);
		m_listctrl.InsertColumn(2, L"Khoa", LVCFMT_CENTER, 120);

		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAMH", strMaMH);
			recset.GetFieldValue(L"TENMH", strTenMH);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);
			
			i = m_listctrl.InsertItem(0, strMaMH);
			m_listctrl.SetItemText(i, 1, strTenMH);
			m_listctrl.SetItemText(i, 2, strTenKhoa);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}
	else if (field1 == L"Lớp Học") {
		query1 = "SELECT MALOP,TENLOP,TENMH, TENKHOA, SOLUONG, NGAYBATDAU,NGAYKETTHUC FROM LOP L INNER JOIN (SELECT MAMH, TENMH, TENKHOA FROM MONHOC MH INNER JOIN KHOA K ON K.MAKHOA = MH.MAKHOA) TMP ON L.MAMH = TMP.MAMH ";
		if (flag == true) {
			query2.Format(L" WHERE TENLOP = N'%s'", m_fieldsearch_val);
		} 
		TRY{
		selectQuery = query1 + query2 + L" ORDER BY TENKHOA";;
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaLop,strTenLop, strTenMH, strKhoa, soluong, ngaybatdau, ngayketthuc;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã lớp", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên lớp", LVCFMT_CENTER, 120);
		m_listctrl.InsertColumn(2, L"Môn học", LVCFMT_CENTER, 120);
		m_listctrl.InsertColumn(3, L"Khoa", LVCFMT_CENTER, 120);
		m_listctrl.InsertColumn(4, L"Số lượng", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(5, L"Ngày bắt đầu", LVCFMT_CENTER, 100);
		m_listctrl.InsertColumn(6, L"Ngày kết thúc", LVCFMT_CENTER, 100);
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MALOP", strMaLop);
			recset.GetFieldValue(L"TENLOP", strTenLop);
			recset.GetFieldValue(L"TENMH", strTenMH);
			recset.GetFieldValue(L"TENKHOA", strKhoa);
			recset.GetFieldValue(L"SOLUONG", soluong);
			recset.GetFieldValue(L"NGAYBATDAU", ngaybatdau);
			recset.GetFieldValue(L"NGAYKETTHUC", ngayketthuc);

			i = m_listctrl.InsertItem(0, strMaLop);
			m_listctrl.SetItemText(i, 1, strTenLop);
			m_listctrl.SetItemText(i, 2, strTenMH);
			m_listctrl.SetItemText(i, 3, strKhoa);
			m_listctrl.SetItemText(i, 4, soluong);
			m_listctrl.SetItemText(i, 5, ngaybatdau);
			m_listctrl.SetItemText(i, 6, ngayketthuc);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}
	
}

void ChuongTrinhDaoTao::OnCbnSelchangeField1Cbb()
{
	m_filter_ctrl.EnableWindow(TRUE);
}




void ChuongTrinhDaoTao::OnBnClickedRefreshBtn()
{
	int nColumnCount = m_listctrl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_listctrl.DeleteColumn(0);
	}
	m_listctrl.DeleteAllItems();

	CString field1, field2;
	int indexOfField1 = m_field1cbb_ctrl.GetCurSel();
	//lay gia tri tai index do
	m_field1cbb_ctrl.GetLBText(indexOfField1, field1);
	CString query1, query2, selectQuery;
	bool flag = true;
	CEdit* editField = (CEdit*)GetDlgItem(IDC_FIELD_SEARCH_TXT);

	if (editField == NULL)
		return;
	CString str;

	editField->GetWindowTextW(str);

	if (str.IsEmpty())
	{
		flag = false;
	}
	if (field1 == "Khoa") {
		query1 = "SELECT MAKHOA, TENKHOA FROM KHOA";
		if (flag == true) {
			query2.Format(L"WHERE TENKHOA = '%s'", m_fieldsearch_val);
		}
		TRY{
		selectQuery = query1 + query2;
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaKhoa,strTenKhoa;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã Khoa", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên Khoa", LVCFMT_CENTER, 100);

		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAKHOA", strMaKhoa);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);
			i = m_listctrl.InsertItem(0, strMaKhoa);
			m_listctrl.SetItemText(i, 1, strTenKhoa);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}
	else if (field1 == "Môn Học") {
		query1 = "SELECT MAMH, TENMH,TENKHOA FROM MONHOC MH INNERJOIN KHOA K ON K.MAKHOA = MH.MAKHOA";
		if (flag == true) {
			query2.Format(L"WHERE TENMH = '%s'", m_fieldsearch_val);
		}
		TRY{
		selectQuery = query1 + query2;
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaMH,strTenMH, strTenKhoa;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã môn học", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên môn học", LVCFMT_CENTER, 100);
		m_listctrl.InsertColumn(2, L"Khoa", LVCFMT_CENTER, 100);

		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MAMH", strMaMH);
			recset.GetFieldValue(L"TENMH", strTenMH);
			recset.GetFieldValue(L"TENKHOA", strTenKhoa);

			i = m_listctrl.InsertItem(0, strMaMH);
			m_listctrl.SetItemText(i, 1, strTenMH);
			m_listctrl.SetItemText(i, 1, strTenKhoa);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}
	else if (field1 == "Lớp Học") {
		query1 = "SELECT MALOP,TENLOP,TENMH, TENKHOA, SOLUONG, NGAYBATDAU,NGAYKETTHUC FROM LOP L INNERJOIN (SELECT MAMH, TENMH, TENKHOA FROM MONHOC MH INNERJOIN KHOA K ON K.MAKHOA = MH.MAKHOA) TMP ON L.MAMH = TMP.MAMH ";
		if (flag == true) {
			query2.Format(L"WHERE TENLOP = '%s'", m_fieldsearch_val);
		}
		TRY{
		selectQuery = query1 + query2;
		CRecordset recset(&database);

		recset.Open(CRecordset::forwardOnly, selectQuery, CRecordset::readOnly);

		CString strMaLop,strTenLop, strTenMH, strKhoa, soluong, ngaybatdau, ngayketthuc;
		int i = 0;
		m_listctrl.InsertColumn(0, L"Mã lớp", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(1, L"Tên lớp", LVCFMT_CENTER, 100);
		m_listctrl.InsertColumn(1, L"Môn học", LVCFMT_CENTER, 100);
		m_listctrl.InsertColumn(2, L"Khoa", LVCFMT_CENTER, 100);
		m_listctrl.InsertColumn(3, L"Số lượng", LVCFMT_CENTER, 50);
		m_listctrl.InsertColumn(4, L"Ngày bắt đầu", LVCFMT_CENTER, 80);
		m_listctrl.InsertColumn(5, L"Ngày kết thúc", LVCFMT_CENTER, 80);
		while (!recset.IsEOF()) { //EOF: end of file
			recset.GetFieldValue(L"MALOP", strMaLop);
			recset.GetFieldValue(L"TENLOP", strTenLop);
			recset.GetFieldValue(L"TENMH", strTenMH);
			recset.GetFieldValue(L"TENKHOA", strKhoa);
			recset.GetFieldValue(L"SOLUONG", soluong);
			recset.GetFieldValue(L"NGAYBATDAU", ngaybatdau);
			recset.GetFieldValue(L"NGAYKETTHUC", ngayketthuc);

			i = m_listctrl.InsertItem(0, strMaLop);
			m_listctrl.SetItemText(i, 1, strTenLop);
			m_listctrl.SetItemText(i, 2, strTenMH);
			m_listctrl.SetItemText(i, 3, strKhoa);
			m_listctrl.SetItemText(i, 4, soluong);
			m_listctrl.SetItemText(i, 5, ngaybatdau);
			m_listctrl.SetItemText(i, 6, ngayketthuc);
			//Move next
			recset.MoveNext();
		}
		recset.Close();
		}CATCH(CDBException, e) {
			AfxMessageBox(e->m_strError);
		}END_CATCH
	}

}
void ChuongTrinhDaoTao::FillSubjectControl() {
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
			m_lopmhcbb_ctrl.AddString(strTenMonHoc);
			recsetMonHoc.MoveNext();
		}
		recsetMonHoc.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox mon hoc: " + e->m_strError);
	} END_CATCH
}
void ChuongTrinhDaoTao::FillDepartMentControl() {
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

			m_khoacbb_ctrl.AddString(strTenKhoa);
			m_lopkhoacbb_Ctrl.AddString(strTenKhoa);
			recsetKhoa.MoveNext();
		}
		recsetKhoa.Close();
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error combobox khoa: " + e->m_strError);
	} END_CATCH
}


void ChuongTrinhDaoTao::OnLvnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_editkhoa_ctrl.EnableWindow(TRUE);
	m_editmh_ctrl.EnableWindow(TRUE);
	m_editlop_ctrl.EnableWindow(TRUE);
	m_deletekhoa_ctrl.EnableWindow(TRUE);
	m_deletemh_ctrl.EnableWindow(TRUE);
	m_deletelop_ctrl.EnableWindow(TRUE);
}


void ChuongTrinhDaoTao::OnDtnDatetimechangeEnddatePicker(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
