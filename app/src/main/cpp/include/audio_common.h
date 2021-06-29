#ifndef AUDIO_COMMON_H_
#define AUDIO_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL  0
#endif


typedef void             VOID;

typedef char             INT8;
typedef unsigned char    UINT8;

typedef short            INT16;
typedef unsigned short   UINT16;

typedef int              INT32;
typedef unsigned int     UINT32;

typedef long long           INT64;
typedef unsigned long long  UINT64;

typedef float            Float32;
typedef double           Float64;


// error code
#define TT_AUDIO_ERR_OK               (0)
#define TT_AUDIO_ERR_VERSION_NULL     (-1)
#define TT_AUDIO_ERR_VERSION_LENGTH   (-2) // versionStr length is too short
#define TT_AUDIO_ERR_INVALID          (-3)


//*****************************************************************************
// Function: Returns the version number of the audio lib.
//
// Input:
//       - version: Pointer to a character array where the version info is stored.
//       - length : Length of version. The RECOMMENDED byte-length is not less than 40.
//
// Return value:   0 - OK
//                 others - Error (probably length is not sufficient)
//*****************************************************************************
extern INT32 TT_Audio_Get_Version(INT8 *versionStr, INT32 length);


//*****************************************************************************
// Function: Returns the validity of the audio lib.
//
// Return value:   0 - OK
//                       -3 - invalid
//*****************************************************************************
extern INT32 TT_Audio_Check_Validity();



#ifdef __cplusplus
}
#endif

#endif

