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
//  Declaration of CVC1EncWrapper class.
//  This is the main class for the RAW2ES VC-1 sample.
//
//****************************************************************************

#ifndef __VC1EncWrap_H
#define __VC1EncWrap_H
#include "stdafx.h"

public ref class CVC1EncWrapper
{
public:
    CVC1EncWrapper();
    DWORD Init();
    void Destroy();
    DWORD Encode(BYTE *pInputBuffer, BYTE *pOutputBuffer, INT64 i);
    //DWORD GetCodecPrivateData();
    DWORD ForceKeyFrame();

    // config propaty getter/setter
    DOUBLE GetBitRate();
    DWORD  GetComplexityLevel();
    DWORD  GetQP();
    DOUBLE GetFrameRate();
    BOOL   GetInterlacedSource();
    DWORD  GetMaxKeyFrameDistance();
    DWORD  GetMaxHeight();
    DWORD  GetMaxWidth();
    DWORD  GetNumOfBFrames();
    DOUBLE GetPeakBitRate();
    DWORD  GetProfile();
    DWORD  GetRateControlMode();
    DWORD  GetVBVBufferInBytes();

    DWORD  SetBitRate(DOUBLE dBitRate);
    DWORD  SetComplexityLevel(DWORD dwComplexityLevel);
    DWORD  SetQP(DWORD dwQP);
    DWORD  SetFrameRate(DOUBLE dFrameRate);
    DWORD  SetInterlacedSource(BOOL bInterlacedSource);
    DWORD  SetMaxKeyFrameDistance(DWORD dwMaxKeyFrameDistance);
    DWORD  SetMaxHeight(DWORD dwMaxHeight);
    DWORD  SetMaxWidth(DWORD dwMaxWidth);
    DWORD  SetNumOfBFrames(DWORD dwNumOfBFrames);
    DWORD  SetPeakBitRate(DOUBLE dPeakBitRate);
    DWORD  SetProfile(DWORD dwProfile);
    DWORD  SetRateControlMode(DWORD dwRateControlMode);
    DWORD  SetVBVBufferInBytes(DWORD dwVBVBufferInBytes);

//private:  

    // Utility functions.
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
    
    // Settings-related variables.
    DWORD   m_dwInputFrameSize;
    BYTE   *m_pInputBuffer;
    DWORD   m_dwOutputFrameSize;
    BYTE   *m_pOutputBuffer;
    BOOL    m_bColorFormat; // TRUE when user sets COLOR_FORMAT value(s).
    BOOL    m_bPARI; // TRUE when user sets PixelAspectRatioIndex.

    BYTE   *m_pPrivCodecData; // Private Codec Data info
    DWORD   m_dwPrivCodecDataSize;
};

#endif