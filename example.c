#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_IMPLEMENTATION
#include "str.h"

int main()
{
    size_t cap = 3;
    String s = str_new(cap);
    cap *= cap;
    str_grow(&s, cap);

    str_len(s) += snprintf(s, cap, "abc 123");
    str_len(s) += snprintf(str_end(s), str_rem(s), " - ");
    str_len(s) += snprintf(str_end(s), str_rem(s), "foobar");
    printf("\n=====\n%s\n=====\nlen=%zu, cap=%zu\n", s, strlen(s), str_cap(s));

    str_clear(s);
    printf("\n-----\n");

    str_printf(s, "abc 123");
    str_grow(&s, str_cap(s)*2);
    str_appendf(s, " - ");
    str_appendf(s, "foobar");
    printf("\n=====\n%s\n=====\nlen=%zu, cap=%zu\n", s, strlen(s), str_cap(s));

    str_clear(s);

    return 0;
}
