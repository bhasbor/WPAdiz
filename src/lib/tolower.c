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
