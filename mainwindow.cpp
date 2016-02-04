#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);                //A neccesarry process to init VTK if you are using Visual Studio to compile
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);


#include "mainwindow.h"

enum Image_Mode{
	SCALAR = 0,
	COLOR	
};

enum Error_Type{
	UNDEFINED_IMAGE = 0,
	NULL_POINTS
};


mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	isFileDisplayed = false;
	colorMode = SCALAR;

	ui.setupUi(this);
	this->showMaximized();    //Maximize the window
	//Connect buttons and triggers
	connect(ui.actionOpenFile, SIGNAL(triggered()), this, SLOT(OpenImageDir()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SaveImageDir()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(ShowAbout()));
	connect(ui.ResliceModeBox, SIGNAL(stateChanged(int)), this, SLOT(ResliceMode(int)));
	connect(ui.ThickModeBox, SIGNAL(stateChanged(int)), this, SLOT(ThickMode(int)));
	connect(ui.ColorModeBox, SIGNAL(stateChanged(int)), this, SLOT(ChangeToRGBColorMap(int)));
	connect(ui.resetButton, SIGNAL(clicked()), this, SLOT(ResetViews()));
	connect(ui.addSeedButton, SIGNAL(clicked()), this, SLOT(AddSeed()));
	connect(ui.removeSeedButton, SIGNAL(clicked()), this, SLOT(RemoveSeed()));
	connect(ui.segStartButton, SIGNAL(clicked()), this, SLOT(AutoSegmentation()));
	connect(ui.segStartButton_2, SIGNAL(clicked()), this, SLOT(MannualSegmentation()));
	connect(ui.calcHerterButton, SIGNAL(clicked()), this, SLOT(CalcHeterogeneity()));

	//Settings
	ui.infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.stateTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

mainwindow::~mainwindow()
{

}


void mainwindow::OpenImageDir(){
	_imageDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), 
		"./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	
	ReadImageDir(); 
}

void mainwindow::ReadImageDir(){
	if (NULL!= _imageDir){
		//extract info
		pDCM = new DCMReader(_imageDir);
		//if (true == pDCM->getLoadStatus()){
			ImageInfo imageinfo = pDCM->getImageInfo();


			//show info
			ui.infoTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.patientName)));
			ui.infoTable->setItem(1, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.patientID)));
			ui.infoTable->setItem(2, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.patientSex)));
			ui.infoTable->setItem(3, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.patientAge)));
			ui.infoTable->setItem(4, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.studyDate)));
			ui.infoTable->setItem(5, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.modality)));
			ui.infoTable->setItem(6, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.manufacturer)));
			ui.infoTable->setItem(7, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.institution)));
			ui.infoTable->setItem(8, 0, new QTableWidgetItem(QString::fromStdString(imageinfo.model)));
			CursorDim originIndex;
			originIndex._x = originIndex._y = originIndex._z = 0;
			rawImageData = pDCM->getRawImage();
			curImageData = rawImageData;
			ShowImage(curImageData, originIndex);
		//}
	}
	else{
		OutputError(UNDEFINED_IMAGE);
	}
}


void mainwindow::SaveImageDir(){
	if (NULL!= curImageData){
		QString _saveDir = QFileDialog::getSaveFileName(this, tr("Save File"),
			"./",
			tr("Images (*.png *.xpm *.jpg)"));

	}
	else{
		//error
	}

}


class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback *New()
	{
		return new vtkResliceCursorCallback;
	}

	void Execute(vtkObject *caller, unsigned long ev,
		void *callData)
	{

		if (ev == vtkResliceCursorWidget::WindowLevelEvent ||
			ev == vtkCommand::WindowLevelEvent ||
			ev == vtkResliceCursorWidget::ResliceThicknessChangedEvent)
		{
			// Render everything
			for (int i = 0; i < 3; i++)
			{
				this->RCW[i]->Render();
			}
			this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
			return;
		}
		vtkImagePlaneWidget* ipw =
			dynamic_cast<vtkImagePlaneWidget*>(caller);
		if (ipw)
		{
			double* wl = static_cast<double*>(callData);

			if (ipw == this->IPW[0])
			{
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[1])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[2])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
			}
		}

		vtkResliceCursorWidget *rcw = dynamic_cast<
			vtkResliceCursorWidget *>(caller);
		if (rcw)
		{
			vtkResliceCursorLineRepresentation *rep = dynamic_cast<
				vtkResliceCursorLineRepresentation *>(rcw->GetRepresentation());
			// Although the return value is not used, we keep the get calls
			// in case they had side-effects
			rep->GetResliceCursorActor()->GetCursorAlgorithm()->GetResliceCursor();
			for (int i = 0; i < 3; i++)
			{
				vtkPlaneSource *ps = static_cast<vtkPlaneSource *>(
					this->IPW[i]->GetPolyDataAlgorithm());
				ps->SetOrigin(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetOrigin());
				ps->SetPoint1(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint1());
				ps->SetPoint2(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint2());

				// If the reslice plane has modified, update it on the 3D widget
				this->IPW[i]->UpdatePlacement();
				double *curCenter = RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->GetCenter();
				ui.stateTable->setItem(5, 0, new QTableWidgetItem(QString::number(curCenter[0]) + " ," + QString::number(curCenter[1])
					+ " ," + QString::number(curCenter[2])));
				ui.stateTable->setItem(6, 0, new QTableWidgetItem(QString::number(curCenter[0])));
			}
		}

		// Render everything
		for (int i = 0; i < 3; i++)
		{
			this->RCW[i]->Render();
		}
		this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
	}

	vtkResliceCursorCallback() {}
	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget *RCW[3];
	Ui::mainwindowClass ui;
	vtkImageData* image;
};


//mode 0:Scaler Mode
//mode 1:RGB Mode
void mainwindow::ShowImage(vtkImageData* ImageData, CursorDim cursor = CursorDim{ 0.0, 0.0, 0.0 }){
	if (colorMode == SCALAR || colorMode == COLOR){
		if (_imageDir != NULL&&pDCM != NULL){
			/*vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
			actor->GetMapper()->SetInputData(pDCM->getRawImage());
			vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
			renderer->AddActor(actor);
			renderer->ResetCamera();
			vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
			renderWindow->AddRenderer(renderer);
			vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
			vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
			renderWindowInteractor->SetInteractorStyle(style);
			renderWindowInteractor->SetRenderWindow(renderWindow);
			renderWindowInteractor->Initialize();
			renderWindowInteractor->Start();*/

			//Get the basic information of the image
			ImageData->GetScalarRange(imageRange);
			ImageData->GetDimensions(imageDims);
			ImageData->GetOrigin(imageOrigin);
			ImageData->GetSpacing(imageSpacing);
			ImageData->GetCenter(imageCenter);
			ImageData->GetExtent(imageExtent);
			//ui.debugBrowser->append(QString::number(imageDims[0]) + " " + QString::number(imageDims[1])+ " " + QString::number(imageDims[2]));
			
		
				for (int i = 0; i < 3; i++)
				{
					riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();
				}

			ui.qvtkWidget->SetRenderWindow(riw[0]->GetRenderWindow());
			riw[0]->SetupInteractor(
				ui.qvtkWidget->GetRenderWindow()->GetInteractor());

			ui.qvtkWidget_2->SetRenderWindow(riw[1]->GetRenderWindow());
			riw[1]->SetupInteractor(
				ui.qvtkWidget_2->GetRenderWindow()->GetInteractor());

			ui.qvtkWidget_3->SetRenderWindow(riw[2]->GetRenderWindow());
			riw[2]->SetupInteractor(
				ui.qvtkWidget_3->GetRenderWindow()->GetInteractor());
			for (int i = 0; i < 3; i++)
			{
				// make them all share the same reslice cursor object.
				vtkResliceCursorLineRepresentation *rep =
					vtkResliceCursorLineRepresentation::SafeDownCast(
					riw[i]->GetResliceCursorWidget()->GetRepresentation());
				riw[i]->SetResliceCursor(riw[0]->GetResliceCursor());

				rep->GetResliceCursorActor()->
					GetCursorAlgorithm()->SetReslicePlaneNormal(i);

				riw[i]->SetInputData(ImageData);
				riw[i]->SetSliceOrientation(i);
				riw[i]->SetResliceModeToAxisAligned();
				//riw[i]->SetResliceMode(1);
			}
			double resliceCenter[3] = { cursor._x, cursor._y, cursor._z };
			riw[0]->GetResliceCursor()->SetCenter(resliceCenter);
			vtkSmartPointer<vtkCellPicker> picker =
				vtkSmartPointer<vtkCellPicker>::New();
			picker->SetTolerance(0.005);

			vtkSmartPointer<vtkProperty> ipwProp =
				vtkSmartPointer<vtkProperty>::New();

			vtkSmartPointer< vtkRenderer > ren =
				vtkSmartPointer< vtkRenderer >::New();

			ui.qvtkWidget_4->GetRenderWindow()->AddRenderer(ren);
			vtkRenderWindowInteractor *iren = ui.qvtkWidget_4->GetInteractor();


			for (int i = 0; i < 3; i++)
			{
				planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
				planeWidget[i]->SetInteractor(iren);
				planeWidget[i]->SetPicker(picker);
				planeWidget[i]->RestrictPlaneToVolumeOn();
				double color[3] = { 0, 0, 0 };
				color[i] = 1;
				planeWidget[i]->GetPlaneProperty()->SetColor(color);

				color[0] /= 4.0;
				color[1] /= 4.0;
				color[2] /= 4.0;
				riw[i]->GetRenderer()->SetBackground(color);
				//To do, color mode background
				planeWidget[i]->SetTexturePlaneProperty(ipwProp);
				planeWidget[i]->TextureInterpolateOff();
				planeWidget[i]->SetResliceInterpolateToLinear();
				planeWidget[i]->SetInputData(ImageData);
				planeWidget[i]->SetPlaneOrientation(i);
				planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
				planeWidget[i]->DisplayTextOn();
				planeWidget[i]->SetDefaultRenderer(ren);
				if (colorMode == SCALAR){
						planeWidget[i]->SetWindowLevel(imageRange[1]-imageRange[0], ((imageRange[0] + imageRange[1]) / 2));
				}
				planeWidget[i]->On();
				planeWidget[i]->InteractionOn();
			}

			vtkSmartPointer<vtkResliceCursorCallback> cbk =
				vtkSmartPointer<vtkResliceCursorCallback>::New();

			for (int i = 0; i < 3; i++)
			{
				cbk->IPW[i] = planeWidget[i];
				cbk->RCW[i] = riw[i]->GetResliceCursorWidget();
				cbk->ui = ui;
				cbk->image = curImageData;
				riw[i]->GetResliceCursorWidget()->AddObserver(
					vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
				riw[i]->GetResliceCursorWidget()->AddObserver(
					vtkResliceCursorWidget::WindowLevelEvent, cbk);
				riw[i]->GetResliceCursorWidget()->AddObserver(
					vtkResliceCursorWidget::ResliceThicknessChangedEvent, cbk);
				riw[i]->GetResliceCursorWidget()->AddObserver(
					vtkResliceCursorWidget::ResetCursorEvent, cbk);
				riw[i]->GetInteractorStyle()->AddObserver(
					vtkCommand::WindowLevelEvent, cbk);
				if (colorMode == SCALAR){
					// Make them all share the same color map.
					riw[i]->SetLookupTable(riw[0]->GetLookupTable());
					planeWidget[i]->GetColorMap()->SetLookupTable(riw[0]->GetLookupTable());
					//planeWidget[i]->GetColorMap()->SetInput(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap()->GetInput());
					planeWidget[i]->SetColorMap(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap());
				}
				else{
					//riw[i]->SetLookupTable(NULL);
					/*vtkLookupTable *lut = vtkLookupTable::New();
					lut->SetHueRange(0, 1);
					lut->SetSaturationRange(0, 1);
					lut->SetValueRange(0, 1);
					lut->SetNumberOfColors(256);
					lut->Build();*/
					riw[i]->GetWindowLevel()->SetLookupTable(NULL);
					riw[i]->GetWindowLevel()->SetOutputFormatToRGB();
					planeWidget[i]->GetColorMap()->SetLookupTable(NULL);
					planeWidget[i]->GetColorMap()->SetOutputFormatToRGB();

					
				}
			}

			for (int i = 0; i < 3; i++)
			{
				riw[i]->Reset();
			}
			for (int i = 0; i < 3; i++)
			{
				vtkPlaneSource *ps = static_cast<vtkPlaneSource *>(
					planeWidget[i]->GetPolyDataAlgorithm());
				ps->SetNormal(riw[0]->GetResliceCursor()->GetPlane(i)->GetNormal());
				ps->SetCenter(riw[0]->GetResliceCursor()->GetPlane(i)->GetOrigin());

				// If the reslice plane has modified, update it on the 3D widget
				planeWidget[i]->UpdatePlacement();
			}

			// Render in response to changes.
			for (int i = 0; i < 3; i++)
			{
				riw[i]->GetRenderer()->ResetCamera();
				riw[i]->Render();
			}

			double *curCenter = riw[0]->GetResliceCursor()->GetCenter();
			ui.stateTable->setItem(5, 0, new QTableWidgetItem(QString::number(curCenter[0]) + " ," + QString::number(curCenter[1])
				+ " ," + QString::number(curCenter[2])));
			ui.qvtkWidget_4->GetRenderWindow()->Render();
			ui.ResliceModeBox->setEnabled(1);
			ui.ThickModeBox->setEnabled(0);
			isFileDisplayed = true;
			ShowStatistics();
		}
	}
}




void mainwindow::ChangeToRGBColorMap(int mode){
	//ui.debugBrowser->append(QString::number(mode));
	if (_imageDir != NULL&&pDCM != NULL){
		if (mode){
			vtkImageData* colorImageData =
				vtkImageData::New();
			colorImageData->ShallowCopy(curImageData);
			vtkSmartPointer<vtkLookupTable> colorTable =
				vtkSmartPointer<vtkLookupTable>::New();
			colorTable->SetRange(imageRange);
			colorTable->SetHueRange(0, 1);
			colorTable->SetValueRange(0, 1);
			colorTable->SetSaturationRange(0, 1);
			colorTable->SetNumberOfColors(256);
			//To do. May have interface for user to select the color or default color.
			colorTable->Build();
			vtkSmartPointer<vtkImageMapToColors> colorMap =
				vtkSmartPointer<vtkImageMapToColors>::New();
			colorMap->SetInputData(colorImageData);
			colorMap->SetLookupTable(colorTable);
			colorMap->Update();
			colorMode = COLOR;
			ShowImage(colorMap->GetOutput());
		}
		else{
			colorMode = SCALAR;
			ShowImage(curImageData);
		}
	}
}

void mainwindow::ResliceMode(int mode)
{
	if (true == isFileDisplayed){
		ui.ThickModeBox->setEnabled(mode ? 1 : 0);

		for (int i = 0; i < 3; i++)
		{
			riw[i]->SetResliceMode(mode ? 1 : 0);
			if (colorMode == COLOR){
				riw[i]->GetWindowLevel()->SetLookupTable(NULL);
				riw[i]->GetWindowLevel()->SetOutputFormatToRGB();
				planeWidget[i]->GetColorMap()->SetLookupTable(NULL);
				planeWidget[i]->GetColorMap()->SetOutputFormatToRGB();
			}
			riw[i]->GetRenderer()->ResetCamera();
			riw[i]->Render();

		}
	}
}

void mainwindow::ResetViews()
{
	// Reset the basic settings
	ui.seedTextBrowser->clear();
	_index.clear();
	curImageData = rawImageData;
	colorMode = SCALAR;
	ui.ThickModeBox->setCheckState(Qt::Unchecked);
	ui.ColorModeBox->setCheckState(Qt::Unchecked);
	ui.ResliceModeBox->setCheckState(Qt::Unchecked);
	ShowImage(rawImageData);

	// Reset the reslice image views
	for (int i = 0; i < 3; i++)
	{
		riw[i]->Reset();
	}

	// Also sync the Image plane widget on the 3D top right view with any
	// changes to the reslice cursor.
	for (int i = 0; i < 3; i++)
	{
		vtkPlaneSource *ps = static_cast<vtkPlaneSource *>(
			planeWidget[i]->GetPolyDataAlgorithm());
		ps->SetNormal(riw[0]->GetResliceCursor()->GetPlane(i)->GetNormal());
		ps->SetCenter(riw[0]->GetResliceCursor()->GetPlane(i)->GetOrigin());

		// If the reslice plane has modified, update it on the 3D widget
			planeWidget[i]->UpdatePlacement();
	}

	// Render in response to changes.
	for (int i = 0; i < 3; i++)
	{
		riw[i]->GetRenderer()->ResetCamera();
		riw[i]->Render();
	}
	ui.qvtkWidget_4->GetRenderWindow()->Render();
}

void mainwindow::ThickMode(int mode)
{
	if (true == isFileDisplayed){
		for (int i = 0; i < 3; i++)
		{
			riw[i]->SetThickMode(mode ? 1 : 0);
			riw[i]->GetRenderer()->ResetCamera();
			riw[i]->Render();
		}
	}
}

void mainwindow::AddSeed(){
	CursorDim cursor;
	cursor._x = riw[0]->GetResliceCursor()->GetCenter()[0];
	cursor._y = riw[0]->GetResliceCursor()->GetCenter()[1];
	cursor._z = riw[0]->GetResliceCursor()->GetCenter()[2];
	_index.push_back(cursor);
	ui.seedTextBrowser->append(QString::number(cursor._x) + " " + QString::number(cursor._y) + " " + QString::number(cursor._z)); //Show the location of seeds in the window.
/*
	vtkSmartPointer<vtkSphereSource> sphereSource = 																		//Add a sphere to indicate the location of points
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(cursor._x, cursor._y, cursor._z);
	sphereSource->SetRadius(5);
	sphereSource->Update();*/

}

void mainwindow::RemoveSeed(){
	
	QTextBrowser* pBrowser = ui.seedTextBrowser;
	if (!_index.empty()){
		_index.pop_back();
		pBrowser->setFocus();
		QTextCursor storeCursorPos = pBrowser->textCursor();
		pBrowser->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
		pBrowser->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		pBrowser->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
		pBrowser->textCursor().removeSelectedText();
		pBrowser->textCursor().deletePreviousChar();
		pBrowser->setTextCursor(storeCursorPos);
		
	}
}


void mainwindow::AutoSegmentation(){
	ROISegmentation *ROISeg = new ROISegmentation(pDCM);
	ROISeg->setRegionGrowSeeds(_index);
	vtkImageData * ROIImageData;
	if (true == ui.regionRadioButton->isChecked()&&!_index.empty()){
		ROIImageData = ROISeg->startROISegmentation(1);
	}
	else if (true == ui.thresholdRadioButton->isChecked()&&!_index.empty()){
		ROIImageData = ROISeg->startROISegmentation(2);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("Please choose a method and at least one Seed Point before Segmentation\n");
		msgBox.exec();
	}
	if (ROIImageData != NULL){
		int newDims[3];
		ROIImageData->GetDimensions(newDims);
		//ui.debugBrowser->append("RegionDIMS:    " + QString::number(newDims[0]) + " " + QString::number(newDims[1]) + " " + QString::number(newDims[2]));
		CursorDim cursor;
		cursor._x = riw[0]->GetResliceCursor()->GetCenter()[0];
		cursor._y = riw[0]->GetResliceCursor()->GetCenter()[1];
		cursor._z = riw[0]->GetResliceCursor()->GetCenter()[2];
		curImageData = ROIImageData;
		ui.seedTextBrowser->clear();
		_index.clear();
		ShowImage(curImageData);
	}
}



void mainwindow::MannualSegmentation(){
	vtkImageData* ROIImageData;
	if (!_index.empty()){
		if (true == ui.pointRadioButton->isChecked()){
			LassoROIExtract();
		}
		else{
			double x_min, x_max, y_min, y_max, z_min, z_max;
			std::vector<CursorDim>::iterator iter = _index.begin();
			x_min = x_max = iter->_x;
			y_min = y_max = iter->_y;
			z_max = z_min = iter->_z;
			iter++;
			for (iter; iter != _index.end(); iter++){
				x_min = iter->_x < x_min ? iter->_x : x_min;
				x_max = iter->_x > x_max ? iter->_x : x_max;
				y_min = iter->_y < y_min ? iter->_y : y_min;
				y_max = iter->_y > y_max ? iter->_y : y_max;
				z_min = iter->_z < z_min ? iter->_z : z_min;
				z_max = iter->_z > z_max ? iter->_z : z_max;
			}
			double bounds[6] = { x_min, x_max, y_min, y_max, z_min, z_max };
			if (true == ui.boxStencilRadioButton->isChecked()){
				StencilROIExtract(0, bounds);
			}
			else{
				StencilROIExtract(1, bounds);
			}
		}
	}
	else{
		OutputError(UNDEFINED_IMAGE);
	}
}

//To Do
void mainwindow::LassoROIExtract(){
	vtkSmartPointer<vtkPoints> selectionPoints =
		vtkSmartPointer<vtkPoints>::New();
	std::vector<CursorDim>::iterator iter = _index.begin();
	int _i = 0;
	for (iter; iter != _index.end(); ++iter){
		selectionPoints->InsertPoint(_i++, iter->_x, iter->_y, iter->_z);
	}
	
	vtkSmartPointer<vtkLassoStencilSource> stencilSource =
		vtkSmartPointer<vtkLassoStencilSource>::New();
	stencilSource->SetOutputOrigin(imageOrigin);
	stencilSource->SetOutputSpacing(imageSpacing);
	stencilSource->SetOutputWholeExtent(imageExtent);
	stencilSource->SetPoints(selectionPoints);
	stencilSource->SetShapeToPolygon();
	stencilSource->Update();
	
	/*vtkSmartPointer<vtkCubeSource> polydata = vtkSmartPointer<vtkCubeSource>::New();
	polydata->SetCenter(0, 0, 0);
	polydata->SetXLength(2000);
	polydata->SetYLength(2000);
	polydata->SetZLength(2000);
	polydata->Update();
	vtkSmartPointer<vtkSelectPolyData> loop =
		vtkSmartPointer<vtkSelectPolyData>::New();
	loop->SetInputData(polydata->GetOutput());
	loop->SetLoop(selectionPoints);
	loop->GenerateSelectionScalarsOff();
	loop->SetSelectionModeToClosestPointRegion(); //negative scalars inside
	loop->Update();

	vtkSmartPointer<vtkPolyDataToImageStencil> pol2stenc =
		vtkSmartPointer<vtkPolyDataToImageStencil>::New();
	pol2stenc->SetInputData(loop->GetOutput());
	pol2stenc->SetOutputOrigin(imageOrigin);
	pol2stenc->SetOutputSpacing(imageSpacing);
	pol2stenc->SetOutputWholeExtent(imageExtent);
	pol2stenc->Update();
	*/
	vtkSmartPointer<vtkImageStencil> stencil =
		vtkSmartPointer<vtkImageStencil>::New();
	stencil->SetInputData(curImageData);
	stencil->SetStencilData(stencilSource->GetOutput());
	stencil->SetBackgroundValue(0);
	stencil->Update();
	curImageData = stencil->GetOutput();
	ui.ThickModeBox->setCheckState(Qt::Unchecked);
	ui.ColorModeBox->setCheckState(Qt::Unchecked);
	ui.ResliceModeBox->setCheckState(Qt::Unchecked);
	ui.seedTextBrowser->clear();
	_index.clear();
	ShowImage(curImageData);
}



//mode 0:Box
//mode 1:Ellipsoid
void mainwindow::StencilROIExtract(int mode, double bounds[6]){
	vtkSmartPointer<vtkROIStencilSource> stencilSource =
		vtkSmartPointer<vtkROIStencilSource>::New();
	stencilSource->SetOutputOrigin(imageOrigin);
	stencilSource->SetOutputSpacing(imageSpacing);
	stencilSource->SetOutputWholeExtent(imageExtent);
	switch (mode)
	{
	case 0:stencilSource->SetShapeToBox(); break;
	case 1:stencilSource->SetShapeToEllipsoid(); break;
	default:stencilSource->SetShapeToBox(); break;
	}
	stencilSource->SetBounds(bounds);
	stencilSource->Update();

	/*vtkSmartPointer<vtkImageStencil> stencil =
		vtkSmartPointer<vtkImageStencil>::New();
	stencil->SetInputData(curImageData);
	stencil->SetStencilData(stencilSource->GetOutput());
	stencil->SetBackgroundValue(0);
	stencil->Update();*/
	vtkSmartPointer<vtkImageReslice> reslice = 
		vtkSmartPointer<vtkImageReslice>::New();
	reslice->SetInputData(curImageData);
	reslice->SetStencilData(stencilSource->GetOutput());
	double xmin, xmax, ymin, ymax, zmin, zmax;
	xmin = floor((bounds[0] - imageOrigin[0]) / imageSpacing[0]);
	xmax = ceil((bounds[1] - imageOrigin[0]) / imageSpacing[0]);
	ymin = floor((bounds[2] - imageOrigin[1]) / imageSpacing[1]);
	ymax = ceil((bounds[3] - imageOrigin[1]) / imageSpacing[1]);
	zmin = floor((bounds[4] - imageOrigin[2]) / imageSpacing[2]);
	zmax = ceil((bounds[5] - imageOrigin[2]) / imageSpacing[2]);
	reslice->SetOutputExtent(xmin, xmax, ymin, ymax, zmin, zmax);
	reslice->SetBackgroundLevel(0);
	reslice->Update();
	curImageData = reslice->GetOutput();
	ui.ThickModeBox->setCheckState(Qt::Unchecked);
	ui.ColorModeBox->setCheckState(Qt::Unchecked);
	ui.ResliceModeBox->setCheckState(Qt::Unchecked);
	ui.seedTextBrowser->clear();
	_index.clear();
	ShowImage(curImageData);
}


void mainwindow::ShowStatistics(){
	vtkSmartPointer<vtkImageAccumulate> iAccumulate =
		vtkSmartPointer<vtkImageAccumulate>::New();
	iAccumulate->SetInputData(curImageData);
	iAccumulate->IgnoreZeroOn();    //Ignore all zero index
	iAccumulate->Update();
	ui.stateTable->setItem(0, 0, new QTableWidgetItem(QString::number(iAccumulate->GetMin()[0])));
	ui.stateTable->setItem(1, 0, new QTableWidgetItem(QString::number(iAccumulate->GetMax()[0])));
	ui.stateTable->setItem(2, 0, new QTableWidgetItem(QString::number(iAccumulate->GetMean()[0])));
	ui.stateTable->setItem(3, 0, new QTableWidgetItem(QString::number(iAccumulate->GetStandardDeviation()[0])));
	ui.stateTable->setItem(4, 0, new QTableWidgetItem(QString::number(iAccumulate->GetVoxelCount())));

}


//Uniform all the error message. Throw error message box according to error type.
void mainwindow::OutputError(int errorType){
	QMessageBox errorMsg;
	switch (errorType){
	case UNDEFINED_IMAGE:
		errorMsg.setText("Undefined Image!");
		break;
	case NULL_POINTS:
		errorMsg.setText("Error Points!");
	default:
		errorMsg.setText("Error");
		break;
		errorMsg.exec();
	}
}



void mainwindow::CalcHeterogeneity(){
	if (NULL != curImageData){
		double heterogeneity = 0;
		heterogeneity = AlgorithmUtils::calcHeterogeneity(curImageData);
		ui.stateTable->setItem(7, 0, new QTableWidgetItem(QString::number(heterogeneity)));
	}
	else{
		OutputError(UNDEFINED_IMAGE);
	}
}


void mainwindow::ShowAbout(){
	QMessageBox aboutMsg;

}