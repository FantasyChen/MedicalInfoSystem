#include "DCMReader.h"

/*
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
*/


/*
The directory name is necessary to generate a new DCMRedaer object and the
object assume the input is a directory, if DCM files is not contained then 
error will show in the GUI.
*/


void DCMReader::StaticUpdate(ReaderType::Pointer reader){
	reader->Update();
}

DCMReader::DCMReader(QString file){
	
	_filename = file;
	reader = ReaderType::New();
	dicomIO = ImageIOType::New();
	int inputNum;
	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	qDebug() << _filename.toStdString().c_str() << endl;
	nameGenerator->SetUseSeriesDetails(true);
	//nameGenerator->AddSeriesRestriction("0008|0021");
	nameGenerator->SetDirectory(_filename.toStdString());
	typedef std::vector< std::string >    SeriesIdContainer;
	const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
	_isFileLoaded = !(seriesUID.empty());
	qDebug() << _isFileLoaded << endl;
	if (true == _isFileLoaded){
		SeriesIdContainer::const_iterator seriesItr = seriesUID.begin();

		SeriesIdContainer::const_iterator seriesEnd = seriesUID.end();
		/*while (seriesItr != seriesEnd)
		{
		qDebug() << seriesItr->c_str() << endl;
		++seriesItr;
		}*/
		std::string seriesIdentifier = seriesUID.begin()->c_str();
		typedef std::vector< std::string >   FileNamesContainer;
		FileNamesContainer fileNames;
		fileNames = nameGenerator->GetFileNames(seriesIdentifier);
		FileNamesContainer::const_iterator filesItr = fileNames.begin();
		FileNamesContainer::const_iterator filesEnd = fileNames.end();
		//while (filesItr != filesEnd)
		//{
		//	qDebug() << filesItr->c_str() << endl;
		//	++filesItr;
		//}
		reader->SetFileNames(fileNames);
		reader->SetImageIO(dicomIO);
		ProgressBase::GetInstance()->Observe(reader.GetPointer());
		ProgressBase::GetInstance()->show();
		/*typedef itk::QtSlotAdaptor<ReaderType> SlotAdaptorType;
		SlotAdaptorType slotAdaptor;

		// Connect the adaptor to a method of the ITK filter
		slotAdaptor.SetCallbackFunction(reader, &ReaderType::Update);
*/

		reader->Update();
		/*std::thread updateThread(StaticUpdate, reader);
		updateThread.join()*/;
	}
	
	//qDebug()<< "Origin:    " + QString::number(reader->GetOutput()->GetOrigin()[0]) + " " + QString::number(reader->GetOutput()->GetOrigin()[1])
	//	+ " " + QString::number(reader->GetOutput()->GetOrigin()[2]) << endl;
	//qDebug()<< "Spacing:    " + QString::number(reader->GetOutput()->GetSpacing()[0]) + " " + QString::number(reader->GetOutput()->GetSpacing()[1])
	//	+ " " + QString::number(reader->GetOutput()->GetSpacing()[2]) << endl;




}


/*
Extract the Dicom information from head files.
*/

ImageInfo DCMReader::getImageInfo(){
	_imageInfo.patientName = FindDicomTag("0010|0010", dicomIO);
	_imageInfo.patientID = FindDicomTag("0010|0020", dicomIO);
	_imageInfo.patientSex = FindDicomTag("0010|0040", dicomIO);
	_imageInfo.patientAge = FindDicomTag("0010|1010", dicomIO);
	_imageInfo.studyDate = FindDicomTag("0008|0020", dicomIO);
	_imageInfo.modality = FindDicomTag("0008|0060", dicomIO);
	_imageInfo.manufacturer = FindDicomTag("0008|0070", dicomIO);
	_imageInfo.institution = FindDicomTag("0008|0080", dicomIO);
	_imageInfo.model = FindDicomTag("0008|1090", dicomIO);
	/*
	DcmFileFormat fileformat;  
    OFCondition oc = fileformat.loadFile(_filename.toStdString().c_str()); 
	if (oc.good()){
		OFString patientName;
		OFString type;
		OFString patientSex;
		OFString modality;
		OFString patientAge;
		if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
		{
			_imageInfo.patientName = patientName.data();
		}
		if (fileformat.getDataset()->findAndGetOFString(DCM_DataSetType, type).good())
		{
			_imageInfo.type = type.data();
		}
		if (fileformat.getDataset()->findAndGetOFString(DCM_Modality, modality).good())
		{
			_imageInfo.modality = modality.data();
		}
		if (fileformat.getDataset()->findAndGetOFString(DCM_PatientSex, patientSex).good())
		{
			_imageInfo.patientSex = patientSex.data();
		}
		if (fileformat.getDataset()->findAndGetOFString(DCM_PatientAge, patientAge).good())
		{
			_imageInfo.patientAge = patientAge.data();
		}
	}
	*/
	return _imageInfo;
}

/*
:Extract raw image information from the dicom files.Because the input is assumed to
be series dicom, so the raw data of image should actually be a volume pixels in 3 - D.
*/
vtkImageData* DCMReader::getRawImage(){
	typedef itk::ImageToVTKImageFilter<ImageType>       ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(reader->GetOutput());
	connector->Update();
	vtkImageData * rawImage = vtkImageData::New();
	rawImage->ShallowCopy(connector->GetOutput());
	return rawImage;
}

std::string DCMReader::FindDicomTag(const std::string & entryId, const itk::GDCMImageIO::Pointer dicomIO)
{
	std::string tagvalue;
	bool found = dicomIO->GetValueFromTag(entryId, tagvalue);
	if (!found)
	{
		tagvalue = "NOT FOUND";
	}
	return tagvalue;
}

/*
To check whether the given directories contains DCM files, if not, return false.
*/
bool DCMReader::getLoadStatus(){
	return _isFileLoaded;
}


itk::ImageSource<DCMReader::ImageType>::OutputImageType* DCMReader::getITKRawImage(){
	return reader->GetOutput();
}
