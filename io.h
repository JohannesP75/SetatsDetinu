#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include "country.h"
/********************************************
*
* Project       : King.cbp
* File creation : 2015-07-18-18.35.03 (2015-07-18-16.35.03 UTC)
*
*********************************************/

void print_presentation();

void print_instructions();

void tabulation(int n);

int read_line(char* buffer, size_t size, FILE* file);

void print_stderr_budget(t_budget budget);

void print_stderr_population(t_population population);

void print_stderr_land(t_land land);

void print_stderr_country(t_country country);

#endif // IO_H_INCLUDED