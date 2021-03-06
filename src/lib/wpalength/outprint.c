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
  out_add_print(wchar_t* word, const unsigned length, const unsigned tab)

  {
       printf("- "YELLOW"[ OK ]"CLOSECOLOR BLUE"(\"%u\") "CLOSECOLOR BLUE"("CLOSECOLOR"%u"BLUE")"CLOSECOLOR " | %ls", length, tab, word);
  }

void
  out_err_print(wchar_t* word, const unsigned length, const unsigned tab)

  {
       printf("-"BLUE" ["CLOSECOLOR RED" ! "CLOSECOLOR BLUE"]"CLOSECOLOR RED" (\"%u\")"CLOSECOLOR BLUE" ("CLOSECOLOR"%u"BLUE")"CLOSECOLOR" | %ls", length, tab, word);
  }

void
  out_print_read_file(char* file, const unsigned long* charmax, const uint8_t leng, const unsigned* lengshort, const unsigned max_leng_wpa)

  {

       printf("-> Lettura da file '%s' Completata.\n", file);
       printf("-> Sono presenti circa \"%lu\" parole.\n", *charmax);
       printf("-> Parole con meno di %u caratteri: "YELLOW"%u"CLOSECOLOR"\n"
              "-> Parole superiori a 64           ("YELLOW"%u"CLOSECOLOR")\n", leng, *lengshort, max_leng_wpa);
  }

void
  out_print_cancell(const unsigned* lengshort, const unsigned long* charmax)

  {
       printf("\n Completato: Parole cancellate "YELLOW"%u"CLOSECOLOR", su "YELLOW"%lu"CLOSECOLOR" parole.\n", *lengshort, *charmax);
  }
