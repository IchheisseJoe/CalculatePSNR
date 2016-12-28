#ifndef __PCM_FILE__
#define __PCM_FILE__

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <string>

template <class _T> class PCMFile
{
private:
	uint64_t	m_ulSize;
	FILE		*m_pFile;
	int			m_nDataBit, m_nSamplingRate, m_nChannels;
	std::string	m_strFileName;
	
public:
	PCMFile(char *szName, int data_bit, int sampling, int channel);
	~PCMFile();
	bool		Open();
	void		Close();
	bool		IsEOF();
	uint64_t	Size();
	_T 			GetSample();
	uint64_t	Trim();
	uint64_t	SampleSize();
	uint64_t	TimeLength();
};


template <class _T> 
PCMFile<_T>::PCMFile(char* szName, int data_bit, int sampling, int channel) : m_pFile(NULL)
{
	m_strFileName	= szName;
	m_nDataBit		= data_bit;
	m_nSamplingRate	= sampling;
	m_nChannels		= channel;
}

template <class _T> 
PCMFile<_T>::~PCMFile()
{
	Close();
}

template <class _T> 
bool PCMFile<_T>::Open()
{
	m_pFile	= fopen(m_strFileName.c_str(), "r");
	if(m_pFile == NULL)
	{
		fprintf(stderr, "cannot open file due to : (%d) %s\n", errno, strerror(errno));
		return false;
	}
	fseek(m_pFile, 0L, SEEK_END);
	m_ulSize = (uint64_t)ftell(m_pFile);
	fseek(m_pFile, 0L, SEEK_SET);
	return true;
}

template <class _T> 
bool PCMFile<_T>::IsEOF()
{
	return (feof(m_pFile)!=0);
}

template <class _T> 
void PCMFile<_T>::Close()
{
	if(m_pFile!=NULL)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

template <class _T> 
_T PCMFile<_T>::GetSample()
{
	_T sample;
	fread(&sample, sizeof(_T), 1, m_pFile);
	return sample;
}

template <class _T> 
uint64_t PCMFile<_T>::Size()
{
	return m_ulSize;
}

template <class _T>
uint64_t PCMFile<_T>::Trim()
{

}

template <class _T>
uint64_t PCMFile<_T>::SampleSize()
{
	return m_ulSize/(sizeof(_T)*m_nChannels);
}

template <class _T>
uint64_t PCMFile<_T>::TimeLength()
{
	return SampleSize()/m_nSamplingRate;
}



#endif