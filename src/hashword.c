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

#include <unistd.h>

#include "lib/outerr.h"
#include "lib/essential.h"
#include "lib/wpahashword/write_file.h"

 unsigned int num  = 0;
 unsigned int num2 = 0;

 /* Prototipi */
 void usage(char*);
 void conc_diminutivi(FILE*, FILE*);
 int  parser(char*, const unsigned int, char*, char*);
 int  concatenation(char*, char*, char*, char*, uint8_t*, int16_t*, uint8_t*);

int main (int argc, char* argv[]) {

/* Varie informazioni del programma
  *      richiamabile attravarso la
   *         funzione author();
    */

_date     ="2016";
_version  ="v.1.2";
_programm ="WPAhashword";
_author   ="(leminski) `https://github.com/leminski`";

   author();

   /* Check argument */
   if(argc == 1) {
      printf("Nessuna opzione: digitare -h\n");
      return -1;
   }

   FILE *read;
   int ch;
   uint8_t _tratt = 0, flag_diminutivi = 0;
   int16_t up = -1;
   char *word = NULL, *file = NULL, *file_two = NULL, *outfile = NULL, temp[9000], number[9000], number2[9000];

   opterr = 0;
   while( (ch = getopt(argc, argv, "hf:r:c:o:b:d")) != -1) {

      switch(ch) {

         case 'h':

                  if(argc > 1) { usage(argv[0]); return -1; }
                  break;

         case 'c':

                  strncpy(temp, optarg, sizeof(temp));

                  switch( parser(temp, sizeof(temp), number, number2) ) {

                     case 0:
                            word = optarg;
                            break;

                     case 1:
                            num  = atoi(number);
                            num2 = atoi(number2);

                            _tratt = 1;

                            break;

                     case SINTAX_MANY_TRATT:

                            outerr_hash(NULL, NULL, SINTAX_MANY_TRATT);
                            return -1;

                            break;

                     case INVALID_PARAM:

                            outerr_hash(number, number2, INVALID_PARAM);
                            return -1;

                            break;

                     case INVALID_ERR_PAR_NUM:

                            outerr_hash(number, NULL, INVALID_ERR_PAR_NUM);
                            return -1;

                            break;

                     case INVALID_ERR_PAR_NUM2:

                            outerr_hash(NULL, number2, INVALID_ERR_PAR_NUM2);
                            return -1;

                            break;
                  }

                  if(num > num2) {

                     outerr_hash(NULL, NULL, ERROR_BIG);
                     return -1;
                  }

                  break;
         case 'b':

                  if( atoi(optarg) < 0 || atoi(optarg) > 255) {
                     outerr_hash(optarg, NULL, INVALID_PARAM_B);
                     return -1;
                  }

                  if( atoi(optarg) == 0) {
                     up = 0;
                  }
                  else {
                     up = atoi(optarg);
                  }

                  break;

         case 'f':

                  file = optarg;

                  read = fopen(file, "r");

                  if(!read) { perror("Error: "); return -1; }

                  fclose(read);
                  break;

         case 'd':

                  flag_diminutivi = 1;
                  break;

         case 'r':

                  file_two = optarg;

                  read = fopen(file_two, "r");

                  if(!read) { perror("Error: "); return -1; }

                  fclose(read);
                  break;

         case 'o':

                  outfile = optarg;
                  break;

         case '?': default:
                  printf("wpahashword: Unknow parameter '-%c' \nDigit: '-h'\n", optopt);
                  return -1;
      }
   }

   for( ; optind < argc; optind++) {

     if( strcmp(argv[optind], "-") ) {
        printf("wpahashword: Unknow parameter '%s' \nDigit: '-h'\n", argv[optind]);
        return -1;
     }
   }

   if(outfile == NULL) {
      outerr_hash(NULL,NULL, ERROR_OUT);
      return -1;
   }

   if(file == NULL) {
      outerr_hash(NULL, NULL, ERROR_PARAM_FILE);
      return -1;
   }

   if(flag_diminutivi == 1 && file_two != NULL) {
      outerr_hash(NULL, NULL, ERROR_PARAM_D);
      return -1;
   }

   concatenation(file, outfile, file_two, word, &_tratt, &up, &flag_diminutivi);

  return 0;

}

void
  usage(char* ptr)

  {
      fprintf(stderr," Usage: %s -f <fileinput> -c <word> -o <outfile> -[OPTIONAL PARAMETERS..]\n\n "
             "Parameters:\n\n "
             "-f :   File input\n "
             "-c :   Parola da concatenare con le parole presenti nel file\n "
             "       Se messo il carattere '-' (tra soli due numeri), si concatenano\n "
             "       le parole con i numeri che vanno dal range indicato a destra fino\n "
             "       a quello indicato a sinistra. (es.) -c 1-10.\n "
             "       Suggerimento: per inserire uno spazio, bisogna inserirlo tra le \"\" \n "
             "       (es.) .. -c \" \"\n\n "
             "-o :   File output su cui salvare le operazioni\n\n "
             "Optional Parameters:\n\n "
             "-d :   Crea per ogni parola contenuta in un file ('-f') il suo diminutivo\n "
             "-r :   Secondo file di input, e quindi si possono concatenare le parole\n "
             "       dei due file\n "
             "-b :   Flag (valore):\n "
             "                     0       : per avere tutte le parole in maiuscolo\n "
             "                     1 a 255 : indica a quale posizione si vuole avere\n "
             "                               la lettera in maiuscolo. Se si indica un\n "
             "                               valore che è superiore ad una parola, viene\n "
             "                               omesso.\n\n", ptr);

      exit(0);
  }

int
  concatenation(char* file, char* file_out, char* file_two, char* word, uint8_t* tratt, int16_t* up, uint8_t* flag_diminutivi)

  {
       if( word == NULL && num == 0 && num2 == 0) {
          outerr_hash(NULL, NULL, ERROR_PARAM_C);
          return -1;
       }

       FILE *read, *write;

       read = fopen(&*file, "r");

       write = fopen(file_out, "aw");

       printf(" * Flag concatenation activated\n");

       if(*flag_diminutivi == 1) {

          printf("  \\\n");
          printf("   \\_(->) * Flag diminutivi activated\n\n");

          printf(" [+] File '%s' created.\n\n", file_out);

          conc_diminutivi(read, write);

          fclose(read); fclose(write);

          return 0;
       }

       int error_up = write_file(file, file_out, file_two, *&up, word, *&tratt, &num, &num2);

       if(error_up > 0)
          printf("\n [+] File '%s' created: `(%u words omitted) (why? Didit -h for help)`.\n", file_out, error_up);

       else
          printf("\n [+] File '%s' created.\n", file_out);

     return 0;
  }


int
  parser(char* word, const unsigned int size, char* number, char* number2) {

   unsigned int ret = 0, check = 0;

   /* Fase di check (parsing) */
   for(unsigned int i = 0; i <= size; i++)

      if(word[i] == '-')
         check++;

   if(check > 1)
      return SINTAX_MANY_TRATT;

   else if(check == 1) {

      for(unsigned int i = 0; i <= size; i++) {

         if(word[i] == '-') {

            ret = i + 1;
            i = 0;

            for(unsigned int z = ret; z <= size; z++) {

               number2[i] = word[z];
               i++;
            }
         }
         number[i] = word[i];
      } /* End ciclo first for */

           if( !atoi(number) && !atoi(number2) ) { return INVALID_PARAM; }
      else if( !atoi(number) )                   { return INVALID_ERR_PAR_NUM; }
      else if( !atoi(number2) )                  { return INVALID_ERR_PAR_NUM2; }

      return 1;
   }
   else if( check == 0) {

      return 0;
   }

   return 0;
 }
