// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#include "imengine/GenericPixelFunction.h"
#include "imengine/TransformData.h"

#include <cassert>

namespace local = imengine;

local::GenericPixelFunction::GenericPixelFunction() :
AbsPixelFunction()
{
}

local::GenericPixelFunction::~GenericPixelFunction() {
}

void local::GenericPixelFunction::initTransform(TransformData* transformData) {
    assert(0 != transformData);
    _transformData = transformData;
}

void local::GenericPixelFunction::doTransform() {
    // tabulate function values on a (x,y) grid
    int ngrid = _transformData->getGridSize();
    for(int j = 0; j < ngrid; j++) {
        double y = _transformData->getY(j);
        for(int i = 0; i < ngrid; i++) {
            double x = _transformData->getX(i);
            double value = (*this)(x,y);
            _transformData->setTarget(i,j,value);
        }
    }
    double spacing = _transformData->getGridSpacing();
    // calculate the discrete Fourier transform of the tabulated data
    _transformData->setToTransform();
}