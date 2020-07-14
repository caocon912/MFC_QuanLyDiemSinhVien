#pragma once


// MFC_ViewSinhVien dialog

class MFC_ViewSinhVien : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_ViewSinhVien)

public:
	MFC_ViewSinhVien(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFC_ViewSinhVien();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWSV_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedThemdiemBtn();
	afx_msg void OnCbnSelchangeKhoaCbb();
	CComboBox m_khoa_ctrl;
	CButton m_editsv_btn;
	CButton m_save_editsv_btn;
	COleDateTime m_dobsv_val;
	CString m_emailsv_val;
	CString m_mssv_val;
	CString m_pobsv_val;
	CString m_sdtsv_val;
	CButton m_themdiem_ctrl;
	CString m_timkiemdiem_ctrl;
	CButton m_timkiemmh_ctrl;
	CListCtrl m_danhsachdiemsv_listctrl;
	virtual BOOL OnInitDialog();
	void LoadThongTinSinhVien(CString mssv);
	CString m_hotensv_val;
	afx_msg void OnBnClickedEditsvBtn();
	CEdit m_hotensv_ctrl;
	CDateTimeCtrl m_dobsv_ctrl;
	CEdit m_emailsv_ctrl;
	CEdit m_mssv_ctrl;
	CEdit m_pobsv_ctrl;
	CEdit m_sdtsv_ctrl;
	afx_msg void OnBnClickedSaveeditBtn();
};
