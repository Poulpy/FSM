#ifndef UCHAR_ARRAY_H
#define UCHAR_ARRAY_H

struct char_array {
  unsigned char *chars;
  size_t len;
};

struct char_array new_uchar_array(size_t len);
struct char_array new_ascii_array();
void free_uchar_array(struct char_array *ca);
void append_uchar_array(struct char_array *ca, unsigned char c);

#endif
