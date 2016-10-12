#include <stdio.h>

/* Autore Software */

const char*  _programm;  /* Nome programma -Optional-*/
const char*  _date;      /* Inserisce la data */
const char*  _version;   /* Versione del programma */
const char*  _author;    /* Autore del programma */

void author();

/* Types length (dove non c'e 'int' è sottointeso */

 #define UCHAR     255                  /* (unsigned char)      da 0..                  */
 #define SCHAR     127                  /* (signed char)        da -128..               */
 #define USHORT    65535                /* (unsigned short)     da 0..                  */
 #define SHORT     32767                /* (signed short)       da -32768               */
 #define UINT      0xFF                 /* (unsigned short)     da 0..                  */
 #define INT       2147483647           /* (int)                da -2147483648..        */
 #define ULONGLONG 18446744073709551615 /* (unsigned long long) da 0..                  */
 #define LONGLONG  9223372036854775807  /* (long long)          da -9223372036854775808 */

/* Grandezze */

const unsigned       kB;
const unsigned long  MB;
const unsigned long  GB;

/* Size file */

void file_print_size(unsigned long);
