/********************************************
*
* Project       : King.cbp
* File creation : 2015-07-31-14.15.45 (2015-07-31-12.15.45 UTC)
*
*********************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "common.h"
#include "country.h"

void print_presentation(){
    tabulation(34);printf("KING\n");
    tabulation(2);printf("CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY\n\n\nDo you want instructions ? (Answer YES, NO or AGAIN - for restarting)\n");
}

void print_instructions(){
    printf("\n\n\nCongratulations! You've just been elected premier of Setats\n");
    printf("Detinu, a small communist island 30 by 70 miles long. Your\n");
    printf("job is to decide upon the contry's budget and distribute\n");
    printf("money to your countrymen from the communal treasury.\n");
    printf("The money system is rallods, and each person needs %d\n",RALLODS_PER_CITIZEN);
    printf("rallods per year to survive. Your country's income comes\n");
    printf("from farm produce and tourists visiting your magnificent\n");
    printf("forests, hunting, fishing, etc. Half your land is farm land\n");
    printf("which also has an excellent mineral content and may be sold\n");
    printf("to foreign industry (strip mining) who import and support\n");
    printf("their own workers. Crops cost between %d and %d rallods per\n",MIN_PLANTING_COSTS,MAX_PLANTING_COSTS);
    printf("square mile to plant.\n");
    printf("Your goal is to complete your %d year term of office.\n",TERM_OFFICE);
    printf("Good luck!\n\n");
}

void tabulation(int n){
    int i;
    for(i=0;i<n;i++)printf("\t");
}

/* Return integer between 0 and n-1 */
unsigned int random(unsigned int n){
    srand(time(0));
    return rand()%n;
}

/* Return integer between a and b */
unsigned int random_ab(unsigned int a,unsigned int b){
    srand(time(0));
    return rand()%(b-a+1)+a;
}

int read_line(char* buffer, size_t size, FILE* file){
    // On r‚cupŠre d'abord la ligne
    int S=0;

    if(fgets(buffer,30,stdin)!=NULL){
        // On enlŠve ensuite le retour … la ligne
        char *position = strchr(buffer, '\n');

        if(position!=NULL){
            S=1;
            *position='\0';
        }
    }

    // On purge enfin le tampon
    //int c = 0;
    printf("\n");
    //while(c!='\n'&&c!=EOF)c=getchar();

    return S;
}

void print_stderr_budget(t_budget budget){
#if DEBUG
    fprintf(stderr,"Budget\n");
    fprintf(stderr,"Treasury : %d\n", budget.treasury);
    fprintf(stderr,"Expenses :\n\tPollution control : %d\n\tFood distribution : %d", budget.pollution_control_budget, budget.distribution_budget);
#endif // DEBUG
}

void print_stderr_population(t_population population){
#if DEBUG
    fprintf(stderr,"\tCitizens : %d (Dead : %d, Foreign Workers : %d)\n",population.citizens,population.dead_citizens,population.foreign_workers);
#endif // DEBUG
}

void print_stderr_land(t_land land){
#if DEBUG
    fprintf(stderr,"\tLand : %d (Planted : %d - Sold : %d)\n",land.land,land.land_planted,land.land_sold);
    fprintf(stderr,"\tSell prices : %d - Planting costs : %d \n",land.land_price, land.planting_costs);
#endif // DEBUG
}

void print_stderr_country(t_country country){
#if DEBUG
    fprintf(stderr,"Country values (Turn %d) :\n", country.turn);
    print_stderr_population(country.population);
    print_stderr_land(country.land);
    print_stderr_budget(country.budget);
    fprintf(stderr,"\tEnding : %d\n",country.ending);
#endif // DEBUG
}