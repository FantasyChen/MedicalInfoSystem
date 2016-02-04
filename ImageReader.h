#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <QString>
#include <vtkImageData.h>

struct ImageInfo{
	std::string patientName;
	std::string patientID;
	std::string patientSex;
	std::string patientAge;
	std::string studyDate;
	std::string modality;
	std::string manufacturer;
	std::string institution;
	std::string model;

};

class ImageReader{
public:
	ImageReader(){};
	virtual ~ImageReader(){};
	virtual vtkImageData* getRawImage() = 0;
	virtual ImageInfo getImageInfo()=0;

protected:
	QString _filename;
	ImageInfo _imageInfo;
};





#endif