#ifndef DCMREADER_H
#define DCMREADER_H


#include <QString>
#include <QDebug>
#include <string>
#include <ImageReader.h>
#include <progressbase.h>
#include <thread>
#include "itkQtAdaptor.h"

#include <itkImage.h>
#include <itkImageFileReader.h>
#include "itkGDCMImageIO.h"
#include <itkImageToVTKImageFilter.h>
#include "itkGDCMSeriesFileNames.h"
#include <itkImageSeriesReader.h>
#include "itkMetaDataObject.h"



class DCMReader: public ImageReader{
	typedef double    PixelType;
	typedef itk::Image< PixelType, 3>         ImageType;
	typedef itk::ImageSeriesReader< ImageType >        ReaderType;
	typedef itk::GDCMImageIO       ImageIOType;

public:
	DCMReader(QString file);
	~DCMReader(){};
	vtkImageData* getRawImage();
	ImageInfo getImageInfo();
	bool getLoadStatus();
	itk::ImageSource<DCMReader::ImageType>::OutputImageType* DCMReader::getITKRawImage();
	static void StaticUpdate(ReaderType::Pointer reader);

private:
	QString _filename;   //Assume input is DCM series, so _filename should be the directory name.
	std::string FindDicomTag(const std::string & entryId, const itk::GDCMImageIO::Pointer dicomIO);
	ReaderType::Pointer reader;
	ImageIOType::Pointer dicomIO;
	bool _isFileLoaded;
};





#endif