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
