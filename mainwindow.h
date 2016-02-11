#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "DCMReader.h"
#include <QFileDialog>
#include "qdebug.h"
#include "AlgorithmUtils.h"
#include "qboxlayout.h"
#include <QVBoxLayout>
#include <ROISegmentation.h>
#include "QMessageBox"
#include "volumewindow.h"
#include <thread>

#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkImageData.h>

#include "vtkResliceImageViewer.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursor.h"
#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkPlaneSource.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageSlabReslice.h"
#include "vtkBoundedPlanePointPlacer.h"
#include "vtkDistanceWidget.h"
#include "vtkDistanceRepresentation.h"
#include "vtkHandleRepresentation.h"
#include "vtkResliceImageViewerMeasurements.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkImagePlaneWidget.h"
#include "vtkImageStencil.h"
#include "vtkLassoStencilSource.h"
#include "vtkImageAccumulate.h"
#include "vtkROIStencilSource.h"
#include "vtkSelectPolyData.h"
#include "vtkPolyDataToImageStencil.h"
#include "vtkCubeSource.h"
#include "vtkOutputWindow.h"
#include "vtkFileOutputWindow.h"
/*
This class basically derived from QMainWindow and so once generated, 
it will provide the basic window for GUI.Not only many basic application 
and function is implemented in this class, but also many function used to
view and display or modify the image is realized here.
*/



class mainwindow : public QMainWindow
{
	Q_OBJECT

public:;
	mainwindow(QWidget *parent = 0);
	~mainwindow();


protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];

private slots:
	void OpenImageDir();
	void SaveImageDir();
	void ResliceMode(int mode);
	void ThickMode(int mode);
	void ResetViews();
	void AddSeed();
	void RemoveSeed();
	void AutoSegmentation();
	void MannualSegmentation();
	void ChangeToRGBColorMap(int mode);
	void CalcHeterogeneity();
	void ShowAbout();
	void ShowVolumeWindow();
	void HideVolumeWindow();

private:
	volumewindow* _vWindow; 
	QString _imageDir;
	DCMReader *pDCM;
	bool isFileDisplayed;
	std::vector<CursorDim> _index;
	vtkImageData* rawImageData;//The image data before processing
	vtkImageData* curImageData; //The image data under current processing
	int imageDims[3];
	double imageOrigin[3];
	double imageSpacing[3];
	double imageCenter[3];
	int imageExtent[6];
	double imageRange[2];
	Ui::mainwindowClass ui;
	int colorMode;
	void OutputError(int errorType);
	void ReadImageDir();
	void LassoROIExtract();
	void mainwindow::ShowImage(vtkImageData* ImageData,  CursorDim cursor);
	void ShowStatistics();
	void StencilROIExtract(int mode, double bounds[6]);
};

#endif // MAINWINDOW_H
