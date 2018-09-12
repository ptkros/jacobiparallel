//
//  algos.h
//  JacobiParallel
//
//  Created by Patrik Rosini on 20/04/2016.
//  Copyright © 2016 Patrik Rosini. All rights reserved.
//

#ifndef algos_h
#define algos_h

void jacobip(int nworkers, int chunk, double *h_A, double *h_b, double *h_x, double *h_y, double tol, double lambda, double &rho, double &time, int d);
void jacobil(double *h_A, double *h_b, double *h_x, double *h_y, double tol, double lambda, double &rho, double &time, int d);
double diag_dom(double *h_A, int d);

#endif /* algos_h */
