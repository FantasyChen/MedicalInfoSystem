#include <ROISegmentation.h>
#include "itkConfidenceConnectedImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include <QDebug>

ROISegmentation::ROISegmentation(DCMReader *_DCM){
	pDCM = _DCM; 

}

ROISegmentation::~ROISegmentation(){
}

void ROISegmentation::setRegionGrowSeeds(std::vector<CursorDim> __index){
	_index = __index;
}


/*
Mode I:Region Grow
Mode II:Thresholding
*/
vtkImageData* ROISegmentation::startROISegmentation(int mode){
	if (1 == mode){
		return startRegionGrow();
	}
	if (2 == mode){
		return startConnectedThresholding();
	}
	else{
		return NULL;
	}
}

vtkImageData* ROISegmentation::startRegionGrow(){
	typedef itk::CastImageFilter< ImageType, ImageType >
		CastingFilterType;
	CastingFilterType::Pointer caster = CastingFilterType::New();
	typedef itk::CurvatureFlowImageFilter< ImageType, ImageType >
		CurvatureFlowImageFilterType;
	CurvatureFlowImageFilterType::Pointer smoothing =
		CurvatureFlowImageFilterType::New();
	typedef itk::ConfidenceConnectedImageFilter<ImageType, ImageType>
		ConnectedFilterType;
	ConnectedFilterType::Pointer confidenceConnected = ConnectedFilterType::New();
	smoothing->SetInput(pDCM->getITKRawImage());
	confidenceConnected->SetInput(smoothing->GetOutput());
	caster->SetInput(confidenceConnected->GetOutput());

	//Parameter Settings
	smoothing->SetNumberOfIterations(2);
	smoothing->SetTimeStep(0.05);
	confidenceConnected->SetMultiplier(2.5);
	confidenceConnected->SetNumberOfIterations(2);
	confidenceConnected->SetInitialNeighborhoodRadius(1);
	confidenceConnected->SetReplaceValue(255);
	if (!_index.empty()){
		ImageType::PointType seedPoint;
		ImageType::IndexType seedIndex;
		std::vector<CursorDim>::iterator iter = _index.begin();
		for (iter; iter != _index.end(); ++iter){
			seedPoint[0] = iter->_x;
			seedPoint[1] = iter->_y;
			seedPoint[2] = iter->_z;
			if (pDCM->getITKRawImage()->TransformPhysicalPointToIndex(seedPoint, seedIndex)){
				qDebug()<<"SeedIndex:    " << seedIndex[0] << "  " << seedIndex[1] << "  " << seedIndex[2] << endl;
				confidenceConnected->AddSeed(seedIndex);
			}
		}
		caster->Update();

		typedef itk::ImageToVTKImageFilter<ImageType>       ConnectorType;
		ConnectorType::Pointer connector = ConnectorType::New();
		connector->SetInput(caster->GetOutput());
		connector->Update();
		vtkImageData * rawImage = vtkImageData::New();
		rawImage->DeepCopy(connector->GetOutput());
		return rawImage;
	}
	else{
		return NULL;
	}
}

vtkImageData* ROISegmentation::startConnectedThresholding(){
	typedef itk::CastImageFilter< ImageType, ImageType >
		CastingFilterType;
	CastingFilterType::Pointer caster = CastingFilterType::New();
	typedef itk::CurvatureFlowImageFilter< ImageType, ImageType >
		CurvatureFlowImageFilterType;
	CurvatureFlowImageFilterType::Pointer smoothing =
		CurvatureFlowImageFilterType::New();
	typedef itk::ConnectedThresholdImageFilter< ImageType,
		ImageType > ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	if (!_index.empty()){
		smoothing->SetInput(pDCM->getITKRawImage());
		connectedThreshold->SetInput(smoothing->GetOutput());
		caster->SetInput(connectedThreshold->GetOutput());
		smoothing->SetNumberOfIterations(3);
		smoothing->SetTimeStep(0.125);
		connectedThreshold->SetLower(0);
		connectedThreshold->SetUpper(255);
		connectedThreshold->SetReplaceValue(255);
		ImageType::PointType seedPoint;
		ImageType::IndexType seedIndex;
		std::vector<CursorDim>::iterator iter = _index.begin();
		for (iter; iter != _index.end(); ++iter){
			seedPoint[0] = iter->_x;
			seedPoint[1] = iter->_y;
			seedPoint[2] = iter->_z;
			if (pDCM->getITKRawImage()->TransformPhysicalPointToIndex(seedPoint, seedIndex)){
				qDebug() << "SeedIndex:    " << seedIndex[0] << "  " << seedIndex[1] << "  " << seedIndex[2] << endl;
				connectedThreshold->AddSeed(seedIndex);
			}
		}
		caster->Update();
		typedef itk::ImageToVTKImageFilter<ImageType>       ConnectorType;
		ConnectorType::Pointer connector = ConnectorType::New();
		connector->SetInput(caster->GetOutput());
		connector->Update();
		vtkImageData * rawImage = vtkImageData::New();
		rawImage->DeepCopy(connector->GetOutput());
		return rawImage;
	}
	else{
		return NULL;
	}
}