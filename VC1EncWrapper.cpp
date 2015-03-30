//*****************************************************************************
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//  VC1EncES.cpp
//
//  Implementation of CVC1EncWrapper.
//
//*****************************************************************************

#include "stdafx.h"
#include "VC1EncWrapper.h"
#include "Crtdbg.h"

CVC1EncWrapper::CVC1EncWrapper()
{
    m_dwBframeDeltaQP = 0;
    m_bClosedEntryPt = FALSE;
    m_dwDisplayHeight = 0;
    m_dwDisplayWidth = 0;
    m_dwEncodeHeight = 0; 
    m_dwEncodeWidth = 0; 
    m_bLBPresent = FALSE;
    m_bLookahead = FALSE;
    m_bAdaptiveGOP = TRUE;
    m_dwKeyPop = 0;
    m_dwNumThreads = 0; 
    m_dwAffinityMask = 0;
    m_dwPixHeight = 0;
    m_dwPixWidth = 0;
    m_dwPixIndex = 0;
    m_dwVideoType = 0; 
    m_bTFF = FALSE;
    m_bRFF = FALSE;
    m_bSHMode = FALSE;

    m_pEncoder = NULL;
    m_pInputBuffer = NULL;
    m_dwInputFrameSize = 0;
    //m_hInput = NULL;
    //m_hOutput = NULL;  
    m_bColorFormat = FALSE;
    m_bPARI = FALSE;
    //m_ppArgv = NULL; 
    //m_iArgc = 0;

    //ZeroMemory(m_wszInputFilePath, MAX_PATH);
    //ZeroMemory(m_wszOutputFilePath, MAX_PATH);
    ZeroMemory(m_ColorFormat, sizeof(*m_ColorFormat));
    ZeroMemory(m_ConfigProps, sizeof(*m_ConfigProps));
    ZeroMemory(m_Filters, sizeof(*m_Filters));
    ZeroMemory(m_MEProps, sizeof(*m_MEProps));
    ZeroMemory(m_QuantProps, sizeof(*m_QuantProps));
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::Init
//
//  Description: Initialize the encoder SDK and the 
//               encoding sample app.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::Init()
{
    DWORD dwError = ERR_OK;

    // Cache the command line args variables.
    //m_ppArgv = argv;
    //m_iArgc = argc;
 
    // Create the VC-1 encoder class.
    m_pEncoder = new CVC1Encoder;
    if(NULL == m_pEncoder)
    {
        dwError = ERR_MEMORY;
    }

    // Get the user's required settings.
    //if(ERR_OK == dwError)
    //{
    //    if(FALSE == get_userConfigProps()) 
    //    {
    //        dwError = ERR_INVALIDARG;
    //    }
    //}

    if(ERR_OK == dwError)
    {
        // Configure the encoder with the user settings.
        dwError = m_pEncoder->Configure(*m_ConfigProps);
    }    

    // Retrieve the advanced props from the encoder.
    // Because Configure was called,
    // the advanced props should already be set to appropriate defaults.
    //if(ERR_OK == dwError)
    //{
    //    dwError = get_advancedProps();
    //}

    // Get the user's advanced settings.
    // This will overwrite only the defaults for which
    // the user has specified a value.
    //if(ERR_OK == dwError)
    //{
    //    if(FALSE == get_userAdvancedProps()) 
    //    {
    //        dwError = ERR_INVALIDARG;
    //    }
    //} 

    //if(ERR_OK == dwError)
    //{
    //    // Set the advanced properties.
    //    dwError = set_advancedProps();
    //}

    // Set the output mode.
    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetOutputMode(RAW);
    }

    if(ERR_OK == dwError)
    {
        // Compute the source frame size. YUV420が1ピクセル当たり12bitで表現されるので。
        m_dwInputFrameSize = m_ConfigProps->dwMaxWidth * m_ConfigProps->dwMaxHeight * 3 / 2;

        if(m_dwInputFrameSize > 0)
        {
            // Allocate the input frame buffer.
            m_pInputBuffer = new BYTE[m_dwInputFrameSize];
            if(NULL == m_pInputBuffer)
            {
                dwError = ERR_MEMORY;
            }
        }
        else
        {
            dwError = ERR_INVALIDSETTING;
        }
    }

    if(ERR_OK != dwError)
    {
        // Print the error message.
        wprintf_s(L"Failure in CVC1EncWrapper::Init\nerror = %i \n", dwError);
    }

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::Destroy
//
//  Description: Releases previously allocated resources.
//
////////////////////////////////////////////////////////
void CVC1EncWrapper::Destroy()
{
    SAFE_DELETE(m_pEncoder);
    SAFE_ARRAY_DELETE(m_pInputBuffer);
    SAFE_ARRAY_DELETE(m_pOutputBuffer);
    //CloseInputFile();
    //CloseVC1File();

    return;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::Encode
//
//  Description: Performs the second encoding pass.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::Encode()
{
    if(NULL == m_pEncoder)
    {
        return ERR_ENCODER;
    }

    DWORD dwError = ERR_OK;
    DWORD dwFrameCount = 0;
    DWORD dwOutputBufSize = 0; // Size of the output buffer to allocate.
    BYTE *pOutputBuffer = NULL;
    INT64 qwTimeStampOut = 0; // Placeholder variable only.
    FrameType ft = I; // Placeholder variable only.
    DWORD dwBufLen = 0; // Length of buffered data returned by Encode.

    //dwError = OpenInputFile();

    //if(ERR_OK == dwError)
    //{
    //    dwFrameCount = get_frameCount();

    //    if(0 == dwFrameCount)
    //    {
    //        dwError = ERR_NOMORE_FRAMES;
    //    }
    //}

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->StartEncode();

        wprintf_s (L"------------Encoding-----------\n");
    }

    //if(ERR_OK == dwError)
    //{
    //    dwError = CreateVC1File();
    //}

    if(ERR_OK == dwError)
    {
        // Get the buffer size from the SDK.
        dwError = m_pEncoder->GetMaxOutputBuffer(&dwOutputBufSize); 

    }

    if(ERR_OK == dwError)
    {
        // Allocate the buffer for the compressed frame.
        pOutputBuffer = new BYTE[dwOutputBufSize];

        if(NULL == pOutputBuffer)
        {
            dwError = ERR_MEMORY;
        }
    }

    if(ERR_OK == dwError)
    {
        // Loop frame-by-frame.
        for(DWORD i = 0; i < dwFrameCount; i++)
        {
            dwError = ReadFrame(i);

            if(ERR_OK == dwError)
            {
                wprintf_s(L"------------Frame %7d-----------\r", i);

                // Clear the buffer before using it.
                ZeroMemory(pOutputBuffer, dwOutputBufSize);
                // must wrap
                dwError = m_pEncoder->EncodeFrame(m_pInputBuffer,
                                                  pOutputBuffer,
                                                  &dwBufLen,
                                                  i, /*time stamps irrelevant for this scenario*/
                                                  &qwTimeStampOut,
                                                  m_bTFF,
                                                  m_bRFF,
                                                  &ft);
            }

            if (ERR_OK == dwError) 
            { 
                dwError = WriteFrame(pOutputBuffer, dwBufLen);                
            }
            else if(ERR_NO_OP_FRAME == dwError)
            {
                // Don't write for no-op frames, just move on.
                continue;
            }
            else
            {
                // Encode frame error.
                break;
            }
        } // i loop
    }

    if(ERR_OK == dwError)
    {
        // Flush any remaining frames.
		while(ERR_NOMORE_FRAMES != dwError)
		{
			ZeroMemory(pOutputBuffer, dwOutputBufSize);

			dwError = m_pEncoder->Flush(pOutputBuffer, &dwBufLen, &qwTimeStampOut, &ft);

			if((ERR_OK == dwError || ERR_NOMORE_FRAMES == dwError)
				&& (dwBufLen > 0))
			{
			  if (ERR_IO == WriteFrame(pOutputBuffer, dwBufLen))
			  {
				break;
			  }
			}
		} 
    }

    if(ERR_NOMORE_FRAMES == dwError)
    {
        dwError = ERR_OK;
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->EndEncode();

        wprintf_s (L"------------End Encode-----------\n\n");
        wprintf_s (L"------------Done-----------\n\n");
    }

    if(ERR_OK == dwError)
    {
        // Display the statistics.
         dwError = ShowStatistics();
    }

    SAFE_ARRAY_DELETE(pOutputBuffer);
    //CloseInputFile();

    if(ERR_OK != dwError)
    {
        // Print the error message.
        wprintf_s(L"Failure in CVC1EncWrapper::Encode\nerror = %i \n", dwError);
    }

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::ReadFrame
//
//  Description: Reads the specified frame number by
//               indexing into the source file.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::ReadFrame(DWORD dwNumber)
{
    DWORD dwError = ERR_OK;
    DWORD dwBytesRead = 0;

    assert(m_pInputBuffer);
    assert(m_hInput);

    // The OVERLAPPED structure holds the offset for ReadFile.
    // This function doesn't actually do overlapped reading, but
    // ReadFile supports read offsets for synchronous, sequential
    // file reading by using the struct.
    __int64 fileOffset = 0;
    OVERLAPPED ovRead;
    ZeroMemory(&ovRead, sizeof(OVERLAPPED));
    ZeroMemory(m_pInputBuffer, m_dwInputFrameSize);

    // Compute the offset into the file.
    fileOffset = (__int64)dwNumber * m_dwInputFrameSize;
    ovRead.Offset = (DWORD) fileOffset & 0xFFFFFFFF;
    ovRead.OffsetHigh = DWORD (fileOffset >> 32);

    //// Read the frame.
    //BOOL bRet = ReadFile(m_hInput, m_pInputBuffer, m_dwInputFrameSize, &dwBytesRead, &ovRead);

    //if (FALSE == bRet) 
    //{
    //    dwError = ERR_IO;
    //}

    // Just a sanity check.
    //assert(dwBytesRead == m_dwInputFrameSize);

    //if(ERR_OK != dwError)
    //{
    //    // Print the error message.
    //    wprintf_s(L"Failure in CVC1EncWrapper::ReadFrame\nerror = %i \n", dwError);
    //}

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::WriteFrame
//
//  Description: Appends the provided frame to the output
//               file.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::WriteFrame(BYTE *pVC1Frame, DWORD dwLength)
{
    DWORD dwError = ERR_OK;
    BOOL bRet = FALSE;
    DWORD dwBytesWritten = 0;

    //bRet = WriteFile (m_hOutput, pVC1Frame, dwLength, &dwBytesWritten, NULL);
    //        
    //if (FALSE == bRet || 
    //    dwBytesWritten != dwLength) 
    //{
    //    dwError = ERR_IO;
    //}

    if(ERR_OK != dwError)
    {
        // Print the error message.
        wprintf_s(L"Failure in CVC1EncWrapper::WriteFrame\nerror = %i \n", dwError);
    }

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::ShowStatistics
//
//  Description: Writes a stats line to the console window.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::ShowStatistics()
{
    DWORD dwError = ERR_OK;
    DOUBLE dAvgBitRate = 0.0;
    DOUBLE dTotalBytes = 0.0;
    DOUBLE dTotalFrames = 0.0;
    DOUBLE dCodedFrames = 0.0;

    dwError = m_pEncoder->GetWriterStatistics(&dAvgBitRate, &dTotalBytes, &dTotalFrames, &dCodedFrames);

    if(ERR_OK == dwError)
    {
        wprintf_s(L"Average bit rate: %6.2f, total bytes processed: %10.2f.\n", dAvgBitRate, dTotalBytes);
        wprintf_s(L"Total frames: %6.2f, Coded frames: %6.2f.\n\n", dTotalFrames, dCodedFrames);
    }    

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::get_frameCount
//
//  Description: Computes the number of frames in the YUV
//               file based upon its size.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::get_frameCount()
{
    DWORD dwFrameCount = 0;
    BOOL bRet = FALSE;

    assert(NULL != m_hInput &&
           INVALID_HANDLE_VALUE != m_hInput);

    LARGE_INTEGER liFileSize;
    ZeroMemory(&liFileSize, sizeof(LARGE_INTEGER));

    //bRet = GetFileSizeEx(m_hInput, (PLARGE_INTEGER) &liFileSize);

    if(TRUE == bRet)
    {        
        dwFrameCount = (DWORD)(liFileSize.QuadPart / m_dwInputFrameSize);
    }

    return dwFrameCount;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::get_advancedProps
//
//  Description: Retrieves all the advanced properties.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::get_advancedProps()
{
    DWORD dwError = ERR_OK;

    assert(NULL != m_pEncoder);

    // GetColorFormat deliberately omitted

    if(m_ConfigProps->dwProfile != 0)
    {
        pin_ptr<DWORD> p = &m_dwBframeDeltaQP;
        dwError = m_pEncoder->GetBFrameDeltaQP(p);
    }    

    if(ERR_OK == dwError)
    {
        pin_ptr<BOOL> p = &m_bClosedEntryPt;
        dwError = m_pEncoder->GetClosedEntryPoint(p);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> pWidth = &m_dwDisplayWidth;
        pin_ptr<DWORD> pHeight = &m_dwDisplayHeight;
        dwError = m_pEncoder->GetDisplayResolution(pHeight, pWidth);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> pWidth = &m_dwEncodeWidth;
        pin_ptr<DWORD> pHeight = &m_dwEncodeHeight;
        dwError = m_pEncoder->GetEncodeResolution(pHeight, pWidth);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->GetFilters(m_Filters);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<BOOL> p = &m_bLBPresent;
        dwError = m_pEncoder->GetLetterBoxPresent(p);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<BOOL> p = &m_bLookahead;
        dwError = m_pEncoder->GetLookAhead(p);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<BOOL> p = &m_bAdaptiveGOP;
        dwError = m_pEncoder->GetAdaptiveGOP(p);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> p = &m_dwKeyPop;
        dwError = m_pEncoder->GetKeyPopReduction(p);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->GetMEProperties(m_MEProps);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> pNumThreads = &m_dwNumThreads;
        pin_ptr<DWORD> pAffinityMask = &m_dwAffinityMask;
        dwError = m_pEncoder->GetNumOfThreads(pNumThreads, pAffinityMask);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> pHeight = &m_dwPixHeight;
        pin_ptr<DWORD> pWidth = &m_dwPixWidth;
        dwError = m_pEncoder->GetPixelAspectRatio(pHeight, pWidth);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> p = &m_dwPixIndex;
        dwError = m_pEncoder->GetPixelAspectRatioIndex(p);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->GetQuantizationProperties(m_QuantProps);
    }

    if(ERR_OK == dwError)
    {
        pin_ptr<DWORD> p = &m_dwVideoType;
        dwError = m_pEncoder->GetVideoType(p);
    }

    if(ERR_OK != dwError)
    {
        // Print the error message.
        wprintf_s(L"Failure in CVC1EncWrapper::get_advancedProps\nerror = %i \n", dwError);
    }

    return dwError;
}

////////////////////////////////////////////////////////
//
//  CVC1EncWrapper::set_advancedProps
//
//  Description: Specifies all the advanced properties.
//
////////////////////////////////////////////////////////
DWORD CVC1EncWrapper::set_advancedProps()
{
    DWORD dwError = ERR_OK;

    assert(NULL != m_pEncoder);

    if(m_ConfigProps->dwProfile != 0)
    {
        dwError = m_pEncoder->SetBFrameDeltaQP(m_dwBframeDeltaQP);
    }

    if(ERR_OK == dwError)
    {
        // Only set color format info if the user provided a value.
        if(TRUE == m_bColorFormat)
        {
            dwError = m_pEncoder->SetColorFormat(*m_ColorFormat);
        }
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetClosedEntryPoint(m_bClosedEntryPt);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetDisplayResolution(m_dwDisplayHeight, m_dwDisplayWidth);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetEncodeResolution(m_dwEncodeHeight, m_dwEncodeWidth);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetFilters(*m_Filters);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetLetterBoxPresent(m_bLBPresent);
    }

    if(ERR_OK == dwError)
    {        
        dwError = m_pEncoder->SetLookAhead(m_bLookahead);        
    }

    if(ERR_OK == dwError)
    {        
        dwError = m_pEncoder->SetAdaptiveGOP(m_bAdaptiveGOP);        
    }

    if(ERR_OK == dwError)
    {        
        dwError = m_pEncoder->SetKeyPopReduction(m_dwKeyPop);        
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetMEProperties(*m_MEProps);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetNumOfThreads(m_dwNumThreads, m_dwAffinityMask);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetPixelAspectRatio(m_dwPixHeight, m_dwPixWidth);
    }

    if(ERR_OK == dwError)
    {
        // Set only if the user provided a value.
        if(TRUE == m_bPARI)
        {
            dwError = m_pEncoder->SetPixelAspectRatioIndex(m_dwPixIndex);
        }
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetQuantizationProperties(*m_QuantProps);
    }

    if(ERR_OK == dwError)
    {
        dwError = m_pEncoder->SetVideoType(m_dwVideoType);
    }

    if(ERR_OK != dwError)
    {
        // Print the error message.
        wprintf_s(L"Failure in CVC1EncWrapper::set_advancedProps\nerror = %i \n", dwError);
    }

    return dwError;
}





