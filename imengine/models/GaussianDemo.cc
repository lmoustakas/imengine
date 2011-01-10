// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/models/GaussianDemo.h"

#include <cassert>
#include <cmath>

namespace local = imengine::models;

local::GaussianDemo::GaussianDemo(double sigma) :
GenericPixelFunction(), _sigma(sigma)
{
    assert(sigma > 0);
    _twosigmasq = 2*sigma*sigma;
    _norm = std::sqrt(2)*sigma;
}

local::GaussianDemo::~GaussianDemo() { }

double local::GaussianDemo::operator()(double x, double y) const {
    double rsq = x*x + y*y;
    return std::exp(-rsq/_twosigmasq)/_norm;
}