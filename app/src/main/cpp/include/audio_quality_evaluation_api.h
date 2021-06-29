#ifndef Audio_Quality_Evaluation_API_H_
#define Audio_Quality_Evaluation_API_H_

#include "audio_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TT_Audio_Quality_Evaluation_ERR_OK 0      //  ok
#define TT_Audio_Quality_Evaluation_ERR_CREATE -1 // create fail
#define TT_Audio_Quality_Evaluation_ERR_HANDLE -2
#define TT_Audio_Quality_Evaluation_ERR_PARAMS -3
#define TT_Audio_Quality_Evaluation_ERR_FS -4
#define TT_Audio_Quality_Evaluation_ERR_CHANNEL -5
#define TT_Audio_Quality_Evaluation_ERR_FRAMELEN -6
#define TT_Audio_Quality_Evaluation_ERR_INIT -7
#define TT_Audio_Quality_Evaluation_ERR_SET_CONFIG -8
#define TT_Audio_Quality_Evaluation_ERR_OPEN_INPUT_FILE -9
#define TT_Audio_Quality_Evaluation_ERR_OPEN_OUTPUT_FILE -10
#define TT_Audio_Quality_Evaluation_ERR_PROCESS_FILE -11
#define TT_Audio_Quality_Evaluation_ERR_PCMIN -12
#define TT_Audio_Quality_Evaluation_ERR_PCMOUT -13
#define TT_Audio_Quality_Evaluation_ERR_NOT_INIT -14
#define TT_Audio_Quality_Evaluation_ERR_PROCESS_FRAME -15
#define TT_Audio_Quality_Evaluation_ERR_FREE -16
#define TT_Audio_Quality_Evaluation_ERR_VERSION_NULL -17
#define TT_Audio_Quality_Evaluation_ERR_VERSION_LENGTH -18

    // init params
    typedef struct AudioQualityEvaluationParams
    {
        UINT32 fs;       // add comments
        UINT32 channel;  //
        UINT32 frameLen; //
        UINT16 mode;     // aqe mode flag
        // other params
    } stAudioQualityEvaluationParams;

    // set params
    typedef struct AudioQualityEvaluationConfig
    {
        INT16 params0; // aqe mode flag
        // other params
    } stAudioQualityEvaluationConfig;

    extern const stAudioQualityEvaluationParams TTAudioQualityEvaluationParamsDefault;
    //*****************************************************************************
    // Function: Returns the version number of the code.
    //
    // Input:
    //       - version: Pointer to a character array where the version info is stored.
    //       - length : Length of version. The RECOMMENDED byte-length is not less than 40 (use a proper length).
    //
    // Return value:   0 - OK
    //                 others - Error (probably length is not sufficient)
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Get_Version(INT8 *version, INT32 length);

    //*****************************************************************************
    //  Function: Creates an instance to the Audio Module  channel.
    //
    // Input:
    //      -  AudioQualityEvaluationInst: Pointer to Audio Module instance that should be created.
    //
    // Output:
    //      -  AudioQualityEvaluationInst: Pointer to created Audio Module instance.
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Create(VOID **AudioQualityEvaluationInst);

    //*****************************************************************************
    // Function: Initializes a Audio Module instance.
    //
    // Input:
    //      - AudioQualityEvaluationInst: Instance that should be initialized.
    //      - pstParams: (add comments)
    //
    // Output:
    //      - AudioQualityEvaluationInst: Initialized instance
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Init(VOID *AudioQualityEvaluationInst, stAudioQualityEvaluationParams *pstParams);

    //*****************************************************************************
    // Function: Do Audio Module for input speech frame.
    //
    // ATTENTION: some comments like (the length of one frame MUST be 10ms, that is 160 points for 16000Hz and so on.)
    //
    // Input
    //      - AudioQualityEvaluationInst: Audio Module Instance. Needs to be initiated before call.
    //      - PCMIn : input PCM frame.
    //
    // Output:
    //      - AudioQualityEvaluationInst: Updated Audio Module instance
    //      - PCMOut: PCM frame after Audio Module.
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Process_Frame(VOID *AudioQualityEvaluationInst, INT16 *PCMIn, INT32 PCMLen, Float32 *AudioConfidence, INT32 *AudioFrameCount);

    //*****************************************************************************
    // Function: Do Audio Module for input speech file.
    //
    // Input
    //      - AudioQualityEvaluationInst: Audio Module Instance. Needs to be initiated before call.
    //      - file_in : input PCM file.
    //
    // Output:
    //      - AudioQualityEvaluationInst: Updated Audio Module instance
    //      - file_out: PCM file after Audio Module.
    //
    // Return value:  0 - OK
    //               others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Process_File(VOID *AudioQualityEvaluationInst, char *file_in, Float32 *AudioConfidence, INT32 *AudioFrameCount);

    //*****************************************************************************
    //  Function: Set Audio Module params when user tuning.
    //
    // Input:
    //      -  AudioQualityEvaluationInst: Pointer to an Audio Module instance that was initialized ALREADY.
    //
    // Output:
    //      -  AudioQualityEvaluationInst: updated Audio Module instance.
    //      -  pstConfig: configs that will be used to update the instance.
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_SetParams(VOID *AudioQualityEvaluationInst, stAudioQualityEvaluationConfig *pstConfig);

    //*****************************************************************************
    // Function: Get parameters.
    //
    // Input
    //      - AudioQualityEvaluationInst: Audio Module Instance. Needs to be initiated before call.
    //
    // Output :
    //      - stAudioQualityEvaluationParams: struct of parameters.
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_GetParams(VOID *AudioQualityEvaluationInst, stAudioQualityEvaluationParams *pstParams);

    //*****************************************************************************
    // Function: Frees the dynamic memory of a specified Audio Module instance.
    //
    // Input:
    //      - AudioQualityEvaluationInst: Pointer to Audio Module instance that should be freed.
    //
    // Return value:  0 - OK
    //                others - Error
    //*****************************************************************************
    extern INT32 TT_Audio_Quality_Evaluation_Free(VOID *AudioQualityEvaluationInst);

#ifdef __cplusplus
}
#endif

#endif
