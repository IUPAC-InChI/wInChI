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



// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "io.h"
#include "wIChI.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
static BOOL HasTrailingSlash( const CString& str )
{
	int iLength = str.GetLength() - 1;

	if( str[iLength] == _T('\\') )
		return TRUE;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
static BOOL IsDirectory( CString& str )
{
	//if it has a trailing slash...remove it...
	if( HasTrailingSlash(str) )
		str = str.Left(str.GetLength() - 1);

	// If the last character in the string is a : then
	// we are a root directory. CFile::GetStatus uses
	// FindFirstFile to verify our existence, and fails
	// on C:\ so we need to add some wildcards
	if(str.Right(1) == _T(":"))
	{
		str += _T("\\*.*");
	}

	//Get the status of the file...return TRUE if a directory...
	CFileStatus fs;
	if( CFile::GetStatus( str, fs ) && (fs.m_attribute & CFile::directory))
	{
		// GetStatus returns FALSE if it can't find the file
		// If it returns True, and it is a filename,
		// go to that directory instead of returning false
		return TRUE;
	}

	//otherwise return FALSE
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
void InchiBrowseFileEdit::OnBrowse()
{
	CString str,strOrig;
	//SECFileSystem fs;
	
	if( m_dwDialogStyle & OFN_NOCHANGEDIR ) {
	//	strOrig = fs.GetCurrentDirectory();
		GetCurrentDirectory( MAX_PATH, strOrig.GetBufferSetLength(MAX_PATH)); 
		strOrig.ReleaseBuffer();
	}

	if (m_strInitialFile.IsEmpty()) {
		// Edit control containing patname
		//GetWindowText(str);
		pWndParent->GetDlgItem(IDC_EDIT_INPUT_FILE)->GetWindowText(str);
	} else {
		str = m_strInitialFile; //they specified a file...assume valid...
	}

	//Lets use an instance of SECFileSystem to check the validity of the text
	BOOL bClearStr = FALSE;

	//if string is empty...do nothing
	if( !str.IsEmpty() )
	{
		//check to see if it is a directory and not a file
		if( IsDirectory(str) )
		/*{
			//never can be too careful
			if( fs.DirectoryExists(str) )
			{
				fs.ChangeDirectory(str);
				bClearStr = TRUE;
			}
		}*/
		{
			if ( 0 == _access(str,00) ) {
				DWORD dw = GetFileAttributes(str);
				if ( dw != INVALID_FILE_ATTRIBUTES ) {
					if ( dw & FILE_ATTRIBUTE_DIRECTORY ) {
						BOOL ret = SetCurrentDirectory(str);
						if ( ret ) {
							bClearStr = TRUE;
						}
					} else
					if ( dw &(FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE |
							  FILE_ATTRIBUTE_NORMAL) ) {
						// it is a file
					} else {
						bClearStr = TRUE;
					}
				}
			}
		}
		else //not a directory...
		{
			//if it is a file...we don't want to clear the string...
			//but if it isn't a file and it isn't a directory..probably bogus...clear it
			/*if( !fs.FileExists(str) )
				bClearStr = TRUE;*/
			if ( 0 == _access(str,00) ) {
				DWORD dw = GetFileAttributes(str);
				if ( dw == INVALID_FILE_ATTRIBUTES ) {
					bClearStr = TRUE;
				}
			} else {
					bClearStr = TRUE;
			}
		}
	}
			
	
	if( bClearStr )
		str = _T("");

	if ( str.IsEmpty() && !strOrig.IsEmpty() && IsDirectory(strOrig) ) {
		str = strOrig + "\\"; // 2024-08-30 DCh
	}

	//CFileDialog Dialog(m_bOpenDialog, m_strExt, str, m_dwDialogStyle, m_strFilters, this);
	/*Dialog.m_ofn.lpstrTitle = GetBrowseCaption();
	
	if (Dialog.DoModal() == IDOK)
		SetWindowText(Dialog.GetPathName());

	if( m_dwDialogStyle & OFN_NOCHANGEDIR )
		fs.ChangeDirectory(strOrig);*/
	CString fileName = str;
	BOOL ret = MyDoPromptFileName(fileName, AFX_IDS_OPENFILE/*nIDSTitle*/,
					 1 /*bOpenFileDialog*/, NULL);

	if ( ret ) {
		pWndParent->GetDlgItem(IDC_EDIT_INPUT_FILE)->SetWindowText(fileName);
		if( m_dwDialogStyle & OFN_NOCHANGEDIR ) {
			SetCurrentDirectory( strOrig);
		}
	}

}



/////////////////////////////////////////////////////////////////////////////
// DlgOptions dialog


/////////////////////////////////////////////////////////////////////////////
DlgOptions::DlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOptions::IDD, pParent)
{
	m_bMerge = FALSE;
	//{{AFX_DATA_INIT(DlgOptions)
	m_InputFile = _T("");
	m_Header = _T("");
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
void DDV_EmptyString(CDataExchange* pDX, CString& Str, const CString& Message)
{
	if( pDX->m_bSaveAndValidate && Str.IsEmpty())
	{
		::AfxMessageBox(Message);
		pDX->Fail();
	}
}


/////////////////////////////////////////////////////////////////////////////
void DlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOptions)
	DDX_Text(pDX, IDC_EDIT_INPUT_FILE, m_InputFile);
	DDV_EmptyString(pDX, m_InputFile, "Enter input file");
	DDX_Text(pDX, IDC_EDIT_SDFID, m_Header);
	//}}AFX_DATA_MAP

	if( !pDX->m_bSaveAndValidate )
	{
		m_OldInputFile = m_InputFile;
	}
	else
	{
		if( m_OldInputFile.CompareNoCase(m_InputFile) != 0 )
		{
			m_bMerge = FALSE;
		}
	}

}



BEGIN_MESSAGE_MAP(DlgOptions, CDialog)
	//{{AFX_MSG_MAP(DlgOptions)
	ON_BN_CLICKED(IDC_BUTTON_ADV, OnButtonAdv)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON2, &DlgOptions::OnBnClickedButton2)
    ON_EN_CHANGE(IDC_EDIT_INPUT_FILE, &DlgOptions::OnEnChangeEditInputFile)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// DlgOptions message handlers


/////////////////////////////////////////////////////////////////////////////
BOOL DlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MYFTYPES  mf[] = {
					 {"*.mol", "MolFile (*.mol)"},
					 {"*.sdf", "SDFile (*.sdf)"},
//					 {"*.cml", "CMLFile (*.cml)"},
					 {"*.*", "All Files (*.*)"},
					 };
	int num_mf = sizeof(mf)/sizeof(mf[0]);

	m_editFileInput.Initialize(IDC_EDIT_INPUT_FILE, this);
	//m_editFileInput.SetFileFilters("MolFile (*.mol)|*.mol|SDFile (*.sdf)|*.sdf|All Files (*.*)|*.*||");
	m_editFileInput.SetFileFilters(mf, num_mf);

	m_editFileInput.ModifyDialogStyle(0,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
void DlgOptions::OnButtonAdv() 
{
	// TODO: Add your control notification handler code here
	m_Dlg.DoModal();
	
}


/////////////////////////////////////////////////////////////////////////////
void DlgOptions::GetOptions(CStringArray& Opt, int *Write2Disk ) const
{
	CString str;
	char ext[_MAX_EXT];

   _splitpath( (LPCSTR)m_InputFile, NULL, NULL, NULL, ext );
   _strupr(ext);
    if( strcmp(ext,".CML") == 0 )
	{
		Opt.Add("/CML");
	}
	else
	{
		if( !m_Header.IsEmpty() ) 
		{
			str= "/SDF:";
			str += m_Header;
			Opt.Add(str);
		}
		else
			Opt.Add("/MOL");
	}

	if( m_bMerge )
		Opt.Add("/MERGE");

	m_Dlg.GetOptions(Opt, Write2Disk );
}


void DlgOptions::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    m_editFileInput.OnBrowse();
}


void DlgOptions::OnEnChangeEditInputFile()
{
    // TODO:  Add your control notification handler code here
}
/********************************************************************************/
BOOL InchiBrowseFileEdit::MyDoPromptFileName(CString& fileName, UINT nIDSTitle,
						  BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
	CFileDialog dlgFile(bOpenFileDialog);
	 
	
	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

	
	dlgFile.m_ofn.lpstrFilter = m_strFilters;
	dlgFile.m_ofn.hwndOwner = hWndParent;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	//m_pMyFileOpenDlg = &dlgFile;
	BOOL bRet = (dlgFile.DoModal() == (IDOK ? TRUE : FALSE));
	fileName.ReleaseBuffer();
	return bRet;
}
