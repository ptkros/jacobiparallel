//
//  main.cpp
//  JacobiParallel
//
//  Created by Patrik Rosini on 30/03/2016.
//  Copyright © 2016 Patrik Rosini. All rights reserved.
//

#include "utils.h"
#include "algos.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <cctype>
#include "ff/utils.hpp"

using namespace std;
using namespace ff;

int main(int argc, const char * argv[]) {
    
    if (argc < 5) {
        cerr << "Use: " << argv[0] << " nworkers chunk lsyspathname|lsysdim version=p|l [errtolerance=10^-10]" << endl;
        cerr << "Example: " << argv[0] << " 2 0 ~/Desktop/lsys.txt" << endl;
        cerr << "--------------------lsys.txt----------------------" << endl;
        cerr << "\t189.749 29.1484 97.351 = 79.0176\n\t48.36 203.086 87.0305 = 21.992\n\t19.2312 19.1234 57.532 = 7.78229"<< endl;
        cerr << "--------------------lsys.txt----------------------" << endl;
        return -1;
    }
    
    double lambda = 0.0;
    double rho = 0.0;
    double time = 0.0;
    double tol = 0.0000000001;
    double *h_A = NULL;
    double *h_b = NULL;
    double *h_x = NULL;
    double *h_y = NULL;
    int i = 0;
    int d = 0;
    int nworkers = atoi(argv[1]);
    int chunk = atoi(argv[2]);
    string path_name(argv[3]);
    string version(argv[4]);
    
    if(argc == 6){
        tol = atof(argv[5]);
    }
    
    // Get matrix's dimension
    
    if(isdigit(argv[3][0])){
        d = atoi(argv[3]);
        h_A = new double[d*d];
        h_b = new double[d];
        
        // Linear system generation
        
        lsys_gen(h_A, h_b, d);
    }
    else{
        
        // Read matrix's dimension
        
        if(lsys_dim(path_name, d) == -1){
            exit(EXIT_FAILURE);
        }
        
        h_A = new double[d*d];
        h_b = new double[d];
        
        // Linear system reading
        
        if(lsys_read(path_name, h_A, h_b, d) == -1){
            exit(EXIT_FAILURE);
        }
        
    }
    
    // Check matrix diagonally dominant
    
    lambda = diag_dom(h_A, d);
    
    if (lambda >= 1){
        cerr << "Matrix is not diagonally dominant!" << endl;
        exit(EXIT_FAILURE);
    }
        
    h_x = new double[d];
    h_y = new double[d];
    
        
    // Initial solutions vector as null
    
    for (i=0; i<d; i++)
        h_x[i] = 0.0;
    
    // Jacobi
    
    if(version.compare("p") == 0){
        
        jacobip(nworkers,chunk,h_A,h_b,h_x,h_y,tol,lambda,rho,time,d);
        
    }
    else if(version.compare("l") == 0){
        
        jacobil(h_A,h_b,h_x,h_y,tol,lambda,rho,time,d);
        
    }
    else{
        cerr << "Bad Jacobi version!";
        exit(EXIT_FAILURE);
    }

    cout << "Linear system vars: " << d << endl;
    cout << "Time: "<< time << " ms" << endl;
    cout << "Tolerance: " << tol << endl;
    cout << "Iterations: " << (int)rho << endl;
    cout << endl;
    cout << "Solutions: " << endl;
    for (i=0; i<d; i++) {
        cout << "x" << i+1 << ": " << h_x[i] << endl;
    }
    
    delete[] h_A;
    delete[] h_b;
    delete[] h_x;
    delete[] h_y;
    
    return 0;
}
