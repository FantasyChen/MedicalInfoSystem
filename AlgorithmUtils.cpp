#include "AlgorithmUtils.h"

double AlgorithmUtils::calcHeterogeneity(vtkImageData* rawImageData){
	int imageDims[3];
	double imageOrigin[3];
	double imageSpacing[3];
	double imageCenter[3];
	int imageExtent[6];
	double imageRange[2];

	rawImageData->GetDimensions(imageDims);
	rawImageData->GetOrigin(imageOrigin);
	rawImageData->GetSpacing(imageSpacing);
	rawImageData->GetCenter(imageCenter);
	rawImageData->GetExtent(imageExtent);
	rawImageData->GetScalarRange(imageRange);

	double hetero_Num = 0;    //numerator 
	double hetero_Deno = 0;   //denominator
	double hetero_Num_Cur = 0;   //current xi-xmean
	double hetero_Deno_Weight = 0;
	double hetero_Deno_Main = 0;

	double theresholdValue = 0;
	double theresholdPercent = 0.3; //define the theresholdPercent
	double maxValue = 0;
	double curVoxel = 0;
	double calcVoxel = 0;
	double spacingRatioZ = imageSpacing[2] / imageSpacing[0];
	double spacingRatioY = imageSpacing[1] / imageSpacing[0];
	double totalValue = 0;
	int voxelNum = 0;
	double meanValue = 0;
	//calculate the mean value and the valid voxels
	for (int i = imageExtent[0]; i <= imageExtent[1]; i++){
		for (int j = imageExtent[2]; j <= imageExtent[3]; j++){
			for (int k = imageExtent[4]; k <= imageExtent[5]; k++){
				curVoxel = rawImageData->GetScalarComponentAsDouble(i, j, k, 0);
				//suppose the empty space to be zero
				if (curVoxel != 0) {
					maxValue = curVoxel > maxValue ? curVoxel : maxValue;
					voxelNum++;
					totalValue += curVoxel;
				}
				else{
					//do nothing
				}
			}
		}
	}
	meanValue = totalValue / voxelNum;
	theresholdValue = maxValue * theresholdPercent;
	
	for (int i = imageExtent[0]; i <= imageExtent[1]; i++){
		for (int j = imageExtent[2]; j <= imageExtent[3]; j++){
			for (int k = imageExtent[4]; k <= imageExtent[5]; k++){
				curVoxel = rawImageData->GetScalarComponentAsDouble(i, j, k, 0);
				//suppose the empty space to be zero
				if (curVoxel >= theresholdValue) { 
					hetero_Num_Cur = curVoxel - meanValue;
					hetero_Deno_Main += hetero_Num_Cur * hetero_Num_Cur;
					//case up (i,j,k++)       
					if (k < imageExtent[5]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i, j, k + 1, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * spacingRatioZ;
							hetero_Deno_Weight += spacingRatioZ;
						}
					}
					//case down (i,j,k--)
					if (k > imageExtent[4]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i, j, k - 1, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * spacingRatioZ;
							hetero_Deno_Weight += spacingRatioZ;
						}
					}
					//case front (i,j++,k)
					if (j < imageExtent[3]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i, j + 1, k, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * spacingRatioY;
							hetero_Deno_Weight += spacingRatioY;
						}
					}
					//case back (i,j--,k)
					if (j > imageExtent[2]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i, j - 1, k, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * spacingRatioY;
							hetero_Deno_Weight += spacingRatioY;
						}
					}
					//case left (i--,j,k)
					if (i > imageExtent[0]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i - 1, j, k, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * 1;
							hetero_Deno_Weight += 1;
						}
					}
					//case right
					if (i < imageExtent[1]){  //if exists
						calcVoxel = rawImageData->GetScalarComponentAsDouble(i + 1, j, k, 0);
						if (calcVoxel != 0){
							hetero_Num += hetero_Num_Cur*(calcVoxel - meanValue) * 1;
							hetero_Deno_Weight += 1;
						}
					}
				}
				else{
					//do nothing
				}
			}
		}
	}
	hetero_Deno = hetero_Deno_Main * hetero_Deno_Weight / voxelNum;
	return hetero_Num / hetero_Deno;
}


vtkImageData* AlgorithmUtils::calcSmallesetEffectRegion(vtkImageData* rawImageData){
	return rawImageData;
}