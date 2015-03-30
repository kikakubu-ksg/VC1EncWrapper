//*****************************************************************************
//
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//  RAW2ES.cpp
//
//  Application entry point.
//
//*****************************************************************************

#include "stdafx.h"
#include "VC1EncWrapper.h"
#include "VC1EncES.h"

VC1EncWrapper::VC1EncWrapper(){}; // コンストラクタ

DWORD VC1EncWrapper::Execute()
{
    DWORD dwError = 0;
    char x = 0;

    CVC1EncES VC1EncES;

    dwError = VC1EncES.Init();

    clock_t startTime = clock(); 

    //if(ERR_OK == dwError)
    //{
    //    dwError = VC1EncES.Analyze(); // 1st pass
    //}

    if(ERR_OK == dwError)
    {
        dwError = VC1EncES.Encode(); // 2nd pass
    }

    VC1EncES.Destroy();

    if(ERR_OK != dwError)
    {
        wprintf_s(L"\nFinal error code: %d", dwError);
    }

    clock_t endTime = clock();
    double duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    wprintf_s (L"\nTotal elapsed time: %f seconds\n", duration);

    wprintf_s(L"\nPress <Enter> to continue...\n");
    cin.getline(&x, 1);

    return 0;
}

