// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5068019C_844C_415F_B491_CE91915BD062__INCLUDED_)
#define AFX_STDAFX_H__5068019C_844C_415F_B491_CE91915BD062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WIN32_WINNT  0x0601   // Win 7 - ad hoc setting by DCh 2024-08-30

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning( disable : 4018)
//#include <SECALL.H>

#include <afxole.h>

#define INCHI_LIB
#include "../../IChI_lib/src/ichi_lib.h"

#define GOTOSTRU    // enable CDlgGoTo structure number 2024-09-01 DT

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5068019C_844C_415F_B491_CE91915BD062__INCLUDED_)
