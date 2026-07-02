#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6475098180663358236);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2585492389743957981);
void pose_H_mod_fun(double *state, double *out_2975532171405769290);
void pose_f_fun(double *state, double dt, double *out_1528409513938175977);
void pose_F_fun(double *state, double dt, double *out_3529724907323973828);
void pose_h_4(double *state, double *unused, double *out_3668973491572904971);
void pose_H_4(double *state, double *unused, double *out_2872549635346189431);
void pose_h_10(double *state, double *unused, double *out_7370234972326288681);
void pose_H_10(double *state, double *unused, double *out_2473329072195742474);
void pose_h_13(double *state, double *unused, double *out_2115791500742660878);
void pose_H_13(double *state, double *unused, double *out_339724189986143370);
void pose_h_14(double *state, double *unused, double *out_4699950938202754957);
void pose_H_14(double *state, double *unused, double *out_1090691220993295098);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}