#ifndef STR_H_
#define STR_H_

typedef char * String;

typedef struct {
    size_t len;
    size_t cap;
} String_Header;

#define str_hdr(s) ((String_Header *)(s) - 1)
#define str_len(s) (str_hdr(s)->len)
#define str_cap(s) (str_hdr(s)->cap)
#define str_rem(s) (str_cap(s) - str_len(s))
#define str_end(s) (s + str_len(s))

#define str_printf(s, ...) do { str_len(s) += snprintf(s, str_cap(s), __VA_ARGS__); } while (0)
#define str_appendf(s, ...) do { str_len(s) += snprintf(str_end(s), str_rem(s), __VA_ARGS__); } while (0)

String str_new(size_t cap);
void str_grow(String *s, size_t cap);
void str_clear(String s);
void str_free(String s);

#endif // STR_H_

#ifdef STR_IMPLEMENTATION

String str_new(size_t cap)
{
    // TODO: handle error
    String_Header *h = (String_Header *)malloc(sizeof(String_Header) + sizeof(char) * cap);
    h->len = 0;
    h->cap = cap;
    String s = (String)(h + 1);
    s[0] = '\0';
    return s;
}

void str_grow(String *s, size_t cap)
{
    // TODO: handle error
    String_Header *h = (String_Header *)realloc(str_hdr(*s), sizeof(String_Header) + sizeof(char) * cap);
    h->cap = cap;
    *s = (String)(h + 1);
}

void str_clear(String s)
{
    str_len(s) = 0;
    if (str_cap(s) > 0) s[0] = '\0';
}

void str_free(String s)
{
    free(str_hdr(s));
}

#endif // STR_IMPLEMENTATION
