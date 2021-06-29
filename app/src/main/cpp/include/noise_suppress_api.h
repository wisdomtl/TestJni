#ifndef NOISE_SUPPRESS_API_H_
#define NOISE_SUPPRESS_API_H_

#include "audio_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TT_NS_ERR_OK                  0   // ns ok
#define TT_NS_ERR_CREATE             -1   // create fail
#define TT_NS_ERR_HANDLE             -2
#define TT_NS_ERR_PARAMS             -3
#define TT_NS_ERR_FS                 -4   // fs invalid
#define TT_NS_ERR_MAXDENOISEDB       -5   // denoisedB invalid
#define TT_NS_ERR_INIT               -6
#define TT_NS_ERR_OPEN_INPUT_FILE    -7
#define TT_NS_ERR_OPEN_OUTPUT_FILE   -8
#define TT_NS_ERR_PCMIN              -9
#define TT_NS_ERR_PCMOUT             -10
#define TT_NS_ERR_NOT_INIT           -11
#define TT_NS_ERR_CONFIG             -12
#define TT_NS_ERR_PROCESS_FILE       -13
#define TT_NS_ERR_PROCESS_FRAME      -14
#define TT_NS_ERR_VERSION_NULL       -15
#define TT_NS_ERR_VERSION_LENGTH     -16


typedef struct NSParamsStruct{
    INT32 fs;            // 8k 16k 32k allowed
    INT32 maxDenoisedB;  // [-20,0]dB
}stNSParams;


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
extern INT32 TT_NS_Get_Version(INT8 *version, INT32 length);


//*****************************************************************************
//  Function: Creates an instance to the noise suppress structure.
//
// Input:
//      -  NS_inst: Pointer to noise suppress instance that should be created.
//
// Output:
//      -  NS_inst: Pointer to created noise suppress instance.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_NS_Create(VOID **NS_inst);


//*****************************************************************************
// Function: Initializes a NS instance.
//
// Input:
//      - NS_inst: Instance that should be initialized.
//      - pstParams: sample frequency, only 8kHz, 16kHz and 32kHz are allowed.
//                            max denoise gain should be set in [-20, 0]dB.
//
// Output:
//      - NS_inst: Initialized instance
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_NS_Init(VOID *NS_inst, stNSParams *pstParams);


//*****************************************************************************
// Function: Do noise suppression for input speech file.
//
// Input
//      - NS_inst: Ns Instance. Needs to be initiated before call.
//      - file_in   : input PCM file.
//
// Output:
//      - NS_inst: Updated Ns instance
//      - file_out: PCM file after NS.
//
// Return value:  0 - OK
//                others - Error
//*****************************************************************************
extern INT32 TT_NS_Process_File(VOID *NS_inst, char *file_in, char *file_out);


//*****************************************************************************
// Function: Get parameters.
//
// Input
//      - NS_inst: Ns Instance. Needs to be initiated before call.
//
// Output :
//      -stNSParams: struct of parameters.
//
// Return value:  0 - OK
//               others  - Error
//*****************************************************************************
extern INT32 TT_NS_GetParams(VOID *NS_inst, stNSParams *pstParams);


//*****************************************************************************
// Function: Frees the dynamic memory of a specified noise suppress instance.
//
// Input:
//      - NS_inst: Pointer to NS instance that should be freed.
//
// Return value:  0 - OK
//               others - Error
//*****************************************************************************
extern INT32 TT_NS_Free(VOID *NS_inst);


#ifdef __cplusplus
}
#endif

#endif

