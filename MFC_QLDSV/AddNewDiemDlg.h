#pragma once


// AddNewDiemDlg dialog

class AddNewDiemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewDiemDlg)

public:
	AddNewDiemDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddNewDiemDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEMDIEM_DLG };
#endif
private:
	CDatabase database;
	CString sDsn;
	CString mssv;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNhapdiemBtn();
	CString m_malop_val;
	CString m_diemqt_val;
	CString m_diemgk_val;
	CString m_diemck_val;
	void setMSSV(CString maSoSV);
	CString getMSSV();
};
