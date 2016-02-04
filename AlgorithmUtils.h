#ifndef ALGORITHMUTILS_H
#define ALGORITHMUTILS_H


#include "mainwindow.h"
#include "vtkImageData.h"

class AlgorithmUtils{
public:
	AlgorithmUtils(){
	}
	~AlgorithmUtils(){};
	static double calcHeterogeneity(vtkImageData* rawImageData);

private:

};
#endif