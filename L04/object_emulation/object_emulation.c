#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dsos.h"

/**
 * @brief Saves C-string to text file.
 * @param[in] filename : File name 
 * @param[in] data     : Samples array
 * @param[in] datasize : Number of samples
 * @return None
 */
void save_data_to_file(char* filename, double* data, int datasize)
{
  FILE *hFile;
  hFile = fopen(filename,"w");
  if(hFile == NULL)
  {
    printf("Cannot open '%s' file for writing.", filename);
    return;
  }
  for(int i = 0; i < datasize-1; i++)
  {
	fprintf(hFile,"%f,\n", data[i]);
  }
  fprintf(hFile,"%f", data[datasize-1]);
	
  fclose(hFile);
}

int main()
{
	uint64_t coeffs[] = { 
	// USER CODE BEGIN
	0x3FFFE62F08D2DDB4,   0xBFEFCCB099E06B4F,   0x3ED4A20EABF99825,   0x3EE4A20EABF99825,   0x3ED4A20EABF99825 
	// USER CODE END
	};
	
	const int n = 10000;
	double y[n];
	DSOS_HandleTypeDef obj1;
	DSOS_Init(&obj1, (double*)coeffs);
	
	// Perform step-by-step simulation
	for(int i = 0; i < n; i++)
		y[i] = DSOS_GetOutput(&obj1, 1.0); // Step response
	
	// Log data to file
	save_data_to_file("y.csv", y, n);
	
	return 0;
}