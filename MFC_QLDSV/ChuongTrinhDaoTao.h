#pragma once


// ChuongTrinhDaoTao dialog

class ChuongTrinhDaoTao : public CDialogEx
{
	DECLARE_DYNAMIC(ChuongTrinhDaoTao)

public:
	ChuongTrinhDaoTao(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ChuongTrinhDaoTao();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTDT_DLG };
#endif
private:
	CString makhoa, tenkhoa;
	CString mamh, tenmh;
	CString malop, tenlop;
	CDatabase database;
	CString sDsn;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_makhoa_val;
	CString m_tenkhoa_val;
	CComboBox m_khoacbb_ctrl;
	CString m_khoacbb_val;
	CEdit m_mamh_ctrl;
	CString m_mamh_val;
	CEdit m_tenmh_ctrl;
	CString m_tenmh_val;
	CComboBox m_lopkhoacbb_Ctrl;
	CComboBox m_lopmhcbb_ctrl;
	CString m_malop_val;
	CEdit m_malop_ctrl;
	CEdit m_tenlop_ctrl;
	CString m_tenlop_val;
	CButton m_savelop_ctrl;
	CButton m_savemh_ctrl;
	CButton m_savekhoa_ctrl;
	CComboBox m_field1cbb_ctrl;
	CComboBox m_field2cbb_ctrl;
	CButton m_filter_ctrl;
	CListCtrl m_listctrl;
	afx_msg void OnBnClickedAddkhoaBtn();
	afx_msg void OnBnClickedEditkhoaBtn();
	afx_msg void OnBnClickedSavekhoaBtn();
	afx_msg void OnBnClickedDeletekhoaBtn();
	afx_msg void OnBnClickedAddmhBtn();
};
