#pragma once


// DanhSachSinhVienTheoKhoa dialog

class DanhSachSinhVienTheoKhoa : public CDialogEx
{
	DECLARE_DYNAMIC(DanhSachSinhVienTheoKhoa)

public:
	DanhSachSinhVienTheoKhoa(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DanhSachSinhVienTheoKhoa();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSDSV_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNhapdiemBtn();
	CString m_newmssv_val;
	CString m_newmalop_val;
	CString m_newdiem_val;
	CEdit m_newmssv_ctrl;
	CComboBox m_filterKhoa_ctrl;
	CString m_filterkhoa_val;
	CComboBox m_newmalop_ctrl;
	afx_msg void OnCbnSelchangeMonhocCbb();
	afx_msg void OnEnChangeNewmssvTxt();
	afx_msg void OnCbnSelchangeKhoaCbb();
	
	virtual BOOL OnInitDialog();
	void FillNewClassControl();
	void FillFilterDepartmentControl();
};
