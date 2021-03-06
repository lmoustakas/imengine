// Created 17-Apr-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_SERSIC_DEMO
#define IMENGINE_MODELS_SERSIC_DEMO

#include "imengine/GenericPixelFunction.h"
#include "imengine/PolarEllipticityTransform.h"

namespace imengine {
namespace models {
	class SersicDemo : public GenericPixelFunction {
	public:
	    // Creates a new model with half-light radius re using the
	    // specified Sersic index and ellipticity parameters.
		SersicDemo(double re, double index, double eg1, double eg2, double rmax,
		    double egcos = 0, double egsin = 0);
		virtual ~SersicDemo();
		virtual double operator()(double x, double y) const;
        // Sets the parameter values to use.
        void setParameters(double re, double index, double eg1, double eg2, double rmax,
            double egcos = 0, double egsin = 0);
        // Calculate the value of k for the specified index so that re is
        // the half-light radius.
        static double kValue(double index);
	private:
        static double kValueF(double index, void *params);
        static double kValueDF(double index, void *params);
        static void kValueFDF(double index, void *params, double *y, double *dy);
        bool _initialized;
        double _twopi, _re, _alphaScale, _alpha, _index, _norm, _inverseIndex, _rmax;
        PolarEllipticityTransform _transform;
	}; // SersicDemo
}} // imengine::models

#endif // IMENGINE_MODELS_SERSIC_DEMO
