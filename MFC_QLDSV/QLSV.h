#pragma once


// QLSV dialog

class QLSV : public CDialogEx
{
	DECLARE_DYNAMIC(QLSV)

public:
	QLSV(CWnd* pParent = nullptr);   // standard constructor
	virtual ~QLSV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSSVDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_mssv_val;
	CString m_hoten_val;
	COleDateTime m_dob_val;
	CString m_address1_val;
	CString m_sdt_val;
	CString m_email_val;
	CString m_pwd_val;
	CString m_khoa_cbb_val;
	CComboBox m_khoacbb_ctrl;
	CString m_cmnd_val;
	CEdit m_cmnd_ctrl;
	CString m_pob_val;
	CString m_address2_val;
	CString m_nienkhoa_val;
	CListCtrl m_dssv_listctrl;
};
