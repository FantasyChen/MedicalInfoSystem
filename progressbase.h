#ifndef PROGRESSBASE_H
#define PROGRESSBASE_H

#include <QWidget>
#include "ui_progressbase.h"
#include "qprogressbar.h"
#include "itkCommand.h"
#include "itkProgressAccumulator.h"
class ProgressBase : public QWidget
{
	Q_OBJECT
	typedef itk::MemberCommand<ProgressBase>  RedrawCommandType;
private:
	ProgressBase(QWidget *parent = 0);
	Ui::ProgressBase ui;
	RedrawCommandType::Pointer m_RedrawCommand;

public:
	~ProgressBase();
	/** Get Command */
	RedrawCommandType * GetRedrawCommand(void) const;


	/** Manage a Progress event */
	void ProcessEvent(itk::Object * caller, const itk::EventObject & event);
	void ConstProcessEvent(const itk::Object * caller, const itk::EventObject & event);


	/** Manage a Progress event */
	void Observe(itk::Object *caller);
	static ProgressBase *GetInstance()
	{
		static ProgressBase* instance = new ProgressBase;
		return instance;
	}
};

#endif // PROGRESSBASE_H
