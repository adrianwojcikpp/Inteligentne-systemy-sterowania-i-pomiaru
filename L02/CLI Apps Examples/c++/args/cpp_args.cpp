/**
 ******************************************************************************
 * @file    /cli_examples/cpp/cpp_args.cpp
 * @author  Adrian Wojcik
 * @version V1.0
 * @date    14-Mar-2020
 * @brief   Raspberry Pi CLI apps example: C++ with getopt
 ******************************************************************************
 */

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
	const char *flagstate[2] = { "RESET", "SET" };
	int aflag = 0;
	int bflag = 0;
	char *cvalue = nullptr;
	int index;
  
	int arg;

	opterr = 0;
	
	std::cout << "C++ CLI example" << std::endl;
	
	/* Standard while/switch procedure for 'getopt' function */
	while((arg = getopt (argc, argv, "abc:")) != -1)
	{
		switch(arg)
		{
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case '?':
				if(optopt == 'c')
					std::cerr << "option -" << static_cast<char>(optopt) << " requires argument" <<std::endl;
				else if(isprint(optopt))
					std::cerr << "option -" << static_cast<char>(optopt) << " not recognized" <<std::endl;   
				else
					std::cerr << "option character \\x" << optopt << " not recognized" <<std::endl;
				return 1;
			default:
				abort();
		}
	}

	/* Printing results */
	std::cout << "a (flag) = " << flagstate[aflag] << std::endl;
	std::cout << "b (flag) = " << flagstate[bflag] << std::endl;
	if(cvalue != nullptr) 
		std::cout << "c (value) = " << cvalue << std::endl;

	for (index = optind; index < argc; index++)
		std::cout << "Non-option argument #" << (index-optind+1) << ": "<<  argv[index] << std::endl;
	
	return 0;
}
