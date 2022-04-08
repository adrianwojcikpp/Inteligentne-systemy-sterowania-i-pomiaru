#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct dsos {
	double a1, a2, b0, b1, b2;
	double u_prev[2];
	double y_prev[2];
};

/**
 * @brief Initialization second order system
 * @param[out] sys    : Second order system structure
 * @param[in]  coeffs : Raw coefficients 
 */
 void dsos_init(struct dsos* sys, double* coeffs)
 {
	sys->a1 = coeffs[0]; 
	sys->a2 = coeffs[1];
	sys->b0 = coeffs[2]; 
	sys->b1 = coeffs[3]; 
	sys->b2 = coeffs[4];	 
 }

/**
 * @brief Single-step second order system simulation
 * @param[in/out] sys : Second order system structure
 * @param[in]     u   : Input signal sample
 * @return System response 
 */
double lsim_step(struct dsos* sys, double u)
{
	double y = sys->a1*sys->y_prev[0] + sys->a2*sys->y_prev[1] + sys->b0*u + sys->b1*sys->u_prev[0] + sys->b2*sys->u_prev[1];
	sys->y_prev[1] = sys->y_prev[0];
	sys->y_prev[0] = y;
	sys->u_prev[1] = sys->u_prev[0];
	sys->u_prev[0] = u;
	return y;
}

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