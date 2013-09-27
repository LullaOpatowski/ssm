/**************************************************************************
 *    This file is part of ssm.
 *
 *    ssm is free software: you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published
 *    by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    ssm is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public
 *    License along with ssm.  If not, see
 *    <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include "ssm.h"

double f_id(double x)
{
    return x;
}


double f_log(double x)
{
    double safe = ( x > SSM_ZERO_LOG ) ? x : SSM_ZERO_LOG;
    return log(safe);
}

double f_inv_log(double x)
{
    return exp(x);
}

double f_logit(double x)
{
    //sanatize
    double safe = ( x > SSM_ZERO_LOG ) ? x : SSM_ZERO_LOG;
    safe = (safe < SSM_ONE_LOGIT ) ? safe : SSM_ONE_LOGIT;

    return log(safe/(1.0-safe));
}


double f_inv_logit(double x)
{
    if (x > 0) {
	return (1.0/(1.0+exp(-x)));
    } else {
	return (exp(x)/(1.0+exp(x)));
    }
}



double f_logit_ab(double x, double a, double b)
{
    if (a == b)
        return x; // nothing will happen in the transformed space for x, so no need to transform it
    else{
	double ratio = (x-a)/(b-x);
	if(ratio < SSM_ZERO_LOG){
	    ratio = SSM_ZERO_LOG;
	} else if(ratio > (1.0/SSM_ZERO_LOG)) {
	    ratio = 1.0/SSM_ZERO_LOG;
	}
	return log(ratio);
    }
}


double f_inv_logit_ab(double x, double a, double b)
{
    if (a == b) {
        return x ;
    } else {
	if (x < 0) {
	    return (b*exp(x)+a)/(1.0+exp(x));
	} else {
	    return (b+a*exp(-x))/(1.0+exp(-x));
	};
    } 
}



/**
 * derivative of f_log
 */
double f_der_log(double x)
{
    return 1.0/x;
}



/**
 * derivative of f_inv_log
 */
double f_der_inv_log(double x)
{
    return exp(x);
}


/**
 * derivative of f_logit
 */
double f_der_logit(double x)
{
    return 1.0/(x-x*x);
}

/**
 * derivative of f_inv_logit
 */
double f_der_inv_logit(double x)
{
    if (x > 0) {
	return exp(-x)/pow(1.0 + exp(-x), 2.0);
    } else {
	return exp(x)/pow(1.0 + exp(x), 2.0);
    }
}

/**
 * derivative of f_logit_ab
 */
double f_der_logit_ab(double x, double a, double b)
{
    if (a == b) {
        return x ;
    } else {
        return (b-a)/((x-a)*(b-x));
    }
}

/**
 * derivative of f_inv_logit_ab
 */
double f_der_inv_logit_ab(double x, double a, double b)
{
    if (a == b) {
        return x ;
    } else {
	if (x > 0) {
	    return (b-a)*exp(-x)/pow(exp(-x) + 1.0, 2.0);
	} else {
	    return (b-a)*exp(x)/pow(exp(x) + 1.0, 2.0);
	}
    }
}


double f_user_par_id(double x, ssm_input_t *par, ssm_calc_t *calc)
{
    return x;
}
