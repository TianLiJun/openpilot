#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_572765048651206919);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1868650952314995446);
void car_H_mod_fun(double *state, double *out_8123154871421490104);
void car_f_fun(double *state, double dt, double *out_8032845832033412475);
void car_F_fun(double *state, double dt, double *out_6325878182416727548);
void car_h_25(double *state, double *unused, double *out_401556959086496555);
void car_H_25(double *state, double *unused, double *out_1130400976375824275);
void car_h_24(double *state, double *unused, double *out_1379898055622992501);
void car_H_24(double *state, double *unused, double *out_2818217412244928466);
void car_h_30(double *state, double *unused, double *out_4509112446954835751);
void car_H_30(double *state, double *unused, double *out_3648733934883072902);
void car_h_26(double *state, double *unused, double *out_3905796562278358234);
void car_H_26(double *state, double *unused, double *out_2611102342498231949);
void car_h_27(double *state, double *unused, double *out_7818440152816886473);
void car_H_27(double *state, double *unused, double *out_5872328006067016119);
void car_h_29(double *state, double *unused, double *out_4063442402018482614);
void car_H_29(double *state, double *unused, double *out_4158965279197465086);
void car_h_28(double *state, double *unused, double *out_8421756037493363990);
void car_H_28(double *state, double *unused, double *out_923433737872065488);
void car_h_31(double *state, double *unused, double *out_820682643097981522);
void car_H_31(double *state, double *unused, double *out_3237310444731583425);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}