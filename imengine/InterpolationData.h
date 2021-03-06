// Created 14-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_INTERPOLATION_DATA
#define IMENGINE_INTERPOLATION_DATA

#include "imengine/DataGrid.h"
#include "imengine/types.h"

namespace imengine {
    // Stores a grid of image function values to support pixelation.
    class TransformData;
	class InterpolationData : public DataGrid {
	public:
	    // The reference grid point for pixel (0,0) is at (pad,pad)
		InterpolationData(int gridSize, int pad, double gridSpacing, double gridX, double gridY);
		virtual ~InterpolationData();
		
		// Creates a new object with the same dimensions
        InterpolationData *createWorkspace() const;
		
        // Accesses constructor parameters
        double getGridX() const;
        double getGridY() const;

        // Returns the value associated with grid point (i,j)
        Real getValue(int i, int j) const;
        
		// Sets the value associated with grid point (i,j) (no range checks on i,j)
        void setValue(int i, int j, Real value);
		
        // Returns the absolute value associated with pixel coord (x,y) (no range checks on x,y)
        Real getValueForPixel(int x, int y) const;
        
        // dumps grid values to std::cout in row-wise order
        void dump() const;

        // transforms require direct access to our private _data array
        friend class TransformData;
        
	private:
        int _pad;
        double _gridX, _gridY;
        Real *_data;
	}; // InterpolationData
	
    inline double InterpolationData::getGridX() const { return _gridX; }
    inline double InterpolationData::getGridY() const { return _gridY; }

    inline Real InterpolationData::getValue(int i, int j) const {
        return _data[i + _gridSize*j];
    }

	inline Real InterpolationData::getValueForPixel(int x, int y) const {
        Real value(_data[getIndex(x + _pad) + _gridSize*getIndex(y + _pad)]);
        return value > 0 ? +value : -value;
	}
} // imengine

#endif // IMENGINE_INTERPOLATION_DATA
