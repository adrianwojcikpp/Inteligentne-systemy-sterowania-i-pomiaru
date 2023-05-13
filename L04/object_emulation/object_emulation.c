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
    0x3FFE73157290ECF3,   0xBFECE7777FC82207,   0x3EF4C9AA64820B98,   0x3F04C9AA64820B98,   0x3EF4C9AA64820B98
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






