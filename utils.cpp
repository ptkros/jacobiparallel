//
//  utils.cpp
//  JacobiParallel
//
//  Created by Patrik Rosini on 08/04/2016.
//  Copyright © 2016 Patrik Rosini. All rights reserved.
//

#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate linear system

void lsys_gen(double *h_A, double *h_b, int d){
    
    int i = 0;
    int j = 0;
    
    srand(time(NULL));
    
    for(i=0; i<d; i++){
        
        double temp = 0.0;
        
        for(j=0; j<d; j++){
            
            if( i != j){
                
                h_A[i*d+j] = ((double)rand()/(double)RAND_MAX)*100.;
                temp += h_A[i*d+j];
            }
        }
        
        h_A[i*d+i] = temp*1.25;
        //h_A[i*d+i] = temp+((double)rand()/(double)RAND_MAX)*100.;
        h_b[i] = ((double)rand()/(double)RAND_MAX)*100.;
    }
        
}

// Function to read linear system dimension

int lsys_dim(string path_name, int &d){
    
    int ldj = 0;
    int ldi = 0;
    ifstream lsys(path_name);
    
    if(!lsys){
        cerr << "File is not open!" << endl;
        return -1;
    }
    
    while (!lsys.eof()) {
        
        string svalue;
        
        getline(lsys, svalue, ' ');
        
        if(svalue != "="){
            ldj++;
        }
        else if(svalue == "="){
            getline(lsys, svalue);
            ldi++;
        }
        
    }
    
    ldj = sqrt(ldj);
    
    if (ldj != ldi) {
        cerr << "Matrix is not square!" << endl;
        return -1;
    }
    
    d = ldj;

    lsys.close();
    
    return 0;
}


// Function to read linear system from .txt

int lsys_read(string path_name, double *h_A, double *h_b, int d){
    
    int i=0;
    int j=0;
    ifstream lsys(path_name);
    
    if(!lsys){
        cerr << "File is not open!" << endl;
        return -1;
    }
    
    cout << "Linear system reading..." << endl;
    
    while (!lsys.eof()) {
    
        string svalue;
        
        getline(lsys, svalue, ' ');
        
        if(svalue != "="){
            h_A[i*d+j] = stod(svalue, NULL);
            j++;
        }
        else if(svalue == "="){
            getline(lsys, svalue);
            h_b[i] = stod(svalue, NULL);
            i++;
            j=0;
        }
        
    }
    
    cout << "Linear system read" << endl;
    
    lsys.close();
    
    return 0;
}

