#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3576604326285445174);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_496602688636603974);
void pose_H_mod_fun(double *state, double *out_2198066657604437951);
void pose_f_fun(double *state, double dt, double *out_3966114934127565362);
void pose_F_fun(double *state, double dt, double *out_5076573913221290856);
void pose_h_4(double *state, double *unused, double *out_6142098143209384501);
void pose_H_4(double *state, double *unused, double *out_2269303973952347607);
void pose_h_10(double *state, double *unused, double *out_8285425693527011599);
void pose_H_10(double *state, double *unused, double *out_1179697727219865805);
void pose_h_13(double *state, double *unused, double *out_5990382156794574262);
void pose_H_13(double *state, double *unused, double *out_942969851379985194);
void pose_h_14(double *state, double *unused, double *out_7430784843815807548);
void pose_H_14(double *state, double *unused, double *out_1693936882387136922);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}