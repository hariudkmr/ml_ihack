#ifndef _MFCC_DATA_H_
#define _MFCC_DATA_H_ 

#include "arm_math_types.h"


#ifdef   __cplusplus
extern "C"
{
#endif

/*****

 DCT COEFFICIENTS FOR THE MFCC

*****/


#define DCT_OUTPUT_LEN                   (5u)
#define MEL_FILTERS_LEN                  (40u)

#define NB_MFCC_DCT_COEFS_CONFIG1_F32    (200u)

extern const float32_t mfcc_dct_coefs_config1_f32[NB_MFCC_DCT_COEFS_CONFIG1_F32];
#define MFCC_DCT_COEFS    mfcc_dct_coefs_config1_f32



/*****

 WINDOW COEFFICIENTS

*****/


#define NB_MFCC_WIN_COEFS_CONFIG1_F32    (1024u)

extern const float32_t mfcc_window_coefs_config1_f32[NB_MFCC_WIN_COEFS_CONFIG1_F32];
#define MFCC_WINDOW_COEFS    mfcc_window_coefs_config1_f32



/*****

 MEL FILTER COEFFICIENTS FOR THE MFCC

*****/

#define FFT_LEN                          (1024u)
#define MEL_MIN_FREQUENCY_HZ             (64u)
#define MEL_MAX_FREQUENCY_HZ             (8000u)
#define SPECTROGRAM_BUFFER_TYPE          (BUFFER_TYPE_F32)

#define NB_MFCC_NB_FILTER_CONFIG1_F32    (40u)

extern const uint32_t mfcc_filter_pos_config1_f32[NB_MFCC_NB_FILTER_CONFIG1_F32];
extern const uint32_t mfcc_filter_len_config1_f32[NB_MFCC_NB_FILTER_CONFIG1_F32];

#define MFCC_FILTER_POS    mfcc_filter_pos_config1_f32
#define MFCC_FILTER_LEN    mfcc_filter_len_config1_f32





#define NB_MFCC_FILTER_COEFS_CONFIG1_F32    (979u)
extern const float32_t mfcc_filter_coefs_config1_f32[NB_MFCC_FILTER_COEFS_CONFIG1_F32];
#define MFCC_FILTER_COEFS    mfcc_filter_coefs_config1_f32



#ifdef   __cplusplus
}
#endif

#endif

