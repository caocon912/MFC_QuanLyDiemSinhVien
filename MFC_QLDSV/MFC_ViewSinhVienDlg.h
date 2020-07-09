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
};
