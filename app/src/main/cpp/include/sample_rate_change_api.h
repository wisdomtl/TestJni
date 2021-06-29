#ifndef SAMPLE_RATE_CHANGE_API_H_
#define SAMPLE_RATE_CHANGE_API_H_

#include "audio_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TT_SRC_ERR_OK                  0   // src ok
#define TT_SRC_ERR_CREATE             -1   // create fail
#define TT_SRC_ERR_HANDLE             -2
#define TT_SRC_ERR_PARAMS             -3
#define TT_SRC_ERR_SAMPLE_RATE        -4
#define TT_SRC_ERR_QUALITY            -5
#define TT_SRC_ERR_CHANNEL            -6
#define TT_SRC_ERR_INIT               -7
#define TT_SRC_ERR_NOT_INIT           -8
#define TT_SRC_ERR_OPEN_INPUT_FILE    -9
#define TT_SRC_ERR_OPEN_OUTPUT_FILE   -10
#define TT_SRC_ERR_PROCESS_FILE       -11
#define TT_SRC_ERR_PCMIN              -12
#define TT_SRC_ERR_PCMOUT             -13
#define TT_SRC_ERR_PROCESS_FRAME      -14
#define TT_SRC_ERR_VERSION_NULL       -15
#define TT_SRC_ERR_VERSION_LENGTH     -16

typedef struct SRCParamsStruct{
    INT32 inSampleRate;   // in sample rate
    INT32 outSampleRate;  // out sample rate
    INT32 quality;        // [0, 10]
    INT32 channel;        // {1}  only mono supported currently
}SRCParams;


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
extern INT32 TT_SRC_Get_Version(INT8 *version, INT32 length);


//*****************************************************************************
//  Function: Creates an instance to the SRC(sample rate change) structure.
//
// Input:
//      -  SRC_inst: Pointer to SRC instance that should be created.
//
// Output:
//      -  SRC_inst: Pointer to created SRC instance.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_SRC_Create(VOID **SRC_inst);


//*****************************************************************************
// Function: Initializes a SRC instance.
//
// Input:
//      - SRC_inst: Instance that should be initialized.
//      - pstParams:
//
// Output:
//      - SRC_inst: Initialized instance
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_SRC_Init(VOID *SRC_inst, SRCParams *pstParams);


//*****************************************************************************
// Function: Do SRC for input speech file.
//
// Input:
//      - SRC_inst: SRC Instance. Needs to be initiated before call.
//      - file_in : input PCM file.
//
// Output:
//      - NS_inst : Updated SRC instance
//      - file_out: PCM file after SRC.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_SRC_Process_File(VOID *SRC_inst, char *file_in, char *file_out);


//*****************************************************************************
// Function: Get parameters.
//
// Input:
//      - SRC_inst: SRC Instance. Needs to be initiated before call.
//
// Output:
//      - pstParams: pointer struct of parameters.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_SRC_GetParams(VOID *SRC_inst, SRCParams *pstParams);


//*****************************************************************************
// Function: Frees the dynamic memory of a specified SRC instance.
//
// Input:
//      - SRC_inst: Pointer to SRC instance that should be freed.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_SRC_Free(VOID *SRC_inst);


#ifdef __cplusplus
}
#endif

#endif


