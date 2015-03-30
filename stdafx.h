// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//  stdafx.h
//
//  Contains project-wide includes and definitions.

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						



#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <tchar.h>
#include <vfw.h>
#include <assert.h>
#include <iostream>
#include "vc1prosdk.h"

using namespace std;

#define FOURCC_WVC1     mmioFOURCC('W','V','C','1')
#define FOURCC_wvc1     mmioFOURCC('w','v','c','1')

#define DEFINE_GUIDA(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
DEFINE_GUIDA(MEDIASUBTYPE_WVC1, FOURCC_WVC1, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

DEFINE_GUID(MEDIASUBTYPE_wvc1,
FOURCC_wvc1, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if (x) { delete x; x = NULL;}
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(x) if (x) { delete [] x; x = NULL;}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL;}
#endif

#ifndef SAFE_CLOSE_FILEHANDLE
#define SAFE_CLOSE_FILEHANDLE(x) if (x) { CloseHandle(x); x = NULL; }
#endif

#ifndef UNICODE
#define UNICODE
#endif
