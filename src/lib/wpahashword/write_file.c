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

#include "write_file.h"

int
  write_file(char* file, char* file_out, char* file_two, int16_t* check_toupper, char* word, uint8_t* _tratt, unsigned* num, unsigned* num2)

  {
       unsigned error_up = 0;

       FILE *read, *read2, *write;

       read = fopen(file, "r");

       if(!read) { perror(""); return -1; }

       char buffer[9000];

       write = fopen(file_out, "aw");

         switch( *_tratt )

         {
            case 0:							/* Concatenamento senza interi */
                    if(*check_toupper == -1) {				/* Non maiuscolo */

                                if(file_two == NULL) {

                                   while( (fscanf(read, "%s", buffer) ) != EOF)
                                      fprintf(write, "%s%s\n", buffer, word);
                                }
                                else {

                                   char buffer2[9000];

                                   read2 = fopen(file_two, "r");

                                   while( (fscanf(read, "%s", buffer) ) != EOF) {

                                      while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                         fprintf(write, "%s%s%s\n", buffer, buffer2, word);
                                      }
                                      rewind(read2);
                                   }
                                   fclose(read2);
                                }
                    }
                    else if(*check_toupper == 0) {						/* Maiuscolo */

                                if(file_two == NULL) {

                                   while( (fscanf(read, "%s", buffer) ) != EOF) {

                                      _hash_touplower(buffer, sizeof(buffer), 0);

                                      fprintf(write, "%s%s\n", buffer, word);
                                   }
                                }
                                else {

                                   char buffer2[9000];

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
                    else if(*check_toupper > 0 && *check_toupper <= 255) {			/* Maiuscolo Scelto dall utente */

                          if(file_two == NULL) {

                             while( (fscanf(read, "%s", buffer) ) != EOF) {

                                if(*check_toupper <= strlen(buffer)) {

                                   buffer[*check_toupper - 1] = toupper(buffer[*check_toupper - 1]);

                                   fprintf(write, "%s%s\n", buffer, word);
                                }
                                else {
                                    error_up++;
                                }
                             }
                          }
                          else {

                                 char buffer2[9000];

                                 read2 = fopen(file_two, "r");

                                 while( (fscanf(read, "%s", buffer) ) != EOF) {

                                    while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                       if(*check_toupper <= strlen(buffer)) {

                                           buffer[*check_toupper - 1 ] = toupper(buffer[*check_toupper - 1]);
                                           buffer2[*check_toupper - 1] = toupper(buffer2[*check_toupper - 1]);

                                           fprintf(write, "%s%s%s\n", buffer, buffer2, word);
                                       }
                                       else {
                                          error_up++;
                                       }
                                    }
                                    rewind(read2);
                                 }
                                 fclose(read2);
                             }
                    }
            break;
            case 1:							/* Con gli interi */

                   if(*check_toupper == -1) {				/* Non maiuscolo */

                       if(file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             for(unsigned i = *num; i <= *num2; i++)
                                fprintf(write, "%s%u\n", buffer, i);
                          }
                       }
                       else {

                          char buffer2[9000];

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                for(unsigned int i = *num; i <= *num2; i++)
                                   fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
                   }
                   if(*check_toupper == 0) {				/* Maiuscolo */

                       if(file_two == NULL) {

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             _hash_touplower(buffer, sizeof(buffer), 0);

                             for(unsigned i = *num; i <= *num2; i++)
                               fprintf(write, "%s%u\n", buffer, i);
                          }
                       }
                       else {

                          char buffer2[9000];

                          read2 = fopen(file_two, "r");

                          while( (fscanf(read, "%s", buffer) ) != EOF) {

                             while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                _hash_touplower(buffer, sizeof(buffer), 0);
                                _hash_touplower(buffer2, sizeof(buffer2), 0);

                                for(unsigned int i = *num; i <= *num2; i++)
                                   fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                             }
                             rewind(read2);
                          }
                          fclose(read2);
                       }
                   }
                   else if(*check_toupper > 0 && *check_toupper <= 255) {			/* Maiuscolo Scelto dall utente */

                          if(file_two == NULL) {

                             while( (fscanf(read, "%s", buffer) ) != EOF) {

                                if(*check_toupper <= strlen(buffer)) {

                                   buffer[*check_toupper - 1] = toupper(buffer[*check_toupper] - 1);

                                   for(unsigned int i = *num; i <= *num2; i++)
                                      fprintf(write, "%s%u\n", buffer, i);
                                }
                                else {
                                    error_up++;
                                }
                             }
                          }
                          else {

                                 char buffer2[9000];

                                 read2 = fopen(file_two, "r");

                                 while( (fscanf(read, "%s", buffer) ) != EOF) {

                                    while( (fscanf(read2, "%s", buffer2) ) != EOF) {

                                       if(*check_toupper <= strlen(buffer)) {

                                           buffer[*check_toupper - 1] = toupper(buffer[*check_toupper - 1]);
                                           buffer2[*check_toupper - 1] = toupper(buffer2[*check_toupper - 1]);

                                           for(unsigned int i = *num; i <= *num2; i++)
                                              fprintf(write, "%s%s%u\n", buffer, buffer2, i);
                                       }
                                       else {
                                          error_up++;
                                       }
                                    }
                                    rewind(read2);
                                 }
                                 fclose(read2);
                             }
                    }
         } /* End switch tratt */

   fclose(read); fclose(write);

   return error_up;
  }

void
  _hash_touplower(char* word, int size, uint8_t check /* 0 - maiuscolo, 1 - minuscolo */)

  {
       /* Maiuscolo */
       if(check == 0) {

          /* converte tutto l array in maiuscolo */
          for(unsigned int i = 0; i <= size; i++) {

             word[i] = toupper( word[i] );
          }
       }
       /* Minuscolo */
       else if(check == 1) {

          /* converte tutto l array in minuscolo */
          for(unsigned int i = 0; i <= size; i++) {

             word[i] = tolower( word[i] );
          }
       }
  }
