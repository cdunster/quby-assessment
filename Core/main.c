/**
 * @file
 * @brief	The main file of the project.
 *
 * The file that contains the program entry point and any higher-level functionality.
 */

#include <stdio.h>
#include "Example.h"

/**
 * @brief	Program entry point.
 *
 * @return	Fault code. 0 if no faults.
 */
int main(void)
{
	printf("Value is %u\n", GetValue());
	return 0;
}
