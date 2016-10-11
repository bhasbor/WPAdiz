#include "diminutivi.h"

 /* Desinenze diminutivi maschili */

 #define ONE  "one"
 #define ETTO "etto"
 #define INO  "ino"
 #define OTTO "otto"

 /* Desinenze diminutivi femminili */

 #define ONA  "ona"
 #define ETTA "etta"
 #define INA  "ina"
 #define OTTA "otta"

 /* Vocali */

 #define A     'a'
 #define E     'e'
 #define I     'i'
 #define O     'o'
 #define U     'u'

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
