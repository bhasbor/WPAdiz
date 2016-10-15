/*
   Legend:
   ERROR:   Errore nel parametro(es. mancante e ecc.)
   SINTAX:  La sintassi del parametro non e corretta
   INVALID: Il valore del parametro non è corretto.
*/

/*
 *  Copyright (C) 2016 leminski <atleminski@gmail.com> https://github.com/leminski
 *
 *  This file is part of WPAdiz
 *
 *  WPAdiz is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  WPAdiz is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with WPAdiz. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "outerr.h"

void  /*Programm hashword */
  outerr_hash(char* buffer, char* buffer2, short int _flag_err)

  {
       switch(_flag_err) {

          case INVALID_PARAM:
                printf("wpahashword: INVALID in questa sintassi, \"%s\" e \"%s\" non sono numeri.\n", buffer, buffer2);

                break;
          case INVALID_ERR_PAR_NUM:
                printf("wpahashword: INVALID in questa sintassi, \"%s\" non e un numero.\n", buffer);

                break;
          case INVALID_ERR_PAR_NUM2:
                printf("wpahashword: INVALID in questa sintassi, \"%s\" non e un numero.\n", buffer2);

                break;
          case SINTAX_MANY_TRATT:
                printf("wpahashword: SINTAX inserting too many '-' in parameter '-c'\n");

                break;
          case ERROR_PARAM_T:
                printf("wpahashword: ERROR non e ammesso il parametro '-r'\n");

                break;
          case ERROR_PARAM_D:
                printf("wpahashword: ERROR il parametro '-d' non accetta altri parametri\n");

                break;
          case ERROR_BIG:
                printf("wpahashword: ERROR il primo numero è più grande del secondo\n");

                break;
          case INVALID_PARAM_B:
                printf("wpahashword: INVALID %d non valido (e.g. 0 or 1 a 255))\n", atoi(buffer));

                break;
          case ERROR_PARAM_C:
                printf("wpahashword: ERROR richiesto parametro '-c'\n");

                break;
          case ERROR_PARAM_FILE:
                printf("wpahashword: ERROR insert file with parameter '-f'\n");

                break;
          case ERROR_OUT:
                printf("wpahashword: ERROR inserie il file su cui salvare le operazioni\n");

                break;
       }
  }

void  /* Programm length */
  outerr_leng(short int _flag_err, unsigned int number)

  {
       switch(_flag_err) {

          case INVALID_PARAM_L:
                printf("wpalength: INVALID value %u in parameter '-l'\n", number);

                break;
          case ERROR_PARAM_E:
                printf("wpalength: ERROR Il parametro '-e' richiede il parametro '-l'\n");

                break;
          case ERROR_PARAM_F:
                printf("wpalength: ERROR insert your file\n");

                break;
          case INVALID_NUMBER:
                printf("wpalength: INVALID -l accetta parametri numerici\n");

                break;
       }
  }

void  /* Programm date */
  outerr_date(short int _flag_err, unsigned short* value, unsigned short* value2)

  {
       switch(_flag_err) {

          case ERROR_PARAM:
                printf("wpadate: ERROR insert -d -m -y -Y and -f\n");

                break;
          case INVALID_DAY:
                printf("wpadate: INVALID '-d' max 31 e min 1\n");

                break;
          case INVALID_MONTH:
                printf("wpadate: INVALID '-m' max 12 e min 1\n");

                break;
          case INVALID_YEAR:
                printf("wpadate: INVALID '-y' max 3000 e min 1\n");

                break;
          case INVALID_END_YEAR:
                printf("wpadate: INVALID '-Y' max 3000, min 1 e più di '-y'\n");

                break;
          case INVALID_PARAM_EY:
                printf("wpadate: INVALID value.. %u maggiore di %u\n", *value, *value2);

                break;
          case INVALID_PARAM_Z:
                printf("wpadate: INVALID inserisci uno dei 3 valori (1 , 2 , 3)\n");

                break;
          case ERROR_OUT_D:
                printf("wpadate: ERROR inserie il file su cui salvare le operazioni\n");

                break;
       }
  }
