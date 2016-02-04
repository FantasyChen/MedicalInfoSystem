#ifndef ROISEGMENTATION_H
#define ROISEGMENTATION_H

#include <DCMReader.h>
#include "itkImageFileReader.h"
#include <itkImageToVTKImageFilter.h>
#include <itkImageBase.h>
#include <itkPoint.h>

struct CursorDim
{
	double _x;
	double _y;
	double _z;
};

class ROISegmentation{

	typedef double    PixelType; 
	typedef itk::Image< PixelType, 3>         ImageType;

public:
	ROISegmentation(DCMReader *_DCM);
	~ROISegmentation();
	void setRegionGrowSeeds(std::vector<CursorDim> __index);
	vtkImageData* startROISegmentation(int mode);

private:
	DCMReader *pDCM;
	std::vector<CursorDim> _index;
	vtkImageData* startRegionGrow();
	vtkImageData* startConnectedThresholding();


};




#endif