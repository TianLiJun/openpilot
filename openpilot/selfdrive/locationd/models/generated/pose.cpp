#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3576604326285445174) {
   out_3576604326285445174[0] = delta_x[0] + nom_x[0];
   out_3576604326285445174[1] = delta_x[1] + nom_x[1];
   out_3576604326285445174[2] = delta_x[2] + nom_x[2];
   out_3576604326285445174[3] = delta_x[3] + nom_x[3];
   out_3576604326285445174[4] = delta_x[4] + nom_x[4];
   out_3576604326285445174[5] = delta_x[5] + nom_x[5];
   out_3576604326285445174[6] = delta_x[6] + nom_x[6];
   out_3576604326285445174[7] = delta_x[7] + nom_x[7];
   out_3576604326285445174[8] = delta_x[8] + nom_x[8];
   out_3576604326285445174[9] = delta_x[9] + nom_x[9];
   out_3576604326285445174[10] = delta_x[10] + nom_x[10];
   out_3576604326285445174[11] = delta_x[11] + nom_x[11];
   out_3576604326285445174[12] = delta_x[12] + nom_x[12];
   out_3576604326285445174[13] = delta_x[13] + nom_x[13];
   out_3576604326285445174[14] = delta_x[14] + nom_x[14];
   out_3576604326285445174[15] = delta_x[15] + nom_x[15];
   out_3576604326285445174[16] = delta_x[16] + nom_x[16];
   out_3576604326285445174[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_496602688636603974) {
   out_496602688636603974[0] = -nom_x[0] + true_x[0];
   out_496602688636603974[1] = -nom_x[1] + true_x[1];
   out_496602688636603974[2] = -nom_x[2] + true_x[2];
   out_496602688636603974[3] = -nom_x[3] + true_x[3];
   out_496602688636603974[4] = -nom_x[4] + true_x[4];
   out_496602688636603974[5] = -nom_x[5] + true_x[5];
   out_496602688636603974[6] = -nom_x[6] + true_x[6];
   out_496602688636603974[7] = -nom_x[7] + true_x[7];
   out_496602688636603974[8] = -nom_x[8] + true_x[8];
   out_496602688636603974[9] = -nom_x[9] + true_x[9];
   out_496602688636603974[10] = -nom_x[10] + true_x[10];
   out_496602688636603974[11] = -nom_x[11] + true_x[11];
   out_496602688636603974[12] = -nom_x[12] + true_x[12];
   out_496602688636603974[13] = -nom_x[13] + true_x[13];
   out_496602688636603974[14] = -nom_x[14] + true_x[14];
   out_496602688636603974[15] = -nom_x[15] + true_x[15];
   out_496602688636603974[16] = -nom_x[16] + true_x[16];
   out_496602688636603974[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2198066657604437951) {
   out_2198066657604437951[0] = 1.0;
   out_2198066657604437951[1] = 0.0;
   out_2198066657604437951[2] = 0.0;
   out_2198066657604437951[3] = 0.0;
   out_2198066657604437951[4] = 0.0;
   out_2198066657604437951[5] = 0.0;
   out_2198066657604437951[6] = 0.0;
   out_2198066657604437951[7] = 0.0;
   out_2198066657604437951[8] = 0.0;
   out_2198066657604437951[9] = 0.0;
   out_2198066657604437951[10] = 0.0;
   out_2198066657604437951[11] = 0.0;
   out_2198066657604437951[12] = 0.0;
   out_2198066657604437951[13] = 0.0;
   out_2198066657604437951[14] = 0.0;
   out_2198066657604437951[15] = 0.0;
   out_2198066657604437951[16] = 0.0;
   out_2198066657604437951[17] = 0.0;
   out_2198066657604437951[18] = 0.0;
   out_2198066657604437951[19] = 1.0;
   out_2198066657604437951[20] = 0.0;
   out_2198066657604437951[21] = 0.0;
   out_2198066657604437951[22] = 0.0;
   out_2198066657604437951[23] = 0.0;
   out_2198066657604437951[24] = 0.0;
   out_2198066657604437951[25] = 0.0;
   out_2198066657604437951[26] = 0.0;
   out_2198066657604437951[27] = 0.0;
   out_2198066657604437951[28] = 0.0;
   out_2198066657604437951[29] = 0.0;
   out_2198066657604437951[30] = 0.0;
   out_2198066657604437951[31] = 0.0;
   out_2198066657604437951[32] = 0.0;
   out_2198066657604437951[33] = 0.0;
   out_2198066657604437951[34] = 0.0;
   out_2198066657604437951[35] = 0.0;
   out_2198066657604437951[36] = 0.0;
   out_2198066657604437951[37] = 0.0;
   out_2198066657604437951[38] = 1.0;
   out_2198066657604437951[39] = 0.0;
   out_2198066657604437951[40] = 0.0;
   out_2198066657604437951[41] = 0.0;
   out_2198066657604437951[42] = 0.0;
   out_2198066657604437951[43] = 0.0;
   out_2198066657604437951[44] = 0.0;
   out_2198066657604437951[45] = 0.0;
   out_2198066657604437951[46] = 0.0;
   out_2198066657604437951[47] = 0.0;
   out_2198066657604437951[48] = 0.0;
   out_2198066657604437951[49] = 0.0;
   out_2198066657604437951[50] = 0.0;
   out_2198066657604437951[51] = 0.0;
   out_2198066657604437951[52] = 0.0;
   out_2198066657604437951[53] = 0.0;
   out_2198066657604437951[54] = 0.0;
   out_2198066657604437951[55] = 0.0;
   out_2198066657604437951[56] = 0.0;
   out_2198066657604437951[57] = 1.0;
   out_2198066657604437951[58] = 0.0;
   out_2198066657604437951[59] = 0.0;
   out_2198066657604437951[60] = 0.0;
   out_2198066657604437951[61] = 0.0;
   out_2198066657604437951[62] = 0.0;
   out_2198066657604437951[63] = 0.0;
   out_2198066657604437951[64] = 0.0;
   out_2198066657604437951[65] = 0.0;
   out_2198066657604437951[66] = 0.0;
   out_2198066657604437951[67] = 0.0;
   out_2198066657604437951[68] = 0.0;
   out_2198066657604437951[69] = 0.0;
   out_2198066657604437951[70] = 0.0;
   out_2198066657604437951[71] = 0.0;
   out_2198066657604437951[72] = 0.0;
   out_2198066657604437951[73] = 0.0;
   out_2198066657604437951[74] = 0.0;
   out_2198066657604437951[75] = 0.0;
   out_2198066657604437951[76] = 1.0;
   out_2198066657604437951[77] = 0.0;
   out_2198066657604437951[78] = 0.0;
   out_2198066657604437951[79] = 0.0;
   out_2198066657604437951[80] = 0.0;
   out_2198066657604437951[81] = 0.0;
   out_2198066657604437951[82] = 0.0;
   out_2198066657604437951[83] = 0.0;
   out_2198066657604437951[84] = 0.0;
   out_2198066657604437951[85] = 0.0;
   out_2198066657604437951[86] = 0.0;
   out_2198066657604437951[87] = 0.0;
   out_2198066657604437951[88] = 0.0;
   out_2198066657604437951[89] = 0.0;
   out_2198066657604437951[90] = 0.0;
   out_2198066657604437951[91] = 0.0;
   out_2198066657604437951[92] = 0.0;
   out_2198066657604437951[93] = 0.0;
   out_2198066657604437951[94] = 0.0;
   out_2198066657604437951[95] = 1.0;
   out_2198066657604437951[96] = 0.0;
   out_2198066657604437951[97] = 0.0;
   out_2198066657604437951[98] = 0.0;
   out_2198066657604437951[99] = 0.0;
   out_2198066657604437951[100] = 0.0;
   out_2198066657604437951[101] = 0.0;
   out_2198066657604437951[102] = 0.0;
   out_2198066657604437951[103] = 0.0;
   out_2198066657604437951[104] = 0.0;
   out_2198066657604437951[105] = 0.0;
   out_2198066657604437951[106] = 0.0;
   out_2198066657604437951[107] = 0.0;
   out_2198066657604437951[108] = 0.0;
   out_2198066657604437951[109] = 0.0;
   out_2198066657604437951[110] = 0.0;
   out_2198066657604437951[111] = 0.0;
   out_2198066657604437951[112] = 0.0;
   out_2198066657604437951[113] = 0.0;
   out_2198066657604437951[114] = 1.0;
   out_2198066657604437951[115] = 0.0;
   out_2198066657604437951[116] = 0.0;
   out_2198066657604437951[117] = 0.0;
   out_2198066657604437951[118] = 0.0;
   out_2198066657604437951[119] = 0.0;
   out_2198066657604437951[120] = 0.0;
   out_2198066657604437951[121] = 0.0;
   out_2198066657604437951[122] = 0.0;
   out_2198066657604437951[123] = 0.0;
   out_2198066657604437951[124] = 0.0;
   out_2198066657604437951[125] = 0.0;
   out_2198066657604437951[126] = 0.0;
   out_2198066657604437951[127] = 0.0;
   out_2198066657604437951[128] = 0.0;
   out_2198066657604437951[129] = 0.0;
   out_2198066657604437951[130] = 0.0;
   out_2198066657604437951[131] = 0.0;
   out_2198066657604437951[132] = 0.0;
   out_2198066657604437951[133] = 1.0;
   out_2198066657604437951[134] = 0.0;
   out_2198066657604437951[135] = 0.0;
   out_2198066657604437951[136] = 0.0;
   out_2198066657604437951[137] = 0.0;
   out_2198066657604437951[138] = 0.0;
   out_2198066657604437951[139] = 0.0;
   out_2198066657604437951[140] = 0.0;
   out_2198066657604437951[141] = 0.0;
   out_2198066657604437951[142] = 0.0;
   out_2198066657604437951[143] = 0.0;
   out_2198066657604437951[144] = 0.0;
   out_2198066657604437951[145] = 0.0;
   out_2198066657604437951[146] = 0.0;
   out_2198066657604437951[147] = 0.0;
   out_2198066657604437951[148] = 0.0;
   out_2198066657604437951[149] = 0.0;
   out_2198066657604437951[150] = 0.0;
   out_2198066657604437951[151] = 0.0;
   out_2198066657604437951[152] = 1.0;
   out_2198066657604437951[153] = 0.0;
   out_2198066657604437951[154] = 0.0;
   out_2198066657604437951[155] = 0.0;
   out_2198066657604437951[156] = 0.0;
   out_2198066657604437951[157] = 0.0;
   out_2198066657604437951[158] = 0.0;
   out_2198066657604437951[159] = 0.0;
   out_2198066657604437951[160] = 0.0;
   out_2198066657604437951[161] = 0.0;
   out_2198066657604437951[162] = 0.0;
   out_2198066657604437951[163] = 0.0;
   out_2198066657604437951[164] = 0.0;
   out_2198066657604437951[165] = 0.0;
   out_2198066657604437951[166] = 0.0;
   out_2198066657604437951[167] = 0.0;
   out_2198066657604437951[168] = 0.0;
   out_2198066657604437951[169] = 0.0;
   out_2198066657604437951[170] = 0.0;
   out_2198066657604437951[171] = 1.0;
   out_2198066657604437951[172] = 0.0;
   out_2198066657604437951[173] = 0.0;
   out_2198066657604437951[174] = 0.0;
   out_2198066657604437951[175] = 0.0;
   out_2198066657604437951[176] = 0.0;
   out_2198066657604437951[177] = 0.0;
   out_2198066657604437951[178] = 0.0;
   out_2198066657604437951[179] = 0.0;
   out_2198066657604437951[180] = 0.0;
   out_2198066657604437951[181] = 0.0;
   out_2198066657604437951[182] = 0.0;
   out_2198066657604437951[183] = 0.0;
   out_2198066657604437951[184] = 0.0;
   out_2198066657604437951[185] = 0.0;
   out_2198066657604437951[186] = 0.0;
   out_2198066657604437951[187] = 0.0;
   out_2198066657604437951[188] = 0.0;
   out_2198066657604437951[189] = 0.0;
   out_2198066657604437951[190] = 1.0;
   out_2198066657604437951[191] = 0.0;
   out_2198066657604437951[192] = 0.0;
   out_2198066657604437951[193] = 0.0;
   out_2198066657604437951[194] = 0.0;
   out_2198066657604437951[195] = 0.0;
   out_2198066657604437951[196] = 0.0;
   out_2198066657604437951[197] = 0.0;
   out_2198066657604437951[198] = 0.0;
   out_2198066657604437951[199] = 0.0;
   out_2198066657604437951[200] = 0.0;
   out_2198066657604437951[201] = 0.0;
   out_2198066657604437951[202] = 0.0;
   out_2198066657604437951[203] = 0.0;
   out_2198066657604437951[204] = 0.0;
   out_2198066657604437951[205] = 0.0;
   out_2198066657604437951[206] = 0.0;
   out_2198066657604437951[207] = 0.0;
   out_2198066657604437951[208] = 0.0;
   out_2198066657604437951[209] = 1.0;
   out_2198066657604437951[210] = 0.0;
   out_2198066657604437951[211] = 0.0;
   out_2198066657604437951[212] = 0.0;
   out_2198066657604437951[213] = 0.0;
   out_2198066657604437951[214] = 0.0;
   out_2198066657604437951[215] = 0.0;
   out_2198066657604437951[216] = 0.0;
   out_2198066657604437951[217] = 0.0;
   out_2198066657604437951[218] = 0.0;
   out_2198066657604437951[219] = 0.0;
   out_2198066657604437951[220] = 0.0;
   out_2198066657604437951[221] = 0.0;
   out_2198066657604437951[222] = 0.0;
   out_2198066657604437951[223] = 0.0;
   out_2198066657604437951[224] = 0.0;
   out_2198066657604437951[225] = 0.0;
   out_2198066657604437951[226] = 0.0;
   out_2198066657604437951[227] = 0.0;
   out_2198066657604437951[228] = 1.0;
   out_2198066657604437951[229] = 0.0;
   out_2198066657604437951[230] = 0.0;
   out_2198066657604437951[231] = 0.0;
   out_2198066657604437951[232] = 0.0;
   out_2198066657604437951[233] = 0.0;
   out_2198066657604437951[234] = 0.0;
   out_2198066657604437951[235] = 0.0;
   out_2198066657604437951[236] = 0.0;
   out_2198066657604437951[237] = 0.0;
   out_2198066657604437951[238] = 0.0;
   out_2198066657604437951[239] = 0.0;
   out_2198066657604437951[240] = 0.0;
   out_2198066657604437951[241] = 0.0;
   out_2198066657604437951[242] = 0.0;
   out_2198066657604437951[243] = 0.0;
   out_2198066657604437951[244] = 0.0;
   out_2198066657604437951[245] = 0.0;
   out_2198066657604437951[246] = 0.0;
   out_2198066657604437951[247] = 1.0;
   out_2198066657604437951[248] = 0.0;
   out_2198066657604437951[249] = 0.0;
   out_2198066657604437951[250] = 0.0;
   out_2198066657604437951[251] = 0.0;
   out_2198066657604437951[252] = 0.0;
   out_2198066657604437951[253] = 0.0;
   out_2198066657604437951[254] = 0.0;
   out_2198066657604437951[255] = 0.0;
   out_2198066657604437951[256] = 0.0;
   out_2198066657604437951[257] = 0.0;
   out_2198066657604437951[258] = 0.0;
   out_2198066657604437951[259] = 0.0;
   out_2198066657604437951[260] = 0.0;
   out_2198066657604437951[261] = 0.0;
   out_2198066657604437951[262] = 0.0;
   out_2198066657604437951[263] = 0.0;
   out_2198066657604437951[264] = 0.0;
   out_2198066657604437951[265] = 0.0;
   out_2198066657604437951[266] = 1.0;
   out_2198066657604437951[267] = 0.0;
   out_2198066657604437951[268] = 0.0;
   out_2198066657604437951[269] = 0.0;
   out_2198066657604437951[270] = 0.0;
   out_2198066657604437951[271] = 0.0;
   out_2198066657604437951[272] = 0.0;
   out_2198066657604437951[273] = 0.0;
   out_2198066657604437951[274] = 0.0;
   out_2198066657604437951[275] = 0.0;
   out_2198066657604437951[276] = 0.0;
   out_2198066657604437951[277] = 0.0;
   out_2198066657604437951[278] = 0.0;
   out_2198066657604437951[279] = 0.0;
   out_2198066657604437951[280] = 0.0;
   out_2198066657604437951[281] = 0.0;
   out_2198066657604437951[282] = 0.0;
   out_2198066657604437951[283] = 0.0;
   out_2198066657604437951[284] = 0.0;
   out_2198066657604437951[285] = 1.0;
   out_2198066657604437951[286] = 0.0;
   out_2198066657604437951[287] = 0.0;
   out_2198066657604437951[288] = 0.0;
   out_2198066657604437951[289] = 0.0;
   out_2198066657604437951[290] = 0.0;
   out_2198066657604437951[291] = 0.0;
   out_2198066657604437951[292] = 0.0;
   out_2198066657604437951[293] = 0.0;
   out_2198066657604437951[294] = 0.0;
   out_2198066657604437951[295] = 0.0;
   out_2198066657604437951[296] = 0.0;
   out_2198066657604437951[297] = 0.0;
   out_2198066657604437951[298] = 0.0;
   out_2198066657604437951[299] = 0.0;
   out_2198066657604437951[300] = 0.0;
   out_2198066657604437951[301] = 0.0;
   out_2198066657604437951[302] = 0.0;
   out_2198066657604437951[303] = 0.0;
   out_2198066657604437951[304] = 1.0;
   out_2198066657604437951[305] = 0.0;
   out_2198066657604437951[306] = 0.0;
   out_2198066657604437951[307] = 0.0;
   out_2198066657604437951[308] = 0.0;
   out_2198066657604437951[309] = 0.0;
   out_2198066657604437951[310] = 0.0;
   out_2198066657604437951[311] = 0.0;
   out_2198066657604437951[312] = 0.0;
   out_2198066657604437951[313] = 0.0;
   out_2198066657604437951[314] = 0.0;
   out_2198066657604437951[315] = 0.0;
   out_2198066657604437951[316] = 0.0;
   out_2198066657604437951[317] = 0.0;
   out_2198066657604437951[318] = 0.0;
   out_2198066657604437951[319] = 0.0;
   out_2198066657604437951[320] = 0.0;
   out_2198066657604437951[321] = 0.0;
   out_2198066657604437951[322] = 0.0;
   out_2198066657604437951[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3966114934127565362) {
   out_3966114934127565362[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3966114934127565362[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3966114934127565362[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3966114934127565362[3] = dt*state[12] + state[3];
   out_3966114934127565362[4] = dt*state[13] + state[4];
   out_3966114934127565362[5] = dt*state[14] + state[5];
   out_3966114934127565362[6] = state[6];
   out_3966114934127565362[7] = state[7];
   out_3966114934127565362[8] = state[8];
   out_3966114934127565362[9] = state[9];
   out_3966114934127565362[10] = state[10];
   out_3966114934127565362[11] = state[11];
   out_3966114934127565362[12] = state[12];
   out_3966114934127565362[13] = state[13];
   out_3966114934127565362[14] = state[14];
   out_3966114934127565362[15] = state[15];
   out_3966114934127565362[16] = state[16];
   out_3966114934127565362[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5076573913221290856) {
   out_5076573913221290856[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5076573913221290856[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5076573913221290856[2] = 0;
   out_5076573913221290856[3] = 0;
   out_5076573913221290856[4] = 0;
   out_5076573913221290856[5] = 0;
   out_5076573913221290856[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5076573913221290856[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5076573913221290856[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5076573913221290856[9] = 0;
   out_5076573913221290856[10] = 0;
   out_5076573913221290856[11] = 0;
   out_5076573913221290856[12] = 0;
   out_5076573913221290856[13] = 0;
   out_5076573913221290856[14] = 0;
   out_5076573913221290856[15] = 0;
   out_5076573913221290856[16] = 0;
   out_5076573913221290856[17] = 0;
   out_5076573913221290856[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5076573913221290856[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5076573913221290856[20] = 0;
   out_5076573913221290856[21] = 0;
   out_5076573913221290856[22] = 0;
   out_5076573913221290856[23] = 0;
   out_5076573913221290856[24] = 0;
   out_5076573913221290856[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5076573913221290856[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5076573913221290856[27] = 0;
   out_5076573913221290856[28] = 0;
   out_5076573913221290856[29] = 0;
   out_5076573913221290856[30] = 0;
   out_5076573913221290856[31] = 0;
   out_5076573913221290856[32] = 0;
   out_5076573913221290856[33] = 0;
   out_5076573913221290856[34] = 0;
   out_5076573913221290856[35] = 0;
   out_5076573913221290856[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5076573913221290856[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5076573913221290856[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5076573913221290856[39] = 0;
   out_5076573913221290856[40] = 0;
   out_5076573913221290856[41] = 0;
   out_5076573913221290856[42] = 0;
   out_5076573913221290856[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5076573913221290856[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5076573913221290856[45] = 0;
   out_5076573913221290856[46] = 0;
   out_5076573913221290856[47] = 0;
   out_5076573913221290856[48] = 0;
   out_5076573913221290856[49] = 0;
   out_5076573913221290856[50] = 0;
   out_5076573913221290856[51] = 0;
   out_5076573913221290856[52] = 0;
   out_5076573913221290856[53] = 0;
   out_5076573913221290856[54] = 0;
   out_5076573913221290856[55] = 0;
   out_5076573913221290856[56] = 0;
   out_5076573913221290856[57] = 1;
   out_5076573913221290856[58] = 0;
   out_5076573913221290856[59] = 0;
   out_5076573913221290856[60] = 0;
   out_5076573913221290856[61] = 0;
   out_5076573913221290856[62] = 0;
   out_5076573913221290856[63] = 0;
   out_5076573913221290856[64] = 0;
   out_5076573913221290856[65] = 0;
   out_5076573913221290856[66] = dt;
   out_5076573913221290856[67] = 0;
   out_5076573913221290856[68] = 0;
   out_5076573913221290856[69] = 0;
   out_5076573913221290856[70] = 0;
   out_5076573913221290856[71] = 0;
   out_5076573913221290856[72] = 0;
   out_5076573913221290856[73] = 0;
   out_5076573913221290856[74] = 0;
   out_5076573913221290856[75] = 0;
   out_5076573913221290856[76] = 1;
   out_5076573913221290856[77] = 0;
   out_5076573913221290856[78] = 0;
   out_5076573913221290856[79] = 0;
   out_5076573913221290856[80] = 0;
   out_5076573913221290856[81] = 0;
   out_5076573913221290856[82] = 0;
   out_5076573913221290856[83] = 0;
   out_5076573913221290856[84] = 0;
   out_5076573913221290856[85] = dt;
   out_5076573913221290856[86] = 0;
   out_5076573913221290856[87] = 0;
   out_5076573913221290856[88] = 0;
   out_5076573913221290856[89] = 0;
   out_5076573913221290856[90] = 0;
   out_5076573913221290856[91] = 0;
   out_5076573913221290856[92] = 0;
   out_5076573913221290856[93] = 0;
   out_5076573913221290856[94] = 0;
   out_5076573913221290856[95] = 1;
   out_5076573913221290856[96] = 0;
   out_5076573913221290856[97] = 0;
   out_5076573913221290856[98] = 0;
   out_5076573913221290856[99] = 0;
   out_5076573913221290856[100] = 0;
   out_5076573913221290856[101] = 0;
   out_5076573913221290856[102] = 0;
   out_5076573913221290856[103] = 0;
   out_5076573913221290856[104] = dt;
   out_5076573913221290856[105] = 0;
   out_5076573913221290856[106] = 0;
   out_5076573913221290856[107] = 0;
   out_5076573913221290856[108] = 0;
   out_5076573913221290856[109] = 0;
   out_5076573913221290856[110] = 0;
   out_5076573913221290856[111] = 0;
   out_5076573913221290856[112] = 0;
   out_5076573913221290856[113] = 0;
   out_5076573913221290856[114] = 1;
   out_5076573913221290856[115] = 0;
   out_5076573913221290856[116] = 0;
   out_5076573913221290856[117] = 0;
   out_5076573913221290856[118] = 0;
   out_5076573913221290856[119] = 0;
   out_5076573913221290856[120] = 0;
   out_5076573913221290856[121] = 0;
   out_5076573913221290856[122] = 0;
   out_5076573913221290856[123] = 0;
   out_5076573913221290856[124] = 0;
   out_5076573913221290856[125] = 0;
   out_5076573913221290856[126] = 0;
   out_5076573913221290856[127] = 0;
   out_5076573913221290856[128] = 0;
   out_5076573913221290856[129] = 0;
   out_5076573913221290856[130] = 0;
   out_5076573913221290856[131] = 0;
   out_5076573913221290856[132] = 0;
   out_5076573913221290856[133] = 1;
   out_5076573913221290856[134] = 0;
   out_5076573913221290856[135] = 0;
   out_5076573913221290856[136] = 0;
   out_5076573913221290856[137] = 0;
   out_5076573913221290856[138] = 0;
   out_5076573913221290856[139] = 0;
   out_5076573913221290856[140] = 0;
   out_5076573913221290856[141] = 0;
   out_5076573913221290856[142] = 0;
   out_5076573913221290856[143] = 0;
   out_5076573913221290856[144] = 0;
   out_5076573913221290856[145] = 0;
   out_5076573913221290856[146] = 0;
   out_5076573913221290856[147] = 0;
   out_5076573913221290856[148] = 0;
   out_5076573913221290856[149] = 0;
   out_5076573913221290856[150] = 0;
   out_5076573913221290856[151] = 0;
   out_5076573913221290856[152] = 1;
   out_5076573913221290856[153] = 0;
   out_5076573913221290856[154] = 0;
   out_5076573913221290856[155] = 0;
   out_5076573913221290856[156] = 0;
   out_5076573913221290856[157] = 0;
   out_5076573913221290856[158] = 0;
   out_5076573913221290856[159] = 0;
   out_5076573913221290856[160] = 0;
   out_5076573913221290856[161] = 0;
   out_5076573913221290856[162] = 0;
   out_5076573913221290856[163] = 0;
   out_5076573913221290856[164] = 0;
   out_5076573913221290856[165] = 0;
   out_5076573913221290856[166] = 0;
   out_5076573913221290856[167] = 0;
   out_5076573913221290856[168] = 0;
   out_5076573913221290856[169] = 0;
   out_5076573913221290856[170] = 0;
   out_5076573913221290856[171] = 1;
   out_5076573913221290856[172] = 0;
   out_5076573913221290856[173] = 0;
   out_5076573913221290856[174] = 0;
   out_5076573913221290856[175] = 0;
   out_5076573913221290856[176] = 0;
   out_5076573913221290856[177] = 0;
   out_5076573913221290856[178] = 0;
   out_5076573913221290856[179] = 0;
   out_5076573913221290856[180] = 0;
   out_5076573913221290856[181] = 0;
   out_5076573913221290856[182] = 0;
   out_5076573913221290856[183] = 0;
   out_5076573913221290856[184] = 0;
   out_5076573913221290856[185] = 0;
   out_5076573913221290856[186] = 0;
   out_5076573913221290856[187] = 0;
   out_5076573913221290856[188] = 0;
   out_5076573913221290856[189] = 0;
   out_5076573913221290856[190] = 1;
   out_5076573913221290856[191] = 0;
   out_5076573913221290856[192] = 0;
   out_5076573913221290856[193] = 0;
   out_5076573913221290856[194] = 0;
   out_5076573913221290856[195] = 0;
   out_5076573913221290856[196] = 0;
   out_5076573913221290856[197] = 0;
   out_5076573913221290856[198] = 0;
   out_5076573913221290856[199] = 0;
   out_5076573913221290856[200] = 0;
   out_5076573913221290856[201] = 0;
   out_5076573913221290856[202] = 0;
   out_5076573913221290856[203] = 0;
   out_5076573913221290856[204] = 0;
   out_5076573913221290856[205] = 0;
   out_5076573913221290856[206] = 0;
   out_5076573913221290856[207] = 0;
   out_5076573913221290856[208] = 0;
   out_5076573913221290856[209] = 1;
   out_5076573913221290856[210] = 0;
   out_5076573913221290856[211] = 0;
   out_5076573913221290856[212] = 0;
   out_5076573913221290856[213] = 0;
   out_5076573913221290856[214] = 0;
   out_5076573913221290856[215] = 0;
   out_5076573913221290856[216] = 0;
   out_5076573913221290856[217] = 0;
   out_5076573913221290856[218] = 0;
   out_5076573913221290856[219] = 0;
   out_5076573913221290856[220] = 0;
   out_5076573913221290856[221] = 0;
   out_5076573913221290856[222] = 0;
   out_5076573913221290856[223] = 0;
   out_5076573913221290856[224] = 0;
   out_5076573913221290856[225] = 0;
   out_5076573913221290856[226] = 0;
   out_5076573913221290856[227] = 0;
   out_5076573913221290856[228] = 1;
   out_5076573913221290856[229] = 0;
   out_5076573913221290856[230] = 0;
   out_5076573913221290856[231] = 0;
   out_5076573913221290856[232] = 0;
   out_5076573913221290856[233] = 0;
   out_5076573913221290856[234] = 0;
   out_5076573913221290856[235] = 0;
   out_5076573913221290856[236] = 0;
   out_5076573913221290856[237] = 0;
   out_5076573913221290856[238] = 0;
   out_5076573913221290856[239] = 0;
   out_5076573913221290856[240] = 0;
   out_5076573913221290856[241] = 0;
   out_5076573913221290856[242] = 0;
   out_5076573913221290856[243] = 0;
   out_5076573913221290856[244] = 0;
   out_5076573913221290856[245] = 0;
   out_5076573913221290856[246] = 0;
   out_5076573913221290856[247] = 1;
   out_5076573913221290856[248] = 0;
   out_5076573913221290856[249] = 0;
   out_5076573913221290856[250] = 0;
   out_5076573913221290856[251] = 0;
   out_5076573913221290856[252] = 0;
   out_5076573913221290856[253] = 0;
   out_5076573913221290856[254] = 0;
   out_5076573913221290856[255] = 0;
   out_5076573913221290856[256] = 0;
   out_5076573913221290856[257] = 0;
   out_5076573913221290856[258] = 0;
   out_5076573913221290856[259] = 0;
   out_5076573913221290856[260] = 0;
   out_5076573913221290856[261] = 0;
   out_5076573913221290856[262] = 0;
   out_5076573913221290856[263] = 0;
   out_5076573913221290856[264] = 0;
   out_5076573913221290856[265] = 0;
   out_5076573913221290856[266] = 1;
   out_5076573913221290856[267] = 0;
   out_5076573913221290856[268] = 0;
   out_5076573913221290856[269] = 0;
   out_5076573913221290856[270] = 0;
   out_5076573913221290856[271] = 0;
   out_5076573913221290856[272] = 0;
   out_5076573913221290856[273] = 0;
   out_5076573913221290856[274] = 0;
   out_5076573913221290856[275] = 0;
   out_5076573913221290856[276] = 0;
   out_5076573913221290856[277] = 0;
   out_5076573913221290856[278] = 0;
   out_5076573913221290856[279] = 0;
   out_5076573913221290856[280] = 0;
   out_5076573913221290856[281] = 0;
   out_5076573913221290856[282] = 0;
   out_5076573913221290856[283] = 0;
   out_5076573913221290856[284] = 0;
   out_5076573913221290856[285] = 1;
   out_5076573913221290856[286] = 0;
   out_5076573913221290856[287] = 0;
   out_5076573913221290856[288] = 0;
   out_5076573913221290856[289] = 0;
   out_5076573913221290856[290] = 0;
   out_5076573913221290856[291] = 0;
   out_5076573913221290856[292] = 0;
   out_5076573913221290856[293] = 0;
   out_5076573913221290856[294] = 0;
   out_5076573913221290856[295] = 0;
   out_5076573913221290856[296] = 0;
   out_5076573913221290856[297] = 0;
   out_5076573913221290856[298] = 0;
   out_5076573913221290856[299] = 0;
   out_5076573913221290856[300] = 0;
   out_5076573913221290856[301] = 0;
   out_5076573913221290856[302] = 0;
   out_5076573913221290856[303] = 0;
   out_5076573913221290856[304] = 1;
   out_5076573913221290856[305] = 0;
   out_5076573913221290856[306] = 0;
   out_5076573913221290856[307] = 0;
   out_5076573913221290856[308] = 0;
   out_5076573913221290856[309] = 0;
   out_5076573913221290856[310] = 0;
   out_5076573913221290856[311] = 0;
   out_5076573913221290856[312] = 0;
   out_5076573913221290856[313] = 0;
   out_5076573913221290856[314] = 0;
   out_5076573913221290856[315] = 0;
   out_5076573913221290856[316] = 0;
   out_5076573913221290856[317] = 0;
   out_5076573913221290856[318] = 0;
   out_5076573913221290856[319] = 0;
   out_5076573913221290856[320] = 0;
   out_5076573913221290856[321] = 0;
   out_5076573913221290856[322] = 0;
   out_5076573913221290856[323] = 1;
}
void h_4(double *state, double *unused, double *out_6142098143209384501) {
   out_6142098143209384501[0] = state[6] + state[9];
   out_6142098143209384501[1] = state[7] + state[10];
   out_6142098143209384501[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2269303973952347607) {
   out_2269303973952347607[0] = 0;
   out_2269303973952347607[1] = 0;
   out_2269303973952347607[2] = 0;
   out_2269303973952347607[3] = 0;
   out_2269303973952347607[4] = 0;
   out_2269303973952347607[5] = 0;
   out_2269303973952347607[6] = 1;
   out_2269303973952347607[7] = 0;
   out_2269303973952347607[8] = 0;
   out_2269303973952347607[9] = 1;
   out_2269303973952347607[10] = 0;
   out_2269303973952347607[11] = 0;
   out_2269303973952347607[12] = 0;
   out_2269303973952347607[13] = 0;
   out_2269303973952347607[14] = 0;
   out_2269303973952347607[15] = 0;
   out_2269303973952347607[16] = 0;
   out_2269303973952347607[17] = 0;
   out_2269303973952347607[18] = 0;
   out_2269303973952347607[19] = 0;
   out_2269303973952347607[20] = 0;
   out_2269303973952347607[21] = 0;
   out_2269303973952347607[22] = 0;
   out_2269303973952347607[23] = 0;
   out_2269303973952347607[24] = 0;
   out_2269303973952347607[25] = 1;
   out_2269303973952347607[26] = 0;
   out_2269303973952347607[27] = 0;
   out_2269303973952347607[28] = 1;
   out_2269303973952347607[29] = 0;
   out_2269303973952347607[30] = 0;
   out_2269303973952347607[31] = 0;
   out_2269303973952347607[32] = 0;
   out_2269303973952347607[33] = 0;
   out_2269303973952347607[34] = 0;
   out_2269303973952347607[35] = 0;
   out_2269303973952347607[36] = 0;
   out_2269303973952347607[37] = 0;
   out_2269303973952347607[38] = 0;
   out_2269303973952347607[39] = 0;
   out_2269303973952347607[40] = 0;
   out_2269303973952347607[41] = 0;
   out_2269303973952347607[42] = 0;
   out_2269303973952347607[43] = 0;
   out_2269303973952347607[44] = 1;
   out_2269303973952347607[45] = 0;
   out_2269303973952347607[46] = 0;
   out_2269303973952347607[47] = 1;
   out_2269303973952347607[48] = 0;
   out_2269303973952347607[49] = 0;
   out_2269303973952347607[50] = 0;
   out_2269303973952347607[51] = 0;
   out_2269303973952347607[52] = 0;
   out_2269303973952347607[53] = 0;
}
void h_10(double *state, double *unused, double *out_8285425693527011599) {
   out_8285425693527011599[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8285425693527011599[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8285425693527011599[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1179697727219865805) {
   out_1179697727219865805[0] = 0;
   out_1179697727219865805[1] = 9.8100000000000005*cos(state[1]);
   out_1179697727219865805[2] = 0;
   out_1179697727219865805[3] = 0;
   out_1179697727219865805[4] = -state[8];
   out_1179697727219865805[5] = state[7];
   out_1179697727219865805[6] = 0;
   out_1179697727219865805[7] = state[5];
   out_1179697727219865805[8] = -state[4];
   out_1179697727219865805[9] = 0;
   out_1179697727219865805[10] = 0;
   out_1179697727219865805[11] = 0;
   out_1179697727219865805[12] = 1;
   out_1179697727219865805[13] = 0;
   out_1179697727219865805[14] = 0;
   out_1179697727219865805[15] = 1;
   out_1179697727219865805[16] = 0;
   out_1179697727219865805[17] = 0;
   out_1179697727219865805[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1179697727219865805[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1179697727219865805[20] = 0;
   out_1179697727219865805[21] = state[8];
   out_1179697727219865805[22] = 0;
   out_1179697727219865805[23] = -state[6];
   out_1179697727219865805[24] = -state[5];
   out_1179697727219865805[25] = 0;
   out_1179697727219865805[26] = state[3];
   out_1179697727219865805[27] = 0;
   out_1179697727219865805[28] = 0;
   out_1179697727219865805[29] = 0;
   out_1179697727219865805[30] = 0;
   out_1179697727219865805[31] = 1;
   out_1179697727219865805[32] = 0;
   out_1179697727219865805[33] = 0;
   out_1179697727219865805[34] = 1;
   out_1179697727219865805[35] = 0;
   out_1179697727219865805[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1179697727219865805[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1179697727219865805[38] = 0;
   out_1179697727219865805[39] = -state[7];
   out_1179697727219865805[40] = state[6];
   out_1179697727219865805[41] = 0;
   out_1179697727219865805[42] = state[4];
   out_1179697727219865805[43] = -state[3];
   out_1179697727219865805[44] = 0;
   out_1179697727219865805[45] = 0;
   out_1179697727219865805[46] = 0;
   out_1179697727219865805[47] = 0;
   out_1179697727219865805[48] = 0;
   out_1179697727219865805[49] = 0;
   out_1179697727219865805[50] = 1;
   out_1179697727219865805[51] = 0;
   out_1179697727219865805[52] = 0;
   out_1179697727219865805[53] = 1;
}
void h_13(double *state, double *unused, double *out_5990382156794574262) {
   out_5990382156794574262[0] = state[3];
   out_5990382156794574262[1] = state[4];
   out_5990382156794574262[2] = state[5];
}
void H_13(double *state, double *unused, double *out_942969851379985194) {
   out_942969851379985194[0] = 0;
   out_942969851379985194[1] = 0;
   out_942969851379985194[2] = 0;
   out_942969851379985194[3] = 1;
   out_942969851379985194[4] = 0;
   out_942969851379985194[5] = 0;
   out_942969851379985194[6] = 0;
   out_942969851379985194[7] = 0;
   out_942969851379985194[8] = 0;
   out_942969851379985194[9] = 0;
   out_942969851379985194[10] = 0;
   out_942969851379985194[11] = 0;
   out_942969851379985194[12] = 0;
   out_942969851379985194[13] = 0;
   out_942969851379985194[14] = 0;
   out_942969851379985194[15] = 0;
   out_942969851379985194[16] = 0;
   out_942969851379985194[17] = 0;
   out_942969851379985194[18] = 0;
   out_942969851379985194[19] = 0;
   out_942969851379985194[20] = 0;
   out_942969851379985194[21] = 0;
   out_942969851379985194[22] = 1;
   out_942969851379985194[23] = 0;
   out_942969851379985194[24] = 0;
   out_942969851379985194[25] = 0;
   out_942969851379985194[26] = 0;
   out_942969851379985194[27] = 0;
   out_942969851379985194[28] = 0;
   out_942969851379985194[29] = 0;
   out_942969851379985194[30] = 0;
   out_942969851379985194[31] = 0;
   out_942969851379985194[32] = 0;
   out_942969851379985194[33] = 0;
   out_942969851379985194[34] = 0;
   out_942969851379985194[35] = 0;
   out_942969851379985194[36] = 0;
   out_942969851379985194[37] = 0;
   out_942969851379985194[38] = 0;
   out_942969851379985194[39] = 0;
   out_942969851379985194[40] = 0;
   out_942969851379985194[41] = 1;
   out_942969851379985194[42] = 0;
   out_942969851379985194[43] = 0;
   out_942969851379985194[44] = 0;
   out_942969851379985194[45] = 0;
   out_942969851379985194[46] = 0;
   out_942969851379985194[47] = 0;
   out_942969851379985194[48] = 0;
   out_942969851379985194[49] = 0;
   out_942969851379985194[50] = 0;
   out_942969851379985194[51] = 0;
   out_942969851379985194[52] = 0;
   out_942969851379985194[53] = 0;
}
void h_14(double *state, double *unused, double *out_7430784843815807548) {
   out_7430784843815807548[0] = state[6];
   out_7430784843815807548[1] = state[7];
   out_7430784843815807548[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1693936882387136922) {
   out_1693936882387136922[0] = 0;
   out_1693936882387136922[1] = 0;
   out_1693936882387136922[2] = 0;
   out_1693936882387136922[3] = 0;
   out_1693936882387136922[4] = 0;
   out_1693936882387136922[5] = 0;
   out_1693936882387136922[6] = 1;
   out_1693936882387136922[7] = 0;
   out_1693936882387136922[8] = 0;
   out_1693936882387136922[9] = 0;
   out_1693936882387136922[10] = 0;
   out_1693936882387136922[11] = 0;
   out_1693936882387136922[12] = 0;
   out_1693936882387136922[13] = 0;
   out_1693936882387136922[14] = 0;
   out_1693936882387136922[15] = 0;
   out_1693936882387136922[16] = 0;
   out_1693936882387136922[17] = 0;
   out_1693936882387136922[18] = 0;
   out_1693936882387136922[19] = 0;
   out_1693936882387136922[20] = 0;
   out_1693936882387136922[21] = 0;
   out_1693936882387136922[22] = 0;
   out_1693936882387136922[23] = 0;
   out_1693936882387136922[24] = 0;
   out_1693936882387136922[25] = 1;
   out_1693936882387136922[26] = 0;
   out_1693936882387136922[27] = 0;
   out_1693936882387136922[28] = 0;
   out_1693936882387136922[29] = 0;
   out_1693936882387136922[30] = 0;
   out_1693936882387136922[31] = 0;
   out_1693936882387136922[32] = 0;
   out_1693936882387136922[33] = 0;
   out_1693936882387136922[34] = 0;
   out_1693936882387136922[35] = 0;
   out_1693936882387136922[36] = 0;
   out_1693936882387136922[37] = 0;
   out_1693936882387136922[38] = 0;
   out_1693936882387136922[39] = 0;
   out_1693936882387136922[40] = 0;
   out_1693936882387136922[41] = 0;
   out_1693936882387136922[42] = 0;
   out_1693936882387136922[43] = 0;
   out_1693936882387136922[44] = 1;
   out_1693936882387136922[45] = 0;
   out_1693936882387136922[46] = 0;
   out_1693936882387136922[47] = 0;
   out_1693936882387136922[48] = 0;
   out_1693936882387136922[49] = 0;
   out_1693936882387136922[50] = 0;
   out_1693936882387136922[51] = 0;
   out_1693936882387136922[52] = 0;
   out_1693936882387136922[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3576604326285445174) {
  err_fun(nom_x, delta_x, out_3576604326285445174);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_496602688636603974) {
  inv_err_fun(nom_x, true_x, out_496602688636603974);
}
void pose_H_mod_fun(double *state, double *out_2198066657604437951) {
  H_mod_fun(state, out_2198066657604437951);
}
void pose_f_fun(double *state, double dt, double *out_3966114934127565362) {
  f_fun(state,  dt, out_3966114934127565362);
}
void pose_F_fun(double *state, double dt, double *out_5076573913221290856) {
  F_fun(state,  dt, out_5076573913221290856);
}
void pose_h_4(double *state, double *unused, double *out_6142098143209384501) {
  h_4(state, unused, out_6142098143209384501);
}
void pose_H_4(double *state, double *unused, double *out_2269303973952347607) {
  H_4(state, unused, out_2269303973952347607);
}
void pose_h_10(double *state, double *unused, double *out_8285425693527011599) {
  h_10(state, unused, out_8285425693527011599);
}
void pose_H_10(double *state, double *unused, double *out_1179697727219865805) {
  H_10(state, unused, out_1179697727219865805);
}
void pose_h_13(double *state, double *unused, double *out_5990382156794574262) {
  h_13(state, unused, out_5990382156794574262);
}
void pose_H_13(double *state, double *unused, double *out_942969851379985194) {
  H_13(state, unused, out_942969851379985194);
}
void pose_h_14(double *state, double *unused, double *out_7430784843815807548) {
  h_14(state, unused, out_7430784843815807548);
}
void pose_H_14(double *state, double *unused, double *out_1693936882387136922) {
  H_14(state, unused, out_1693936882387136922);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
