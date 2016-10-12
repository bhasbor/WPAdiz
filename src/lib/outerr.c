/*
   Legend:
   ERROR:   Errore nel parametro(es. mancante e ecc.)
   SINTAX:  La sintassi del parametro non e corretta
   INVALID: Il valore del parametro non è corretto.
*/

/*
 *  Copyright (C) 2016 leminski <atleminski@gmail.com> https://github.com/leminski
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "outerr.h"

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


void  /*Programm hashword */
  outerr_hash(char* buffer, char* buffer2, short int _flag_err)

  {
       switch(_flag_err) {

          case INVALID_PARAM:
                printf("[INVALID]: in questa sintassi, \"%s\" e \"%s\" non sono numeri.\n", buffer, buffer2);

                break;
          case INVALID_ERR_PAR_NUM:
                printf("[INVALID]: in questa sintassi, \"%s\" non e un numero.\n", buffer);

                break;
          case INVALID_ERR_PAR_NUM2:
                printf("[INVALID]: in questa sintassi, \"%s\" non e un numero.\n", buffer2); 

                break;
          case SINTAX_MANY_TRATT:
                printf("[SINTAX]: inserting too many '-' in parameter '-c'\n");

                break;
          case ERROR_PARAM_T:
                printf("[ERROR]: non e ammesso il parametro '-c'\n");

                break;
          case ERROR_PARAM_D:
                printf("[ERROR]: il parametro '-d' non accetta altri parametri\n");

                break;
          case ERROR_PARAM_C:
                printf("[ERROR]: il parametro '-c' non è presente\n");

                break;
          case ERROR_OUT:
                printf("[ERROR]: inserie il file su cui salvare le operazioni\n");

                break;
       }
  }

void  /* Programm length */
  outerr_leng(short int _flag_err)

  {
       switch(_flag_err) {

          case INVALID_PARAM_L:
                printf("[INVALID]: invalid value in parameter '-l'\n");

                break;
          case ERROR_PARAM_E:
                printf("[ERROR]: Il parametro '-e' richiede il parametro '-l'\n");

                break;
          case ERROR_PARAM_F:
                printf("[ERROR]: insert your file\n");

                break;
          case INVALID_NUMBER:
                printf("[INVALID]: -l accetta parametri numerici\n");

                break;
       }
  }

void  /* Programm date */
  outerr_date(short int _flag_err, char *param)

  {
       switch(_flag_err) {

          case ERROR_PARAM:
                printf("[ERROR]`: '%s' non è un numero o è un numero minore di 0\n", param);

                break;
          case INVALID_DAY:
                printf("[INVALID]: '-d' max 31 e min 1\n");

                break;
          case INVALID_MONTH:
                printf("[INVALID]: '-m' max 12 e min 1\n");

                break;
          case INVALID_YEAR:
                printf("[INVALID]: '-y' max 3000 e min 1\n");

                break;
          case INVALID_END_YEAR:
                printf("[INVALID]: '-Y' max 3000, min 1 e più di '-y'\n");

                break;
          case ERROR_OUT_D:
                printf("[ERROR]: inserie il file su cui salvare le operazioni\n");

                break;
       }
  }
