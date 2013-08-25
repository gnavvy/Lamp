#include "Lamp.h"

Lamp::Lamp(int m, int d, int k, int r) {
    numData = m;
    numDataDim = d;
    numSeed = k;
    numProjDim = r;
}

void Lamp::project(const vector<double> &seed, const vector<double> &projSeed,
                   const vector<double> &data, vector<double> &projData) {
    int m = numData;
    int d = numDataDim;
    int k = numSeed;
    int r = numProjDim;

    projData.resize(m, 0.0);

    vec alpha(k); alpha.fill(0.0);
    for (int p = 0; p < m; p++) {  // for each data point
        vector<double> xvec(data.begin()+p*d, data.begin()+p*d+d);
        vec x(xvec);
        vec xsum(d); xsum.fill(0.0);
        vec ysum(r); ysum.fill(0.0);
        vec xtilde(d), ytilde(r);
        //==============================================================
        // STEP 1: compute weights alpha(i), xtilde, ytilde
        //==============================================================
        bool coincide = false;
        double alphasum = 0.0;
        for (int s = 0; s < k; s++) {
            // copy feature vector of each seed point to corresponding vector
            vector<double> seedOrigVec(seed.begin()+s*d, seed.begin()+(s+1)*d);
            vector<double> seedProjVec(projSeed.begin()+s*r, projSeed.begin()+(s+1)*r);
            vec xseed(seedOrigVec);
            vec yseed(seedProjVec);
            // compute weight alpha for each seed
            for (int i = 0; i < d; i++) {
                double delta = x(i) - xseed(i);
                alpha(s) += delta * delta;
            }
            // copy feature directly if a point is coincident to the seed point
            if (alpha(s) == 0.0) {
                for (int i = 0; i < r; i++)
                    projData[p*r+i] = seedProjVec[i];
                coincide = true;
                break;
            }
            // equation (2)
            alpha(s) = 1.0/alpha(s);
            // for equation (3)
            alphasum += alpha(s);
            xseed *= alpha(s);
            xsum += xseed;
            yseed *= alpha(s);
            ysum += yseed;
        }
        if (coincide) continue;
        // equation (3)
        xtilde = xsum / alphasum;
        ytilde = ysum / alphasum;
        //==============================================================
        // STEP 2: Obtain xhat, xhat, A and B
        //==============================================================
        mat A(k,d), B(k,r);
        for (int s = 0; s < k; s++) {
            // copy feature vector of each seed point to corresponding vector
            vector<double> seedFeatureVec(seed.begin()+s*d, seed.begin()+(s+1)*d);
            vector<double> seedProjVec(projSeed.begin()+s*r, projSeed.begin()+(s+1)*r);
            vec xseed(seedFeatureVec);
            vec yseed(seedProjVec);
            // equation (4 ~ 6)
            vec xhat = xseed - xtilde;
            vec yhat = yseed - ytilde;
            double wsqrt = sqrt(alpha(s));
            A.row(s) = wsqrt * xhat.t();
            B.row(s) = wsqrt * yhat.t();
        }
        //==============================================================
        // STEP 3: Projection
        //==============================================================
        // equation (7)
        mat AtB = A.t() * B;
        mat U, V(r,r);
        vec S(r);
        svd(U, S, V, AtB);
        mat M = AtB * V;
        // equation (8)
        vec y = ((x - xtilde).t() * M + ytilde.t()).t();
        // copy projection result of each seed to output vector
        for (int i = 0; i < r; i++) {
            projData[p*r+i] = y(i);
        }
    }
}
