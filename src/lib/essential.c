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

#include "essential.h"

/* Autore Software */

const char*    _programm = NULL;   /* Nome programma -Optional-*/
const char*    _date     = NULL;   /* Inserisce la data */
const char*    _version  = NULL;   /* Versione del programma */
const char*    _author   = NULL;   /* Autore del programma */

void
  author()

  {
       /* In caso che nessuna variabile è inizializzata, stampa a schermo una scritta di default */
       if(_author == NULL && _programm == NULL && _version == NULL && _date == NULL)
          printf("\n Copyright Free Software (C)\n\n");

         else if(_programm == NULL)
            printf("\n Copyright (C) %s %s %s\n\n", _date, _version, _author);

            else
               printf("\n %s %s\n Copyright (C) %s %s\n\n", _programm, _version, _date, _author);
  }

/* Grandezze */

const unsigned        kB = 1024;
const unsigned long   MB = 1024 * 1024;
const unsigned long   GB = 1024 * 1024 * 1024;

/* Size file */

void
  file_print_size(unsigned long size)

  {

       if(size < kB)
          printf("\n-> Grandezza file (%ld byte)\n", size);

       else if(size >= kB && size < MB )
          printf("\n-> Grandezza file (%.1f kB)\n", (float)size / kB);

       else if(size >= MB && size < GB)
          printf("\n-> Grandezza file (%.1f MB)\n", (float)size / MB);

       else if(size >= GB)
          printf("\n-> Grandezza file (%.1f GB)\n", (float)size / GB);
  }
