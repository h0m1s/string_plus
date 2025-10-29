#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>
#include <stdio.h>

typedef struct {
  int width;
  char length;
} options;

int s21_sscanf(const char *buffer, const char *format, ...);
void parse_options(const char **ptr, options *options);
void handle_integer(const char **str, va_list args, options options);
void handle_character(const char **str, va_list args, int *successfully_read,
                      options options);
void handle_string(const char **str, va_list args, options options);
void handle_pointer(const char **str, va_list args, int *successfully_read,
                    options options);
void handle_hex(const char **str, va_list args, int *successfully_read,
                options options);
void handle_n(const char *str, va_list args, const char *str_start);
void handle_octal(const char **str, va_list args, options options);
void handle_floats(const char **str, va_list args, int *successfully_read,
                   options options);
void handle_unsigned_integer(const char **str, va_list args, options options);
void handle_hex_octal_normal_integer(const char **str, va_list args,
                                     options options);
long read_number_from_str(const char **str, options options);
long read_hex_number_from_str(const char **str, options options,
                              int **successfully_read);
long read_octal_number_from_str(const char **str, options options);
long read_hex_octal_normal_from_str(const char **str, options options);
double read_float_from_str(const char **str, options options,
                           int *successfully_read);
void change_sign(const char **str, int *sign);
int s21_isspace(char c);
int s21_isdigit(char c);
int s21_is_octal_digit(char c);
int s21_is_hex_digit(char c);
unsigned long hex_to_decimal(const char *str, char **str_end, int width);
int hex_char_to_number(char c);
double str_to_double(const char *str, char **str_end, options options);
double read_from_str_to_double(const char **str);
long char_to_int(char c, const long *result);
void increment_successfull_reads(int *successfully_read);
#endif
