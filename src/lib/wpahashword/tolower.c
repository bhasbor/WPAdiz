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

#include "tolower.h"

void
  _hash_touplower(char* word, int size, uint8_t check) {

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
