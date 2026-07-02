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
void err_fun(double *nom_x, double *delta_x, double *out_6475098180663358236) {
   out_6475098180663358236[0] = delta_x[0] + nom_x[0];
   out_6475098180663358236[1] = delta_x[1] + nom_x[1];
   out_6475098180663358236[2] = delta_x[2] + nom_x[2];
   out_6475098180663358236[3] = delta_x[3] + nom_x[3];
   out_6475098180663358236[4] = delta_x[4] + nom_x[4];
   out_6475098180663358236[5] = delta_x[5] + nom_x[5];
   out_6475098180663358236[6] = delta_x[6] + nom_x[6];
   out_6475098180663358236[7] = delta_x[7] + nom_x[7];
   out_6475098180663358236[8] = delta_x[8] + nom_x[8];
   out_6475098180663358236[9] = delta_x[9] + nom_x[9];
   out_6475098180663358236[10] = delta_x[10] + nom_x[10];
   out_6475098180663358236[11] = delta_x[11] + nom_x[11];
   out_6475098180663358236[12] = delta_x[12] + nom_x[12];
   out_6475098180663358236[13] = delta_x[13] + nom_x[13];
   out_6475098180663358236[14] = delta_x[14] + nom_x[14];
   out_6475098180663358236[15] = delta_x[15] + nom_x[15];
   out_6475098180663358236[16] = delta_x[16] + nom_x[16];
   out_6475098180663358236[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2585492389743957981) {
   out_2585492389743957981[0] = -nom_x[0] + true_x[0];
   out_2585492389743957981[1] = -nom_x[1] + true_x[1];
   out_2585492389743957981[2] = -nom_x[2] + true_x[2];
   out_2585492389743957981[3] = -nom_x[3] + true_x[3];
   out_2585492389743957981[4] = -nom_x[4] + true_x[4];
   out_2585492389743957981[5] = -nom_x[5] + true_x[5];
   out_2585492389743957981[6] = -nom_x[6] + true_x[6];
   out_2585492389743957981[7] = -nom_x[7] + true_x[7];
   out_2585492389743957981[8] = -nom_x[8] + true_x[8];
   out_2585492389743957981[9] = -nom_x[9] + true_x[9];
   out_2585492389743957981[10] = -nom_x[10] + true_x[10];
   out_2585492389743957981[11] = -nom_x[11] + true_x[11];
   out_2585492389743957981[12] = -nom_x[12] + true_x[12];
   out_2585492389743957981[13] = -nom_x[13] + true_x[13];
   out_2585492389743957981[14] = -nom_x[14] + true_x[14];
   out_2585492389743957981[15] = -nom_x[15] + true_x[15];
   out_2585492389743957981[16] = -nom_x[16] + true_x[16];
   out_2585492389743957981[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2975532171405769290) {
   out_2975532171405769290[0] = 1.0;
   out_2975532171405769290[1] = 0.0;
   out_2975532171405769290[2] = 0.0;
   out_2975532171405769290[3] = 0.0;
   out_2975532171405769290[4] = 0.0;
   out_2975532171405769290[5] = 0.0;
   out_2975532171405769290[6] = 0.0;
   out_2975532171405769290[7] = 0.0;
   out_2975532171405769290[8] = 0.0;
   out_2975532171405769290[9] = 0.0;
   out_2975532171405769290[10] = 0.0;
   out_2975532171405769290[11] = 0.0;
   out_2975532171405769290[12] = 0.0;
   out_2975532171405769290[13] = 0.0;
   out_2975532171405769290[14] = 0.0;
   out_2975532171405769290[15] = 0.0;
   out_2975532171405769290[16] = 0.0;
   out_2975532171405769290[17] = 0.0;
   out_2975532171405769290[18] = 0.0;
   out_2975532171405769290[19] = 1.0;
   out_2975532171405769290[20] = 0.0;
   out_2975532171405769290[21] = 0.0;
   out_2975532171405769290[22] = 0.0;
   out_2975532171405769290[23] = 0.0;
   out_2975532171405769290[24] = 0.0;
   out_2975532171405769290[25] = 0.0;
   out_2975532171405769290[26] = 0.0;
   out_2975532171405769290[27] = 0.0;
   out_2975532171405769290[28] = 0.0;
   out_2975532171405769290[29] = 0.0;
   out_2975532171405769290[30] = 0.0;
   out_2975532171405769290[31] = 0.0;
   out_2975532171405769290[32] = 0.0;
   out_2975532171405769290[33] = 0.0;
   out_2975532171405769290[34] = 0.0;
   out_2975532171405769290[35] = 0.0;
   out_2975532171405769290[36] = 0.0;
   out_2975532171405769290[37] = 0.0;
   out_2975532171405769290[38] = 1.0;
   out_2975532171405769290[39] = 0.0;
   out_2975532171405769290[40] = 0.0;
   out_2975532171405769290[41] = 0.0;
   out_2975532171405769290[42] = 0.0;
   out_2975532171405769290[43] = 0.0;
   out_2975532171405769290[44] = 0.0;
   out_2975532171405769290[45] = 0.0;
   out_2975532171405769290[46] = 0.0;
   out_2975532171405769290[47] = 0.0;
   out_2975532171405769290[48] = 0.0;
   out_2975532171405769290[49] = 0.0;
   out_2975532171405769290[50] = 0.0;
   out_2975532171405769290[51] = 0.0;
   out_2975532171405769290[52] = 0.0;
   out_2975532171405769290[53] = 0.0;
   out_2975532171405769290[54] = 0.0;
   out_2975532171405769290[55] = 0.0;
   out_2975532171405769290[56] = 0.0;
   out_2975532171405769290[57] = 1.0;
   out_2975532171405769290[58] = 0.0;
   out_2975532171405769290[59] = 0.0;
   out_2975532171405769290[60] = 0.0;
   out_2975532171405769290[61] = 0.0;
   out_2975532171405769290[62] = 0.0;
   out_2975532171405769290[63] = 0.0;
   out_2975532171405769290[64] = 0.0;
   out_2975532171405769290[65] = 0.0;
   out_2975532171405769290[66] = 0.0;
   out_2975532171405769290[67] = 0.0;
   out_2975532171405769290[68] = 0.0;
   out_2975532171405769290[69] = 0.0;
   out_2975532171405769290[70] = 0.0;
   out_2975532171405769290[71] = 0.0;
   out_2975532171405769290[72] = 0.0;
   out_2975532171405769290[73] = 0.0;
   out_2975532171405769290[74] = 0.0;
   out_2975532171405769290[75] = 0.0;
   out_2975532171405769290[76] = 1.0;
   out_2975532171405769290[77] = 0.0;
   out_2975532171405769290[78] = 0.0;
   out_2975532171405769290[79] = 0.0;
   out_2975532171405769290[80] = 0.0;
   out_2975532171405769290[81] = 0.0;
   out_2975532171405769290[82] = 0.0;
   out_2975532171405769290[83] = 0.0;
   out_2975532171405769290[84] = 0.0;
   out_2975532171405769290[85] = 0.0;
   out_2975532171405769290[86] = 0.0;
   out_2975532171405769290[87] = 0.0;
   out_2975532171405769290[88] = 0.0;
   out_2975532171405769290[89] = 0.0;
   out_2975532171405769290[90] = 0.0;
   out_2975532171405769290[91] = 0.0;
   out_2975532171405769290[92] = 0.0;
   out_2975532171405769290[93] = 0.0;
   out_2975532171405769290[94] = 0.0;
   out_2975532171405769290[95] = 1.0;
   out_2975532171405769290[96] = 0.0;
   out_2975532171405769290[97] = 0.0;
   out_2975532171405769290[98] = 0.0;
   out_2975532171405769290[99] = 0.0;
   out_2975532171405769290[100] = 0.0;
   out_2975532171405769290[101] = 0.0;
   out_2975532171405769290[102] = 0.0;
   out_2975532171405769290[103] = 0.0;
   out_2975532171405769290[104] = 0.0;
   out_2975532171405769290[105] = 0.0;
   out_2975532171405769290[106] = 0.0;
   out_2975532171405769290[107] = 0.0;
   out_2975532171405769290[108] = 0.0;
   out_2975532171405769290[109] = 0.0;
   out_2975532171405769290[110] = 0.0;
   out_2975532171405769290[111] = 0.0;
   out_2975532171405769290[112] = 0.0;
   out_2975532171405769290[113] = 0.0;
   out_2975532171405769290[114] = 1.0;
   out_2975532171405769290[115] = 0.0;
   out_2975532171405769290[116] = 0.0;
   out_2975532171405769290[117] = 0.0;
   out_2975532171405769290[118] = 0.0;
   out_2975532171405769290[119] = 0.0;
   out_2975532171405769290[120] = 0.0;
   out_2975532171405769290[121] = 0.0;
   out_2975532171405769290[122] = 0.0;
   out_2975532171405769290[123] = 0.0;
   out_2975532171405769290[124] = 0.0;
   out_2975532171405769290[125] = 0.0;
   out_2975532171405769290[126] = 0.0;
   out_2975532171405769290[127] = 0.0;
   out_2975532171405769290[128] = 0.0;
   out_2975532171405769290[129] = 0.0;
   out_2975532171405769290[130] = 0.0;
   out_2975532171405769290[131] = 0.0;
   out_2975532171405769290[132] = 0.0;
   out_2975532171405769290[133] = 1.0;
   out_2975532171405769290[134] = 0.0;
   out_2975532171405769290[135] = 0.0;
   out_2975532171405769290[136] = 0.0;
   out_2975532171405769290[137] = 0.0;
   out_2975532171405769290[138] = 0.0;
   out_2975532171405769290[139] = 0.0;
   out_2975532171405769290[140] = 0.0;
   out_2975532171405769290[141] = 0.0;
   out_2975532171405769290[142] = 0.0;
   out_2975532171405769290[143] = 0.0;
   out_2975532171405769290[144] = 0.0;
   out_2975532171405769290[145] = 0.0;
   out_2975532171405769290[146] = 0.0;
   out_2975532171405769290[147] = 0.0;
   out_2975532171405769290[148] = 0.0;
   out_2975532171405769290[149] = 0.0;
   out_2975532171405769290[150] = 0.0;
   out_2975532171405769290[151] = 0.0;
   out_2975532171405769290[152] = 1.0;
   out_2975532171405769290[153] = 0.0;
   out_2975532171405769290[154] = 0.0;
   out_2975532171405769290[155] = 0.0;
   out_2975532171405769290[156] = 0.0;
   out_2975532171405769290[157] = 0.0;
   out_2975532171405769290[158] = 0.0;
   out_2975532171405769290[159] = 0.0;
   out_2975532171405769290[160] = 0.0;
   out_2975532171405769290[161] = 0.0;
   out_2975532171405769290[162] = 0.0;
   out_2975532171405769290[163] = 0.0;
   out_2975532171405769290[164] = 0.0;
   out_2975532171405769290[165] = 0.0;
   out_2975532171405769290[166] = 0.0;
   out_2975532171405769290[167] = 0.0;
   out_2975532171405769290[168] = 0.0;
   out_2975532171405769290[169] = 0.0;
   out_2975532171405769290[170] = 0.0;
   out_2975532171405769290[171] = 1.0;
   out_2975532171405769290[172] = 0.0;
   out_2975532171405769290[173] = 0.0;
   out_2975532171405769290[174] = 0.0;
   out_2975532171405769290[175] = 0.0;
   out_2975532171405769290[176] = 0.0;
   out_2975532171405769290[177] = 0.0;
   out_2975532171405769290[178] = 0.0;
   out_2975532171405769290[179] = 0.0;
   out_2975532171405769290[180] = 0.0;
   out_2975532171405769290[181] = 0.0;
   out_2975532171405769290[182] = 0.0;
   out_2975532171405769290[183] = 0.0;
   out_2975532171405769290[184] = 0.0;
   out_2975532171405769290[185] = 0.0;
   out_2975532171405769290[186] = 0.0;
   out_2975532171405769290[187] = 0.0;
   out_2975532171405769290[188] = 0.0;
   out_2975532171405769290[189] = 0.0;
   out_2975532171405769290[190] = 1.0;
   out_2975532171405769290[191] = 0.0;
   out_2975532171405769290[192] = 0.0;
   out_2975532171405769290[193] = 0.0;
   out_2975532171405769290[194] = 0.0;
   out_2975532171405769290[195] = 0.0;
   out_2975532171405769290[196] = 0.0;
   out_2975532171405769290[197] = 0.0;
   out_2975532171405769290[198] = 0.0;
   out_2975532171405769290[199] = 0.0;
   out_2975532171405769290[200] = 0.0;
   out_2975532171405769290[201] = 0.0;
   out_2975532171405769290[202] = 0.0;
   out_2975532171405769290[203] = 0.0;
   out_2975532171405769290[204] = 0.0;
   out_2975532171405769290[205] = 0.0;
   out_2975532171405769290[206] = 0.0;
   out_2975532171405769290[207] = 0.0;
   out_2975532171405769290[208] = 0.0;
   out_2975532171405769290[209] = 1.0;
   out_2975532171405769290[210] = 0.0;
   out_2975532171405769290[211] = 0.0;
   out_2975532171405769290[212] = 0.0;
   out_2975532171405769290[213] = 0.0;
   out_2975532171405769290[214] = 0.0;
   out_2975532171405769290[215] = 0.0;
   out_2975532171405769290[216] = 0.0;
   out_2975532171405769290[217] = 0.0;
   out_2975532171405769290[218] = 0.0;
   out_2975532171405769290[219] = 0.0;
   out_2975532171405769290[220] = 0.0;
   out_2975532171405769290[221] = 0.0;
   out_2975532171405769290[222] = 0.0;
   out_2975532171405769290[223] = 0.0;
   out_2975532171405769290[224] = 0.0;
   out_2975532171405769290[225] = 0.0;
   out_2975532171405769290[226] = 0.0;
   out_2975532171405769290[227] = 0.0;
   out_2975532171405769290[228] = 1.0;
   out_2975532171405769290[229] = 0.0;
   out_2975532171405769290[230] = 0.0;
   out_2975532171405769290[231] = 0.0;
   out_2975532171405769290[232] = 0.0;
   out_2975532171405769290[233] = 0.0;
   out_2975532171405769290[234] = 0.0;
   out_2975532171405769290[235] = 0.0;
   out_2975532171405769290[236] = 0.0;
   out_2975532171405769290[237] = 0.0;
   out_2975532171405769290[238] = 0.0;
   out_2975532171405769290[239] = 0.0;
   out_2975532171405769290[240] = 0.0;
   out_2975532171405769290[241] = 0.0;
   out_2975532171405769290[242] = 0.0;
   out_2975532171405769290[243] = 0.0;
   out_2975532171405769290[244] = 0.0;
   out_2975532171405769290[245] = 0.0;
   out_2975532171405769290[246] = 0.0;
   out_2975532171405769290[247] = 1.0;
   out_2975532171405769290[248] = 0.0;
   out_2975532171405769290[249] = 0.0;
   out_2975532171405769290[250] = 0.0;
   out_2975532171405769290[251] = 0.0;
   out_2975532171405769290[252] = 0.0;
   out_2975532171405769290[253] = 0.0;
   out_2975532171405769290[254] = 0.0;
   out_2975532171405769290[255] = 0.0;
   out_2975532171405769290[256] = 0.0;
   out_2975532171405769290[257] = 0.0;
   out_2975532171405769290[258] = 0.0;
   out_2975532171405769290[259] = 0.0;
   out_2975532171405769290[260] = 0.0;
   out_2975532171405769290[261] = 0.0;
   out_2975532171405769290[262] = 0.0;
   out_2975532171405769290[263] = 0.0;
   out_2975532171405769290[264] = 0.0;
   out_2975532171405769290[265] = 0.0;
   out_2975532171405769290[266] = 1.0;
   out_2975532171405769290[267] = 0.0;
   out_2975532171405769290[268] = 0.0;
   out_2975532171405769290[269] = 0.0;
   out_2975532171405769290[270] = 0.0;
   out_2975532171405769290[271] = 0.0;
   out_2975532171405769290[272] = 0.0;
   out_2975532171405769290[273] = 0.0;
   out_2975532171405769290[274] = 0.0;
   out_2975532171405769290[275] = 0.0;
   out_2975532171405769290[276] = 0.0;
   out_2975532171405769290[277] = 0.0;
   out_2975532171405769290[278] = 0.0;
   out_2975532171405769290[279] = 0.0;
   out_2975532171405769290[280] = 0.0;
   out_2975532171405769290[281] = 0.0;
   out_2975532171405769290[282] = 0.0;
   out_2975532171405769290[283] = 0.0;
   out_2975532171405769290[284] = 0.0;
   out_2975532171405769290[285] = 1.0;
   out_2975532171405769290[286] = 0.0;
   out_2975532171405769290[287] = 0.0;
   out_2975532171405769290[288] = 0.0;
   out_2975532171405769290[289] = 0.0;
   out_2975532171405769290[290] = 0.0;
   out_2975532171405769290[291] = 0.0;
   out_2975532171405769290[292] = 0.0;
   out_2975532171405769290[293] = 0.0;
   out_2975532171405769290[294] = 0.0;
   out_2975532171405769290[295] = 0.0;
   out_2975532171405769290[296] = 0.0;
   out_2975532171405769290[297] = 0.0;
   out_2975532171405769290[298] = 0.0;
   out_2975532171405769290[299] = 0.0;
   out_2975532171405769290[300] = 0.0;
   out_2975532171405769290[301] = 0.0;
   out_2975532171405769290[302] = 0.0;
   out_2975532171405769290[303] = 0.0;
   out_2975532171405769290[304] = 1.0;
   out_2975532171405769290[305] = 0.0;
   out_2975532171405769290[306] = 0.0;
   out_2975532171405769290[307] = 0.0;
   out_2975532171405769290[308] = 0.0;
   out_2975532171405769290[309] = 0.0;
   out_2975532171405769290[310] = 0.0;
   out_2975532171405769290[311] = 0.0;
   out_2975532171405769290[312] = 0.0;
   out_2975532171405769290[313] = 0.0;
   out_2975532171405769290[314] = 0.0;
   out_2975532171405769290[315] = 0.0;
   out_2975532171405769290[316] = 0.0;
   out_2975532171405769290[317] = 0.0;
   out_2975532171405769290[318] = 0.0;
   out_2975532171405769290[319] = 0.0;
   out_2975532171405769290[320] = 0.0;
   out_2975532171405769290[321] = 0.0;
   out_2975532171405769290[322] = 0.0;
   out_2975532171405769290[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1528409513938175977) {
   out_1528409513938175977[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1528409513938175977[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1528409513938175977[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1528409513938175977[3] = dt*state[12] + state[3];
   out_1528409513938175977[4] = dt*state[13] + state[4];
   out_1528409513938175977[5] = dt*state[14] + state[5];
   out_1528409513938175977[6] = state[6];
   out_1528409513938175977[7] = state[7];
   out_1528409513938175977[8] = state[8];
   out_1528409513938175977[9] = state[9];
   out_1528409513938175977[10] = state[10];
   out_1528409513938175977[11] = state[11];
   out_1528409513938175977[12] = state[12];
   out_1528409513938175977[13] = state[13];
   out_1528409513938175977[14] = state[14];
   out_1528409513938175977[15] = state[15];
   out_1528409513938175977[16] = state[16];
   out_1528409513938175977[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3529724907323973828) {
   out_3529724907323973828[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3529724907323973828[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3529724907323973828[2] = 0;
   out_3529724907323973828[3] = 0;
   out_3529724907323973828[4] = 0;
   out_3529724907323973828[5] = 0;
   out_3529724907323973828[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3529724907323973828[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3529724907323973828[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3529724907323973828[9] = 0;
   out_3529724907323973828[10] = 0;
   out_3529724907323973828[11] = 0;
   out_3529724907323973828[12] = 0;
   out_3529724907323973828[13] = 0;
   out_3529724907323973828[14] = 0;
   out_3529724907323973828[15] = 0;
   out_3529724907323973828[16] = 0;
   out_3529724907323973828[17] = 0;
   out_3529724907323973828[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3529724907323973828[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3529724907323973828[20] = 0;
   out_3529724907323973828[21] = 0;
   out_3529724907323973828[22] = 0;
   out_3529724907323973828[23] = 0;
   out_3529724907323973828[24] = 0;
   out_3529724907323973828[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3529724907323973828[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3529724907323973828[27] = 0;
   out_3529724907323973828[28] = 0;
   out_3529724907323973828[29] = 0;
   out_3529724907323973828[30] = 0;
   out_3529724907323973828[31] = 0;
   out_3529724907323973828[32] = 0;
   out_3529724907323973828[33] = 0;
   out_3529724907323973828[34] = 0;
   out_3529724907323973828[35] = 0;
   out_3529724907323973828[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3529724907323973828[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3529724907323973828[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3529724907323973828[39] = 0;
   out_3529724907323973828[40] = 0;
   out_3529724907323973828[41] = 0;
   out_3529724907323973828[42] = 0;
   out_3529724907323973828[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3529724907323973828[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3529724907323973828[45] = 0;
   out_3529724907323973828[46] = 0;
   out_3529724907323973828[47] = 0;
   out_3529724907323973828[48] = 0;
   out_3529724907323973828[49] = 0;
   out_3529724907323973828[50] = 0;
   out_3529724907323973828[51] = 0;
   out_3529724907323973828[52] = 0;
   out_3529724907323973828[53] = 0;
   out_3529724907323973828[54] = 0;
   out_3529724907323973828[55] = 0;
   out_3529724907323973828[56] = 0;
   out_3529724907323973828[57] = 1;
   out_3529724907323973828[58] = 0;
   out_3529724907323973828[59] = 0;
   out_3529724907323973828[60] = 0;
   out_3529724907323973828[61] = 0;
   out_3529724907323973828[62] = 0;
   out_3529724907323973828[63] = 0;
   out_3529724907323973828[64] = 0;
   out_3529724907323973828[65] = 0;
   out_3529724907323973828[66] = dt;
   out_3529724907323973828[67] = 0;
   out_3529724907323973828[68] = 0;
   out_3529724907323973828[69] = 0;
   out_3529724907323973828[70] = 0;
   out_3529724907323973828[71] = 0;
   out_3529724907323973828[72] = 0;
   out_3529724907323973828[73] = 0;
   out_3529724907323973828[74] = 0;
   out_3529724907323973828[75] = 0;
   out_3529724907323973828[76] = 1;
   out_3529724907323973828[77] = 0;
   out_3529724907323973828[78] = 0;
   out_3529724907323973828[79] = 0;
   out_3529724907323973828[80] = 0;
   out_3529724907323973828[81] = 0;
   out_3529724907323973828[82] = 0;
   out_3529724907323973828[83] = 0;
   out_3529724907323973828[84] = 0;
   out_3529724907323973828[85] = dt;
   out_3529724907323973828[86] = 0;
   out_3529724907323973828[87] = 0;
   out_3529724907323973828[88] = 0;
   out_3529724907323973828[89] = 0;
   out_3529724907323973828[90] = 0;
   out_3529724907323973828[91] = 0;
   out_3529724907323973828[92] = 0;
   out_3529724907323973828[93] = 0;
   out_3529724907323973828[94] = 0;
   out_3529724907323973828[95] = 1;
   out_3529724907323973828[96] = 0;
   out_3529724907323973828[97] = 0;
   out_3529724907323973828[98] = 0;
   out_3529724907323973828[99] = 0;
   out_3529724907323973828[100] = 0;
   out_3529724907323973828[101] = 0;
   out_3529724907323973828[102] = 0;
   out_3529724907323973828[103] = 0;
   out_3529724907323973828[104] = dt;
   out_3529724907323973828[105] = 0;
   out_3529724907323973828[106] = 0;
   out_3529724907323973828[107] = 0;
   out_3529724907323973828[108] = 0;
   out_3529724907323973828[109] = 0;
   out_3529724907323973828[110] = 0;
   out_3529724907323973828[111] = 0;
   out_3529724907323973828[112] = 0;
   out_3529724907323973828[113] = 0;
   out_3529724907323973828[114] = 1;
   out_3529724907323973828[115] = 0;
   out_3529724907323973828[116] = 0;
   out_3529724907323973828[117] = 0;
   out_3529724907323973828[118] = 0;
   out_3529724907323973828[119] = 0;
   out_3529724907323973828[120] = 0;
   out_3529724907323973828[121] = 0;
   out_3529724907323973828[122] = 0;
   out_3529724907323973828[123] = 0;
   out_3529724907323973828[124] = 0;
   out_3529724907323973828[125] = 0;
   out_3529724907323973828[126] = 0;
   out_3529724907323973828[127] = 0;
   out_3529724907323973828[128] = 0;
   out_3529724907323973828[129] = 0;
   out_3529724907323973828[130] = 0;
   out_3529724907323973828[131] = 0;
   out_3529724907323973828[132] = 0;
   out_3529724907323973828[133] = 1;
   out_3529724907323973828[134] = 0;
   out_3529724907323973828[135] = 0;
   out_3529724907323973828[136] = 0;
   out_3529724907323973828[137] = 0;
   out_3529724907323973828[138] = 0;
   out_3529724907323973828[139] = 0;
   out_3529724907323973828[140] = 0;
   out_3529724907323973828[141] = 0;
   out_3529724907323973828[142] = 0;
   out_3529724907323973828[143] = 0;
   out_3529724907323973828[144] = 0;
   out_3529724907323973828[145] = 0;
   out_3529724907323973828[146] = 0;
   out_3529724907323973828[147] = 0;
   out_3529724907323973828[148] = 0;
   out_3529724907323973828[149] = 0;
   out_3529724907323973828[150] = 0;
   out_3529724907323973828[151] = 0;
   out_3529724907323973828[152] = 1;
   out_3529724907323973828[153] = 0;
   out_3529724907323973828[154] = 0;
   out_3529724907323973828[155] = 0;
   out_3529724907323973828[156] = 0;
   out_3529724907323973828[157] = 0;
   out_3529724907323973828[158] = 0;
   out_3529724907323973828[159] = 0;
   out_3529724907323973828[160] = 0;
   out_3529724907323973828[161] = 0;
   out_3529724907323973828[162] = 0;
   out_3529724907323973828[163] = 0;
   out_3529724907323973828[164] = 0;
   out_3529724907323973828[165] = 0;
   out_3529724907323973828[166] = 0;
   out_3529724907323973828[167] = 0;
   out_3529724907323973828[168] = 0;
   out_3529724907323973828[169] = 0;
   out_3529724907323973828[170] = 0;
   out_3529724907323973828[171] = 1;
   out_3529724907323973828[172] = 0;
   out_3529724907323973828[173] = 0;
   out_3529724907323973828[174] = 0;
   out_3529724907323973828[175] = 0;
   out_3529724907323973828[176] = 0;
   out_3529724907323973828[177] = 0;
   out_3529724907323973828[178] = 0;
   out_3529724907323973828[179] = 0;
   out_3529724907323973828[180] = 0;
   out_3529724907323973828[181] = 0;
   out_3529724907323973828[182] = 0;
   out_3529724907323973828[183] = 0;
   out_3529724907323973828[184] = 0;
   out_3529724907323973828[185] = 0;
   out_3529724907323973828[186] = 0;
   out_3529724907323973828[187] = 0;
   out_3529724907323973828[188] = 0;
   out_3529724907323973828[189] = 0;
   out_3529724907323973828[190] = 1;
   out_3529724907323973828[191] = 0;
   out_3529724907323973828[192] = 0;
   out_3529724907323973828[193] = 0;
   out_3529724907323973828[194] = 0;
   out_3529724907323973828[195] = 0;
   out_3529724907323973828[196] = 0;
   out_3529724907323973828[197] = 0;
   out_3529724907323973828[198] = 0;
   out_3529724907323973828[199] = 0;
   out_3529724907323973828[200] = 0;
   out_3529724907323973828[201] = 0;
   out_3529724907323973828[202] = 0;
   out_3529724907323973828[203] = 0;
   out_3529724907323973828[204] = 0;
   out_3529724907323973828[205] = 0;
   out_3529724907323973828[206] = 0;
   out_3529724907323973828[207] = 0;
   out_3529724907323973828[208] = 0;
   out_3529724907323973828[209] = 1;
   out_3529724907323973828[210] = 0;
   out_3529724907323973828[211] = 0;
   out_3529724907323973828[212] = 0;
   out_3529724907323973828[213] = 0;
   out_3529724907323973828[214] = 0;
   out_3529724907323973828[215] = 0;
   out_3529724907323973828[216] = 0;
   out_3529724907323973828[217] = 0;
   out_3529724907323973828[218] = 0;
   out_3529724907323973828[219] = 0;
   out_3529724907323973828[220] = 0;
   out_3529724907323973828[221] = 0;
   out_3529724907323973828[222] = 0;
   out_3529724907323973828[223] = 0;
   out_3529724907323973828[224] = 0;
   out_3529724907323973828[225] = 0;
   out_3529724907323973828[226] = 0;
   out_3529724907323973828[227] = 0;
   out_3529724907323973828[228] = 1;
   out_3529724907323973828[229] = 0;
   out_3529724907323973828[230] = 0;
   out_3529724907323973828[231] = 0;
   out_3529724907323973828[232] = 0;
   out_3529724907323973828[233] = 0;
   out_3529724907323973828[234] = 0;
   out_3529724907323973828[235] = 0;
   out_3529724907323973828[236] = 0;
   out_3529724907323973828[237] = 0;
   out_3529724907323973828[238] = 0;
   out_3529724907323973828[239] = 0;
   out_3529724907323973828[240] = 0;
   out_3529724907323973828[241] = 0;
   out_3529724907323973828[242] = 0;
   out_3529724907323973828[243] = 0;
   out_3529724907323973828[244] = 0;
   out_3529724907323973828[245] = 0;
   out_3529724907323973828[246] = 0;
   out_3529724907323973828[247] = 1;
   out_3529724907323973828[248] = 0;
   out_3529724907323973828[249] = 0;
   out_3529724907323973828[250] = 0;
   out_3529724907323973828[251] = 0;
   out_3529724907323973828[252] = 0;
   out_3529724907323973828[253] = 0;
   out_3529724907323973828[254] = 0;
   out_3529724907323973828[255] = 0;
   out_3529724907323973828[256] = 0;
   out_3529724907323973828[257] = 0;
   out_3529724907323973828[258] = 0;
   out_3529724907323973828[259] = 0;
   out_3529724907323973828[260] = 0;
   out_3529724907323973828[261] = 0;
   out_3529724907323973828[262] = 0;
   out_3529724907323973828[263] = 0;
   out_3529724907323973828[264] = 0;
   out_3529724907323973828[265] = 0;
   out_3529724907323973828[266] = 1;
   out_3529724907323973828[267] = 0;
   out_3529724907323973828[268] = 0;
   out_3529724907323973828[269] = 0;
   out_3529724907323973828[270] = 0;
   out_3529724907323973828[271] = 0;
   out_3529724907323973828[272] = 0;
   out_3529724907323973828[273] = 0;
   out_3529724907323973828[274] = 0;
   out_3529724907323973828[275] = 0;
   out_3529724907323973828[276] = 0;
   out_3529724907323973828[277] = 0;
   out_3529724907323973828[278] = 0;
   out_3529724907323973828[279] = 0;
   out_3529724907323973828[280] = 0;
   out_3529724907323973828[281] = 0;
   out_3529724907323973828[282] = 0;
   out_3529724907323973828[283] = 0;
   out_3529724907323973828[284] = 0;
   out_3529724907323973828[285] = 1;
   out_3529724907323973828[286] = 0;
   out_3529724907323973828[287] = 0;
   out_3529724907323973828[288] = 0;
   out_3529724907323973828[289] = 0;
   out_3529724907323973828[290] = 0;
   out_3529724907323973828[291] = 0;
   out_3529724907323973828[292] = 0;
   out_3529724907323973828[293] = 0;
   out_3529724907323973828[294] = 0;
   out_3529724907323973828[295] = 0;
   out_3529724907323973828[296] = 0;
   out_3529724907323973828[297] = 0;
   out_3529724907323973828[298] = 0;
   out_3529724907323973828[299] = 0;
   out_3529724907323973828[300] = 0;
   out_3529724907323973828[301] = 0;
   out_3529724907323973828[302] = 0;
   out_3529724907323973828[303] = 0;
   out_3529724907323973828[304] = 1;
   out_3529724907323973828[305] = 0;
   out_3529724907323973828[306] = 0;
   out_3529724907323973828[307] = 0;
   out_3529724907323973828[308] = 0;
   out_3529724907323973828[309] = 0;
   out_3529724907323973828[310] = 0;
   out_3529724907323973828[311] = 0;
   out_3529724907323973828[312] = 0;
   out_3529724907323973828[313] = 0;
   out_3529724907323973828[314] = 0;
   out_3529724907323973828[315] = 0;
   out_3529724907323973828[316] = 0;
   out_3529724907323973828[317] = 0;
   out_3529724907323973828[318] = 0;
   out_3529724907323973828[319] = 0;
   out_3529724907323973828[320] = 0;
   out_3529724907323973828[321] = 0;
   out_3529724907323973828[322] = 0;
   out_3529724907323973828[323] = 1;
}
void h_4(double *state, double *unused, double *out_3668973491572904971) {
   out_3668973491572904971[0] = state[6] + state[9];
   out_3668973491572904971[1] = state[7] + state[10];
   out_3668973491572904971[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2872549635346189431) {
   out_2872549635346189431[0] = 0;
   out_2872549635346189431[1] = 0;
   out_2872549635346189431[2] = 0;
   out_2872549635346189431[3] = 0;
   out_2872549635346189431[4] = 0;
   out_2872549635346189431[5] = 0;
   out_2872549635346189431[6] = 1;
   out_2872549635346189431[7] = 0;
   out_2872549635346189431[8] = 0;
   out_2872549635346189431[9] = 1;
   out_2872549635346189431[10] = 0;
   out_2872549635346189431[11] = 0;
   out_2872549635346189431[12] = 0;
   out_2872549635346189431[13] = 0;
   out_2872549635346189431[14] = 0;
   out_2872549635346189431[15] = 0;
   out_2872549635346189431[16] = 0;
   out_2872549635346189431[17] = 0;
   out_2872549635346189431[18] = 0;
   out_2872549635346189431[19] = 0;
   out_2872549635346189431[20] = 0;
   out_2872549635346189431[21] = 0;
   out_2872549635346189431[22] = 0;
   out_2872549635346189431[23] = 0;
   out_2872549635346189431[24] = 0;
   out_2872549635346189431[25] = 1;
   out_2872549635346189431[26] = 0;
   out_2872549635346189431[27] = 0;
   out_2872549635346189431[28] = 1;
   out_2872549635346189431[29] = 0;
   out_2872549635346189431[30] = 0;
   out_2872549635346189431[31] = 0;
   out_2872549635346189431[32] = 0;
   out_2872549635346189431[33] = 0;
   out_2872549635346189431[34] = 0;
   out_2872549635346189431[35] = 0;
   out_2872549635346189431[36] = 0;
   out_2872549635346189431[37] = 0;
   out_2872549635346189431[38] = 0;
   out_2872549635346189431[39] = 0;
   out_2872549635346189431[40] = 0;
   out_2872549635346189431[41] = 0;
   out_2872549635346189431[42] = 0;
   out_2872549635346189431[43] = 0;
   out_2872549635346189431[44] = 1;
   out_2872549635346189431[45] = 0;
   out_2872549635346189431[46] = 0;
   out_2872549635346189431[47] = 1;
   out_2872549635346189431[48] = 0;
   out_2872549635346189431[49] = 0;
   out_2872549635346189431[50] = 0;
   out_2872549635346189431[51] = 0;
   out_2872549635346189431[52] = 0;
   out_2872549635346189431[53] = 0;
}
void h_10(double *state, double *unused, double *out_7370234972326288681) {
   out_7370234972326288681[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7370234972326288681[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7370234972326288681[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2473329072195742474) {
   out_2473329072195742474[0] = 0;
   out_2473329072195742474[1] = 9.8100000000000005*cos(state[1]);
   out_2473329072195742474[2] = 0;
   out_2473329072195742474[3] = 0;
   out_2473329072195742474[4] = -state[8];
   out_2473329072195742474[5] = state[7];
   out_2473329072195742474[6] = 0;
   out_2473329072195742474[7] = state[5];
   out_2473329072195742474[8] = -state[4];
   out_2473329072195742474[9] = 0;
   out_2473329072195742474[10] = 0;
   out_2473329072195742474[11] = 0;
   out_2473329072195742474[12] = 1;
   out_2473329072195742474[13] = 0;
   out_2473329072195742474[14] = 0;
   out_2473329072195742474[15] = 1;
   out_2473329072195742474[16] = 0;
   out_2473329072195742474[17] = 0;
   out_2473329072195742474[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2473329072195742474[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2473329072195742474[20] = 0;
   out_2473329072195742474[21] = state[8];
   out_2473329072195742474[22] = 0;
   out_2473329072195742474[23] = -state[6];
   out_2473329072195742474[24] = -state[5];
   out_2473329072195742474[25] = 0;
   out_2473329072195742474[26] = state[3];
   out_2473329072195742474[27] = 0;
   out_2473329072195742474[28] = 0;
   out_2473329072195742474[29] = 0;
   out_2473329072195742474[30] = 0;
   out_2473329072195742474[31] = 1;
   out_2473329072195742474[32] = 0;
   out_2473329072195742474[33] = 0;
   out_2473329072195742474[34] = 1;
   out_2473329072195742474[35] = 0;
   out_2473329072195742474[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2473329072195742474[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2473329072195742474[38] = 0;
   out_2473329072195742474[39] = -state[7];
   out_2473329072195742474[40] = state[6];
   out_2473329072195742474[41] = 0;
   out_2473329072195742474[42] = state[4];
   out_2473329072195742474[43] = -state[3];
   out_2473329072195742474[44] = 0;
   out_2473329072195742474[45] = 0;
   out_2473329072195742474[46] = 0;
   out_2473329072195742474[47] = 0;
   out_2473329072195742474[48] = 0;
   out_2473329072195742474[49] = 0;
   out_2473329072195742474[50] = 1;
   out_2473329072195742474[51] = 0;
   out_2473329072195742474[52] = 0;
   out_2473329072195742474[53] = 1;
}
void h_13(double *state, double *unused, double *out_2115791500742660878) {
   out_2115791500742660878[0] = state[3];
   out_2115791500742660878[1] = state[4];
   out_2115791500742660878[2] = state[5];
}
void H_13(double *state, double *unused, double *out_339724189986143370) {
   out_339724189986143370[0] = 0;
   out_339724189986143370[1] = 0;
   out_339724189986143370[2] = 0;
   out_339724189986143370[3] = 1;
   out_339724189986143370[4] = 0;
   out_339724189986143370[5] = 0;
   out_339724189986143370[6] = 0;
   out_339724189986143370[7] = 0;
   out_339724189986143370[8] = 0;
   out_339724189986143370[9] = 0;
   out_339724189986143370[10] = 0;
   out_339724189986143370[11] = 0;
   out_339724189986143370[12] = 0;
   out_339724189986143370[13] = 0;
   out_339724189986143370[14] = 0;
   out_339724189986143370[15] = 0;
   out_339724189986143370[16] = 0;
   out_339724189986143370[17] = 0;
   out_339724189986143370[18] = 0;
   out_339724189986143370[19] = 0;
   out_339724189986143370[20] = 0;
   out_339724189986143370[21] = 0;
   out_339724189986143370[22] = 1;
   out_339724189986143370[23] = 0;
   out_339724189986143370[24] = 0;
   out_339724189986143370[25] = 0;
   out_339724189986143370[26] = 0;
   out_339724189986143370[27] = 0;
   out_339724189986143370[28] = 0;
   out_339724189986143370[29] = 0;
   out_339724189986143370[30] = 0;
   out_339724189986143370[31] = 0;
   out_339724189986143370[32] = 0;
   out_339724189986143370[33] = 0;
   out_339724189986143370[34] = 0;
   out_339724189986143370[35] = 0;
   out_339724189986143370[36] = 0;
   out_339724189986143370[37] = 0;
   out_339724189986143370[38] = 0;
   out_339724189986143370[39] = 0;
   out_339724189986143370[40] = 0;
   out_339724189986143370[41] = 1;
   out_339724189986143370[42] = 0;
   out_339724189986143370[43] = 0;
   out_339724189986143370[44] = 0;
   out_339724189986143370[45] = 0;
   out_339724189986143370[46] = 0;
   out_339724189986143370[47] = 0;
   out_339724189986143370[48] = 0;
   out_339724189986143370[49] = 0;
   out_339724189986143370[50] = 0;
   out_339724189986143370[51] = 0;
   out_339724189986143370[52] = 0;
   out_339724189986143370[53] = 0;
}
void h_14(double *state, double *unused, double *out_4699950938202754957) {
   out_4699950938202754957[0] = state[6];
   out_4699950938202754957[1] = state[7];
   out_4699950938202754957[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1090691220993295098) {
   out_1090691220993295098[0] = 0;
   out_1090691220993295098[1] = 0;
   out_1090691220993295098[2] = 0;
   out_1090691220993295098[3] = 0;
   out_1090691220993295098[4] = 0;
   out_1090691220993295098[5] = 0;
   out_1090691220993295098[6] = 1;
   out_1090691220993295098[7] = 0;
   out_1090691220993295098[8] = 0;
   out_1090691220993295098[9] = 0;
   out_1090691220993295098[10] = 0;
   out_1090691220993295098[11] = 0;
   out_1090691220993295098[12] = 0;
   out_1090691220993295098[13] = 0;
   out_1090691220993295098[14] = 0;
   out_1090691220993295098[15] = 0;
   out_1090691220993295098[16] = 0;
   out_1090691220993295098[17] = 0;
   out_1090691220993295098[18] = 0;
   out_1090691220993295098[19] = 0;
   out_1090691220993295098[20] = 0;
   out_1090691220993295098[21] = 0;
   out_1090691220993295098[22] = 0;
   out_1090691220993295098[23] = 0;
   out_1090691220993295098[24] = 0;
   out_1090691220993295098[25] = 1;
   out_1090691220993295098[26] = 0;
   out_1090691220993295098[27] = 0;
   out_1090691220993295098[28] = 0;
   out_1090691220993295098[29] = 0;
   out_1090691220993295098[30] = 0;
   out_1090691220993295098[31] = 0;
   out_1090691220993295098[32] = 0;
   out_1090691220993295098[33] = 0;
   out_1090691220993295098[34] = 0;
   out_1090691220993295098[35] = 0;
   out_1090691220993295098[36] = 0;
   out_1090691220993295098[37] = 0;
   out_1090691220993295098[38] = 0;
   out_1090691220993295098[39] = 0;
   out_1090691220993295098[40] = 0;
   out_1090691220993295098[41] = 0;
   out_1090691220993295098[42] = 0;
   out_1090691220993295098[43] = 0;
   out_1090691220993295098[44] = 1;
   out_1090691220993295098[45] = 0;
   out_1090691220993295098[46] = 0;
   out_1090691220993295098[47] = 0;
   out_1090691220993295098[48] = 0;
   out_1090691220993295098[49] = 0;
   out_1090691220993295098[50] = 0;
   out_1090691220993295098[51] = 0;
   out_1090691220993295098[52] = 0;
   out_1090691220993295098[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6475098180663358236) {
  err_fun(nom_x, delta_x, out_6475098180663358236);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2585492389743957981) {
  inv_err_fun(nom_x, true_x, out_2585492389743957981);
}
void pose_H_mod_fun(double *state, double *out_2975532171405769290) {
  H_mod_fun(state, out_2975532171405769290);
}
void pose_f_fun(double *state, double dt, double *out_1528409513938175977) {
  f_fun(state,  dt, out_1528409513938175977);
}
void pose_F_fun(double *state, double dt, double *out_3529724907323973828) {
  F_fun(state,  dt, out_3529724907323973828);
}
void pose_h_4(double *state, double *unused, double *out_3668973491572904971) {
  h_4(state, unused, out_3668973491572904971);
}
void pose_H_4(double *state, double *unused, double *out_2872549635346189431) {
  H_4(state, unused, out_2872549635346189431);
}
void pose_h_10(double *state, double *unused, double *out_7370234972326288681) {
  h_10(state, unused, out_7370234972326288681);
}
void pose_H_10(double *state, double *unused, double *out_2473329072195742474) {
  H_10(state, unused, out_2473329072195742474);
}
void pose_h_13(double *state, double *unused, double *out_2115791500742660878) {
  h_13(state, unused, out_2115791500742660878);
}
void pose_H_13(double *state, double *unused, double *out_339724189986143370) {
  H_13(state, unused, out_339724189986143370);
}
void pose_h_14(double *state, double *unused, double *out_4699950938202754957) {
  h_14(state, unused, out_4699950938202754957);
}
void pose_H_14(double *state, double *unused, double *out_1090691220993295098) {
  H_14(state, unused, out_1090691220993295098);
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
