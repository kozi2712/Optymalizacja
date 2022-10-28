#pragma once

#include"ode_solver.h"

matrix ff1T(matrix x, matrix ud1, matrix ud2);

matrix df1(double t, matrix Y, matrix ud1, matrix ud2);

matrix FR(matrix x, matrix ud1, matrix ud2);
