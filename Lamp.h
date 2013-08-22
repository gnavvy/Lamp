// C++ implementation of "Local Affine Multidimensional Projection"
// http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=6065024
// Paper Author: P.Joia, F.V Paulovich, D.Coimbra, J.A.Cuminato, & L.G.Nonato
// Author: Y.Wang  (ywang@ucdavis.com)

#ifndef LAMP_H
#define LAMP_H

#include <armadillo>

using namespace std;
using namespace arma;

class Lamp {
public:
    Lamp(int m, int d, int k, int r);

    void project(const vector<double> &seed,      // input:  seed points from R^m
                 const vector<double> &projSeed,  // input:  projection of seed points in R^r
                 const vector<double> &data,      // input:  data points in R^m
                 vector<double> &projData);       // output: projected data in R^r

private:
    int numData;    // number of data points in high dimensional space
    int numSeed;    // number of seed points selected from the dataset
    int numDataDim; // number of dimension in high dimensional space
    int numProjDim; // number of dimension in projected visual space
};

#endif // LAMP_H
