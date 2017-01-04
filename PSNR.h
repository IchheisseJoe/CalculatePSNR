#ifndef __PSNR_H__
#define __PSNR_H__
#include <stdint.h>
#include <math.h>
#include <iostream>
#include "PCMFile.h"

using namespace std;

template <typename _T>
double CalculatePSNR(PCMFile<_T>& source, PCMFile<_T>& target)
{
	uint64_t 	ulMinSize;
	uint64_t 	ulIndex;
	uint64_t 	ulMSE=0;
	_T			s, t;
	uint32_t 	R;
	
	ulMinSize=source.SampleSize() < target.SampleSize()?source.SampleSize():target.SampleSize();
	for(ulIndex=0; ulIndex < ulMinSize; ulIndex++)
	{
		s=source.GetSample();
		t=target.GetSample();
		ulMSE += ((s-t)*(s-t));
	}
	ulMSE /= ulMinSize;
	R=(unsigned) source.GetPeakValue();
	cout<<"R = "<<R<<endl;
	if(ulMSE == 0)
		return 0;
	return 10.0*log10((double)((R*R)/ulMSE));
}

#endif
