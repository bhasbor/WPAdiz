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

#include "outprint.h"

void
  out_add_print(char* word, const unsigned length)

  {
       printf(YELLOW"- [ OK ]"CLOSECOLOR BLUE"(\"%u\")"CLOSECOLOR "| %s", length, word);
  }

void
  out_err_print(char* word, const unsigned length)

  {
       printf("-"BLUE" ["CLOSECOLOR RED" ! "CLOSECOLOR BLUE"]"CLOSECOLOR RED"(\"%u\")"CLOSECOLOR "|  %s", length, word);
  }

void
  out_print_read_file(char* file, const unsigned long* charmax, const unsigned leng, unsigned* lengshort)

  {
       printf("-> Lettura da file '%s' Completata.\n", file);
       printf("-> Sono presenti circa \"%lu\" parole.\n", *charmax);
       printf("-> Parole con meno di %u caratteri: "YELLOW"%u"CLOSECOLOR"\n", leng, *lengshort);
  }

void
  out_print_cancell(unsigned* lengshort, unsigned long* charmax)

  {
       printf("\n Completato: Parole cancellate "YELLOW"%u"CLOSECOLOR", su "YELLOW"%lu"CLOSECOLOR" parole.\n\n", *lengshort, *charmax);
  }
