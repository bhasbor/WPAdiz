/*
 *  Copyright (C) 2016 leminski: Site: https://github.com/leminski
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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include "lib/essential.h"
#include "lib/outerr.h"

 #define DEFAULT_DIZ       "DefaultDate.txt"

 #define MAX_DAY           31
 #define MAX_MONTH         12
 #define MAX_YEAR          3000
 #define MAX_END_YEAR      3000
 #define ERROR_PARAM       -15
 #define ERROR_OUT_D       -21
 #define INVALID_DAY       -16
 #define INVALID_MONTH     -17
 #define INVALID_YEAR      -18
 #define INVALID_END_YEAR  -19

 /* Prototipi */
 void usage(const char*);
 void formatSave(FILE*, const uint8_t, const uint8_t, const unsigned short, const unsigned short, const uint8_t*, const char*, const char*);
 int  check_param(const char*, const uint8_t);

int main(int argc, char* argv[]) {

/* Version e Author for this programm
  *      richiamabile attravarso la
   *         funzione author();
    */

_date     ="2016";
_version  ="v.1.0";
_programm ="WPAdate";
_author   ="(leminski) `https://github.com/leminski`";

   author();

   /* Check arguments */
   if(argc == 1) {
      printf("Nessuna opzione: digitare -h\n");
      return -1;
   }

   short ch;
   uint8_t da = 0, mo = 0, _zero = 0;
   unsigned short ye = 0, EY = 0;
   char *fo = NULL, *ou = NULL;

   FILE *write;

   opterr = 0;
   optarg = NULL;
   while( ( ch=getopt(argc,argv,"Dd:m:y:Y:z:f:o:h") ) != -1 ) {

      switch(ch) {

            case 'h':
                     if(argc > 1) {

                        usage(argv[0]);
                        return -1;
                     }
            case 'D':
                     write = fopen(DEFAULT_DIZ, "w");
                     formatSave(write, 1, 1, 1960, 2016, &_zero,"-", DEFAULT_DIZ);
                     fclose(write);

                     return 0;
            case 'd':
                     if(check_param(optarg, 1) == -1) {
                        outerr_date(INVALID_DAY, NULL);
                        return -1;
                     }

                     da = atoi(optarg);
                     break;
            case 'm':
                     if(check_param(optarg, 2) == -1) {
                        outerr_date(INVALID_MONTH, NULL);
                        return -1;
                     }

                     mo = atoi(optarg);
                     break;
            case 'y':
                     if(check_param(optarg, 3) == -1) {
                        outerr_date(INVALID_YEAR, NULL);
                        return -1;
                     }

                     ye = atoi(optarg);
                     break;
            case 'Y':
                     if(check_param(optarg, 4) == -1) {
                        outerr_date(INVALID_END_YEAR, NULL);
                        return -1;
                     }

                     EY = atoi(optarg);
                     break;
            case 'f':
                     fo = optarg;

                     break;
            case 'o':
                     ou = optarg;

                     break;
            case 'z' :
                      if( (atoi(optarg)) == 1) {
                         _zero = 1;
                      }
                      else if( (atoi(optarg)) == 2) {
                         _zero = 2;
                      }
                      else if( (atoi(optarg)) == 3) {
                         _zero = 3;
                      }
                      else {
                         printf(" Inserisci uno dei tre valori (1, 2, 3). Digita '-h'.\n");
                         return -1;
                     }
                     break;

            case '?':  default:

                printf("wpadate: Unknow parameter '-%c'\nDigit '-h'\n",optopt); return -1;
      }
   } /* End While */

   for(; optind < argc; optind++) {
     if( strcmp(argv[optind], "-") ) {
        printf("wpadate: Unknow parameter '%s' \nDigit: '-h'\n", argv[optind]);
        return -1;
     }
   }

   if(ou == NULL) { outerr_date(ERROR_OUT_D, NULL); return -1; }

   write = fopen(ou, "aw");

   if(!write) {    perror(""); return -1;     }

   formatSave(write, da, mo, ye, EY, &_zero, fo, ou);
   fclose(write);

  return 0;

} /* End main */

void
  usage(const char* ptr) {

   fprintf(stderr, " Usage: %s -d <day> -m <month> -y <year> -Y <endyear> -f <format> -o <file_out> -[OPTIONAL_PARAMETERS..]\n\n "
   	  "Parameters:\n\n "
   	  "-d :  Giorno\n "
  	  "-m :  Mese\n "
   	  "-y :  Anno di inizio(Se non viene immesso,assume il valore 0)\n "
  	  "-Y :  Anno di fine\n "
    	  "-f :  Specifica il formato:(es.1/2/1234, 1-2-1234, 121234)\n "
   	  "-o :  File out\n\n "
          "Optional Parameters:\n\n "
          "-D :  Viene creato un file a partire dal 1 1 1980 fino a 31 12 2016\n "
          "      Per usarlo, bisogna inserire solo questo parametro in\n "
          "      quanto è un parametro di default\n\n "
          "-z :  valore tra:\n "
          "      1  : Con i giorni da 1 a 9 con lo 0.          (es.) 01/2/2016\n "
          "      2  : Con i mesi da 1 a 9 con lo 0.            (es.) 1/02/2016\n "
          "      3  : Con i mesi e i giorni da 1 a 9 con lo 0. (es.) 01/02/2016\n\n "
          "Specific Parameters:\n\n "
          "-d :  Min 1 e Max 31\n "
          "-m :  Min 1 Max 12\n "
          "-y :  Min 1 e Max 3000\n "
          "-Y ;  Min di '-y <valore>' e Max 3000\n\n "

          "\n (Es.): %s -d 1 -m 1 -y 1900 -Y 2000 -f / -o fileout.txt -z 3\n\n", ptr, ptr);
 }

int
  check_param(const char* buff, const uint8_t type)

  {
       if(type == 1)			/* Day */
          if(atoi(buff) > MAX_DAY || atoi(buff) <= 0)
              return -1;

        if(type == 2)			/* Month */
          if(atoi(buff) > MAX_MONTH || atoi(buff) <= 0)
              return -1;

        if(type == 3)			/* Year */
          if(atoi(buff) > MAX_YEAR || atoi(buff) <= 0)
              return -1;

        if(type == 4)			/* End-Year*/
          if(atoi(buff) > MAX_END_YEAR || atoi(buff) <= 0)
              return -1;
  }

void
  formatSave(FILE *write, const uint8_t day, const uint8_t month, const unsigned short year, const unsigned short endyear, const uint8_t* _zero, const char* type, const char* file_o)

  {
       for(register volatile uint8_t d = day; d <= 31; d++)
          for(register volatile uint8_t m = month; m <= 12; m++)
              for(register volatile unsigned short y = year; y <= endyear; y++)

                 if(*_zero == 1)
                    fprintf(write,"%02d%s%d%s%d\n",d,type,m,type,y);

                 else if(*_zero == 2)
                    fprintf(write,"%d%s%02d%s%d\n",d,type,m,type,y);

                 else if(*_zero == 3)
                    fprintf(write,"%02d%s%02d%s%d\n",d,type,m,type,y);

                 else
                    fprintf(write,"%d%s%d%s%d\n",d,type,m,type,y);


       printf("\n [+] Generating output in '%s'\n\n", file_o);
  }
