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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

#include "lib/essential.h"
#include "lib/outerr.h"
#include "lib/wpalength/outprint.h"

 #define MAX_INT              42978990

 struct _file_information {
                            size_t size_file;              /* Byte size file */
                            char* name_file;               /* Name file */
                          };

unsigned check = 0;
unsigned lengshort = 0;
unsigned long charmax = 0;

 /* Prototipi */

 void usage(const char*);
 void pars_leng_char_verb(FILE*, struct _file_information *, const unsigned*);
 int  pars_leng_char(FILE*, struct _file_information *, const unsigned*);
 void file_size(FILE*, struct _file_information *);
 int  check_if_int(char*);
 int  check_length_save(struct _file_information *, const unsigned*, uint8_t*, uint8_t*);
 int  checkspace(char*);
 int  automatic_erase(struct _file_information *, const unsigned*);

int main(int argc, char* argv[]) {

/* Varie informazioni del programma
  *      richiamabile attravarso la
   *         funzione author();
    */

_date     ="2016";
_version  ="v.1.0";
_programm ="WPAlength";
_author   ="(leminski) `https://github.com/leminski`";

   author();

   if(argc == 1) {
      printf("Nessuna opzione: digitare -h\n");
      return -1;
   }

   int ch;
   unsigned leng = 0;
   uint8_t verbose = 0, whatsave = 1;
   char condition[0];

   struct _file_information __information_file;

    /* Initialize structure */

    __information_file.name_file     = NULL;
    __information_file.size_file     = 0;

   opterr=0;  /* Per non mostrare l'errore di default a schermo del parametro non valido */
   while( (ch = getopt(argc,argv,"f:l:hsev")) != -1 ) {

      switch(ch) {

         case 'h':	 /* help */
	                 if(argc > 1) { usage(argv[0]); return -1; }

         case 'f':	 /* file input */
	                 __information_file.name_file = optarg;

	                 FILE *read;

	                 read = fopen(__information_file.name_file, "r");

	                 file_size(read, &__information_file);

	                 if(__information_file.size_file == '\0') {

	                    printf("\n File '%s' vuoto\n", __information_file.name_file);
	                    return -1;
	                 }
                 break;

         case 'l':	 /* lunghezza parola */
	                 if( check_if_int(optarg) == INVALID_PARAM_L ) {
	                    outerr_leng(INVALID_PARAM_L);
	                    return -1;
	                 }

	                 leng = atoi(optarg);
                 break;

         case 's':	 /* Salvataggio parole di lunghezza inferiore a '-l'*/
	                 if(verbose == 1) {
	                    printf("Error: il parametro '-s' non accetta il parametro -v\n");
	                    return -1;
	                 }
	                 whatsave = 0;
                 break;

         case 'e':	 /* Elimina le parole inferiori al numero specificato con il parametro '-l' */
                         while(condition[0] != 's' && condition[0] != 'n') {

        	            printf("\n "YELLOW"[!] Stai per modificare il file '%s'. Vuoi procedere"CLOSECOLOR" s/n?: ",__information_file.name_file);
        	            condition[0] = getchar();
        	         }

        	         if(condition[0] == 's') {

	                    automatic_erase(&__information_file, &leng);
	                 }
	                 else if(condition[0] == 'n') {
	                    printf("\n Annullato.\n");
	                    return -1;
	                 }
	                 return 0;

         case 'v':
	                 verbose = 1;
                 break;

         case '?': default:
	                 printf("wpalength: Unknow parameter '-%c' \nDigit: '-h'\n",optopt); return -1;
      }
   }

   for(; optind < argc; optind++) {
     if( strcmp(argv[optind], "-") ) {
        printf("wpalength: Unknow parameter '%s' \nDigit: '-h'\n", argv[optind]);
        return -1;
     }
   }

   check_length_save(&__information_file, &leng, &whatsave, &verbose);

  return 0;

} /* End main */

void
  usage(const char* ptr)

  {
       fprintf(stderr, " Usage: %s -f <fileinput> -l <maxlengthchar> -[OPTIONAL_PARAMETER..]\n\n"
              " Parameters:\n\n"
              " -f :   File da analizzare\n"
              " -l :   Lunghezza minima di ogni singola parola\n\n"
              " Optional Parameters:\n\n"
              " -v :   Modalità verbose. Visualizza ogni singola parola\n"
              " -s :   Salva le parole inferiori al numero indicato con -l in un file\n"
              " -e :   Elimina nel file originale le parole inferiori indicate dal parametro '-l'\n\n", ptr);
  }

void
  file_size(FILE* read, struct _file_information* _info)   /* Calcolo Grandezza file */

  {
       rewind(read);                                       /* Porta il cursore all inizio del file */
       fseek(read, 0, SEEK_END);

       _info->size_file = ftell(read);

       fclose(read);                                       /* Chiusura automatica del file */
  }

int
  check_length_save(struct _file_information *__info, const unsigned* leng, uint8_t* boolean/* 1 - stdin. 0 - save of file*/, uint8_t* verbose) {

   FILE *read, *write;

   read = fopen(__info->name_file, "r");

   if(!read) { perror(" "); return -1; }

   switch( *boolean ) {                         /* Output sullo stdin(schermo) */

      case 1:
              if( *verbose == 1 )               /* Modalità verbose */
              {
                sleep(1);                       /* Blocca per 2 secondi */  

                pars_leng_char_verb(read, __info, *&leng);
                fclose(read);
              }

              else if( *verbose == 0 )          /* Modalità non verbose */
              {
                printf(" [-] Reading file...\n");

                pars_leng_char(read, __info, *&leng);
                fclose(read);
              }

             file_print_size(__info->size_file); /* Stampa la grandezza del file */

             out_print_read_file(__info->name_file, &charmax, *leng, &lengshort);

             break;

      case 0:                                   /* Salva le parole con meno di '-l' caratteri in un file */
             write = fopen(strcat(__info->name_file, "_save.txt"), "w");

             char buffer[9000];

             if(!write) { perror(""); return -1; }

              while( fgets(buffer, sizeof(buffer), read) ) {
                 charmax++;
                 check = checkspace(buffer);

                 if( (strlen(buffer) - check) < *leng) {

                    fprintf(write,"-°%lu (%u/%u) %s", charmax, (unsigned)(strlen(buffer) - check), *leng, buffer);
                 }
              } /* End while */

              printf(" Success file saved in '%s'\n", __info->name_file);
              fclose(read); fclose(write);

              break;
   } /* End switch() */
   return 0;
 }

void
  pars_leng_char_verb(FILE* read, struct _file_information *_info, const unsigned* leng)

  {
      char buffer[9000];

      while(fgets(buffer, sizeof(buffer), read) ) {
         charmax++;
         check = checkspace(buffer);

         if( ( strlen(buffer) - check ) >= *leng) {
            out_add_print(buffer, (strlen(buffer) - check) );
         }

         if( ( strlen(buffer) - check ) < *leng ) {

            lengshort++;
            out_err_print(buffer, (strlen(buffer) - check) );
         }
      }
  }

int
  pars_leng_char(FILE* read, struct _file_information *_info, const unsigned* leng)

  {
      char buffer[9000];

      while(fgets(buffer, sizeof(buffer), read) ) {
         charmax++;
         check = checkspace(buffer);

         if( ( ( strlen(buffer) - check ) ) < *leng)
            lengshort++;
      }
      return 0;
  }

int
  check_if_int(char* buffer)

  {

      if( !atoi(buffer) ) {                          /* Se non e un numero */
         return INVALID_NUMBER;
      }

      if( atoi(buffer) > MAX_INT || atoi(buffer) <= 0) {
         return INVALID_PARAM_L;
      }
      return 0;
  }

int
  checkspace(char* word)

  {

      register unsigned i = 0;
      unsigned trash = 0;

      for(i = 0; i <= strlen(word); i++) {

         if(word[i] == '\0' || word[i] == '\t' || word[i] == '\r')
            trash++;
      }

      return trash;
  }

int
  automatic_erase(struct _file_information *__info, const unsigned* length)

  {
      char buffer[9000];

      FILE *read, *write, *read2, *write2;

      read  = fopen(__info->name_file,"r");

      printf("\n [+] Check del file '%s'\n", __info->name_file);

      pars_leng_char(read, __info, *&length);                  /* Controlla le parole inferiori al numero indicato con il parametro -l */

      if(lengshort == 0) {

         printf("\n Non ci sono parole inferiori a quelle indicate\n");
         return 0;
      }

      rewind(read);

      /* In caso che le parole siano inferiori..*/

      write = fopen(".tmpfile","w");

      if(!write) { perror(" "); return -1; }

      printf(" [-] Modifica file '%s' in corso..\n", __info->name_file);

      /* Rilegge il file originale */

      while( fgets(buffer, sizeof(buffer), read) ) {

         if( ( (int)strlen(buffer) - checkspace(buffer)) >= *length) {

            /* Scrive il contenuto nel file temporaneo */
            fprintf(write,"%s",buffer);
          }
      }

      fclose(read); fclose(write);

      memset(buffer, 0x00, sizeof(buffer));

      read2  = fopen(".tmpfile","r");
      write2 = fopen(__info->name_file, "w");

      /* Legge il file temporaneo */
      while( fgets(buffer, sizeof(buffer), read2) ) {

         /* Riscrive il contenuto del file temporaneo nel file originale */
         fprintf(write2, "%s", buffer);
      }

      fclose(read2); fclose(write2);

      out_print_cancell(&lengshort, &charmax);

      remove(".tmpfile");   /* Elimina il file temporaneo creato in precedenza */

      return 0;
  }
