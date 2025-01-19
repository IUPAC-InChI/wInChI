#pragma once


// CDlgGoTo dialog

class CDlgGoTo : public CDialog
{
	DECLARE_DYNAMIC(CDlgGoTo)

public:
	CDlgGoTo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgGoTo();

// Dialog Data
	enum { IDD = IDD_DIALOG_GOTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    int m_GoToNumber;
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedOk();
};
