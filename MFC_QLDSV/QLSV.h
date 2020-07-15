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
};
