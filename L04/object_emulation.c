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
	// USER CODE BEGIN
	uint64_t coeffs[] = {0x3FFFE62F08D2DDB4,   0xBFEFCCB099E06B4F,   0x3ED4A20EABF99825,   0x3EE4A20EABF99825,   0x3ED4A20EABF99825};
	//{0x3FFFD06C3C8719B4, 0xBFEFA0FB38F95D55, 0x3EC15FF594F63F2E, 0x3ED15FF594F63F2E, 0x3EC15FF594F63F2E};
	// USER CODE END
	
	const int n = 10000;
	double y[n];
	struct dsos obj1;
	dsos_init(&obj1, (double*)coeffs);
	
	// Perform step-by-step simulation
	for(int i = 0; i < n; i++)
		y[i] = lsim_step(&obj1, 1.0); // Step response
	
	// Log data to file
	save_data_to_file("y.csv", y, n);
	
	return 0;
}