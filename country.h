#ifndef COUNTRY_H_INCLUDED
#define COUNTRY_H_INCLUDED

/********************************************
*
* Project       : King.cbp
* File creation : 2015-07-18-19.09.30 (2015-07-18-17.09.30 UTC)
*
*********************************************/

#include "common.h"

#define MIN_STARTING_TREASURY 59001
#define MAX_STARTING_TREASURY 60999
#define MIN_STARTING_POPULATION 491
#define MAX_STARTING_POPULATION 509
#define MIN_LAND_PRICE 95
#define MAX_LAND_PRICE 105
#define MIN_PLANTING_COSTS 10
#define MAX_PLANTING_COSTS 15
#define STARTING_LAND 2000
#define FORESTED_LAND 1000
#define STARTING_FOREIGN_WORKERS 0
#define TERM_OFFICE 8
#define RALLODS_PER_CITIZEN 100
#define LAND_PLANTED_PER_CITIZEN 2
#define BURIAL_COST 9
#define MAXIMUM_DEATHS_BEFORE_LOSING 200
#define CITIZENS_NUMBER_FLOOR 343
#define MAXIMUM_CASH_IN_OLD_TREASURY 500

typedef struct t_budget{
    unsigned int treasury,pollution_control_budget,distribution_budget;
}t_budget;

typedef struct t_population{
    unsigned int citizens, dead_citizens, foreign_workers, starved_citizens, polluted_citizens,incoming_migrants;
    int migrating_citizens;
}t_population;

typedef struct t_land{
    unsigned int land,land_planted,land_price,land_sold,planting_costs;
}t_land;

typedef struct t_country{
    unsigned int /*land,land_planted,land_price,land_sold,planting_costs,*/turn;
    t_land land;
    t_budget budget;
    t_population population;
    t_ending ending;
}t_country;

void init_country(t_country* country);

void init_country_restart(t_country* country);

void init_budget(t_budget* budget);

void turn_playing_country(t_country* country);

void land_selling_management(t_country* country);

void land_planting_management(t_country* country);

void rallods_distribution_management(t_country* country);

void pollution_management(t_country* country);

void print_presentation_country(t_country country);

void end_turn_computing(t_country* country); // Formerly "ending_magamement"

void ending_management(t_country country); // Formerly "ending_magamement"

#endif // COUNTRY_H_INCLUDED