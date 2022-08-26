/********************************************
*
* Project       : King.cbp
* File creation : 2015-07-31-14.14.40 (2015-07-31-12.14.40 UTC)
*
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include "country.h"
#include "common.h"
#include "io.h"

void init_country(t_country* country){
    if(country!=NULL){
        country->ending=END_NONE;
        country->turn=1;

        // Population
        memset(&(country->population),0, sizeof(t_population));
        country->population.citizens=random_ab(MIN_STARTING_POPULATION,MAX_STARTING_POPULATION);
        country->population.foreign_workers=STARTING_FOREIGN_WORKERS;

        // Land
        country->land.land_price=random_ab(MIN_LAND_PRICE,MAX_LAND_PRICE);
        country->land.planting_costs=random_ab(MIN_PLANTING_COSTS,MAX_PLANTING_COSTS);
        country->land.land=STARTING_LAND;
        country->land.land_planted=0;
        country->land.land_sold=0;

        init_budget(&(country->budget));
    }
}

void init_country_restart(t_country* country){
//1960 PRINT "HOW MANY YEARS HAD YOU BEEN IN OFFICE WHEN INTERRUPTED";
//1961 INPUT X5
//1962 IF X5<0 THEN 1590
//1963 IF X5<8 THEN 1969
//1965 PRINT "   COME ON, YOUR TERM IN OFFICE IS ONLY";N5;"YEARS."
//1967 GOTO 1960
//1969 PRINT "HOW MUCH DID YOU HAVE IN THE TREASURY";
//1970 INPUT A
//1971 IF A<0 THEN 1590
//1975 PRINT "HOW MANY COUNTRYMEN";
//1976 INPUT B
//1977 IF B<0 THEN 1590
//1980 PRINT "HOW MANY WORKERS";
//1981 INPUT C
//1982 IF C<0 THEN 1590
//1990 PRINT "HOW MANY SQUARE MILES OF LAND";
//1991 INPUT D
//1992 IF D<0 THEN 1590
//1993 IF D>2000 THEN 1996
//1994 IF D>1000 THEN 100
//1996 PRINT "   COME ON, YOU STARTED WITH 1000 SQ. MILES OF FARM LAND"
//1997 PRINT "   AND 10,000 SQ. MILES OF FOREST LAND."
//1998 GOTO 1990
    unsigned int input;

    // Term
    do{
        printf("How many years had you been in office when interrupted\n");
        scanf("%d",&input);

        if(input>TERM_OFFICE){
            tabulation(1);
            printf("Come on, your term in office is only %d years.\n", TERM_OFFICE);
        }
    }while(input>TERM_OFFICE);
    country->turn=input;

    // Treasury
    do{
        printf("How much did you have in the treasury\n");
        scanf("%d",&input);
    }while(input<0);
    country->budget.treasury=input;

    // Population
    do{
        printf("How many countrymen");
        scanf("%d",&input);
    }while(input<0);
    country->population.citizens=input;

    // Workers
    do{
        printf("How many workers\n");
        scanf("%d",&input);
    }while(input<0);
    country->population.foreign_workers=input;

    // Land
    do{
        printf("How many square miles of land\n");
        scanf("%d",&input);

        if(input>STARTING_LAND){
            tabulation(2);printf("Come on, you started with %d sq. miles of farm land\n", STARTING_LAND);
            tabulation(2);printf("and %d sq. miles of forest land.\n", FORESTED_LAND);
        }
    }while(input<FORESTED_LAND||input>STARTING_LAND);
    country->population.foreign_workers=input;
}

void init_budget(struct t_budget* budget){
    budget->treasury=random_ab(MIN_STARTING_TREASURY,MAX_STARTING_TREASURY);
    budget->pollution_control_budget=0;
    budget->distribution_budget=0;
}

void turn_playing_country(t_country* country){
    country->land.land_price=random_ab(MIN_LAND_PRICE,MAX_LAND_PRICE);
    country->land.planting_costs=random_ab(MIN_PLANTING_COSTS,MAX_PLANTING_COSTS);

    print_presentation_country(*country);
    land_selling_management(country);
    rallods_distribution_management(country);
    land_planting_management(country);
    pollution_management(country);

    if((country->land.land_sold<0)||(country->budget.distribution_budget<0)||(country->land.land_planted<0)||(country->budget.pollution_control_budget<0))
        country->ending=END_WILFUL_ABANDON;
}

void land_selling_management(t_country* country){
//200 PRINT "HOW MANY SQUARE MILES DO YOU WISH TO SELL TO INDUSTRY";
//210 INPUT H
//215 IF H<0 THEN 200
//220 IF H<=D-1000 THEN 300
//230 PRINT "***  THINK AGAIN. YOU ONLY HAVE";D-1000;"SQUARE MILES OF FARM LAND."
//240 IF X<>0 THEN 200
//250 PRINT:PRINT "(FOREIGN INDUSTRY WILL ONLY BUY FARM LAND BECAUSE"
//260 PRINT "FOREST LAND IS UNECONOMICAL TO STRIP MINE DUE TO TREES,"
//270 PRINT "THICKER TOP SOIL, ETC.)"
//280 X=1
//299 GOTO 200
//300 D=INT(D-H)
//310 A=INT(A+(H*W))
    unsigned int land_to_sell;

    do{
        printf("How many square miles do you wish to sell to industry\n");
        scanf("%d",&land_to_sell);

        if(land_to_sell>country->land.land-FORESTED_LAND)
            printf("***  THINK AGAIN. YOU ONLY HAVE %d SQUARE MILES OF FARM LAND.\n",country->land.land-FORESTED_LAND);
    }while(land_to_sell<0||land_to_sell>country->land.land-FORESTED_LAND);

    country->land.land-=land_to_sell;
    country->budget.treasury+=land_to_sell*country->land.land_price;

    print_stderr_country(*country);
}

void land_planting_management(t_country* country){
//410 PRINT "HOW MANY SQUARE MILES DO YOU WISH TO PLANT";
//420 INPUT J
//421 IF J<0 THEN 410
//422 IF J<=B*2 THEN 426
//423 PRINT "   SORRY, BUT EACH COUNTRYMAN CAN ONLY PLANT 2 SQ. MILES."
//424 GOTO 410
//426 IF J<=D-1000 THEN 430
//427 PRINT "   SORRY, BUT YOU'VE ONLY";D-1000;"SQ. MILES OF FARM LAND."
//428 GOTO 410
//430 U1=INT(J*V9)
//435 IF U1<A THEN 500
//440 IF U1=A THEN 490
//450 PRINT "   THINK AGAIN. YOU'VE ONLY";A;" RALLODS LEFT IN THE TREASURY."
//460 GOTO 410
//490 K=0
//495 A=0
//499 GOTO 1000
//500 A=A-U1
    unsigned int land_to_plant;

    do{
        printf("How many square miles do you wish to plant\n");
        scanf("%d",&land_to_plant);

        if(land_to_plant>country->population.citizens*LAND_PLANTED_PER_CITIZEN)
            printf("\tSORRY, BUT EACH COUNTRYMAN CAN ONLY PLANT %d SQ. MILES.\n",LAND_PLANTED_PER_CITIZEN);
        if(land_to_plant>country->land.land-FORESTED_LAND)
            printf("\tSORRY, BUT YOU'VE ONLY %d SQ. MILES OF FARM LAND.\n",country->land.land-FORESTED_LAND);
        if(country->land.planting_costs*land_to_plant>country->budget.treasury)
            printf("\tTHINK AGAIN. YOU'VE ONLY %d RALLODS LEFT IN THE TREASURY.",country->budget.treasury);
    }while(land_to_plant<0||
           land_to_plant>country->population.citizens*LAND_PLANTED_PER_CITIZEN||
           land_to_plant>country->land.land-FORESTED_LAND||
           country->land.planting_costs*land_to_plant>country->budget.treasury);

    country->land.land_planted=land_to_plant;

    print_stderr_country(*country);
}

void rallods_distribution_management(t_country* country){
//320 PRINT "HOW MANY RALLODS WILL YOU DISTRIBUTE AMONG YOUR COUNTRYMEN";
//340 INPUT I
//342 IF I<0 THEN 320
//350 IF I<A THEN 400
//360 IF I=A THEN 380
//370 PRINT "   THINK AGAIN. YOU'VE ONLY";A;" RALLODS IN THE TREASURY"
//375 GOTO 320
//380 J=0
//390 K=0
//395 A=0
//399 GOTO 1000
//400 A=INT(A-I)
    unsigned int rallods_to_distribute;

    do{
        printf("How many rallods will you distribute among your countrymen\n");
        scanf("%d",&rallods_to_distribute);

        if(rallods_to_distribute>country->budget.treasury)
            printf("\tTHINK AGAIN. YOU'VE ONLY %d RALLODS IN THE TREASURY\n",country->budget.treasury);
    }while(rallods_to_distribute>country->budget.treasury||rallods_to_distribute<0);

    country->budget.treasury-=rallods_to_distribute;
    country->budget.distribution_budget=rallods_to_distribute;

    print_stderr_country(*country);
}

void pollution_management(t_country* country){
//510 PRINT "HOW MANY RALLODS DO YOU WISH TO SPEND ON POLLUTION CONTROL";
//520 INPUT K
//522 IF K<0 THEN 510
//530 IF K<=A THEN 1000
//540 PRINT "   THINK AGAIN. YOU ONLY HAVE ";A;" RALLODS REMAINING."
//550 GOTO 510
    unsigned int pollution_control;

    do{
        printf("How many rallods do you wish to spend on pollution control\n");
        scanf("%d",&pollution_control);

        if(pollution_control>country->budget.treasury)
            printf("\tTHINK AGAIN. YOU ONLY HAVE %d RALLODS REMAINING.",country->budget.treasury);
    }while(pollution_control<0||pollution_control>country->budget.treasury);

    country->budget.pollution_control_budget=pollution_control;
    country->budget.treasury-=country->budget.pollution_control_budget;

    print_stderr_country(*country);
}

void print_presentation_country(t_country country){
//105 PRINT "YOU NOW HAVE ";A;" RALLODS IN THE TREASURY."
//110 PRINT INT(B);:PRINT "COUNTRYMEN, ";
//115 V9=INT(((RND(1)/2)*10+10))
//120 IF C=0 THEN 140
//130 PRINT INT(C);"FOREIGN WORKERS, ";
//140 PRINT "AND";INT(D);"SQ. MILES OF LAND."
//150 PRINT "THIS YEAR INDUSTRY WILL BUY LAND FOR";W;
//152 PRINT "RALLODS PER SQUARE MILE."
//155 PRINT "LAND CURRENTLY COSTS";V9;"RALLODS PER SQUARE MILE TO PLANT."
//162 PRINT
    printf("\nYou now have %d rallods in the Treasury.\n",country.budget.treasury);
    printf("%d countrymen, \n",country.population.citizens);
    if(country.population.foreign_workers!=0)printf("%d foreign workers, \n",country.population.foreign_workers);
    printf("and %d sq. miles of land.\n",country.land.land);
    printf("This year industry will buy land for %d\n",country.land.land_price);
    printf("rallods per square mile.\n");
    printf("Land currently costs %d rallods per square mile to plant\n",country.land.planting_costs);
}

void end_turn_computing(t_country* country){
    unsigned int old_treasury=country->budget.treasury,starved_citizens=0,polluted_citizens=(STARTING_LAND-country->land.land)*random(101)/100.0;
    unsigned int old_population=country->population.citizens;

//1002 PRINT
//1003 PRINT
//1010 A=INT(A-K)
//1020 A4=A
//1100 IF INT(I/100-B)>=0 THEN 1120
//1105 IF I/100<50 THEN 1700
//1110 PRINT INT(B-(I/100));"COUNTRYMEN DIED OF STARVATION"

    // Food management
    if(!(country->budget.distribution_budget/RALLODS_PER_CITIZEN>=country->population.citizens)){
        starved_citizens=country->population.citizens-country->budget.distribution_budget/RALLODS_PER_CITIZEN;

        if(country->budget.distribution_budget/RALLODS_PER_CITIZEN<50)
            country->ending=END_WILFUL_FAMINE;
        else
            printf("%d countrymen died of starvation\n",starved_citizens);
    }

//1120 F1=INT(RND(1)*(2000-D))
//1122 IF K<25 THEN 1130
//1125 F1=INT(F1/(K/25))
//1130 IF F1<=0 THEN 1150
//1140 PRINT F1;"COUNTRYMEN DIED OF CARBON-MONOXIDE AND DUST INHALATION"

    // Pollution management
    if(country->budget.pollution_control_budget<25){
        int buffer=(country->budget.pollution_control_budget>1)?country->budget.pollution_control_budget:1;
        if(buffer==0)buffer=1;
        polluted_citizens*=25/buffer;
    }

    if(polluted_citizens>0)
        printf("%d countrymen died of carbon-monoxide and dust inhalation\n",polluted_citizens);

//1150 IF INT((I/100)-B)<0 THEN 1170
//1160 IF F1>0 THEN 1180
//1165 GOTO 1200
//1170 PRINT "   YOU WERE FORCED TO SPEND";INT((F1+(B-(I/100)))*9);
//1172 PRINT "RALLODS ON FUNERAL EXPENSES"
//1174 B5=INT(F1+(B-(I/100)))
//1175 A=INT(A-((F1+(B-(I/100)))*9))
//1176 GOTO 1185
//1180 PRINT "   YOU WERE FORCED TO SPEND ";INT(F1*9);"RALLODS ON ";
//1181 PRINT "FUNERAL EXPENSES."
//1182 B5=F1
//1183 A=INT(A-(F1*9))
//1185 IF A>=0 THEN 1194
//1187 PRINT "   INSUFFICIENT RESERVES TO COVER COST - LAND WAS SOLD"
//1189 D=INT(D+(A/W))
//1190 A=0
//1194 B=INT(B-B5)

    // Funerals
    unsigned int burial_budget=0;
    int dummy_treasury=country->budget.treasury;

    if(starved_citizens||polluted_citizens){
        burial_budget=(starved_citizens+polluted_citizens)*BURIAL_COST;
        printf("You were forced to spend %d rallods on funeral expenses.\n",burial_budget);
        dummy_treasury-=burial_budget;

        if(dummy_treasury<0){
            printf("\tINSUFFICIENT RESERVES TO COVER COST - LAND WAS SOLD\n");
            country->land.land-=dummy_treasury/country->land.land_price;
            country->budget.treasury=0;
        }
    }

    country->population.polluted_citizens=polluted_citizens;
    country->population.starved_citizens=starved_citizens;
    country->population.dead_citizens=starved_citizens+polluted_citizens;

//1200 IF H=0 THEN 1250
//1220 C1=INT(H+(RND(1)*10)-(RND(1)*20))
//1224 IF C>0 THEN 1230
//1226 C1=C1+20
//1230 PRINT C1;"WORKERS CAME TO THE COUNTRY AND";
//1250 P1=INT(((I/100-B)/10)+(K/25)-((2000-D)/50)-(F1/2))
//1255 PRINT ABS(P1);"COUNTRYMEN ";
//1260 IF P1<0 THEN 1275
//1265 PRINT "CAME TO";
//1270 GOTO 1280
//1275 PRINT "LEFT";
//1280 PRINT " THE ISLAND."
//1290 B=INT(B+P1)
//1292 C=INT(C+C1)

    // Migrations
    unsigned int incoming_migrants=random_ab(country->land.land_sold-20,country->land.land_sold+10)+(country->population.foreign_workers>0)?0:20;
    int migrating_citizens=(country->budget.distribution_budget/RALLODS_PER_CITIZEN-country->population.citizens)/10+country->budget.pollution_control_budget/25-(STARTING_LAND-country->land.land)/50+polluted_citizens/2;

    if(incoming_migrants!=0)
        printf("%d workers came to the country%s",incoming_migrants,(migrating_citizens!=0)?" and ":".");
    if(migrating_citizens!=0){
        printf("%d",abs(migrating_citizens));
        printf((migrating_citizens>0)?"came to the island\n":"left the island\n");
    }

    country->population.citizens+=migrating_citizens;
    country->population.foreign_workers+=incoming_migrants;
    country->population.incoming_migrants=incoming_migrants;

//1305 U2=INT(((2000-D)*((RND(1)+1.5)/2)))
//1310 IF C=0 THEN 1324
//1320 PRINT "OF ";INT(J);"SQ. MILES PLANTED,";
//1324 IF J>U2 THEN 1330
//1326 U2=J
//1330 PRINT " YOU HARVESTED ";INT(J-U2);"SQ. MILES OF CROPS."
//1340 IF U2=0 THEN 1370
//1344 IF T1>=2 THEN 1370
//1350 PRINT "   (DUE TO ";
//1355 IF T1=0 THEN 1365
//1360 PRINT "INCREASED ";
//1365 PRINT "AIR AND WATER POLLUTION FROM FOREIGN INDUSTRY.)"
//1370 Q=INT((J-U2)*(W/2))
//1380 PRINT "MAKING";INT(Q);"RALLODS."
//1390 A=INT(A+Q)

    // Harvests
    unsigned int land_non_harvested=(2*FORESTED_LAND-country->land.land)*random_ab(3,5)/4,harvest;

    if(country->population.foreign_workers!=0)
        printf("Of %d sq. miles planted, you",country->land.land_planted);
    else
        printf("You");

    if(country->land.land_planted<=land_non_harvested)land_non_harvested=country->land.land_planted;

    printf(" harvested %d sq. miles of crops,\n",country->land.land_planted-land_non_harvested);

    harvest=(country->land.land_planted-land_non_harvested)*country->land.land_price/2;

    printf("making %d rallods.",harvest);

    country->budget.treasury+=harvest;

//1400 V1=INT(((B-P1)*22)+(RND(1)*500))
//1405 V2=INT((2000-D)*15)
//1410 PRINT " YOU MADE";ABS(INT(V1-V2));"RALLODS FROM TOURIST TRADE."
//1420 IF V2=0 THEN 1450
//1425 IF V1-V2>=V3 THEN 1450
//1430 PRINT "   DECREASE BECAUSE ";
//1435 G1=10*RND(1)
//1440 IF G1<=2 THEN 1460
//1442 IF G1<=4 THEN 1465
//1444 IF G1<=6 THEN 1470
//1446 IF G1<=8 THEN 1475
//1448 IF G1<=10 THEN 1480
//1450 V3=INT(A+V3)
//1451 A=INT(A+V3)
//1452 GOTO 1500
//1460 PRINT "FISH POPULATION HAS DWINDLED DUE TO WATER POLLUTION."
//1462 GOTO 1450
//1465 PRINT "AIR POLLUTION IS KILLING GAME BIRD POPULATION."
//1467 GOTO 1450
//1470 PRINT "MINERAL BATHS ARE BEING RUINED BY WATER POLLUTION."
//1472 GOTO 1450
//1475 PRINT "UNPLEASANT SMOG IS DISCOURAGING SUN BATHERS."
//1477 GOTO 1450
//1480 PRINT "HOTELS ARE LOOKING SHABBY DUE TO SMOG GRIT."
//1482 GOTO 1450

    // Tourism
    unsigned int tourism_upper=random_ab((country->population.citizens-migrating_citizens)*22,(country->population.citizens-migrating_citizens)*22+500),tourism_lower=(FORESTED_LAND-country->land.land)*15,tourism_profits=tourism_upper-tourism_lower;
    const char* causes_of_decrease[]={
        "fish population has dwindled due to water pollution.",
        "air pollution is killing game bird population.",
        "mineral baths are being ruined by water pollution.",
        "unpleasant smog is discouraging sun bathers.",
        "hotels are looking shabby due to smog grit."
    };

    printf("You made %d rallods from tourism trade.\n",tourism_profits);

    if(!tourism_lower){
        printf("\tDecrease because %s\n",causes_of_decrease[random(sizeof(causes_of_decrease)/sizeof(causes_of_decrease[0]))]);
    }

    country->budget.treasury+=tourism_profits;

//1500 IF B5>200 THEN 1600
//1505 IF B<343 THEN 1700
//1510 IF (A4/100)>5 THEN 1800
//1515 IF C>B THEN 1550
//1520 IF N5-1=X5 THEN 1900
//1545 GOTO 2000

    // Ending assesment

    if(country->population.dead_citizens>MAXIMUM_DEATHS_BEFORE_LOSING)country->ending=END_MISMANAGEMENT;
    else if(country->population.citizens<CITIZENS_NUMBER_FLOOR)country->ending=END_ONE_THIRD_DEAD;
    else if(old_treasury>MAXIMUM_CASH_IN_OLD_TREASURY&&country->population.starved_citizens!=0)country->ending=END_WILFUL_FAMINE;
    else if(country->population.citizens<country->population.foreign_workers)country->ending=END_FOREIGN_TAKEOVER;
    else if(country->turn>TERM_OFFICE)country->ending=END_SUCCESS;

    country->turn++;

    print_stderr_country(*country);

    // R‚initialisation
    country->budget.distribution_budget=0;
    country->budget.pollution_control_budget=0;
    country->population.incoming_migrants=0;
}

void ending_management(t_country country){
    int roll;

    switch(country.ending){
        case END_WILFUL_ABANDON:
            printf("\nGoodbye.\n");
            printf("(If you wish to continue this game at a later date, answer\n");
            printf("'again' when asked if you want instructions at the start\n");
            printf("of the game).");

            break;
        case END_FOREIGN_TAKEOVER:
            printf("\n\nThe number of foreign workers has exceeded the number\n");
            printf("of countrymen. As a minority, they have revolted and\n");
            printf("taken over the country.\n");

            if(random(2))printf("You have been thrown out of office and are now\nresiding in prison.\n");

            break;
        case END_MISMANAGEMENT:
//1600 PRINT
//1602 PRINT
//1610 PRINT B5;"COUNTRYMEN DIED IN ONE YEAR!!!!!"
//1615 PRINT "DUE TO THIS EXTREME MISMANAGEMENT, YOU HAVE NOT ONLY"
//1620 PRINT "BEEN IMPEACHED AND THROWN OUT OF OFFICE, BUT YOU"
//1622 M6=INT(RND(1)*10)
//1625 IF M6<=3 THEN 1670
//1630 IF M6<=6 THEN 1680
//1635 IF M6<=10 THEN 1690
//1670 PRINT "ALSO HAD YOUR LEFT EYE GOUGED OUT!"
//1672 GOTO 1590
//1680 PRINT "HAVE ALSO GAINED A VERY BAD REPUTATION."
//1682 GOTO 1590
//1690 PRINT "HAVE ALSO BEEN DECLARED NATIONAL FINK."
//1692 GOTO 1590
            printf("\n\n%d countrymen died in one year!!!!!\n",country.population.dead_citizens);
            printf("Due to this extreme mismanagement, you have not only\nbeen impeached and thrown out of office, but you\n");

            roll=random_ab(0,10);

            if(roll<=3) printf("also had your left eye gouged out!\n");
            else if(roll<=6) printf("have also gained a very bad reputation.\n");
            else printf("have also been declared national fink.\n");

            printf("\n\n");

            break;
        case END_ONE_THIRD_DEAD:
//1700 PRINT
//1702 PRINT
//1710 PRINT "OVER ONE THIRD OF THE POPULTATION HAS DIED SINCE YOU"
//1715 PRINT "WERE ELECTED TO OFFICE. THE PEOPLE (REMAINING)"
//1720 PRINT "HATE YOUR GUTS."
//1730 GOTO 1570
            printf("Over one third of the population has died since you\n");
            printf("were elected to office. The people (remaining)\n");
            printf("hate your guts.\n");

            if(random(2))printf("You have been thrown out of office and are now\nresiding in prison.\n");

            break;
        case END_WILFUL_FAMINE:
//1800 IF B5-F1<2 THEN 1515
//1807 PRINT
//1815 PRINT "MONEY WAS LEFT OVER IN THE TREASURY WHICH YOU DID"
//1820 PRINT "NOT SPEND. AS A RESULT, SOME OF YOUR COUNTRYMEN DIED"
//1825 PRINT "OF STARVATION. THE PUBLIC IS ENRAGED AND YOU HAVE"
//1830 PRINT "BEEN FORCED TO EITHER RESIGN OR COMMIT SUICIDE."
//1835 PRINT "THE CHOICE IS YOURS."
//1840 PRINT "IF YOU CHOOSE THE LATTER, PLEASE TURN OFF YOUR COMPUTER"
//1845 PRINT "BEFORE PROCEEDING."
//1850 GOTO 1590
            printf("Money was left over in the treasury which you did\n");
            printf("not spend. As a result, some of your countrymen died\n");
            printf("of starvation. The public is enraged and you have\n");
            printf("been forced to either resign or commit suicide.\n");
            printf("The choice is yours.\n");
            printf("If you choose the latter, please turn off your computer\n");
            printf("before proceeding.\n\n");

            break;
        case END_SUCCESS:
//1900 PRINT
//1902 PRINT
//1920 PRINT "CONGRATULATIONS!!!!!!!!!!!!!!!!!!"
//1925 PRINT "YOU HAVE SUCCESFULLY COMPLETED YOUR";N5;"YEAR TERM"
//1930 PRINT "OF OFFICE. YOU WERE, OF COURSE, EXTREMELY LUCKY, BUT"
//1935 PRINT "NEVERTHELESS, IT'S QUITE AN ACHIEVEMENT. GOODBYE AND GOOD"
//1940 PRINT "LUCK - YOU'LL PROBABLY NEED IT IF YOU'RE THE TYPE THAT"
//1945 PRINT "PLAYS THIS GAME."
//1950 GOTO 1590
            printf("CONGRATULATIONS!!!!!!!!!!!!!!!!!!\n");
            printf("You have succesfully completed your %d year term\n", TERM_OFFICE);
            printf("of office. You were, of course, extremely lucky, but\n");
            printf("nevertheless, it's quite an achievement. Goodbye and good\n");
            printf("luck - you'll probably need it if you're the type that");
            printf("plays this game.\n\n");

            break;
        case END_NONE:
        default:
            break;
    }
}