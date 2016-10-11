/* Text color non native del C, ma del sistema operativo Linux
 *
 *  Per chiudere un colore bisogna postporre, dopo la parola, la direttiva CLOSECOLOR.
 *
 *  (es.) ...<main>
 *       .. . .  ..
 *       .. printf(YELLOW"Parola colorata di giallo"CLOSECOLOR"\n");
*/

#define YELLOW     "\x1b[32m"
#define BLUE       "\x1b[34m"
#define RED        "\x1b[31m"

#define CLOSECOLOR "\x1b[0m"
