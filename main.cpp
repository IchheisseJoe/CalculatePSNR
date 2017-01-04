#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "PCMFile.h"
#include "PSNR.h"

using namespace std;
/*
template <class _X> void ShowFile(PCMFile<_X>& pcmfile)
{
	printf("File size   = %lu\n", pcmfile.Size());
	printf("Sample size = %lu\n", pcmfile.SampleSize());
	printf("Time lenght = %lu\n", pcmfile.TimeLength());
//	uint64_t temp=(uint64_t)-1;
//	_X max = (_X)temp;
}
*/


void ShowUsage(char *szAppName)
{
	
}

int main(int argc, char* argv[])
{
	
	int 	nSample;
	int 	nDatabit;
	int 	nChannel;
	char	*szSourceFileName, *szTargetFileName;
	
	for(int i=1; i< argc; )
	{
		if(strcmp(argv[i], "-s")==0)
			nSample = atoi(argv[++i]);
		else if(strcmp(argv[i], "-b")==0)
			nDatabit = atoi(argv[++i]);
		else if(strcmp(argv[i], "-c")==0)
			nChannel = atoi(argv[++i]);
		else if(strcmp(argv[i], "-g")==0)
			szSourceFileName = argv[++i];
		else if(strcmp(argv[i], "-t")==0)
			szTargetFileName = argv[++i];
		else
		{
			fprintf(stderr, "Unknow parameter %s\n", argv[i]);
			goto err_out;
		}
		i++;
	}
	if(nDatabit == 16)
	{
		PCMFile<int16_t>	m_PCM16SFile(szSourceFileName, nDatabit, nSample, nChannel);
		PCMFile<int16_t>	m_PCM16TFile(szTargetFileName, nDatabit, nSample, nChannel);
		
		if(m_PCM16SFile.Open() && m_PCM16TFile.Open())
		{
			//printf("File size = %lu\n", m_PCM16File.Size());
			//printf("Sample size = %lu\n", m_PCM16File.SampleSize());
			//printf("Time lenght = %lu\n", m_PCM16File.TimeLength());
			//ShowFile<int16_t>(m_PCM16File);
			double psnr=CalculatePSNR<int16_t>(m_PCM16SFile, m_PCM16TFile);
			cout<<"PSNR = "<<psnr<<endl;
			m_PCM16SFile.Close();
			m_PCM16TFile.Close();
		}
	}
	else if(nDatabit == 8)
	{
		PCMFile<int8_t>		m_PCM8SFile(szSourceFileName, nDatabit, nSample, nChannel);
		PCMFile<int8_t>		m_PCM8TFile(szTargetFileName, nDatabit, nSample, nChannel);
		if(m_PCM8SFile.Open() && m_PCM8TFile.Open())
		{
			//printf("File size = %lu\n", m_PCM8File.Size());
			//printf("Sample size = %lu\n", m_PCM8File.SampleSize());
			//printf("Time lenght = %lu\n", m_PCM8File.TimeLength());
			//ShowFile<int8_t>(m_PCM8File);
			double psnr=CalculatePSNR<int8_t>(m_PCM8SFile, m_PCM8TFile);
			cout<<"PSNR = "<<psnr<<endl;
			m_PCM8SFile.Close();
			m_PCM8TFile.Close();
		}
	}
	
	
err_out:	
	return 0;
}