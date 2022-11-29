#ifndef _MFCC_DATA_H_
#define _MFCC_DATA_H_ 

{% macro iff16(s,c) -%}
{%- if configs[s][c]["hasF16"] %}
#if defined(ARM_FLOAT16_SUPPORTED)
{%- endif %}
{% endmacro -%}

{% macro endiff16(s,c) -%}
{%- if configs[s][c]["hasF16"] %}
#endif /*defined(ARM_FLOAT16_SUPPORTED) */
{%- endif %}
{% endmacro -%}

#include "arm_math_types.h"

{% if configs["hasF16"] %}
#include "arm_math_types_f16.h"
{% endif %}

#ifdef   __cplusplus
extern "C"
{
#endif

/*****

 DCT COEFFICIENTS FOR THE MFCC

*****/

{% for config in configs["dct"] %}
{{iff16("dct",config)}}
#define DCT_OUTPUT_LEN                   ({{configs["dct"][config]["dctOutputs"]}}u)
#define MEL_FILTERS_LEN                  ({{configs["dct"][config]["melFilters"]}}u)

#define NB_MFCC_DCT_COEFS_{{config.upper()}}    ({{configs["dct"][config]['dctMatrixLength']}}u)

extern const {{configs["dct"][config]["ctype"]}} mfcc_dct_coefs_{{config}}[NB_MFCC_DCT_COEFS_{{config.upper()}}];
#define MFCC_DCT_COEFS    mfcc_dct_coefs_{{config}}
{{endiff16("dct",config)}}

{% endfor %}

/*****

 WINDOW COEFFICIENTS

*****/

{% for config in configs["window"] %}
{{iff16("window",config)}}
#define NB_MFCC_WIN_COEFS_{{config.upper()}}    ({{configs["window"][config]['fftlength']}}u)

extern const {{configs["window"][config]["ctype"]}} mfcc_window_coefs_{{config}}[NB_MFCC_WIN_COEFS_{{config.upper()}}];
#define MFCC_WINDOW_COEFS    mfcc_window_coefs_{{config}}
{{endiff16("window",config)}}

{% endfor %}

/*****

 MEL FILTER COEFFICIENTS FOR THE MFCC

*****/

{% for config in configs["melfilter"] %}
#define FFT_LEN                          ({{configs["melfilter"][config]["fftlength"]}}u)
#define MEL_MIN_FREQUENCY_HZ             ({{configs["melfilter"][config]["fmin"]}}u)
#define MEL_MAX_FREQUENCY_HZ             ({{configs["melfilter"][config]["fmax"]}}u)
#define SPECTROGRAM_BUFFER_TYPE          (BUFFER_TYPE_{{configs["melfilter"][config]["type"].upper()}})

#define NB_MFCC_NB_FILTER_{{config.upper()}}    ({{configs["melfilter"][config]['melFilters']}}u)

extern const uint32_t mfcc_filter_pos_{{config}}[NB_MFCC_NB_FILTER_{{config.upper()}}];
extern const uint32_t mfcc_filter_len_{{config}}[NB_MFCC_NB_FILTER_{{config.upper()}}];

#define MFCC_FILTER_POS    mfcc_filter_pos_{{config}}
#define MFCC_FILTER_LEN    mfcc_filter_len_{{config}}

{% endfor %}



{% for config in configs["melfilter"] %}
{{iff16("melfilter",config)}}
#define NB_MFCC_FILTER_COEFS_{{config.upper()}}    ({{configs["melfilter"][config]['totalLen']}}u)
extern const {{configs["melfilter"][config]["ctype"]}} mfcc_filter_coefs_{{config}}[NB_MFCC_FILTER_COEFS_{{config.upper()}}];
#define MFCC_FILTER_COEFS    mfcc_filter_coefs_{{config}}
{{endiff16("melfilter",config)}}

{% endfor %}

#ifdef   __cplusplus
}
#endif

#endif

