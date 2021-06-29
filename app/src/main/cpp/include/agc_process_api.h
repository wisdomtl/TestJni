#ifndef AGC_PROCESS_API_H_
#define AGC_PROCESS_API_H_

#include "audio_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TT_AGC_ERR_OK                   0   // agc ok
#define TT_AGC_ERR_CREATE              -1   // create fail
#define TT_AGC_ERR_HANDLE              -2
#define TT_AGC_ERR_PARAMS              -3
#define TT_AGC_ERR_FS                  -4   // fs invalid
#define TT_AGC_ERR_TARGETLEVELDBFS     -5   // invalid
#define TT_AGC_ERR_COMPRESSIONGAINDB   -6
#define TT_AGC_ERR_LIMITERENABLE       -7
#define TT_AGC_ERR_INIT                -8
#define TT_AGC_ERR_SET_CONFIG          -9
#define TT_AGC_ERR_OPEN_INPUT_FILE     -10
#define TT_AGC_ERR_OPEN_OUTPUT_FILE    -11
#define TT_AGC_ERR_PROCESS_VIRTUALMIC  -12
#define TT_AGC_ERR_PROCESS_FILE        -13
#define TT_AGC_ERR_PCMIN               -14
#define TT_AGC_ERR_PCMOUT              -15
#define TT_AGC_ERR_NOT_INIT            -16
#define TT_AGC_ERR_PROCESS_FRAME       -17
#define TT_AGC_ERR_FREE                -18
#define TT_AGC_ERR_VERSION_NULL        -19
#define TT_AGC_ERR_VERSION_LENGTH      -20

// init
typedef struct AGCParamsStruct{
    UINT32 fs;                // {16000, 32000}
    INT16 targetLevelDbfs;    // [0,31]dB
    INT16 compressionGaindB;  // [0, 40]dB
    INT8  limiterEnable;      // {0, 1}
}stAGCParams;


//*****************************************************************************
// Function: Returns the version number of the code.
//
// Input:
//       - version: Pointer to a character array where the version info is stored.
//       - length : Length of version. The RECOMMENDED byte-length is not less than 40.
//
// Return value:   0 - OK
//                 others - Error (probably length is not sufficient)
//*****************************************************************************
extern INT32 TT_AGC_Get_Version(INT8*version, INT32 length);


//*****************************************************************************
//  Function: Creates an instance to the AGC(auto gain control) channel.
//
// Input:
//      -  AGC_inst: Pointer to AGC instance that should be created.
//
// Output:
//      -  AGC_inst: Pointer to created AGC instance.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_AGC_Create(VOID **AGC_inst);


//*****************************************************************************
// Function: Initializes a AGC instance.
//
// Input:
//      - AGC_inst: Instance that should be initialized.
//      - pstParams: sample frequency,  16000Hz and 32000Hz supported.
//
// Output:
//      - AGC_inst: Initialized instance
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_AGC_Init(VOID *AGC_inst, stAGCParams *pstParams);


//*****************************************************************************
// Function: Do AGC for input speech file.
//
// Input
//      - AGC_inst: AGC Instance. Needs to be initiated before call.
//      - file_in : input PCM file.
//
// Output:
//      - AGC_inst: Updated AGC instance
//      - file_out: PCM file after AGC.
//
// Return value:  0 - OK
//               others - Error
//*****************************************************************************
extern INT32 TT_AGC_Process_File(VOID *AGC_inst, char *file_in, char *file_out);


//*****************************************************************************
// Function: Get parameters.
//
// Input
//      - AGC_inst: AGC Instance. Needs to be initiated before call.
//
// Output :
//      - stAGCParams: struct of parameters.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_AGC_GetParams(VOID *AGC_inst, stAGCParams* pstParams);


//*****************************************************************************
// Function: Frees the dynamic memory of a specified AGC instance.
//
// Input:
//      - AGC_inst: Pointer to AGC instance that should be freed.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_AGC_Free(VOID *AGC_inst);


#ifdef __cplusplus
}
#endif

#endif

