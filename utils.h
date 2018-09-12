//
//  utils.h
//  JacobiParallel
//
//  Created by Patrik Rosini on 08/04/2016.
//  Copyright © 2016 Patrik Rosini. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <string>

using namespace std;

void lsys_gen(double *h_A, double *h_b, int d);
int lsys_dim(string path_name, int &d);
int lsys_read(string path_name, double *h_A, double *h_b, int d);

#endif /* utils_h */
