/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.07
 * April 30, 2024
 *
 * The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST.
 * Modifications and additions by IUPAC and the InChI Trust.
 * Some portions of code were developed/changed by external contributors
 * (either contractor or volunteer) which are listed in the file
 * 'External-contributors' included in this distribution.
 *
 * IUPAC/InChI-Trust Licence No.1.0 for the
 * International Chemical Identifier (InChI)
 * Copyright (C) IUPAC and InChI Trust
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the IUPAC/InChI Trust InChI Licence No.1.0,
 * or any later version.
 *
 * Please note that this library is distributed WITHOUT ANY WARRANTIES
 * whatsoever, whether expressed or implied.
 * See the IUPAC/InChI-Trust InChI Licence No.1.0 for more details.
 *
 * You should have received a copy of the IUPAC/InChI Trust InChI
 * Licence No. 1.0 with this library; if not, please e-mail:
 *
 * info@inchi-trust.org
 *
 */



#if !defined(AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_)
#define AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptions.h : header file
//

#include "DlgIchiOption.h"

class InchiBrowseFileEdit
{
public:
	InchiBrowseFileEdit() {};
	void OnBrowse();
// Prototypes From Stingray
	BOOL m_bOpenDialog;
	HWND hWndParent;  // parent of FileOpen dialog
	CWnd* pWndParent;
	UINT uiID;   // ID of Edit control containing pathname to selected file
	CString m_strFilters;  // filter for FileOpen dialog
	int nMaxCustFilter;
	DWORD lFlags;
	CString m_strExt;

	DWORD m_dwDialogStyle;
	CString m_strInitialFile;

	BOOL Initialize(UINT uiID, CWnd* pWndParent)
	{
		this->uiID = uiID;
		this->hWndParent = pWndParent->GetSafeHwnd();
		this->pWndParent = pWndParent;
		return TRUE;
	};
	void SetFileFilters(MYFTYPES  mf[], int num_mf) 
	{  
			int i;
			nMaxCustFilter = 0;
			for ( i = 0; i < num_mf; i++ ) {
				m_strFilters += mf[i].description;
				m_strFilters += (char)'\0';        // next string please
				m_strFilters += mf[i].filter;
				m_strFilters += (char)'\0';        // next string please
				nMaxCustFilter++;
				//dlgFile.m_ofn.nMaxCustFilter++;
			}
			m_strFilters += (char)'\0';        // next string please
	};
	void ModifyDialogStyle( DWORD dwRemove, DWORD dwAdd )
	{
		lFlags = dwAdd;
	};
	BOOL MyDoPromptFileName(CString& fileName, UINT nIDSTitle,
						  BOOL bOpenFileDialog, CDocTemplate* pTemplate);


};
/////////////////////////////////////////////////////////////////////////////
// DlgOptions dialog

class DlgOptions : public CDialog
{
// Construction
public:
	DlgOptions(CWnd* pParent = NULL);   // standard constructor

	InchiBrowseFileEdit m_editFileInput;
	BOOL m_bMerge;
	CString m_OldInputFile;
	CDlgInchiOption m_Dlg;
	void GetOptions(CStringArray& Opt, int *Write2Disk ) const;

// Dialog Data
	//{{AFX_DATA(DlgOptions)
	enum { IDD = IDD_DIALOG1 };
	CString	m_InputFile;
	CString	m_Header;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton2();  // Open Browse() for input file
    afx_msg void OnEnChangeEditInputFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_)
