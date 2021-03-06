// Created 08-Jan-2011 by David Kirkby (University of California, Irvine) <dkirkby@uci.edu>

#ifndef IMENGINE_IMAGE_ENGINE
#define IMENGINE_IMAGE_ENGINE

#include "imengine/AbsImageEngine.h"
#include "imengine/ptr_types.h"

namespace imengine {
    // Generates pixelized images of a source convoluted with a psf.
	template <class T> class ImageEngine : public AbsImageEngine {
	public:
	    // Creates a new engine for the specified source and psf functions to generate
	    // square images of pixelsPerSide x pixelsPerSide pixels of dimension pixelScale.
		ImageEngine(AbsPixelFunctionPtr source, AbsPixelFunctionPtr psf);
		virtual ~ImageEngine();
        // (Re)initializes the engine for the specified pixel grid size and scale
        virtual void initialize(int pixelsPerSide, double pixelScale = 1);
		// Generates an image with the source function offset by (dx,dy) and returns
		// the pixel sum
        virtual double generate(AbsImageWriter &writer, double dx = 0, double dy = 0);
    protected:
        // Returns a pointer to a newly created InterpolationData with parameters appropriate
        // for the requested pixel size and pixelation method
        virtual InterpolationData *createGrid() = 0;
        // Estimates the signal in pixel (i,j) using the tabulated values in _imageData
        virtual double estimatePixelValue(int i, int j) = 0;
        AbsPixelFunctionPtr _source, _psf;
        InterpolationDataPtr _imageGrid,_workspace;
	private:
        TransformDataPtr _sourceTransform, _psfTransform, _imageTransform;
        InterpolationDataPtr _generateCache;
        double _lastDx, _lastDy;
        bool _validLast;
	}; // ImageEngine
} // imengine

#endif // IMENGINE_IMAGE_ENGINE
