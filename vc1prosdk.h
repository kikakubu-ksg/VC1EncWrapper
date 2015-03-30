//*@@@+++@@@@******************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
//*@@@---@@@@******************************************************************
#ifndef __encodersdk_api_h__
#define __encodersdk_api_h__

// Encoder enums
typedef enum
{
    I,
    P,
    B,
    BI,
    II,
    IP,
    PI,
    PP,
    BB,
    BIB,
    BBI,
    BIBI,
    Skipped
} FrameType;

typedef enum
{
    RAW,
    ES,
    ES_SH
} OutputType;

#define NOT_APPLICABLE             0
#define CODECSTR_MAX_LEN         256

// Error codes
#define ERR_OK                    0L
#define ERR_ENCODER             -10L
#define ERR_INVALIDARG          -20L
#define ERR_INVALIDSETTING      -30L
#define ERR_MEMORY              -40L
#define ERR_POINTER             -50L

#define ERR_ENCODE_STARTED      -60L
#define ERR_IO                  -70L
#define ERR_NOANALYZE_FRAME     -80L
#define ERR_NOTCONFIGURED       -90L
#define ERR_NOENCODE_FRAME      -100L
#define ERR_NOMORE_FRAMES       -110L
#define ERR_NO_OP_FRAME         -120L
#define ERR_NOSTART_ANALYZE     -130L
#define ERR_NOSTART_ENCODE      -140L

// Encoder parameter grouping
typedef struct {
    BOOL  bColorFormatFlag;
    DWORD dwColorMatrixCoefficient;
    DWORD dwColorPrimaries;
    DWORD dwColorTransferChar;
} COLOR_FORMAT;

typedef struct {
    DOUBLE  dBitRate;
    DWORD   dwComplexityLevel;
    DWORD   dwQP;
    DOUBLE  dFrameRate;
    BOOL    bInterlacedSource;
    DWORD   dwMaxKeyFrameDistance;
    DWORD   dwMaxHeight;
    DWORD   dwMaxWidth;
    DWORD   dwNumOfBFrames;
    DOUBLE  dPeakBitRate;
    DWORD   dwProfile;
    DWORD   dwRateControlMode;
    DWORD   dwVBVBufferInBytes;
} CONFIG_PROPERTIES;

typedef struct {
    BOOL bDenoise;
    BOOL bInLoop;
    BOOL bMedian;
    BOOL bOverlapSmoothing;
    BOOL bNoiseEdgeRemoval;
} FILTERS;

typedef struct {
    DWORD dwDeltaMVRangeIndex;
    DWORD dwMotionSearchLevel;
    DWORD dwMotionSearchMethod;
    DWORD dwMBModeCost;
    DWORD dwMVCost;
    DWORD dwMVRange;
} ME_PROPERTIES;

typedef struct {
    DWORD dwAdaptiveQuant;
    DWORD dwDQuantOption;
    DWORD dwDQuantPStrength;
    DWORD dwDQuantBStrength;
} QUANT_PROPERTIES;

class CVC1EncoderImpl;

class CVC1Encoder
{
public:
    CVC1Encoder ();
    ~CVC1Encoder ();

    ////////////////////////////////////////////////////////////////////////////////////////
    // Start VC1 encode methods. 
    // Note: These methods must be called in this order: Configure, SetMethods, 
    // StartAnalyze, AnalyzeFrame, StartEncode, EncodeFrame, Flush, EndEncode.
    ////////////////////////////////////////////////////////////////////////////////////////
    // Setup encoder for the first time or reset encoder in subsequent runs.   
    // Returns ERR_OK if configured; ERR_INVALIDSETTING if settings conflict. 
    // ERR_ENCODE_STARTED if encode already started; Otherwise ERR_INVALIDARG.
    DWORD Configure (CONFIG_PROPERTIES ConfigProps);

    // Signals to encoder that encoding, for either a 1 pass or 2nd pass encode, is going to begin.
    // Returns ERR_OK if successful; ERR_NOTCONFIGURED if encoder not configured; otherwise ERR_ENCODER.
    DWORD StartAnalyze 
    (
    );

    // Signals to encoder that encoding, for either a 1 pass or 2nd pass encode, is going to begin.
    // Returns ERR_OK if successful; ERR_NOTCONFIGURED if encoder not configured; otherwise ERR_ENCODER.
    DWORD StartEncode 
    (
    );

    // The one and only encode a single frame.
    // Returns ERR_OK, ERR_NOT_CONFIGURED, ERR_ENCODER, ERR_NOSTART_ANALYZE.
    DWORD AnalyzeFrame
    (
        BYTE      *pYUVSrcSample                // YUV source               - raw input sample
    );

    // The one and only encode a single frame.
    // Returns ERR_OK, ERR_ENCODER, ERR_IO, ERR_NOT_CONFIGURED, ERR_NOTSTARTED, ERR_POINTER, 
    // ERR_MEMORY, ERR_NO_OP_FRAME.
    DWORD EncodeFrame
    (
        BYTE      *pYUVSrcSample,               // YUV source               - raw input sample
        BYTE      *pOutputBuffer,               // VC1 output               - compressed output
        DWORD     *pdwVC1DataSize,              // VC1 data size            - compressed data size
        INT64	  qwInputSampleTime,            // input sample time        - input sample time
        INT64	  *pqwOutputSampleTime,         // output sample time       - output sample time
        BOOL	  bTopFieldFirst,               // top field flag           - indicates if top field first
        BOOL	  bRepeatFirstField,            // repeat field flag        - indicates if first field should be repeated
        FrameType *pFrameType                   // indicates frame type     - indicates output frame type
    );

    // This method will flush all remaining buffers left in encode queue once raw input samples
    // have been exhausted. Application should iterate calls to Flush until ERR_NOMORE_FRAMES is returned. 
    // Returns ERR_OK, ERR_INVALIDARG, ERR_NOMORE_FRAMES.
    DWORD Flush
    (
        BYTE      *pOutputBuffer,
        DWORD     *pdwVC1DataSize,              // VC1 data size            - compressed data size
        INT64	  *pqwOutputSampleTime,	        // output sample time       - output sample time
        FrameType *pFrameType                   // indicates frame type     - indicates output frame type
    );

    // This method will signal to encoder that encoding is complete. It must be called to indicate 
    // that the encoding session is over. Returns ERR_OK, ERR_NOSTART_ANALYZE, ERR_NOANALYZE_FRAME, ERR_ENCODER.
    DWORD EndAnalyze ( );

    // This method will signal to encoder that encoding is complete. It must be called to indicate 
    // that the encoding session is over. Returns ERR_OK, ERR_NOSTART_ENCODE, ERR_NOENCODE_FRAME, ERR_ENCODER.
    DWORD EndEncode ( );

    // Force a key frame. Returns ERR_OK, ERR_ENCODER.
    DWORD ForceKeyFrame ( );

    // Since we persist advanced settings across encodes, this function resets
    // encoder settings back to default state. Returns ERR_OK, ERR_ENCODE_STARTED.
    DWORD ResetDefaults();
    ////////////////////////////////////////////////////////////////////////////////////////
    // End VC1 encode methods. 
    ////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////
    // Start the Get methods.
    ////////////////////////////////////////////////////////////////////////////////////////
    // Get adaptive GOP setting from m_pVC1Encoder.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetAdaptiveGOP(BOOL *pbAdaptiveGOP);

    // Get Bframe delta QP from m_pVC1Encoder 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetBFrameDeltaQP(DWORD *pdwBDeltaQP);

    // Get closed/open GOP setting from m_pVC1Encoder 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetClosedEntryPoint(BOOL *pbClosedEntryPoint);

    // This function generates the sequence header into pcSequenceHeaderBits
    // Returns ERR_OK if the header is generated; Otherwise ERR_NOSTART_ENCODE, ERR_POINTER,
    // ERR_ENCODER.
    DWORD GetCodecPrivateData(BYTE *pucSequenceHeader, DWORD *pdwSize, DWORD *pdwEntryPointOffset);

    // Get name of codec.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetCodecString(WCHAR *pszCodecName);

    // Get the config properties.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetConfigProperties(CONFIG_PROPERTIES *pConfigProps);

    // Get display resolution from from m_pVC1Encoder 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetDisplayResolution(DWORD *pdwDisplayHeight, DWORD *pdwDisplayWidth);

    // Get encode resolution from from m_pVC1Encoder 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if either input arg is NULL.
    DWORD GetEncodeResolution(DWORD *pdwEncHeight, DWORD *pdwEncWidth);

    // Get filters from m_pVC1Encoder
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetFilters(FILTERS *pFilters);

    // Get key-pop-reduction from m_pVC1Encoder
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetKeyPopReduction(DWORD *pdwKeyPopReduction);

    // Indicates whether the input sequence is letterboxed or not.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetLetterBoxPresent(BOOL *pbLetterBoxPresent);

    // Get number of frames for lookahead processing.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetLookAhead(BOOL *pbLookAhead);

    // Get max output buffer for the compressed bitstream.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetMaxOutputBuffer(DWORD *pdwMaxOutputBuffer);

    // Get motion properties from m_pVC1Encoder
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetMEProperties(ME_PROPERTIES *pMEProps);

    // Get number of threads and affinity mask.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetNumOfThreads(DWORD *pdwNumThreads, DWORD *pdwAffinityMask);

    // Get the output mode for the encoded bitstream. This is to identify if we should encode ES, 
    // as ASF or as HD-DVD given in each case we’ll include different data in the bitstream.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetOutputMode(OutputType *pVc1OutputType);

    // Get pixel aspect ratio from m_pVC1Encoder 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetPixelAspectRatio(DWORD *pdwAspectHeight, DWORD *pdwAspectWidth);

    // Get quantization properties from m_pVC1Encoder
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetQuantizationProperties(QUANT_PROPERTIES *pQuantProps);

    // Get reconstructed frame, normally called after EncodeFrame().
    // Returns ERR_OK if set; Otherwise ERR_POINTER, ERR_MEMORY, ERR_ENCODER.
    DWORD GetReconstructedFrame(BYTE *pYUVReconSample);

    // Get api version number.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetVersionNumber(WCHAR *pszVersionNum);

    // Get video type.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetVideoType(DWORD *pdwVideoType);

    // Get writer stats from current frame.
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetWriterStatistics(DOUBLE *pdAvgBitRate, DOUBLE *pdTotalBytes, DOUBLE *pdTotalFrames, DOUBLE *pdCodedFrames);

    // The settings described below are intended for HD-DVD encoding settings only. 
    // These methods have to be explicitly called to configure encoder appropriately. 
    // Returns ERR_OK if set; Otherwise ERR_POINTER if input arg is NULL.
    DWORD GetColorFormat(COLOR_FORMAT *pColorFormatType);

    DWORD GetPixelAspectRatioIndex(DWORD *pdwAspectRatioIndex);
    ////////////////////////////////////////////////////////////////////////////////////////
    // End the Get methods.
    ////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////
    // Start the Set methods.
    // Note: Set functions can only be called after Configure() and prior to the 
    // StartAnalyze() function when doing two pass encoding and prior to the StartEncode() 
    // function when doing one pass encoding.
    ////////////////////////////////////////////////////////////////////////////////////////
    // This sets the adaptive GOP used in preprocessing.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetAdaptiveGOP(BOOL bAdaptiveGOP);

    // This sets the BFrame delta QP.
    // Returns ERR_OK if set; Otherwise ERR_INVALIDARG, ERR_INVALIDSETTING, ERR_ENCODE_STARTED.
    DWORD SetBFrameDeltaQP(DWORD dwBDeltaQP);
    
    // Set either closed or open GOPs for the entire sequence. Default CLOSED.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetClosedEntryPoint(BOOL bClosedEntryPoint);

    // Set display resolution in m_pStreamEncoder->m_pVC1Encoder 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetDisplayResolution(DWORD dwDisplayHeight, DWORD	dwDisplayWidth);

    // Set encode resolution in m_pStreamEncoder->m_pVC1Encoder 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetEncodeResolution(DWORD dwEncHeight, DWORD	dwEncWidth);

    // Set filter properties, denoise, loopfilter, median, overlap smoothing, and noise edge removal.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, ERR_INVALIDSETTING.
    DWORD SetFilters(FILTERS Filters);

    // This setting specifies whether to enable key-pop-reduction. 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, ERR_MEMORY.
    DWORD SetKeyPopReduction(DWORD dwKeyPopReduction);

    // Indicates whether the input sequence is letterboxed or not. This doesn’t specify the extent 
    // of the letterbox region which is handled by the letterbox detection code inside the encoder. 
    // Default FALSE.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetLetterBoxPresent(BOOL bLetterBoxPresent);

    // This setting specifies the number of frames after the current frame that the codec will evaluate 
    // before encoding the current frame. When this is done, the video will be encoded more efficiently. 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, ERR_MEMORY.
    DWORD SetLookAhead(BOOL bLookAhead);

    // This settings specifies delta mv range, macroblock mode, motion match method, motion search 
    // level, and mv range.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, 
    // ERR_INVALIDSETTING.
    DWORD SetMEProperties(ME_PROPERTIES MEProps);

    // This sets the number of threads and affinity mask.
    // Returns ERR_OK if set; Otherwise ERR_INVALIDARG, ERR_ENCODER.
    DWORD SetNumOfThreads(DWORD dwNumThreads, DWORD dwAffinityMask);
    
    // Set the output mode for the encoded bitstream. This is to identify if we should encode ES, 
    // as ASF or as HD-DVD given in each case we’ll include different data in bitstream.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetOutputMode(OutputType Vc1OutputType);

    // Set pixel aspect ratio.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetPixelAspectRatio(DWORD dwAspectHeight, DWORD dwAspectWidth);

    // Set quantization properties: adaptive quant, dquant option, and dquant strength.
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, ERR_ENCODER, 
    // ERR_INVALIDSETTING.
    DWORD SetQuantizationProperties(QUANT_PROPERTIES QuantProps);

    // Set the video type mode for the encoded bitstream. 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG, ERR_INVALIDSETTING.
    DWORD SetVideoType(DWORD dwVideoType);

    // The settings described below are intended for HD-DVD encoding settings only. 
    // These methods have to be explicitly called to configure encoder appropriately. 
    // Therefore, there are no default values specified. 
    // Returns ERR_OK if set; ERR_ENCODE_STARTED if encoder already started; Otherwise ERR_INVALIDARG.
    DWORD SetColorFormat(COLOR_FORMAT ColorFormatType);

    DWORD SetPixelAspectRatioIndex(DWORD dwAspectRatioIndex);

    ////////////////////////////////////////////////////////////////////////////////////////
    // End the Set methods.
    ////////////////////////////////////////////////////////////////////////////////////////

private:
   
    class  CVC1EncoderImpl *m_pVC1Encoder;
}; 


#endif //__encodersdk_api_h__
