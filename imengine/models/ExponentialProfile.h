// Created 27-Feb-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_MODELS_EXPONENTIAL_PROFILE
#define IMENGINE_MODELS_EXPONENTIAL_PROFILE

#include "imengine/AbsRadialProfile.h"

namespace imengine {
namespace models {
	class ExponentialProfile : public imengine::AbsRadialProfile {
	public:
	    // Represents the normalized radial profile exp(-alpha*r)
		ExponentialProfile(double alpha);
		virtual ~ExponentialProfile();
		// Evaluates this profile at the specified radius.
        virtual double operator()(double r) const;
        // Evaluates this profile's real-valued radial integral for the specified kappa.
        virtual double radialIntegral(double kappa) const;
        // Sets the parameter values to use.
        void setParameters(double alpha);
	private:
        double _alpha,_norm,_twopi;
	}; // ExponentialProfile
}} // imengine::models

#endif // IMENGINE_MODELS_EXPONENTIAL_PROFILE
