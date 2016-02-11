#include "progressbase.h"

ProgressBase::ProgressBase(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_RedrawCommand = RedrawCommandType::New();
	m_RedrawCommand->SetCallbackFunction(this, &ProgressBase::ProcessEvent);
	m_RedrawCommand->SetCallbackFunction(this, &ProgressBase::ConstProcessEvent);

}

ProgressBase::~ProgressBase()
{

}


ProgressBase::RedrawCommandType *ProgressBase::GetRedrawCommand(void) const
{
	return m_RedrawCommand.GetPointer();
}



void ProgressBase::ProcessEvent(itk::Object * caller, const itk::EventObject & event)
{
	if (typeid(itk::ProgressEvent) == typeid(event))
	{
		 itk::ProcessObject::Pointer  process = dynamic_cast<itk::ProcessObject *>(caller);

		const int value = static_cast<int>(
			process->GetProgress() * ui.progressBar->maximum());
		ui.progressBar->setValue(value);
		ui.progressBar->repaint();
		QApplication::processEvents();      //The GUI is pending. Strike it to move.
	}
}



void ProgressBase::ConstProcessEvent(const itk::Object * caller, const itk::EventObject & event)
{
	if (typeid(itk::ProgressEvent) == typeid(event))
	{
		itk::ProcessObject::ConstPointer  process =
			dynamic_cast<const itk::ProcessObject *>(caller);

		const int value = static_cast<int>(
			process->GetProgress() * ui.progressBar->maximum());
		ui.progressBar->setValue(value);
		ui.progressBar->repaint();
		QApplication::processEvents();      //The GUI is pending. Strike it to move.
	}
}


void ProgressBase::Observe(itk::Object *caller)
{
	caller->AddObserver(itk::ProgressEvent(), m_RedrawCommand.GetPointer());
}


