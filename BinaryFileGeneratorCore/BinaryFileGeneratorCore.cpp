// BinaryFileGeneratorCore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

FILE *dataText = NULL;
FILE *binaryFile = NULL;

static int open_data_text(TCHAR *dataFileName)
{
	_tfopen_s(&dataText, dataFileName, _T("r"));
	if (!dataText)
	{
		return -1;
	}
	return 0;
}

static int open_binary_file(TCHAR *binaryFileName)
{
	_tfopen_s(&binaryFile, binaryFileName, _T("wb+"));
	if (!binaryFile)
	{
		return -1;
	}
	return 0;
}

static char ascii_to_hex(char data)
{
	if (data >= '0' && data <= '9')
	{
		return data - '0';
	}
	else if (data >= 'a' && data <= 'f')
	{
		return data - 'a' + 10;
	}
	else if (data >= 'A' && data <= 'F')
	{
		return data - 'A' + 10;
	}
	else
	{
		return -1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char spaceData = 0, hData = 0, lData = 0;
	unsigned char outData = 0;
	if (open_data_text(argv[1]) < 0)
	{
		printf("Error: open data file failed.\n");
		return -1;
	}

	if (open_binary_file(argv[2]) < 0)
	{
		printf("Error: open binary file failed.\n");
		return -1;
	}

	while (1)
	{
		hData = ascii_to_hex(fgetc(dataText));
		lData = ascii_to_hex(fgetc(dataText));
		if ((hData == EOF) || (lData == EOF))
		{
			break;
		}
		outData = (hData<<4) + lData;
		printf("%x ", outData);
		if (fwrite(&outData, sizeof(char), 1, binaryFile) != 1)
		{
			printf("Error: write binary file failed.\n");
			break;
		}
		spaceData = fgetc(dataText);
		if ((spaceData != ' ') && (spaceData != EOF))
		{
			printf("Error: please use space between bytes.\n");
			break;
		}
	} 


	fclose(dataText);
	fclose(binaryFile);
	return 0;
}

