//
//  algos.cpp
//  JacobiParallel
//
//  Created by Patrik Rosini on 20/04/2016.
//  Copyright © 2016 Patrik Rosini. All rights reserved.
//

#include "algos.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "ff/parallel_for.hpp"
#include <sys/time.h>

using namespace std;
using namespace ff;

// Jacobi parallel

void jacobip(int nworkers, int chunk, double *h_A, double *h_b, double *h_x, double *h_y, double tol, double lambda, double &rho, double &time, int d){
    
    int iter = 0;
    double delta = 0.0;
    double *lh_x = new double[d];
    
    
    // Norm evaluation (reduce function)
    
    auto norm = [](double &delta, const double &elem) {
        delta += elem;

    };
    
    ParallelForReduce<double> pfr(nworkers,true);
    
    cout << "Jacobi parallel started..." << endl;
    ffTime(START_TIME);
    do{
        
        pfr.parallel_reduce(delta, 0.0, 0, d, 1, chunk, [&delta,h_A,h_b,h_x,lh_x,h_y,d](const long i, double &delta){

            // Copy sol vector to local partial sol vector
            
            lh_x[i] = h_x[i];
            
            // Copy RHS terms
            
            h_y[i] = h_b[i];
            
            // Root evaluation at step k

            #ifdef  ORIG
            int j=0;
            for(j=0; j<d; j++){
                
                h_y[i] = h_y[i] - (h_A[i*d+j]*lh_x[j]);
            
            }
            #endif
            #ifdef  VRED
            double dotprod = 0.0;
            dotprod = __sec_reduce_add(h_A[i*d:d] * lh_x[0:d]);
            h_y[i] = h_y[i] - dotprod;
            #endif
            
            h_y[i] = (h_y[i]+(h_A[i*d+i]*lh_x[i])) / h_A[i*d+i];
            
            // Partial error coefficient evaluation
            
            delta += (fabs(pow((h_y[i] - h_x[i]), 2.0)));
            
            // Update partial solutions vector
            
            h_x[i] = h_y[i];
            
        }, norm);
        
        // Max iterations estimation
        
        delta = sqrt(delta);
        rho = (log(tol*((1.0 - lambda)/delta)) / log(lambda));
        
        // Iterations counter
        
        iter++;
        
    }
    while(iter < rho);
    ffTime(STOP_TIME);
    time += ffTime(GET_TIME);
    cout << "Jacobi parallel ended" << endl;
    
    delete[] lh_x;
    
    return;
    
}

// Jacobi legacy

void jacobil(double *h_A, double *h_b, double *h_x, double *h_y, double tol, double lambda, double &rho, double &time, int d){
    
    int iter = 0;
    double delta = 0.0;
    
    cout << "Jacobi legacy started..." << endl;
    ffTime(START_TIME);
    do{
        int i=0;
        for(i=0; i<d; i++) {
            
            // Copy RHS terms
            
            h_y[i] = h_b[i];
        
            // Root evaluation at step k

            #ifdef  ORIG
            int j=0;
            for(j=0; j<d; j++){
                
                h_y[i] = h_y[i] - (h_A[i*d+j]*h_x[j]);
                
            }
            #endif
            #ifdef  VRED
            double dotprod = 0.0;
            dotprod = __sec_reduce_add(h_A[i*d:d] * h_x[0:d]);
            h_y[i] = h_y[i] - dotprod;
            #endif
            
            h_y[i] = (h_y[i]+(h_A[i*d+i]*h_x[i])) / h_A[i*d+i];
            
            // Error coefficient evaluation
            
            delta += (fabs(pow((h_y[i] - h_x[i]), 2.0)));
  
            // Update solutions vector
            
            h_x[i] = h_y[i];
            
        }
        
        // Max iterations estimation
        
        delta = sqrt(delta);
        rho = (log(tol*((1.0 - lambda)/delta)) / log(lambda));
        
        // Iterations counter
        
        iter++;
    }
    while(iter < rho);
    ffTime(STOP_TIME);
    time += ffTime(GET_TIME);
    cout << "Jacobi legacy ended" << endl;
    
    return;
    
}

// Diagonally dominant evaluation

double diag_dom(double *h_A, int d){
    
    double lambda = 0.0;
    
    int i=0;
    for(i=0; i<d; i++){
        
        double sum = 0.0;
        
        int j=0;
        for(j=0; j<d; j++){
            
            if(i != j)
                sum = sum + (fabs(h_A[i*d+j]));
        }
        
        sum = sum / fabs(h_A[i*d+i]);
        
        // Check if ratio > 0
        
        if(lambda < sum)
            lambda = sum;
        
    }
    
    return lambda;
    
}