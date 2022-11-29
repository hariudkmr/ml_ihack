#include "mfcc_data.h"

/* DCT coefficients */

const float32_t mfcc_dct_coefs_config1_f32[NB_MFCC_DCT_COEFS_CONFIG1_F32]={
0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,
0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,
0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,
0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,0.223607f,
0.223434f,0.222057f,0.219310f,0.215212f,0.209786f,0.203067f,0.195096f,0.185922f,0.175602f,0.164200f,
0.151784f,0.138434f,0.124229f,0.109259f,0.093615f,0.077394f,0.060696f,0.043624f,0.026282f,0.008779f,
-0.008779f,-0.026282f,-0.043624f,-0.060696f,-0.077394f,-0.093615f,-0.109259f,-0.124229f,-0.138434f,-0.151784f,
-0.164200f,-0.175602f,-0.185922f,-0.195096f,-0.203067f,-0.209786f,-0.215212f,-0.219310f,-0.222057f,-0.223434f,
0.222917f,0.217429f,0.206586f,0.190656f,0.170032f,0.145221f,0.116834f,0.085571f,0.052200f,0.017544f,
-0.017544f,-0.052200f,-0.085571f,-0.116834f,-0.145221f,-0.170032f,-0.190656f,-0.206586f,-0.217429f,-0.222917f,
-0.222917f,-0.217429f,-0.206586f,-0.190656f,-0.170032f,-0.145221f,-0.116834f,-0.085571f,-0.052200f,-0.017544f,
0.017544f,0.052200f,0.085571f,0.116834f,0.145221f,0.170032f,0.190656f,0.206586f,0.217429f,0.222917f,
0.222057f,0.209786f,0.185922f,0.151784f,0.109259f,0.060696f,0.008779f,-0.043624f,-0.093615f,-0.138434f,
-0.175602f,-0.203067f,-0.219310f,-0.223434f,-0.215212f,-0.195096f,-0.164200f,-0.124229f,-0.077394f,-0.026282f,
0.026282f,0.077394f,0.124229f,0.164200f,0.195096f,0.215212f,0.223434f,0.219310f,0.203067f,0.175602f,
0.138434f,0.093615f,0.043624f,-0.008779f,-0.060696f,-0.109259f,-0.151784f,-0.185922f,-0.209786f,-0.222057f,
0.220854f,0.199235f,0.158114f,0.101515f,0.034980f,-0.034980f,-0.101515f,-0.158114f,-0.199235f,-0.220854f,
-0.220854f,-0.199235f,-0.158114f,-0.101515f,-0.034980f,0.034980f,0.101515f,0.158114f,0.199235f,0.220854f,
0.220854f,0.199235f,0.158114f,0.101515f,0.034980f,-0.034980f,-0.101515f,-0.158114f,-0.199235f,-0.220854f,
-0.220854f,-0.199235f,-0.158114f,-0.101515f,-0.034980f,0.034980f,0.101515f,0.158114f,0.199235f,0.220854f,
};




/* Window coefficients */

const float32_t mfcc_window_coefs_config1_f32[NB_MFCC_WIN_COEFS_CONFIG1_F32]={
0.000000f,0.000009f,0.000038f,0.000085f,0.000151f,0.000235f,0.000339f,0.000461f,0.000602f,0.000762f,
0.000941f,0.001138f,0.001355f,0.001590f,0.001844f,0.002116f,0.002408f,0.002718f,0.003047f,0.003394f,
0.003760f,0.004145f,0.004549f,0.004971f,0.005412f,0.005871f,0.006349f,0.006846f,0.007361f,0.007895f,
0.008447f,0.009018f,0.009607f,0.010215f,0.010841f,0.011486f,0.012149f,0.012830f,0.013530f,0.014248f,
0.014984f,0.015739f,0.016512f,0.017303f,0.018112f,0.018939f,0.019785f,0.020648f,0.021530f,0.022429f,
0.023347f,0.024282f,0.025236f,0.026207f,0.027196f,0.028203f,0.029228f,0.030270f,0.031330f,0.032408f,
0.033504f,0.034617f,0.035747f,0.036895f,0.038060f,0.039243f,0.040443f,0.041660f,0.042895f,0.044147f,
0.045416f,0.046702f,0.048005f,0.049326f,0.050663f,0.052017f,0.053388f,0.054776f,0.056180f,0.057601f,
0.059039f,0.060494f,0.061965f,0.063453f,0.064957f,0.066477f,0.068014f,0.069567f,0.071136f,0.072721f,
0.074322f,0.075940f,0.077573f,0.079223f,0.080888f,0.082569f,0.084265f,0.085977f,0.087705f,0.089449f,
0.091208f,0.092982f,0.094771f,0.096576f,0.098396f,0.100231f,0.102082f,0.103947f,0.105827f,0.107722f,
0.109631f,0.111556f,0.113495f,0.115448f,0.117416f,0.119399f,0.121396f,0.123407f,0.125432f,0.127471f,
0.129524f,0.131592f,0.133673f,0.135768f,0.137876f,0.139999f,0.142135f,0.144284f,0.146447f,0.148623f,
0.150812f,0.153014f,0.155230f,0.157458f,0.159699f,0.161954f,0.164221f,0.166500f,0.168792f,0.171097f,
0.173414f,0.175743f,0.178084f,0.180438f,0.182803f,0.185181f,0.187570f,0.189971f,0.192384f,0.194809f,
0.197244f,0.199692f,0.202150f,0.204620f,0.207101f,0.209593f,0.212096f,0.214610f,0.217134f,0.219669f,
0.222215f,0.224771f,0.227338f,0.229914f,0.232501f,0.235098f,0.237705f,0.240322f,0.242949f,0.245585f,
0.248231f,0.250886f,0.253551f,0.256225f,0.258908f,0.261600f,0.264302f,0.267012f,0.269731f,0.272458f,
0.275194f,0.277939f,0.280692f,0.283453f,0.286222f,0.289000f,0.291785f,0.294578f,0.297379f,0.300188f,
0.303004f,0.305827f,0.308658f,0.311496f,0.314341f,0.317194f,0.320052f,0.322918f,0.325791f,0.328670f,
0.331555f,0.334447f,0.337345f,0.340249f,0.343159f,0.346075f,0.348997f,0.351925f,0.354858f,0.357796f,
0.360740f,0.363689f,0.366644f,0.369603f,0.372567f,0.375536f,0.378510f,0.381488f,0.384471f,0.387458f,
0.390449f,0.393445f,0.396444f,0.399448f,0.402455f,0.405466f,0.408480f,0.411498f,0.414519f,0.417543f,
0.420571f,0.423601f,0.426635f,0.429671f,0.432710f,0.435751f,0.438795f,0.441841f,0.444889f,0.447939f,
0.450991f,0.454046f,0.457101f,0.460159f,0.463218f,0.466278f,0.469340f,0.472402f,0.475466f,0.478531f,
0.481596f,0.484663f,0.487729f,0.490797f,0.493864f,0.496932f,0.500000f,0.503068f,0.506136f,0.509203f,
0.512271f,0.515337f,0.518404f,0.521469f,0.524534f,0.527598f,0.530660f,0.533722f,0.536782f,0.539841f,
0.542899f,0.545954f,0.549009f,0.552061f,0.555111f,0.558159f,0.561205f,0.564249f,0.567290f,0.570329f,
0.573365f,0.576399f,0.579429f,0.582457f,0.585481f,0.588502f,0.591520f,0.594534f,0.597545f,0.600552f,
0.603556f,0.606555f,0.609551f,0.612542f,0.615529f,0.618512f,0.621490f,0.624464f,0.627433f,0.630397f,
0.633356f,0.636311f,0.639260f,0.642204f,0.645142f,0.648075f,0.651003f,0.653925f,0.656841f,0.659751f,
0.662655f,0.665553f,0.668445f,0.671330f,0.674209f,0.677082f,0.679947f,0.682806f,0.685659f,0.688504f,
0.691342f,0.694173f,0.696996f,0.699812f,0.702621f,0.705422f,0.708215f,0.711000f,0.713778f,0.716547f,
0.719308f,0.722061f,0.724806f,0.727542f,0.730269f,0.732988f,0.735698f,0.738400f,0.741092f,0.743775f,
0.746449f,0.749114f,0.751769f,0.754415f,0.757051f,0.759678f,0.762295f,0.764902f,0.767499f,0.770086f,
0.772663f,0.775229f,0.777785f,0.780331f,0.782866f,0.785390f,0.787904f,0.790407f,0.792899f,0.795380f,
0.797850f,0.800308f,0.802756f,0.805191f,0.807616f,0.810029f,0.812430f,0.814819f,0.817197f,0.819562f,
0.821916f,0.824257f,0.826586f,0.828903f,0.831208f,0.833500f,0.835779f,0.838046f,0.840301f,0.842542f,
0.844770f,0.846986f,0.849188f,0.851377f,0.853553f,0.855716f,0.857865f,0.860001f,0.862124f,0.864232f,
0.866327f,0.868408f,0.870476f,0.872529f,0.874568f,0.876593f,0.878604f,0.880601f,0.882584f,0.884552f,
0.886505f,0.888444f,0.890369f,0.892278f,0.894173f,0.896053f,0.897918f,0.899769f,0.901604f,0.903424f,
0.905229f,0.907018f,0.908792f,0.910551f,0.912295f,0.914023f,0.915735f,0.917431f,0.919112f,0.920777f,
0.922427f,0.924060f,0.925678f,0.927279f,0.928864f,0.930433f,0.931986f,0.933523f,0.935044f,0.936548f,
0.938035f,0.939506f,0.940961f,0.942399f,0.943820f,0.945224f,0.946612f,0.947983f,0.949337f,0.950674f,
0.951995f,0.953298f,0.954584f,0.955853f,0.957105f,0.958340f,0.959557f,0.960757f,0.961940f,0.963105f,
0.964253f,0.965383f,0.966496f,0.967592f,0.968670f,0.969730f,0.970772f,0.971797f,0.972804f,0.973793f,
0.974764f,0.975717f,0.976653f,0.977571f,0.978470f,0.979352f,0.980215f,0.981061f,0.981888f,0.982697f,
0.983488f,0.984261f,0.985016f,0.985752f,0.986470f,0.987170f,0.987851f,0.988514f,0.989159f,0.989785f,
0.990393f,0.990982f,0.991553f,0.992105f,0.992639f,0.993154f,0.993651f,0.994129f,0.994588f,0.995029f,
0.995451f,0.995855f,0.996240f,0.996606f,0.996953f,0.997282f,0.997592f,0.997884f,0.998156f,0.998410f,
0.998645f,0.998862f,0.999059f,0.999238f,0.999398f,0.999539f,0.999661f,0.999765f,0.999849f,0.999915f,
0.999962f,0.999991f,1.000000f,0.999991f,0.999962f,0.999915f,0.999849f,0.999765f,0.999661f,0.999539f,
0.999398f,0.999238f,0.999059f,0.998862f,0.998645f,0.998410f,0.998156f,0.997884f,0.997592f,0.997282f,
0.996953f,0.996606f,0.996240f,0.995855f,0.995451f,0.995029f,0.994588f,0.994129f,0.993651f,0.993154f,
0.992639f,0.992105f,0.991553f,0.990982f,0.990393f,0.989785f,0.989159f,0.988514f,0.987851f,0.987170f,
0.986470f,0.985752f,0.985016f,0.984261f,0.983488f,0.982697f,0.981888f,0.981061f,0.980215f,0.979352f,
0.978470f,0.977571f,0.976653f,0.975717f,0.974764f,0.973793f,0.972804f,0.971797f,0.970772f,0.969730f,
0.968670f,0.967592f,0.966496f,0.965383f,0.964253f,0.963105f,0.961940f,0.960757f,0.959557f,0.958340f,
0.957105f,0.955853f,0.954584f,0.953298f,0.951995f,0.950674f,0.949337f,0.947983f,0.946612f,0.945224f,
0.943820f,0.942399f,0.940961f,0.939506f,0.938035f,0.936548f,0.935044f,0.933523f,0.931986f,0.930433f,
0.928864f,0.927279f,0.925678f,0.924060f,0.922427f,0.920777f,0.919112f,0.917431f,0.915735f,0.914023f,
0.912295f,0.910551f,0.908792f,0.907018f,0.905229f,0.903424f,0.901604f,0.899769f,0.897918f,0.896053f,
0.894173f,0.892278f,0.890369f,0.888444f,0.886505f,0.884552f,0.882584f,0.880601f,0.878604f,0.876593f,
0.874568f,0.872529f,0.870476f,0.868408f,0.866327f,0.864232f,0.862124f,0.860001f,0.857865f,0.855716f,
0.853553f,0.851377f,0.849188f,0.846986f,0.844770f,0.842542f,0.840301f,0.838046f,0.835779f,0.833500f,
0.831208f,0.828903f,0.826586f,0.824257f,0.821916f,0.819562f,0.817197f,0.814819f,0.812430f,0.810029f,
0.807616f,0.805191f,0.802756f,0.800308f,0.797850f,0.795380f,0.792899f,0.790407f,0.787904f,0.785390f,
0.782866f,0.780331f,0.777785f,0.775229f,0.772663f,0.770086f,0.767499f,0.764902f,0.762295f,0.759678f,
0.757051f,0.754415f,0.751769f,0.749114f,0.746449f,0.743775f,0.741092f,0.738400f,0.735698f,0.732988f,
0.730269f,0.727542f,0.724806f,0.722061f,0.719308f,0.716547f,0.713778f,0.711000f,0.708215f,0.705422f,
0.702621f,0.699812f,0.696996f,0.694173f,0.691342f,0.688504f,0.685659f,0.682806f,0.679947f,0.677082f,
0.674209f,0.671330f,0.668445f,0.665553f,0.662655f,0.659751f,0.656841f,0.653925f,0.651003f,0.648075f,
0.645142f,0.642204f,0.639260f,0.636311f,0.633356f,0.630397f,0.627433f,0.624464f,0.621490f,0.618512f,
0.615529f,0.612542f,0.609551f,0.606555f,0.603556f,0.600552f,0.597545f,0.594534f,0.591520f,0.588502f,
0.585481f,0.582457f,0.579429f,0.576399f,0.573365f,0.570329f,0.567290f,0.564249f,0.561205f,0.558159f,
0.555111f,0.552061f,0.549009f,0.545954f,0.542899f,0.539841f,0.536782f,0.533722f,0.530660f,0.527598f,
0.524534f,0.521469f,0.518404f,0.515337f,0.512271f,0.509203f,0.506136f,0.503068f,0.500000f,0.496932f,
0.493864f,0.490797f,0.487729f,0.484663f,0.481596f,0.478531f,0.475466f,0.472402f,0.469340f,0.466278f,
0.463218f,0.460159f,0.457101f,0.454046f,0.450991f,0.447939f,0.444889f,0.441841f,0.438795f,0.435751f,
0.432710f,0.429671f,0.426635f,0.423601f,0.420571f,0.417543f,0.414519f,0.411498f,0.408480f,0.405466f,
0.402455f,0.399448f,0.396444f,0.393445f,0.390449f,0.387458f,0.384471f,0.381488f,0.378510f,0.375536f,
0.372567f,0.369603f,0.366644f,0.363689f,0.360740f,0.357796f,0.354858f,0.351925f,0.348997f,0.346075f,
0.343159f,0.340249f,0.337345f,0.334447f,0.331555f,0.328670f,0.325791f,0.322918f,0.320052f,0.317194f,
0.314341f,0.311496f,0.308658f,0.305827f,0.303004f,0.300188f,0.297379f,0.294578f,0.291785f,0.289000f,
0.286222f,0.283453f,0.280692f,0.277939f,0.275194f,0.272458f,0.269731f,0.267012f,0.264302f,0.261600f,
0.258908f,0.256225f,0.253551f,0.250886f,0.248231f,0.245585f,0.242949f,0.240322f,0.237705f,0.235098f,
0.232501f,0.229914f,0.227338f,0.224771f,0.222215f,0.219669f,0.217134f,0.214610f,0.212096f,0.209593f,
0.207101f,0.204620f,0.202150f,0.199692f,0.197244f,0.194809f,0.192384f,0.189971f,0.187570f,0.185181f,
0.182803f,0.180438f,0.178084f,0.175743f,0.173414f,0.171097f,0.168792f,0.166500f,0.164221f,0.161954f,
0.159699f,0.157458f,0.155230f,0.153014f,0.150812f,0.148623f,0.146447f,0.144284f,0.142135f,0.139999f,
0.137876f,0.135768f,0.133673f,0.131592f,0.129524f,0.127471f,0.125432f,0.123407f,0.121396f,0.119399f,
0.117416f,0.115448f,0.113495f,0.111556f,0.109631f,0.107722f,0.105827f,0.103947f,0.102082f,0.100231f,
0.098396f,0.096576f,0.094771f,0.092982f,0.091208f,0.089449f,0.087705f,0.085977f,0.084265f,0.082569f,
0.080888f,0.079223f,0.077573f,0.075940f,0.074322f,0.072721f,0.071136f,0.069567f,0.068014f,0.066477f,
0.064957f,0.063453f,0.061965f,0.060494f,0.059039f,0.057601f,0.056180f,0.054776f,0.053388f,0.052017f,
0.050663f,0.049326f,0.048005f,0.046702f,0.045416f,0.044147f,0.042895f,0.041660f,0.040443f,0.039243f,
0.038060f,0.036895f,0.035747f,0.034617f,0.033504f,0.032408f,0.031330f,0.030270f,0.029228f,0.028203f,
0.027196f,0.026207f,0.025236f,0.024282f,0.023347f,0.022429f,0.021530f,0.020648f,0.019785f,0.018939f,
0.018112f,0.017303f,0.016512f,0.015739f,0.014984f,0.014248f,0.013530f,0.012830f,0.012149f,0.011486f,
0.010841f,0.010215f,0.009607f,0.009018f,0.008447f,0.007895f,0.007361f,0.006846f,0.006349f,0.005871f,
0.005412f,0.004971f,0.004549f,0.004145f,0.003760f,0.003394f,0.003047f,0.002718f,0.002408f,0.002116f,
0.001844f,0.001590f,0.001355f,0.001138f,0.000941f,0.000762f,0.000602f,0.000461f,0.000339f,0.000235f,
0.000151f,0.000085f,0.000038f,0.000009f,};




/* Mel Filter coefficients */
const uint32_t mfcc_filter_pos_config1_f32[NB_MFCC_NB_FILTER_CONFIG1_F32]={
5,8,11,14,18,21,26,30,34,39,
44,50,55,61,68,75,82,90,98,107,
116,126,136,147,159,171,184,198,213,229,
246,263,282,302,323,346,370,395,422,450,
};
const uint32_t mfcc_filter_len_config1_f32[NB_MFCC_NB_FILTER_CONFIG1_F32]={
6,6,7,7,8,9,8,9,10,11,
11,11,13,14,14,15,16,17,18,19,
20,21,23,24,25,27,29,31,33,34,
36,39,41,44,47,49,52,55,58,62,
};




const float32_t mfcc_filter_coefs_config1_f32[NB_MFCC_FILTER_COEFS_CONFIG1_F32]={
0.308774f,0.643874f,0.972443f,0.705272f,0.389034f,0.078619f,0.294728f,0.610966f,0.921381f,0.773819f,
0.474432f,0.180271f,0.226181f,0.525568f,0.819729f,0.891156f,0.606916f,0.327390f,0.052425f,0.108844f,
0.393084f,0.672610f,0.947575f,0.781873f,0.515595f,0.253459f,0.218127f,0.484405f,0.746541f,0.995338f,
0.741109f,0.490659f,0.243875f,0.000653f,0.004662f,0.258891f,0.509341f,0.756125f,0.999347f,0.760890f,
0.524491f,0.291361f,0.061412f,0.239110f,0.475509f,0.708639f,0.938588f,0.834558f,0.610716f,0.389808f,
0.171759f,0.165442f,0.389284f,0.610192f,0.828241f,0.956494f,0.743943f,0.534040f,0.326719f,0.121917f,
0.043506f,0.256057f,0.465960f,0.673281f,0.878083f,0.919573f,0.719630f,0.522031f,0.326721f,0.133649f,
0.080427f,0.280370f,0.477969f,0.673279f,0.866351f,0.942764f,0.754016f,0.567358f,0.382745f,0.200132f,
0.019476f,0.057236f,0.245984f,0.432642f,0.617255f,0.799868f,0.980524f,0.840736f,0.663872f,0.488844f,
0.315615f,0.144149f,0.159264f,0.336128f,0.511156f,0.684385f,0.855851f,0.974409f,0.806362f,0.639973f,
0.475211f,0.312044f,0.150442f,0.025591f,0.193638f,0.360027f,0.524789f,0.687956f,0.849558f,0.990374f,
0.831812f,0.674728f,0.519094f,0.364884f,0.212073f,0.060634f,0.009626f,0.168188f,0.325272f,0.480906f,
0.635116f,0.787927f,0.939366f,0.910544f,0.761778f,0.614314f,0.468129f,0.323202f,0.179509f,0.037031f,
0.089456f,0.238222f,0.385686f,0.531871f,0.676798f,0.820491f,0.962969f,0.895748f,0.755639f,0.616685f,
0.478867f,0.342167f,0.206567f,0.072049f,0.104252f,0.244361f,0.383315f,0.521133f,0.657833f,0.793433f,
0.927951f,0.938596f,0.806192f,0.674819f,0.544463f,0.415107f,0.286736f,0.159335f,0.032890f,0.061404f,
0.193808f,0.325181f,0.455537f,0.584893f,0.713264f,0.840665f,0.967110f,0.907387f,0.782811f,0.659150f,
0.536389f,0.414515f,0.293517f,0.173381f,0.054095f,0.092613f,0.217189f,0.340850f,0.463611f,0.585485f,
0.706483f,0.826619f,0.945905f,0.935647f,0.818026f,0.701221f,0.585219f,0.470010f,0.355583f,0.241927f,
0.129033f,0.016891f,0.064353f,0.181974f,0.298779f,0.414781f,0.529990f,0.644417f,0.758073f,0.870967f,
0.983109f,0.905489f,0.794819f,0.684870f,0.575635f,0.467102f,0.359264f,0.252112f,0.145636f,0.039829f,
0.094511f,0.205181f,0.315130f,0.424365f,0.532898f,0.640736f,0.747888f,0.854364f,0.960171f,0.934682f,
0.830187f,0.726336f,0.623120f,0.520533f,0.418567f,0.317213f,0.216466f,0.116317f,0.016760f,0.065318f,
0.169813f,0.273664f,0.376880f,0.479467f,0.581433f,0.682787f,0.783534f,0.883683f,0.983240f,0.917787f,
0.819392f,0.721568f,0.624308f,0.527607f,0.431457f,0.335853f,0.240788f,0.146256f,0.052251f,0.082213f,
0.180608f,0.278432f,0.375692f,0.472393f,0.568543f,0.664147f,0.759212f,0.853744f,0.947749f,0.958767f,
0.865800f,0.773342f,0.681388f,0.589934f,0.498973f,0.408500f,0.318511f,0.228999f,0.139960f,0.051389f,
0.041233f,0.134200f,0.226658f,0.318612f,0.410066f,0.501027f,0.591500f,0.681489f,0.771001f,0.860040f,
0.948611f,0.963281f,0.875632f,0.788435f,0.701688f,0.615384f,0.529521f,0.444092f,0.359094f,0.274523f,
0.190374f,0.106643f,0.023326f,0.036719f,0.124368f,0.211565f,0.298312f,0.384616f,0.470479f,0.555908f,
0.640906f,0.725477f,0.809626f,0.893357f,0.976674f,0.940419f,0.857917f,0.775818f,0.694116f,0.612808f,
0.531891f,0.451361f,0.371213f,0.291445f,0.212052f,0.133032f,0.054380f,0.059581f,0.142083f,0.224182f,
0.305884f,0.387192f,0.468109f,0.548639f,0.628787f,0.708555f,0.787948f,0.866968f,0.945620f,0.976094f,
0.898169f,0.820604f,0.743393f,0.666535f,0.590025f,0.513862f,0.438040f,0.362559f,0.287414f,0.212602f,
0.138121f,0.063968f,0.023906f,0.101831f,0.179396f,0.256607f,0.333465f,0.409975f,0.486138f,0.561960f,
0.637441f,0.712586f,0.787398f,0.861879f,0.936032f,0.990139f,0.916633f,0.843446f,0.770575f,0.698017f,
0.625771f,0.553833f,0.482201f,0.410872f,0.339844f,0.269114f,0.198679f,0.128537f,0.058686f,0.009861f,
0.083367f,0.156554f,0.229425f,0.301982f,0.374229f,0.446167f,0.517799f,0.589128f,0.660156f,0.730886f,
0.801321f,0.871463f,0.941314f,0.989124f,0.919847f,0.850854f,0.782142f,0.713709f,0.645552f,0.577671f,
0.510061f,0.442722f,0.375650f,0.308845f,0.242303f,0.176023f,0.110003f,0.044240f,0.010876f,0.080153f,
0.149146f,0.217858f,0.286291f,0.354448f,0.422329f,0.489939f,0.557278f,0.624349f,0.691155f,0.757697f,
0.823977f,0.889997f,0.955760f,0.978732f,0.913479f,0.848477f,0.783724f,0.719220f,0.654961f,0.590946f,
0.527174f,0.463642f,0.400349f,0.337292f,0.274470f,0.211882f,0.149525f,0.087398f,0.025500f,0.021268f,
0.086521f,0.151524f,0.216276f,0.280780f,0.345039f,0.409054f,0.472826f,0.536358f,0.599651f,0.662708f,
0.725529f,0.788118f,0.850475f,0.912602f,0.974500f,0.963827f,0.902380f,0.841156f,0.780153f,0.719370f,
0.658806f,0.598459f,0.538327f,0.478408f,0.418702f,0.359207f,0.299921f,0.240843f,0.181971f,0.123304f,
0.064840f,0.006579f,0.036173f,0.097620f,0.158844f,0.219847f,0.280630f,0.341194f,0.401541f,0.461673f,
0.521592f,0.581298f,0.640793f,0.700079f,0.759157f,0.818029f,0.876696f,0.935160f,0.993421f,0.948518f,
0.890656f,0.832993f,0.775526f,0.718255f,0.661177f,0.604292f,0.547598f,0.491095f,0.434780f,0.378652f,
0.322711f,0.266955f,0.211383f,0.155994f,0.100786f,0.045758f,0.051482f,0.109344f,0.167007f,0.224474f,
0.281745f,0.338823f,0.395708f,0.452402f,0.508905f,0.565220f,0.621348f,0.677289f,0.733045f,0.788617f,
0.844006f,0.899214f,0.954242f,0.990909f,0.936238f,0.881744f,0.827426f,0.773282f,0.719311f,0.665513f,
0.611885f,0.558428f,0.505140f,0.452020f,0.399067f,0.346279f,0.293657f,0.241198f,0.188902f,0.136767f,
0.084794f,0.032980f,0.009091f,0.063762f,0.118256f,0.172574f,0.226718f,0.280689f,0.334487f,0.388115f,
0.441572f,0.494860f,0.547980f,0.600933f,0.653721f,0.706343f,0.758802f,0.811098f,0.863233f,0.915206f,
0.967020f,0.981325f,0.929828f,0.878488f,0.827303f,0.776274f,0.725398f,0.674676f,0.624106f,0.573687f,
0.523418f,0.473299f,0.423329f,0.373506f,0.323830f,0.274300f,0.224916f,0.175675f,0.126578f,0.077624f,
0.028811f,0.018675f,0.070172f,0.121512f,0.172697f,0.223726f,0.274602f,0.325324f,0.375894f,0.426313f,
0.476582f,0.526701f,0.576671f,0.626494f,0.676170f,0.725700f,0.775084f,0.824325f,0.873422f,0.922376f,
0.971189f,0.980139f,0.931608f,0.883215f,0.834962f,0.786846f,0.738867f,0.691024f,0.643316f,0.595744f,
0.548305f,0.500999f,0.453826f,0.406784f,0.359873f,0.313093f,0.266442f,0.219919f,0.173525f,0.127258f,
0.081118f,0.035104f,0.019861f,0.068392f,0.116785f,0.165038f,0.213154f,0.261133f,0.308976f,0.356684f,
0.404256f,0.451695f,0.499001f,0.546174f,0.593216f,0.640127f,0.686907f,0.733558f,0.780081f,0.826475f,
0.872742f,0.918882f,0.964896f,0.989215f,0.943451f,0.897810f,0.852293f,0.806898f,0.761625f,0.716474f,
0.671443f,0.626532f,0.581741f,0.537068f,0.492514f,0.448076f,0.403756f,0.359552f,0.315464f,0.271490f,
0.227631f,0.183886f,0.140254f,0.096735f,0.053327f,0.010032f,0.010785f,0.056550f,0.102190f,0.147707f,
0.193102f,0.238375f,0.283526f,0.328557f,0.373468f,0.418259f,0.462932f,0.507486f,0.551924f,0.596244f,
0.640448f,0.684536f,0.728510f,0.772369f,0.816114f,0.859746f,0.903265f,0.946673f,0.989968f,0.966847f,
0.923772f,0.880808f,0.837952f,0.795206f,0.752567f,0.710036f,0.667612f,0.625295f,0.583083f,0.540977f,
0.498976f,0.457080f,0.415287f,0.373598f,0.332011f,0.290527f,0.249145f,0.207864f,0.166683f,0.125604f,
0.084624f,0.043743f,0.002962f,0.033153f,0.076228f,0.119192f,0.162048f,0.204794f,0.247433f,0.289964f,
0.332388f,0.374705f,0.416917f,0.459023f,0.501024f,0.542920f,0.584713f,0.626402f,0.667989f,0.709473f,
0.750855f,0.792136f,0.833317f,0.874396f,0.915376f,0.956257f,0.997038f,0.962279f,0.921693f,0.881206f,
0.840815f,0.800521f,0.760323f,0.720221f,0.680213f,0.640301f,0.600483f,0.560759f,0.521128f,0.481590f,
0.442144f,0.402791f,0.363529f,0.324359f,0.285279f,0.246290f,0.207391f,0.168581f,0.129861f,0.091229f,
0.052686f,0.014230f,0.037721f,0.078307f,0.118794f,0.159185f,0.199479f,0.239677f,0.279779f,0.319787f,
0.359699f,0.399517f,0.439241f,0.478872f,0.518410f,0.557856f,0.597209f,0.636471f,0.675641f,0.714721f,
0.753710f,0.792609f,0.831419f,0.870139f,0.908771f,0.947314f,0.985770f,0.975862f,0.937582f,0.899388f,
0.861280f,0.823258f,0.785322f,0.747471f,0.709705f,0.672023f,0.634426f,0.596912f,0.559481f,0.522133f,
0.484868f,0.447685f,0.410584f,0.373565f,0.336626f,0.299769f,0.262991f,0.226294f,0.189677f,0.153139f,
0.116680f,0.080299f,0.043997f,0.007773f,0.024138f,0.062418f,0.100612f,0.138720f,0.176742f,0.214678f,
0.252529f,0.290295f,0.327977f,0.365574f,0.403088f,0.440519f,0.477867f,0.515132f,0.552315f,0.589416f,
0.626435f,0.663374f,0.700231f,0.737009f,0.773706f,0.810323f,0.846861f,0.883321f,0.919701f,0.956003f,
0.992227f,0.971627f,0.935558f,0.899566f,0.863651f,0.827812f,0.792049f,0.756362f,0.720750f,0.685214f,
0.649752f,0.614364f,0.579051f,0.543812f,0.508646f,0.473553f,0.438533f,0.403586f,0.368711f,0.333908f,
0.299177f,0.264518f,0.229929f,0.195411f,0.160964f,0.126587f,0.092280f,0.058043f,0.023875f,0.028373f,
0.064442f,0.100434f,0.136349f,0.172188f,0.207951f,0.243638f,0.279250f,0.314786f,0.350248f,0.385636f,
0.420949f,0.456188f,0.491354f,0.526447f,0.561467f,0.596414f,0.631289f,0.666092f,0.700823f,0.735483f,
0.770071f,0.804589f,0.839036f,0.873413f,0.907720f,0.941957f,0.976125f,0.989776f,0.955746f,0.921785f,
0.887892f,0.854067f,0.820309f,0.786620f,0.752997f,0.719441f,0.685952f,0.652530f,0.619173f,0.585883f,
0.552658f,0.519498f,0.486404f,0.453374f,0.420409f,0.387508f,0.354672f,0.321899f,0.289190f,0.256544f,
0.223961f,0.191441f,0.158984f,0.126589f,0.094257f,0.061986f,0.029777f,0.010224f,0.044254f,0.078215f,
0.112108f,0.145933f,0.179691f,0.213380f,0.247003f,0.280559f,0.314048f,0.347470f,0.380827f,0.414117f,
0.447342f,0.480502f,0.513596f,0.546626f,0.579591f,0.612492f,0.645328f,0.678101f,0.710810f,0.743456f,
0.776039f,0.808559f,0.841016f,0.873411f,0.905743f,0.938014f,0.970223f,0.997629f,0.965543f,0.933517f,
0.901553f,0.869648f,0.837804f,0.806020f,0.774296f,0.742632f,0.711027f,0.679481f,0.647994f,0.616565f,
0.585195f,0.553884f,0.522630f,0.491435f,0.460297f,0.429216f,0.398193f,0.367226f,0.336317f,0.305463f,
0.274667f,0.243926f,0.213242f,0.182613f,0.152040f,0.121522f,0.091059f,0.060651f,0.030298f,};



