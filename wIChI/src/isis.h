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



#ifndef __NISTCMN_ISIS_H__
#define __NISTCMN_ISIS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



#ifdef __cplusplus
extern "C" {
#endif

BOOL __stdcall InitMDLClipBoard();
BOOL __stdcall IsMDLClipboardAvailable();
int  __stdcall GetMDLClipboardData( HWND hwnd, LPCTSTR Filename );
int  __stdcall SetMDLCTClipboardData( HWND hwnd, LPCTSTR Filename );


#ifdef __cplusplus
	}
#endif


#endif
