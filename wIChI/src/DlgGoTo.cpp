// DlgGoTo.cpp : implementation file
//

#include "stdafx.h"
#include "wIChI.h"
#include "DlgGoTo.h"
#include "afxdialogex.h"


// CDlgGoTo dialog

IMPLEMENT_DYNAMIC(CDlgGoTo, CDialog)

CDlgGoTo::CDlgGoTo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGoTo::IDD, pParent)
{

    m_GoToNumber = 1;
}

CDlgGoTo::~CDlgGoTo()
{
}

void CDlgGoTo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_GOTO_NUMBER, m_GoToNumber);
	DDV_MinMaxInt(pDX, m_GoToNumber, 1, 999999999);
}


BEGIN_MESSAGE_MAP(CDlgGoTo, CDialog)
    ON_BN_CLICKED(IDCANCEL, &CDlgGoTo::OnBnClickedCancel)
    ON_BN_CLICKED(IDOK, &CDlgGoTo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgGoTo message handlers


void CDlgGoTo::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    CDialog::OnCancel();
}




void CDlgGoTo::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CDialog::OnOK();
}
