#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include "color.h"

void out_add_print(wchar_t*, const unsigned);
void out_err_print(wchar_t*, const unsigned);
void out_print_read_file(char*, const unsigned long*, const uint8_t, const unsigned*, const unsigned);
void out_print_cancell(const unsigned*, const unsigned long*);
