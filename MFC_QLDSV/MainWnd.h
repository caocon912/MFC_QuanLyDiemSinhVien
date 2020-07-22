#pragma once


// MainWnd dialog

class MainWnd : public CDialogEx
{
	DECLARE_DYNAMIC(MainWnd)

public:
	MainWnd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainWnd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQlsvBtn();
	afx_msg void OnBnClickedDsdiemBtn();
	afx_msg void OnBnClickedCtdtBtn();
};
