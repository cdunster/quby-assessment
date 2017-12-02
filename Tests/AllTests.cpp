/**
 * @file
 * @brief       The main file for running the unit tests.
 *
 * The file that contains the program entry point when running the unit tests
 * and calls the MACRO function that runs all of the unit tests in the project.
 */

#include "CppUTest/CommandLineTestRunner.h"

/**
 * @brief       Run all of the unit tests in the project.
 */
int main(int ac, char** av)
{
    return RUN_ALL_TESTS(ac, av);
}
