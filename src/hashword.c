/*
 *  Copyright (C) 2016 leminski <atleminski@gmail.com> https://github.com/lemin$
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

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include "lib/outerr.h"
#include "lib/essential.h"
#include "lib/wpahashword/tolower.h"

 /* Definizione dei vari errori */

 unsigned int num  = 0;
 unsigned int num2 = 0;

 /* Prototipi */
 void usage(char*);
 void conc_diminutivi(FILE*, FILE*);
 void control(char*, char*, char*, char*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
 int  parser(char*, const unsigned int, char*, char*);
 int  concatenation(char*, char*, char*, char*, uint8_t*, uint8_t*, uint8_t*);
 int  hashchars(char*, char*, uint8_t*);

int main (int argc, char* argv[]) {

/* Varie informazioni del programma
  *      richiamabile attravarso la
   *         funzione author();
    */

_date     ="2016";
_version  ="v.1.0";
_programm ="WPAhashword";
_author   ="(leminski) `https://github.com/leminski`";

   author();

   /* Check argument */
   if(argc == 1) {
      printf("Nessuna opzione: digitare -h\n");
      return -1;
   }

   int ch;
   uint8_t hash = 0, _tratt = 0, up = 0, flag_diminutivi = 0;
   char *word = NULL, *file_o = NULL, *file_two = NULL, *outfile = NULL, *essid = NULL, temp[9000], number[9000], number2[9000];

   opterr = 0;
   while( (ch = getopt(argc, argv, "hf:r:c:o:tbd")) != -1) {

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

                     printf("Error: il primo numero è piu grande del secondo!\n");
                     return -1;
                  }

                  break;
         case 'b':
                  up = 1;
                  break;

         case 'f':
                  file_o = optarg;
                  break;

         case 'd':
                  flag_diminutivi = 1;
                  break;

         case 'r':
                  file_two = optarg;
                  break;

         case 'o':
                  outfile = optarg;
                  break;

         case 't':
                  if(file_two != NULL) {

                     outerr_hash(NULL, NULL, ERROR_PARAM_T);
                     return -1;
                  }

                  hash = 1;
                  break;

         case '?': default:
                  printf("wpahashword: Unknow parameter '-%c' \nDigit: '-h'\n", optopt);
                  return -1;
      }
   }

   for(; optind < argc; optind++) {
     if( strcmp(argv[optind], "-") ) {
        printf("wpahashword: Unknow parameter '%s' \nDigit: '-h'\n", argv[optind]);
        return -1;
     }
   }

   if(flag_diminutivi == 1 && (file_two != NULL || word != NULL || hash == 1 || essid != NULL)) {
      outerr_hash(NULL, NULL, ERROR_PARAM_D);
      return -1;
   }

   if(outfile == NULL) {
      outerr_hash(NULL, NULL, ERROR_OUT);
      return -1;
   }

   control(&*word, &*file_o, &*file_two, &*outfile, &hash, &_tratt, &up, &flag_diminutivi);

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
             "-t :   Disposizioni di tutte le parole contenute in un singolo file\n "
             "-b :   Flag per avere tutte le parole in maiuscolo\n\n", ptr);

     exit(0);
  }

void
  control(char* word, char* file_in, char* file_two, char* file_out, uint8_t* boolean /* 1 - hash, 0 - concatenation */, uint8_t* tratt, uint8_t* up, uint8_t* flag_diminutivi)

  {
      if(*boolean == 1)
         hashchars(&*file_in, &*file_out, *&up);

      else if(*boolean == 0)
         concatenation(&*file_in, &*file_out, &*file_two, &*word, *&tratt, *&up, *&flag_diminutivi);
  }

int
  hashchars(char* file, char* file_out, uint8_t* up) {

   char buffer[9000], buffer2[9000];

   FILE *read, *read2, *write;

   read = fopen(&*file, "r");
   read2 = fopen(&*file, "r");

   if(!read || !read2) { perror("Error: "); return -1; }

   write = fopen(&*file_out, "aw");

   printf(" * Flag hashword activated\n\n");

   while( (fscanf(read, "%s", buffer) ) != EOF) {

      while( (fscanf(read2, "%s", buffer2) ) != EOF) {

         if( strcmp(buffer, buffer2) ) {

            if(*up == 0) {

               fprintf(write, "%s%s\n", buffer, buffer2);
               fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%sE%s\n", buffer, buffer2);
            }
            else if(*up == 1) {

               buffer[0] = toupper(buffer[0]);

	       fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%sE%s\n", buffer, buffer2);

               buffer[0] = tolower(buffer[0]);

               buffer2[0] = toupper(buffer2[0]);

               fprintf(write, "%s%s\n", buffer, buffer2);
               fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%sE%s\n", buffer, buffer2);

               buffer[0] = toupper(buffer[0]);

               fprintf(write, "%s%s\n", buffer, buffer2);
               fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%sE%s\n", buffer, buffer2);

               buffer[0] = tolower(buffer[0]);
               buffer2[0] = tolower(buffer2[0]);

               _hash_touplower(buffer, sizeof(buffer), 0);
               _hash_touplower(buffer2, sizeof(buffer), 0);

               fprintf(write, "%s%s\n", buffer, buffer2);
               fprintf(write, "%se%s\n", buffer, buffer2);
               fprintf(write, "%sE%s\n", buffer, buffer2);

               _hash_touplower(buffer, sizeof(buffer), 1);
               _hash_touplower(buffer2, sizeof(buffer), 1);
            }
         }
      }

      rewind(read2);
   }

   printf(" File '%s' create!\n", file_out);

   fclose(read); fclose(read2); fclose(write);

   return 0;
 }

int
  concatenation(char* file, char* file_out, char* file_two, char* word, uint8_t* tratt, uint8_t* up, uint8_t* flag_diminutivi) {

   char buffer[9000], buffer2[9000];

   FILE *read, *read2, *write;

   read = fopen(&*file, "r");

   if(!read) { perror("Error: "); return -1; }

   write = fopen(&*file_out, "aw");

   printf(" * Flag concatenation activated\n");

   if(*flag_diminutivi == 1) {

      printf("  \\\n");
      printf("   \\_(->) * Flag diminutivi activated\n\n");

      printf(" [+] File '%s' create.\n\n", file_out);

      conc_diminutivi(read, write);

      fclose(read); fclose(write);

      return 0;
   }

   switch( *tratt ) {

/**/  case 1:               				/* Con creazioni di numeri che vanno dal numero prima del '-' fino al numero che va dopo al '-' */
             switch( *up ) {                   		/* Flag Maiuscolo */

                case 0:                        		/* Non maiuscolo */
                       if(&*file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             for(unsigned int i = num; i <= num2; i++) {

                                fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                             }
                          }
                       }
                       else {

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                for(unsigned int i = num; i <= num2; i++) {

                                   fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                                }
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
                case 1:                        		/* Maiuscolo */
                       if(&*file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             for(unsigned int i = num; i <= num2; i++) {

                                _hash_touplower(buffer, sizeof(buffer), 0);

                                fprintf(write, "%s%u\n", buffer, i);
                             }
                          }
                       }
                       else {

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                for(unsigned int i = num; i <= num2; i++) {

                                   _hash_touplower(buffer, sizeof(buffer), 0);
                                   _hash_touplower(buffer2, sizeof(buffer2), 0);

                                   fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                                }
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
             }
/**/  case 0:               				/* FLag senza processamento dei numeri */
             switch( *up ) {                            /* Flag Maiuscolo */

                case 0:                                 /* Non maiuscolo */
                       if(&*file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             fprintf(write, "%s%s%s\n", buffer, buffer2, word);
                          }
                       }
                       else {

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                   fprintf(write, "%s%s%s\n", buffer, buffer2, word);
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
                case 1:                                 /* Maiuscolo */
                       if(&*file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             _hash_touplower(buffer, sizeof(buffer), 0);

                             fprintf(write, "%s%s\n", buffer, word);
                          }
                       }
                       else {

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                   _hash_touplower(buffer, sizeof(buffer), 0);
                                   _hash_touplower(buffer2, sizeof(buffer2), 0);

                                   fprintf(write, "%s%s%s\n", buffer, buffer2, word);
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
             }
   }

   printf("\n [+] File '%s' create.\n", file_out);

   fclose(read); fclose(write);

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
