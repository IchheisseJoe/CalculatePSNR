#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "PCMFile.h"

using namespace std;

template <class _X> void ShowFile(PCMFile<_X>& pcmfile)
{
	printf("File size   = %lu\n", pcmfile.Size());
	printf("Sample size = %lu\n", pcmfile.SampleSize());
	printf("Time lenght = %lu\n", pcmfile.TimeLength());

	
}

void ShowUsage(char *szAppName)
{
	
}

int main(int argc, char* argv[])
{
	
	int 	nSample;
	int 	nDatabit;
	int 	nChannel;
	char	*szFileName;
	
	for(int i=1; i< argc; )
	{
		if(strcmp(argv[i], "-s")==0)
			nSample = atoi(argv[++i]);
		else if(strcmp(argv[i], "-b")==0)
			nDatabit = atoi(argv[++i]);
		else if(strcmp(argv[i], "-c")==0)
			nChannel = atoi(argv[++i]);
		else if(strcmp(argv[i], "-g")==0)
			szFileName = argv[++i];
		else
		{
			fprintf(stderr, "Unknow parameter %s\n", argv[i]);
			goto err_out;
		}
		i++;
	}
	if(nDatabit == 16)
	{
		PCMFile<int16_t>	m_PCM16File(szFileName, nDatabit, nSample, nChannel);
		if(m_PCM16File.Open())
		{
			//printf("File size = %lu\n", m_PCM16File.Size());
			//printf("Sample size = %lu\n", m_PCM16File.SampleSize());
			//printf("Time lenght = %lu\n", m_PCM16File.TimeLength());
			ShowFile<int16_t>(m_PCM16File);
			m_PCM16File.Close();
		}
	}
	else if(nDatabit == 8)
	{
		PCMFile<int8_t>		m_PCM8File(szFileName, nDatabit, nSample, nChannel);
		if(m_PCM8File.Open())
		{
			//printf("File size = %lu\n", m_PCM8File.Size());
			//printf("Sample size = %lu\n", m_PCM8File.SampleSize());
			//printf("Time lenght = %lu\n", m_PCM8File.TimeLength());
			ShowFile<int8_t>(m_PCM8File);
			m_PCM8File.Close();
		}
	}
	
	
err_out:	
	return 0;
}