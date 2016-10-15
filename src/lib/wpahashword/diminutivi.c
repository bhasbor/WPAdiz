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

#include "diminutivi.h"

void
  conc_diminutivi(FILE* read, FILE* write)

  {
       char buffer[9000];

       while( (fscanf(read, "%s", buffer) ) != EOF) {

          int a = strlen(buffer);

             if( buffer[a-1] == A) {

                buffer[a-1] = 0x00;
                buffer[a] = 0x00;

                fprintf(write, "%s%s\n", buffer, ONA);
                fprintf(write, "%s%s\n", buffer, INA);
                fprintf(write, "%s%s\n", buffer, ETTA);
                fprintf(write, "%s%s\n", buffer, OTTA);
             }
             else if( buffer[a-1] == E || buffer[a-1] == I || buffer[a-1] == O || buffer[a-1] == U) {

                buffer[a-1] = 0x00;
                buffer[a] = 0x00;

                fprintf(write, "%s%s\n", buffer, ONE);
                fprintf(write, "%s%s\n", buffer, OTTO);

                if(buffer[a-2] == 'c') {
                   buffer[a-2] = 'c';
                   buffer[a-1] = 'h';
                }
                if(buffer[a-2] == 'g') {
                   buffer[a-1] = 'h';
                }

                fprintf(write, "%s%s\n", buffer, INO);
                fprintf(write, "%s%s\n", buffer, ETTO);
             }
       }
  }
