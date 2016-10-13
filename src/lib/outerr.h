#include <stdio.h>

/* Define for programm hashword */

 #define INVALID_PARAM        -3  /* Errore di sintassi nell input digitato */
 #define INVALID_ERR_PAR_NUM  -4  /* Errore di sintassi nell input immesso nel primo parametro */
 #define INVALID_ERR_PAR_NUM2 -5  /* Errore di sintassi nell input immesso nel secondo parametro */
 #define SINTAX_MANY_TRATT    -6  /* Se vengono aggiunti due o piu simboli '-' */
 #define ERROR_PARAM_T        -7
 #define ERROR_PARAM_D        -8
 #define ERROR_PARAM_C        -9
 #define ERROR_OUT            -20

 /* Define for programm legth */

 #define ERROR_PARAM_F       -9
 #define ERROR_PARAM_E       -10
 #define INVALID_PARAM_L     -11
 #define INVALID_NUMBER      -12

 /* Define for programm date */

 #define ERROR_PARAM       -15
 #define ERROR_OUT_D       -21
 #define INVALID_DAY       -16
 #define INVALID_MONTH     -17
 #define INVALID_YEAR      -18
 #define INVALID_END_YEAR  -19
 #define MAX_DAY           31
 #define MAX_MONTH         12
 #define MAX_YEAR          3000
 #define MAX_END_YEAR      3000

void outerr_hash(char*, char*, short int);
void outerr_leng(short int);
void outerr_date(short int, char*);
