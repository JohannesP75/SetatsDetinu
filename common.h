#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <string.h>
/********************************************
*
* Project       : King.cbp
* File creation : 2015-07-18-18.51.25 (2015-07-18-16.51.25 UTC)
*
*********************************************/

typedef enum t_ending{
    END_WILFUL_ABANDON,
    END_FOREIGN_TAKEOVER,
    END_MISMANAGEMENT,
    END_ONE_THIRD_DEAD,
    END_WILFUL_FAMINE,
    END_SUCCESS,
    END_NONE,
    NUMBER_OF_ENDS
}t_ending;

/* Return integer between 0 and n-1 */
unsigned int random(unsigned int n);

/* Return integer between a and b */
unsigned int random_ab(unsigned int a,unsigned int b);

#endif // COMMON_H_INCLUDED