/**
  ******************************************************************************
  * @file    cli_app_template.cpp
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    08-Mar-2022
  * @brief   Instruction #02 tasks solution template
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <getopt.h>

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/

/**
 * Application options structure.
 */
struct options
{
  // USER CODE BEGIN
  bool flag_a;
  bool flag_b;
  double value_c;
  options() : flag_a(false), flag_b(false), value_c(0.0) { }
  // USER CODE END
};

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/

/**
  * @brief Command-line arguments parsing.
  * @param[in] argc : argument count; number of command-line arguments passed 
  *                   by the user including the name of the program.
  * @param[in] argv : argument vector; character pointers (C-strings) listing 
  *                   all the arguments.
  * @param[out] op  : application options structure.
  * @retval 0 
  */
void parse_args(int argc, char* argv[], options* op)
{
  int arg;
  while((arg = getopt(argc, argv, "abc:h")) != -1)
  {
    switch(arg)
    {
      // USER CODE BEGIN
      case 'a':
      {
        op->flag_a = true;
        break;
      }
      case 'b':
      {
        op->flag_b = true;
        break;
      }
      case 'c':
      {
        op->value_c = std::stod(optarg);
        break;
      }
      case 'h':
      {
        std::cout << "Usage: app [options]" << std::endl
                  << "Options:" << std::endl
                  << "-h            Display help message." << std::endl
                  << "-a            [TODO]" << std::endl
                  << "-b            [TODO]" << std::endl
                  << "-c <numeric>  [TODO]" << std::endl;
        break;
      }
      // USER CODE END
      default:
        break;
    }
  }
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @param[in] argc : argument count; number of command-line arguments passed 
  *                   by the user including the name of the program.
  * @param[in] argv : argument vector; character pointers (C-strings) listing 
  *                   all the arguments.
  * @retval 0 
  */
int main(int argc, char* argv[])
{
  options op;
  parse_args(argc, argv, &op);
  
  // USER CODE BEGIN
  std::cout << "Options: a=" << op.flag_a 
                   << ", b=" << op.flag_b 
                   << ", c=" << op.value_c << std::endl;
  // USER CODE END
  
  return 0;
}

/* Function definitions ------------------------------------------------------*/
