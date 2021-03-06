// Created 13-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_DATA_GRID
#define IMENGINE_DATA_GRID

#include "boost/utility.hpp"

namespace imengine {
    // Represents an "exploded" grid of data where the origin is mapped to each corner,
    // following the usual convention for discrete Fourier tranforms.
	class DataGrid : boost::noncopyable {
	public:
	    // Creates a new data grid with the specified size, spacing, and coordinate offset
		DataGrid(int gridSize, double gridSpacing);
		virtual ~DataGrid();
		// returns read-only initialization attributes
        int getGridSize() const;
        double getGridSpacing() const;
        // returns the (unexploded) axis value associated with an index value (no range check on i,j)
        double getX(int i) const;
        double getY(int j) const;
        // maps an un-exploded index with (0,0) in the bottom-left corner to an exploded index
        int getIndex(int k) const;
    protected:
        int _gridSize,_break1,_break2;
        double _gridSpacing;
	}; // DataGrid
	
	inline int DataGrid::getGridSize() const { return _gridSize; }
    inline double DataGrid::getGridSpacing() const { return _gridSpacing; }
    
    inline double DataGrid::getX(int i) const {
        return _gridSpacing*(i < _break1 ? i : i-_gridSize);
    }
    
    inline double DataGrid::getY(int j) const {
        return _gridSpacing*(j < _break1 ? j : j-_gridSize);
    }
    
    inline int DataGrid::getIndex(int k) const {
        return (k >= _break2) ? (k - _break2) : (k + _break1);
    }
    
} // imengine

#endif // IMENGINE_DATA_GRID
