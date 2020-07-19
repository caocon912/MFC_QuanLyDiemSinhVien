#pragma once


// DanhSachSinhVienTheoKhoa dialog

class DanhSachSinhVienTheoKhoa :public CDialogEx
{
	DECLARE_DYNAMIC(DanhSachSinhVienTheoKhoa)
  
public:
	DanhSachSinhVienTheoKhoa(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DanhSachSinhVienTheoKhoa();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSDSV_DLG };
#endif
private:
	CString m_timkiemsv_txt;
	CDatabase database;
	CString sDsn;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNhapdiemBtn();
	CString m_newmssv_val;
	CComboBox m_newmalop_ctrl;
	CString m_newmalop_val;
	CString m_newdiem_val;
	CEdit m_newmssv_ctrl;
	CComboBox m_filterKhoa_ctrl;
	CString m_filterkhoa_val;
	CComboBox m_filterMonHoc_ctrl;
	CComboBox m_filterMaLop_ctrl;
	CListCtrl m_dssv_listctrl;
	afx_msg void OnCbnSelchangeMonhocCbb();
	afx_msg void OnEnChangeNewmssvTxt();
	afx_msg void OnCbnSelchangeKhoaCbb();
	virtual BOOL OnInitDialog();
	void FillNewClassControl();
	void FillFilterDepartmentControl();
	void FillFilterSubjectControl();
	void FillFilterClassControl();
	afx_msg void OnBnClickedXemchitietBtn();
	afx_msg void OnBnClickedXemBtn();
	afx_msg void OnBnClickedTimkiemsvBtn();
	afx_msg void OnLvnItemchangedDsdsvtkListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_xemchitiet_ctrl;
	afx_msg void OnCbnSelchangeMalopCbb();
	CString m_filterMonHoc_val;
	CEdit m_newdiemgk_txt;
	CString m_newdiemck_val;
	CString m_newdiemgk_val;
	afx_msg void OnBnClickedImportfileBtn();
	CString m_pathfile_val;
	afx_msg void OnCbnSelchangeNewmalopCbb();
	afx_msg void OnBnClickedUploadfileBtn();
	CButton m_uploadfile_ctrl;
	CString GetExcelDriver();
};
