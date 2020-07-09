#pragma once


// MFC_DSDSV dialog

class MFC_DSDSV : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_DSDSV)

public:
	MFC_DSDSV(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFC_DSDSV();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSDSV_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedDsdsvtkListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedXemchitietBtn();
	afx_msg void OnBnClickedTimkiemsvBtn();
	CComboBox m_dskhoa_ctrl;
	CString m_dskhoa_val;
	CComboBox m_dsmonhoc_ctrl;
	CString m_dsmonhoc_val;
	CComboBox m_dslop_ctrl;
	CString m_dslop_val;
	CEdit m_newmssv_ctrl;
	CString m_newmssv_val;
	CComboBox m_newmalop_ctrl;
	CString m_newmalop_val;
	CString m_newdiem_val;
	afx_msg void OnCbnSelchangeKhoaCbb();
	afx_msg void OnCbnSelchangeMalopCbb2();
};
