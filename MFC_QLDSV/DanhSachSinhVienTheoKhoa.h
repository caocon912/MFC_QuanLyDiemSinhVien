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
	afx_msg void OnEnChangeNewmssvTxt();
	afx_msg void OnCbnSelchangeKhoaCbb();
	CEdit m_newmssv_ctrl;
	CString m_filterkhoa_val;
	
	afx_msg void OnCbnSelchangeMonhocCbb();
	CComboBox m_filterKhoa_ctrl;
	BOOL OnInitDialog();
};
