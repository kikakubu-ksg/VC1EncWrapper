//****************************************************************************
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//  VC1EncES.h
//
//  Declaration of CVC1EncES class.
//  This is the main class for the RAW2ES VC-1 sample.
//
//****************************************************************************

#ifndef __VC1EncES_H
#define __VC1EncES_H
#include "stdafx.h"

public ref class CVC1EncES
{
public:
    CVC1EncES();
    DWORD Init();
    void Destroy();
    DWORD Encode();

private:  

    // Video reader helper functions.
    //DWORD OpenInputFile();
    //void CloseInputFile();
    DWORD ReadFrame(DWORD dwNumber) ;
    DWORD get_frameCount();

    // Video writer helper functions
    //DWORD CreateVC1File (); 
    //void CloseVC1File ();
    DWORD WriteFrame(BYTE *pVC1Frame, DWORD dwLength);
 
    // Utility functions.
    //BOOL get_userConfigProps();
    //BOOL get_userAdvancedProps();
    DWORD get_advancedProps();
    DWORD set_advancedProps();
    DWORD ShowStatistics();

    ////// Member variables //////

    // VC-1 Encoder settings.
    COLOR_FORMAT      *m_ColorFormat;
    CONFIG_PROPERTIES *m_ConfigProps;
    FILTERS           *m_Filters;
    ME_PROPERTIES     *m_MEProps;
    QUANT_PROPERTIES  *m_QuantProps;
    DWORD   m_dwBframeDeltaQP;
    BOOL    m_bClosedEntryPt;
    DWORD   m_dwDisplayHeight;
    DWORD   m_dwDisplayWidth;
    DWORD   m_dwEncodeHeight;
    DWORD   m_dwEncodeWidth;
    BOOL    m_bLBPresent;
    BOOL    m_bLookahead;
    BOOL    m_bAdaptiveGOP;
    DWORD   m_dwKeyPop;
    DWORD   m_dwNumThreads;
    DWORD   m_dwAffinityMask;
    DWORD   m_dwPixHeight;
    DWORD   m_dwPixWidth;
    DWORD   m_dwPixIndex;
    DWORD   m_dwVideoType;
    BOOL    m_bTFF;  // Top field first flag.
    BOOL    m_bRFF;  // Repeat first field flag.
    BOOL    m_bSHMode; // ES_SH stream.

    // Instance of the VC-1 encoder class.
    class  CVC1Encoder *m_pEncoder;

     // File paths and handles for media.
    //WCHAR   m_wszInputFilePath[MAX_PATH];
    //HANDLE  m_hInput;
    //WCHAR   m_wszOutputFilePath[MAX_PATH];
    //HANDLE  m_hOutput;
    
    // Settings-related variables.
    DWORD   m_dwInputFrameSize;
    BYTE   *m_pInputBuffer;
    BOOL    m_bColorFormat; // TRUE when user sets COLOR_FORMAT value(s).
    BOOL    m_bPARI; // TRUE when user sets PixelAspectRatioIndex.
    wchar_t **m_ppArgv; // Pointer to command line string pointer.
    int     m_iArgc;  // Args count.
};

#endif