// Created 09-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_TRANSFORM_DATA
#define IMENGINE_TRANSFORM_DATA

#include "imengine/DataGrid.h"
#include "imengine/types.h"
#include "imengine/ptr_types.h"

#include "boost/function.hpp"

#include <cassert>

namespace imengine {
    // Stores complex discrete Fourier transform values on a square grid
	class TransformData : public DataGrid {
	public:
	    // Creates a new transform data grid for the specified real-space target grid
        TransformData(InterpolationDataPtr target);
		virtual ~TransformData();

		// Returns the real and imaginary components of element (i,j)
		// with 0 <= i,j < getGridSize(). There is no method to return a complex<Real>
		// since, in general, this would require creating the returned object.
        Real const getReal(int i, int j) const;
        Real const getImag(int i, int j) const;
        
        // Assigns a complete set of values by repeatedly calling the function provided.
        // The provided function should be compatible with the following declaration:
        //
        //   void tabulator(double kx, double ky, Complex& result)
        //
        typedef boost::function<void (double,double,Complex&)> Tabulator;
        void tabulate(Tabulator tabulator);
        
        // reads a value from the target InterpolationGrid
        Real getTargetValue(int i, int j) const;
        
        // writes a real value into the target InterpolationGrid
        void setTargetValue(int i, int j, Real value);
        
        // calculates and returns re*re + im*im (no range checks on i,j)
        Real absSquared(int i, int j) const;

        // returns the wavenumber associated an index value (no range check on i)
        double waveNumber(int i) const;
        
        // sets our values to the element-by-element product of two other transforms,
        // including an optional translation to be applied analytically via a complex
        // exponential factor exp(-ik.dr)
        void setToProduct(TransformDataPtr t1, TransformDataPtr t2,
            double dx=0, double dy=0);
            
        // sets our values to the element-by-element sum of two other transforms
        // weighted by the specified coefficients, including an optional translation
        // applied to the second transform only.
        void setToSum(TransformDataPtr t1, TransformDataPtr t2, double c1, double c2,
            double dx=0, double dy=0);
        
        // dumps grid complex values to std::cout in row-wise order
        void dump() const;

        // Calculates the real part of our inverse Fourier transform and saves the result
        // in our target InterpolationData object. Normalization is defined by:
        // data[m,n] = Re[Sum[transform[j,k] Exp[+2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]]
        virtual void inverseTransform() = 0;
        
        // Sets our contents to the discrete Fourier transform of our target InterpolationData
        // object. Normalization is defined by:
        // transform[m,n] = Sum[data[j,k] Exp[-2piI(j*m+k*n)/N],{j,0,N-1},{k,0,N-1}]
        virtual void setToTransform() = 0;
        
        // Returns a smart pointer to a new object that shares our target but does
        // not copy our transform data.
        virtual TransformDataPtr clone() const = 0;

        //void validate() const;

	protected:
		// accesses the real/imag parts of transform data (no range checks on i,j)
        Real& real(int i, int j);
        Real& imag(int i, int j);
        Real const& real(int i, int j) const;
        Real const& imag(int i, int j) const;

        // returns a pointer to our transform data array
        Real *getDataPtr() const;

        // returns a bare pointer to the target data array
        Real *getTargetDataPtr() const;
        
        // returns a smart pointer to our target data array
        InterpolationDataPtr getTarget() const;

    private:
        // Translates transform[i,j] = {re,im} by (dx,dy).
        void _translate(Real &re, Real &im, double dx, double dy, int i, int j);
        InterpolationDataPtr _target;
        Real *_data;
        double _dk;
	}; // TransformData

    inline Real& TransformData::real(int i, int j) {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)];
    }
    inline Real& TransformData::imag(int i, int j) {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)+1];
    }
    inline Real const& TransformData::real(int i, int j) const {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)];
    }
    inline Real const& TransformData::imag(int i, int j) const {
        assert(i >= 0 && i < _break1);
        assert(j >= 0 && j < _gridSize);
        return _data[2*(i + _break1*j)+1];
    }
    
    inline Real TransformData::absSquared(int i, int j) const {
        assert(i >= 0 && i < _gridSize);
        assert(j >= 0 && j < _gridSize);
        Real re(getReal(i,j)), im(getImag(i,j));
        return re*re + im*im;
    }

    inline double TransformData::waveNumber(int i) const {
        assert(i >= 0 && i < _gridSize);
        return _dk*(i < _break1 ? i : i-_gridSize);
    }
    
    inline Real *TransformData::getDataPtr() const {
        return _data;
    }
    
    inline InterpolationDataPtr TransformData::getTarget() const {
        return _target;
    }
    
} // imengine

#endif // IMENGINE_TRANSFORM_DATA
