// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) Microsoft Corporation. All rights reserved.

// stdafx.cpp : source file that includes just the standard includes
// RAW2ES.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//// Prints the command line options to the console window.
//void PrintHelp()
//{
//    wprintf_s (L"\n\nRAW2ES Sample Help\n");
//    wprintf_s (L"Copyright (C) Microsoft Corporation. All rights reserved.\n");
//
//    wprintf_s (L"\n");
//
//    wprintf_s (L"The required parameters are based on the default rate control mode 3,\n");
//    wprintf_s (L"2-pass peak constrained VBR.\n");
//    wprintf_s (L"If you change the rate control mode, simply specify appropriate values\n");
//    wprintf_s (L"for the required parameters.\n\n");
//
//    wprintf_s (L"Syntax: \nRAW2ES.exe -i <inputfile> -o <outputfile> \n");
//    wprintf_s (L"\t-maxw <source width> -maxh <source height> \n");
//    wprintf_s (L"\t-rate <bitrate> -framerate <frame rate> -peakrate <peakrate> -profiletype <profile type>\n");
//    wprintf_s (L"\t-bframes <number of b frames> -maxkeydist <maximum key frame distance>\n");
//    wprintf_s (L"\t-vbv <vbv buffer size> [Optional 1] <value1> [Optional 2] <value2> ...\n");
//    wprintf_s (L"\n\nCommand line options:\n\n");
//
//    wprintf_s (L"-i <input YUV file name>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"-o <output VC-1 file name>\n");
//    wprintf_s (L"\n");
//
//    ///////////////  CONFIG_PROPERTIES  ///////////////////
//
//    wprintf_s (L"[-rate] <output rate (kilobits per second)>\n");
//    wprintf_s (L"\n");
//
//     wprintf_s (L"[-complexity] <encoder complexity>\n");
//    wprintf_s (L"\t0 to 5, 0 = best performance, 5 = best quality.\n");
//    wprintf_s (L"\n");
// 
//    wprintf_s (L"[-qp] <quantization parameter (QP)>\n");
//    wprintf_s (L"\tFixed QP if -ratecontrol equals 1 (1-pass VBR)\n");
//    wprintf_s (L"\tMax QP if -ratecontrol equals 0 or 2 (CBR)\n");
//    wprintf_s (L"\n"); 
//
//    wprintf_s (L"[-framerate] <source frame rate>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-interlaced] Specifies interlaced source.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-maxkeydist] <maximum distance between key frames>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-bframes] <number of B-frames per P-frame>\n");
//    wprintf_s (L"\tRange is 0 to 7.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-peakrate] <peak bit rate (kilobits per second)>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-profiletype] <type specifier>\n");
//    wprintf_s (L"\t0 = Simple, 1= Main, 2 = Advanced.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-ratecontrol]\n");
//    wprintf_s(L"\t0 = 1-pass CBR\n\t1 = 1-pass VBR fixed QP\n");
//    wprintf_s (L"\t2 = 2-pass CBR\n\t3 = 2-pass peak constrained VBR\n\t4 = 2-pass unconstrained VBR.");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-vbv] <size of vbv buffer>\n");
//    wprintf_s (L"\tMaximum is 4294967295\n");
//    wprintf_s (L"\n");
//
//    //////////////////////// BFRAME_PROPERTIES /////////////////////////////
//
//    wprintf_s (L"[-bdeltaqp] <qp increase for B-frames>\n");
//    wprintf_s (L"\t0 to 30\n");
//    wprintf_s (L"\n");
//
//
//    ////////////////// COLOR_FORMAT ///////////////////////
//
//    wprintf_s (L"[-colorformatflags] <colorformatflag> <colorprimaries> <transferchar> \n\t\t    <matrixcoef>\n");
//    wprintf_s (L"\t- If colorformatflag is 1, then you must specify colorprimaries, \n\t  transferchar, and matrixcoef.\n");
//    wprintf_s (L"\t- If colorformatflag is 0, then no need to specify colorprimaries,\n\t  transferchar, and matrixcoef");
//    wprintf_s (L" because the decoder will generate them\n\t  for you.\n");
//    wprintf_s (L"\n");
//
//
//    /////////////////// FILTERS /////////////////////////
//
//    wprintf_s (L"[-denoise] <0 or 1>\n");
//    wprintf_s (L"\tTurn on or off denoise filter.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-inloop] <0 or 1>\n");
//    wprintf_s (L"\tTurn on or off in-loop filter.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-median] <0 or 1>\n");
//    wprintf_s (L"\tTurn on or off median filter.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-overlap] <0 or 1>\n");
//    wprintf_s (L"\tTurn on or off overlap smoothing.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-noiseedge] <0 or 1>\n");
//    wprintf_s (L"\tTurn on or off noise edge removal.\n");
//    wprintf_s (L"\n");
//
//    //////////////////  ME_PROPERTIES  ////////////////////
//    
//    wprintf_s (L"[-deltamvrange] <delta mv range index>\n");
//    wprintf_s (L"\t0 = off, 1= horizontal, 2= vertical, 3 = h + v.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-motionsearchlevel] <level>\n"); 
//    wprintf_s (L"\t0 = Luma only. (Default)\n\t1 = Luma w/ nearest-int chroma. \n\t2 = Luma w/ true chroma.\n");
//    wprintf_s (L"\t3 = Macroblock-adaptive with true chroma. \n\t4 = Macroblock adaptive with nearest int chroma.\n");
//    wprintf_s (L"\n");   
//
//    wprintf_s (L"[-mesearchmethod] <phase>\n"); 
//    wprintf_s (L"\t0 = off, 1 = always use hadamard, 2 = adaptive sad/hadamard \n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-mbcost] <cost method>\n");
//    wprintf_s (L"\t0 = SAD/Hadamard, 1 = RD cost.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-mvcost] <cost method>\n");
//    wprintf_s (L"\t0 = static, 1 = dynamic.\n");
//    wprintf_s (L"\n");
//
//
//    wprintf_s (L"[-mvrange] <mv range>\n");
//    wprintf_s (L"\t0 to 3 are increasing ranges. 4 is macroblock adaptive.\n");
//    wprintf_s (L"\n");
//
//    ///////////////////////  QUANT_PROPERTIES /////////////////////
//
//
//    wprintf_s (L"[-dquantoption] <level>\n");
//    wprintf_s (L"\t0 to 3, 0 = off, 1 = I frame only, 2 = I/P frame only, 3 = I/P/B frame.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-adaptivequant] <adaptive quantization>\n");
//    wprintf_s (L"\t0 to 21\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-dquantpstrength] <level>\n");
//    wprintf_s (L"\tRange is 0 to 2.\n");
//    wprintf_s (L"\t0 = VC-1 encoder-managed setting.\n");
//    wprintf_s (L"\tOnly valid when -dquantoption > 0. \n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-dquantbstrength] <level>\n");
//    wprintf_s (L"\tRange is 0 to 4.\n");
//    wprintf_s (L"\t0 = VC-1 encoder-managed setting.\n");
//    wprintf_s (L"\tOnly valid when -dquantoption > 0. \n");
//    wprintf_s (L"\n");
//
//    ////////////////////  Other advanced settings  ///////////////////////
//
//    wprintf_s (L"[-closedentrypt] <closed entry point value.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-dw] <display width (pixels)>\n");
//    wprintf_s (L"\n");    
//
//    wprintf_s (L"[-dh] <display height (pixels)>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-ew] <encode width (pixels)>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-eh] <encode height (pixels)>\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-lbpresent]\n"); 
//    wprintf_s (L"\tIndicates letterboxing is present.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-lookahead]\n");
//    wprintf_s (L"Indicates use lookahead.\n");
//    wprintf_s (L"\t-ratecontrolmode must equal 0.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-adaptiveGOP]\n");
//    wprintf_s (L"Indicates use adaptive GOP.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-keyPop] <key pop level>\n");
//    wprintf_s (L"Indicates use key frame pulse reduction.\n");
//    wprintf_s (L"Range is 0 to 4. 0 = Off, 1 -4 are strength levels.");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-threads] <num threads>\n");
//    wprintf_s (L"\tMaximum is 4.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-affinity] <affinity mask>\n");
//    wprintf_s (L"\tProcessor mapping.\n");
//    wprintf_s (L"\n");    
//
//    wprintf_s (L"[-aspectratio] <aspectratioindex> <aspectratiowidth> <aspectratioheight> \n");
//    wprintf_s (L"\tIf aspectratioindex is 15, then you must specify aspectratiowidth and\n\t  aspectratioheight\n");
//    wprintf_s (L"\n");   
//
//    wprintf_s (L"[-videotype] <type>\n");
//    wprintf_s (L"\t0 = progressive, 1 = interlaced frames, 2= interlaced fields\n");
//    wprintf_s (L"\t3 = detect interlacing type, 4 = automatic.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-tff]\n"); 
//    wprintf_s (L"\tIndicates top field first.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-rff]\n"); 
//    wprintf_s (L"\tIndicates repeat first field.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"[-SH]\n"); 
//    wprintf_s (L"\tIndicates ES_SH mode.\n");
//    wprintf_s (L"\n");
//
//    wprintf_s (L"\n\nExample: RAW2ES.exe -i video.yuv -o encoded.vc1 -maxw 720 -maxh 576\n");
//    wprintf_s (L"\tencoded.vc1 -framerate 25 -rate 1200\n");
//    wprintf_s (L"\t-profiletype 2 -bframes 2 -maxkeydist 6 -vbv 300000\n\n");
//
//}
