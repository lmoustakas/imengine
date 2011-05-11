// Created 26-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/PolarEllipticityTransform.h"
#include "imengine/InvalidValue.h"

#include <cmath>

namespace local = imengine;

local::PolarEllipticityTransform::PolarEllipticityTransform(double lambda, double phi,
double egcos, double egsin)
{
    setParameters(lambda,phi,egcos,egsin);
}

local::PolarEllipticityTransform::~PolarEllipticityTransform() {
}

void local::PolarEllipticityTransform::setParameters(double lambda, double phi,
double egcos, double egsin) {
    if(isInitialized() && lambda == _lambda && phi == _phi &&
        egcos == _egcos && egsin == _egsin) return;
    _lambda = lambda;
    _phi = phi;
    _egcos = egcos;
    _egsin = egsin;
    // Calculate the 2x2 matrix elements of M = {{a,b},{c,d}}
    double lamsq(lambda*lambda);
    double EG((lamsq-1)/(lamsq+1));
    double eg1(EG*std::cos(2*phi)),eg2(EG*std::sin(2*phi));
    _a = 1 - eg1 + egcos;
    _b = -eg2 - egsin;
    _c = -eg2 + egsin;
    _d = 1 + eg1 + egcos;
    _detM = _a*_d - _b*_c; // = 1 - eg1^2 - eg2^2  + egsin^2 + egcos^2 + 2 egcos
    assertNotEqualTo<double>("PolarEllipticityTransform det(M)",_detM,0);
    setChanged();
}

double local::PolarEllipticityTransform::determinant() const {
    return _detM;
}

double local::PolarEllipticityTransform::transformedRadius(double x, double y) const {
    double xp(_a*x + _b*y);
    double yp(_c*x + _d*y);
    return std::sqrt(xp*xp + yp*yp);
}

double local::PolarEllipticityTransform::transformedWaveNumber(double kx, double ky) const {
    double kxp(_d*kx - _c*ky);
    double kyp(_a*ky - _b*kx);
    return std::sqrt(kxp*kxp + kyp*kyp)/_detM;
}
