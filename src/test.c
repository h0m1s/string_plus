#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"
#define EPSILON 0.0000000001

int double_equals(double a, double b) { return fabs(a - b) < EPSILON; }
START_TEST(s21_memchr_test) {
  const char* not_empty_str = "Hello,\tSchool21!";
  const char* empty_str = "";
  char have_ch = 'H';
  char doesnt_have_ch = 'y';
  char null_terminator = '\0';
  char non_printable = '\t';
  ck_assert_ptr_eq(s21_memchr(not_empty_str, have_ch, strlen(not_empty_str)),
                   memchr(not_empty_str, have_ch, strlen(not_empty_str)));
  ck_assert_ptr_eq(
      s21_memchr(not_empty_str, doesnt_have_ch, strlen(not_empty_str)),
      memchr(not_empty_str, doesnt_have_ch, strlen(not_empty_str)));
  ck_assert_ptr_eq(
      s21_memchr(not_empty_str, null_terminator, strlen(not_empty_str)),
      memchr(not_empty_str, null_terminator, strlen(not_empty_str)));
  ck_assert_ptr_eq(s21_memchr(empty_str, doesnt_have_ch, strlen(empty_str)),
                   memchr(empty_str, doesnt_have_ch, strlen(empty_str)));
  ck_assert_ptr_eq(
      s21_memchr(not_empty_str, non_printable, strlen(not_empty_str)),
      memchr(not_empty_str, non_printable, strlen(not_empty_str)));
}
END_TEST

START_TEST(s21_memcmp_test) {
  const char* str1 = "Hello,\tSchool21!";
  const char* str2 = "Hello,\tSchool21!";
  const char* str1_diff = "Hello,\tschool21!";
  const char* empty_str1 = "";
  const char* empty_str2 = "";
  const char* str_with_null_terminator = "Hello,\0School21!";

  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
  ck_assert_int_eq(s21_memcmp(str1, str1_diff, 10),
                   memcmp(str1, str1_diff, 10));
  ck_assert_int_eq(s21_memcmp(empty_str1, empty_str2, 1),
                   memcmp(empty_str1, empty_str2, 1));
  ck_assert_int_eq(s21_memcmp(str1, str1_diff, 0), memcmp(str1, str1_diff, 0));
  ck_assert_int_eq(s21_memcmp(str1, str_with_null_terminator, 10),
                   memcmp(str1, str_with_null_terminator, 10));
  ck_assert_int_eq(s21_memcmp(str1, str2, 1), memcmp(str1, str2, 1));
}

END_TEST

START_TEST(s21_memcpy_test) {
  char dest1[20];
  char dest2[20];
  const char src[] = "Hello, School21!";
  char long_src[] = "very looooooooooooooooooooooooong string";
  const char src_with_mid_null_terminator[] = "Hello, \0School21!";

  ck_assert_ptr_eq(s21_memcpy(dest1, src, 16), dest1);
  ck_assert_ptr_eq(memcpy(dest2, src, 16), dest2);
  ck_assert_mem_eq(dest1, dest2, 16);

  ck_assert_ptr_eq(s21_memcpy(dest1, src, 10), dest1);
  ck_assert_ptr_eq(memcpy(dest2, src, 10), dest2);
  ck_assert_mem_eq(dest1, dest2, 10);

  ck_assert_ptr_eq(s21_memcpy(dest1, long_src, 10), dest1);
  ck_assert_ptr_eq(memcpy(dest2, long_src, 10), dest2);
  ck_assert_mem_eq(dest1, dest2, 10);

  ck_assert_ptr_eq(s21_memcpy(dest1, src_with_mid_null_terminator, 16), dest1);
  ck_assert_ptr_eq(memcpy(dest2, src_with_mid_null_terminator, 16), dest2);
  ck_assert_mem_eq(dest1, dest2, 16);
}
END_TEST

START_TEST(s21_memset_test) {
  char str1[20];
  char str2[20];

  ck_assert_ptr_eq(s21_memset(str1, 'A', 10), str1);
  ck_assert_ptr_eq(memset(str2, 'A', 10), str2);
  ck_assert_mem_eq(str1, str2, 10);

  ck_assert_ptr_eq(s21_memset(str1, 'B', 5), str1);
  ck_assert_ptr_eq(memset(str2, 'B', 5), str2);
  ck_assert_mem_eq(str1, str2, 5);

  ck_assert_ptr_eq(s21_memset(str1, '\0', 20), str1);
  ck_assert_ptr_eq(memset(str2, '\0', 20), str2);
  ck_assert_mem_eq(str1, str2, 20);

  ck_assert_ptr_eq(s21_memset(str1, 'D', 15), str1);
  ck_assert_ptr_eq(memset(str2, 'D', 15), str2);
  ck_assert_mem_eq(str1, str2, 15);
}
END_TEST

START_TEST(s21_strchr_test) {
  const char* not_empty_str = "Hello,\tSchool21!";
  const char* empty_str = "";
  char have_ch = 'H';
  char doesnt_have_ch = 'y';
  char null_terminator = '\0';
  char non_printable = '\t';
  ck_assert_ptr_eq(s21_strchr(not_empty_str, have_ch),
                   strchr(not_empty_str, have_ch));
  ck_assert_ptr_eq(s21_strchr(not_empty_str, doesnt_have_ch),
                   strchr(not_empty_str, doesnt_have_ch));
  ck_assert_ptr_eq(s21_strchr(not_empty_str, null_terminator),
                   strchr(not_empty_str, null_terminator));
  ck_assert_ptr_eq(s21_strchr(empty_str, doesnt_have_ch),
                   strchr(empty_str, doesnt_have_ch));
  ck_assert_ptr_eq(s21_strchr(not_empty_str, non_printable),
                   strchr(not_empty_str, non_printable));
}
END_TEST

START_TEST(s21_strncat_test) {
  char s21_res_ptr[100];
  char res_ptr[100];

  char str1[20] = "Hello, ";
  char empty_str1[20] = "";
  const char* str2 = "School21!";
  char empty_str[100];
  empty_str[0] = '\0';
  const char non_null_terminated_str2[10] = {'S', 'c', 'h', 'o', 'o',
                                             'l', '2', '1', '!'};

  strcpy(s21_res_ptr, s21_strncat(str1, str2, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  strcpy(res_ptr, strncat(str1, str2, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);

  strcpy(s21_res_ptr, s21_strncat(str1, str2, (s21_size_t)3));
  strcpy(str1, "Hello, ");
  strcpy(res_ptr, strncat(str1, str2, (s21_size_t)3));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);

  strcpy(s21_res_ptr, s21_strncat(str1, empty_str, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  strcpy(res_ptr, strncat(str1, empty_str, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);

  strcpy(s21_res_ptr, s21_strncat(empty_str1, str2, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  empty_str1[0] = '\0';
  strcpy(res_ptr, strncat(empty_str1, str2, (s21_size_t)9));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);

  strcpy(s21_res_ptr, s21_strncat(str1, str2, (s21_size_t)0));
  strcpy(str1, "Hello, ");
  strcpy(res_ptr, strncat(str1, str2, (s21_size_t)0));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);

  strcpy(s21_res_ptr,
         s21_strncat(str1, non_null_terminated_str2, (s21_size_t)10));
  strcpy(str1, "Hello, ");
  strcpy(res_ptr, strncat(str1, non_null_terminated_str2, (s21_size_t)10));
  strcpy(str1, "Hello, ");
  ck_assert_pstr_eq(s21_res_ptr, res_ptr);
}
END_TEST

START_TEST(s21_strncmp_test) {
  const char* str1 = "Hello,\tSchool21!";
  const char* str2 = "Hello,\tSchool21!";
  const char* str1_diff = "Hello,\tschool21!";
  const char* empty_str1 = "";
  const char* empty_str2 = "";
  const char* str_with_null_terminator = "Hello,\0School21!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
  ck_assert_int_eq(s21_strncmp(str1, str1_diff, 10),
                   strncmp(str1, str1_diff, 10));
  ck_assert_int_eq(s21_strncmp(empty_str1, empty_str2, 10),
                   strncmp(empty_str1, empty_str2, 10));
  ck_assert_int_eq(s21_strncmp(str1, str1_diff, 0),
                   strncmp(str1, str1_diff, 0));
  ck_assert_int_eq(s21_strncmp(str1, str_with_null_terminator, 10),
                   strncmp(str1, str_with_null_terminator, 10));
  ck_assert_int_eq(s21_strncmp(str1, str2, 100), strncmp(str1, str2, 100));
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str1[20];
  const char str2[] = "Hello, School21!";
  const char empty_str[] = "";
  char long_str[] = "very looooooooooooooooooooooooong string";
  const char str_with_mid_null_terminator[] = "Hello, \0School21!";
  ck_assert_ptr_eq(s21_strncpy(str1, str2, 16), strncpy(str1, str2, 16));
  ck_assert_ptr_eq(s21_strncpy(str1, str2, 10), strncpy(str1, str2, 10));
  ck_assert_ptr_eq(s21_strncpy(str1, empty_str, 20),
                   strncpy(str1, empty_str, 20));
  ck_assert_ptr_eq(s21_strncpy(long_str, str2, 10),
                   strncpy(long_str, str2, 10));
  ck_assert_ptr_eq(s21_strncpy(str1, str_with_mid_null_terminator, 16),
                   strncpy(str1, str_with_mid_null_terminator, 16));
}
END_TEST

START_TEST(s21_strlen_test) {
  char test_1[] = "abcde";
  char test_2[] = "";
  char test_3[] = "  ";
  char test_4[] = "abc\0";
  char test_5[] = "abcd\0ef";
  ck_assert_int_eq(s21_strlen(test_1), strlen(test_1));
  ck_assert_int_eq(s21_strlen(test_2), strlen(test_2));
  ck_assert_int_eq(s21_strlen(test_3), strlen(test_3));
  ck_assert_int_eq(s21_strlen(test_4), strlen(test_4));
  ck_assert_int_eq(s21_strlen(test_5), strlen(test_5));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char test_1[] = "abcde";
  char test_2[] = "";
  char test_3[] = "abc\0ed";
  char test_1_1[] = "ed";
  char test_1_2[] = "a";
  char test_1_3[] = "";
  char test_1_4[] = "\0a";
  ck_assert_int_eq(s21_strcspn(test_1, test_1_1), strcspn(test_1, test_1_1));
  ck_assert_int_eq(s21_strcspn(test_1, test_1_2), strcspn(test_1, test_1_2));
  ck_assert_int_eq(s21_strcspn(test_1, test_1_3), strcspn(test_1, test_1_3));
  ck_assert_int_eq(s21_strcspn(test_1, test_1_4), strcspn(test_1, test_1_4));
  ck_assert_int_eq(s21_strcspn(test_2, test_1_1), strcspn(test_2, test_1_1));
  ck_assert_int_eq(s21_strcspn(test_2, test_1_2), strcspn(test_2, test_1_2));
  ck_assert_int_eq(s21_strcspn(test_2, test_1_3), strcspn(test_2, test_1_3));
  ck_assert_int_eq(s21_strcspn(test_2, test_1_4), strcspn(test_2, test_1_4));
  ck_assert_int_eq(s21_strcspn(test_3, test_1_1), strcspn(test_3, test_1_1));
  ck_assert_int_eq(s21_strcspn(test_3, test_1_2), strcspn(test_3, test_1_2));
  ck_assert_int_eq(s21_strcspn(test_3, test_1_3), strcspn(test_3, test_1_3));
  ck_assert_int_eq(s21_strcspn(test_3, test_1_4), strcspn(test_3, test_1_4));
}
END_TEST;

START_TEST(s21_strerror_test) {
  for (int test = -1; test <= 200; test++) {
    ck_assert_str_eq(s21_strerror(test), strerror(test));
  }
}
END_TEST;

START_TEST(s21_strpbrk_test) {
  char test_1[] = "School21";
  char test_2[] = "a";
  char test_1_1[] = "lo";
  char test_1_2[] = "";
  ck_assert_str_eq(s21_strpbrk(test_1, test_1_1), strpbrk(test_1, test_1_1));
  ck_assert_pstr_eq(s21_strpbrk(test_1, test_2), strpbrk(test_1, test_2));
  ck_assert_str_eq(s21_strpbrk(test_2, test_2), strpbrk(test_2, test_2));
  ck_assert_pstr_eq(s21_strpbrk(test_1, test_1_2), strpbrk(test_1, test_1_2));
  ck_assert_pstr_eq(s21_strpbrk(test_1_2, test_2), strpbrk(test_1_2, test_2));
}
END_TEST;

START_TEST(s21_sprintf_test) {
  char s21_str[100];
  char str[100];

  s21_sprintf(s21_str, "School21");
  sprintf(str, "School21");
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%k");
  sprintf(str, "Error Â¯\\_(*_*)_/Â¯");
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%Ld");
  sprintf(str, "Error Â¯\\_(*_*)_/Â¯");
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%c %d %f %s %u %%", 'c', 21, 21.21, "School21", 21);
  sprintf(str, "%c %d %f %s %u %%", 'c', 21, 21.21, "School21", 21);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%f %f %u", 123.999999999, -123.123, -123);
  sprintf(str, "%f %f %u", 123.999999999, -123.123, -123);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%+d % d % d %d %06d %06d %02d", 21, 21, -21, -21, 21,
              -21, 12345);
  sprintf(str, "%+d % d % d %d %06d %06d %02d", 21, 21, -21, -21, 21, -21,
          12345);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%6d %6d %6f %6.2f %.3f %.f", 21, 1234567, 1.234,
              123.12345, 12.12345, 12.12345);
  sprintf(str, "%6d %6d %6f %6.2f %.3f %.f", 21, 1234567, 1.234, 123.12345,
          12.12345, 12.12345);
  ck_assert_str_eq(s21_str, str);

  long int long_int = 2147483647;
  unsigned long int un_long_int = 4294967295;
  unsigned short int un_short_int = 65535;
  s21_sprintf(s21_str, "%ld %hd %lu %hu", long_int, 21, un_long_int,
              un_short_int);
  sprintf(str, "%ld %hd %lu %hu", long_int, 21, un_long_int, un_short_int);
  ck_assert_str_eq(s21_str, str);

  unsigned long int un_long_ox = 100;
  unsigned short int un_short_ox = 100;
  s21_sprintf(s21_str, "%lo %ho %lx %hx %lX %hX", un_long_ox, un_short_ox,
              un_long_ox, un_short_ox, un_long_ox, un_short_ox);
  sprintf(str, "%lo %ho %lx %hx %lX %hX", un_long_ox, un_short_ox, un_long_ox,
          un_short_ox, un_long_ox, un_short_ox);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%-6d", 21);
  sprintf(str, "%-6d", 21);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%g %G %e %e %E", 12.9999996, 12.9999996, 12345.12345,
              1.23456, 0.123456);
  sprintf(str, "%g %G %e %e %E", 12.9999996, 12.9999996, 12345.12345, 1.23456,
          0.123456);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%e %E", -12.345678, -0.0123456);
  sprintf(str, "%e %E", -12.345678, -0.0123456);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%.5g %.5G", 123.1234567, 123.1234567);
  sprintf(str, "%.5g %.5G", 123.1234567, 123.1234567);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%g %G", -12.123, -12.123);
  sprintf(str, "%g %G", -12.123, -12.123);
  ck_assert_str_eq(s21_str, str);

  int p = 21;
  s21_sprintf(s21_str, "%x %X %o %p", 123, 321, 455, &p);
  sprintf(str, "%x %X %o %p", 123, 321, 455, &p);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%x %X %o", 0, 0, 0);
  sprintf(str, "%x %X %o", 0, 0, 0);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%#x %#X %#o %#.0f", 123, 321, 455, 123.123);
  sprintf(str, "%#x %#X %#o %#.0f", 123, 321, 455, 123.123);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%06d", 123);
  sprintf(str, "%06d", 123);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%*d, %.*f, %*.*f", 6, 123, 2, 12.123456, 6, 2,
              12.345678);
  sprintf(str, "%*d, %.*f, %*.*f", 6, 123, 2, 12.123456, 6, 2, 12.345678);
  ck_assert_str_eq(s21_str, str);

  s21_sprintf(s21_str, "%Lf %Le %Lg", 123.123, 12.345671, 12.99999999);
  sprintf(str, "%lf %le %lg", 123.123, 12.345671, 12.99999999);
  ck_assert_str_eq(s21_str, str);
}
END_TEST;

START_TEST(test_s21_strrchr) {
  char str[] = "Hello, world!";
  ck_assert_str_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
  ck_assert_str_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
  ck_assert_ptr_eq(s21_strrchr("", 'o'), strrchr("", 'o'));
}
END_TEST

START_TEST(test_s21_strstr) {
  char haystack[] = "Hello, world!";
  char needle1[] = "world";
  char needle2[] = "Hello";
  char needle3[] = "not_found";
  char needle4[] = "\0";
  ck_assert_str_eq(s21_strstr(haystack, needle1), strstr(haystack, needle1));
  ck_assert_str_eq(s21_strstr(haystack, needle2), strstr(haystack, needle2));
  ck_assert_ptr_eq(s21_strstr(haystack, needle3), strstr(haystack, needle3));
  ck_assert_str_eq(s21_strstr(haystack, needle4), strstr(haystack, needle4));
  ck_assert_str_eq(s21_strstr(haystack, ""), strstr(haystack, ""));
}
END_TEST;

START_TEST(test_s21_strtok) {
  char str[] = "Hello, world! Strtok. Test";
  const char delim[] = " ,.!;";
  char* my_token;
  char* original_token;
  my_token = s21_strtok(str, delim);
  original_token = strtok(str, delim);
  ck_assert_str_eq(my_token, original_token);
  my_token = s21_strtok(str, delim);
  original_token = strtok(str, delim);
  ck_assert_str_eq(my_token, original_token);
  my_token = s21_strtok(str, delim);
  original_token = strtok(str, delim);
  ck_assert_str_eq(my_token, original_token);
  my_token = s21_strtok(str, delim);
  original_token = strtok(str, delim);
  ck_assert_str_eq(my_token, original_token);
  my_token = s21_strtok(str, delim);
  original_token = strtok(str, delim);
  ck_assert_str_eq(my_token, original_token);
  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
  ck_assert_ptr_eq(s21_strtok(str, "\0"), strtok(str, "\0"));
  ck_assert_ptr_eq(s21_strtok("\0", "?"), strtok("\0", "?"));
}
END_TEST;

START_TEST(s21_to_upper_test) {
  const char* not_empty_str = "Hello,School21!";
  const char* empty_str = "";
  const char* name_str = "Alex";
  const char* trim_chars_str = "!";

  char* str_upper1 = s21_to_upper(not_empty_str);
  char* str_upper2 = s21_to_upper(empty_str);
  char* str_upper3 = s21_to_upper(name_str);
  char* str_upper4 = s21_to_upper(trim_chars_str);
  char* str_upper5 = s21_to_upper(s21_NULL);

  ck_assert_str_eq(str_upper1, "HELLO,SCHOOL21!");
  ck_assert_str_eq(str_upper2, "");
  ck_assert_str_eq(str_upper3, "ALEX");
  ck_assert_str_eq(str_upper4, trim_chars_str);
  ck_assert_ptr_eq(str_upper5, NULL);

  free(str_upper1);
  free(str_upper2);
  free(str_upper3);
  free(str_upper4);
}
END_TEST

START_TEST(s21_to_lower_test) {
  const char* not_empty_str = "Hello,School21!";
  const char* empty_str = "";
  const char* name_str = "Alex";
  const char* trim_chars_str = "!";

  char* str_lower1 = s21_to_lower(not_empty_str);
  char* str_lower2 = s21_to_lower(empty_str);
  char* str_lower3 = s21_to_lower(name_str);
  char* str_lower4 = s21_to_lower(trim_chars_str);

  ck_assert_str_eq(str_lower1, "hello,school21!");
  ck_assert_str_eq(str_lower2, "");
  ck_assert_str_eq(str_lower3, "alex");
  ck_assert_str_eq(str_lower4, trim_chars_str);

  free(str_lower1);
  free(str_lower2);
  free(str_lower3);
  free(str_lower4);
}
END_TEST

START_TEST(s21_insert_test) {
  const char* not_empty_str = "Hello,School21!";
  const char* empty_str = "";
  const char* name_str = "Alex";

  char* str_insert1 = s21_insert(not_empty_str, name_str, 6);
  char* str_insert2 = s21_insert(empty_str, name_str, 0);
  char* str_insert3 = s21_insert(empty_str, name_str, 30);

  ck_assert_str_eq(str_insert1, "Hello,AlexSchool21!");
  ck_assert_str_eq(str_insert2, "Alex");
  ck_assert_pstr_eq(str_insert3, s21_NULL);

  free(str_insert1);
  free(str_insert2);
  free(str_insert3);
}
END_TEST

START_TEST(s21_trim_test) {
  const char* not_empty_str = "   Hello,School21!   ";
  const char* empty_str = "";
  const char* name_str = "!Alex!";
  const char* trim_chars_str = "!";

  char* str_trim1 = s21_trim(not_empty_str, s21_NULL);
  char* str_trim2 = s21_trim(name_str, trim_chars_str);
  char* str_trim3 = s21_trim(empty_str, name_str);

  ck_assert_str_eq(str_trim1, "Hello,School21!");
  ck_assert_str_eq(str_trim2, "Alex");
  ck_assert_str_eq(str_trim3, "");

  free(str_trim1);
  free(str_trim2);
  free(str_trim3);
}
END_TEST

START_TEST(s21_sscanf_test) {
  int d, s21_d, x, s21_x, o, s21_o, n, s21_n;
  int i1, s21_i1;
  int i2, s21_i2;
  int i3, s21_i3;
  unsigned int u, s21_u;
  char c, s21_c;
  float f1, s21_f1;
  float f2, s21_f2;
  float f3, s21_f3;
  char s[10], s21_s[10];
  void *p, *s21_p;

  s21_sscanf("s -21   \n21.0  \vSchool21 \f-1E-2 0xfa \r+1e+10",
             "%c %d %f %s %E %p %g", &s21_c, &s21_d, &s21_f1, s21_s, &s21_f2,
             &s21_p, &s21_f3);
  sscanf("s -21   \n21.0 \vSchool21 \f-1E-2 0xfa \r+1e+10",
         "%c %d %f %s %E %p %g", &c, &d, &f1, s, &f2, &p, &f3);
  ck_assert_int_eq(s21_c, c);
  ck_assert_int_eq(s21_d, d);
  ck_assert_double_eq(s21_f1, f1);
  ck_assert_double_eq(s21_f2, f2);
  ck_assert_double_eq(s21_f3, f3);
  ck_assert_str_eq(s21_s, s);
  ck_assert_ptr_eq(s21_p, p);

  s21_sscanf("-0x1AF -567 \t-21.21 2121 +0xabcDEF2 0567 -21",
             "%x %o %G %u %i %i %i %n", &s21_x, &s21_o, &s21_f1, &s21_u,
             &s21_i1, &s21_i2, &s21_i3, &s21_n);
  sscanf("-0x1AF -567 \t-21.21 2121 +0xabcDEF2 0567 -21",
         "%x %o %G %u %i %i %i %n", &x, &o, &f1, &u, &i1, &i2, &i3, &n);
  ck_assert_int_eq(s21_x, x);
  ck_assert_int_eq(s21_o, o);
  ck_assert_int_eq(s21_u, u);
  ck_assert_int_eq(s21_i1, i1);
  ck_assert_int_eq(s21_i2, i2);
  ck_assert_int_eq(s21_i3, i3);
  ck_assert_double_eq(s21_f1, f1);
  ck_assert_int_eq(s21_n, n);

  int a, s21_a, hex, s21_hex, oct, s21_oct;
  char c_str[10], s21_c_str[10];
  int *w_p, *s21_w_p;
  unsigned int w_u, s21_w_u;
  int w_i1, s21_w_i1;
  int w_i2, s21_w_i2;
  int w_i3, s21_w_i3;
  float w_f, s21_w_f;
  s21_sscanf("123 45s 0x2af 3a567 212123 0567 0x1af",
             "%03d %04c %5p %2x %3o %3u", &s21_a, s21_c_str, &s21_w_p, &s21_hex,
             &s21_oct, &s21_w_u);
  sscanf("123 45s 0x2af 3a567 212123 0567 0x1af", "%03d %04c %5p %2x %3o %3u",
         &a, c_str, &w_p, &hex, &oct, &w_u);

  s21_sscanf("123.123 212123 0567 0x1af", "%07f %6i %4i %04i", &s21_w_f,
             &s21_w_i1, &s21_w_i2, &s21_w_i3);
  sscanf("123.123 212123 0567 0x1af", "%07f %6i %4i %04i", &w_f, &w_i1, &w_i2,
         &w_i3);

  ck_assert_int_eq(s21_a, a);
  ck_assert_mem_eq(s21_c_str, c_str, 4);
  ck_assert_ptr_eq(s21_w_p, w_p);
  ck_assert_int_eq(s21_hex, hex);
  ck_assert_int_eq(s21_oct, oct);
  ck_assert_int_eq(s21_w_u, w_u);
  ck_assert_int_eq(s21_w_i1, w_i1);
  ck_assert_int_eq(s21_w_i2, w_i2);
  ck_assert_int_eq(s21_w_i3, w_i3);
  ck_assert_double_eq(s21_w_f, w_f);

  double le, s21_le, lg, s21_lg, lf, s21_lf;
  sscanf("123.123e-2 123.123 123.123", "%le %lg %lf", &le, &lg, &lf);
  s21_sscanf("123.123e-2 123.123 123.123", "%Le %Lg %Lf", &s21_le, &s21_lg,
             &s21_lf);

  ck_assert(double_equals(s21_le, le));
  ck_assert(double_equals(s21_lg, lg));
  ck_assert(double_equals(s21_lf, lf));

  long int ld, s21_ld, li1, s21_li1, li2, s21_li2, li3, s21_li3, lo, s21_lo, lx,
      s21_lx;
  long unsigned int lu, s21_lu;
  sscanf("123 123 0567 0x1fa 21 0567 0x1fa", "%ld %li %li %li %lu %lo %lx", &ld,
         &li1, &li2, &li3, &lu, &lo, &lx);
  s21_sscanf("123 123 0567 0x1fa 21 0567 0x1fa", "%ld %li %li %li %lu %lo %lx",
             &s21_ld, &s21_li1, &s21_li2, &s21_li3, &s21_lu, &s21_lo, &s21_lx);

  ck_assert_int_eq(s21_ld, ld);
  ck_assert_int_eq(s21_li1, li1);
  ck_assert_int_eq(s21_li2, li2);
  ck_assert_int_eq(s21_li3, li3);
  ck_assert_int_eq(s21_lu, lu);
  ck_assert_int_eq(s21_lo, lo);
  ck_assert_int_eq(s21_lx, lx);

  short int hd, s21_hd, hi1, s21_hi1, hi2, s21_hi2, hi3, s21_hi3, ho, s21_ho,
      hx, s21_hx;
  short unsigned int hu, s21_hu;
  sscanf("% 123 123 0567 0x1fa 21 0567 0x1fa", "%% %hd %hi %hi %hi %hu %ho %hx",
         &hd, &hi1, &hi2, &hi3, &hu, &ho, &hx);
  s21_sscanf("% 123 123 0567 0x1fa 21 0567 0x1fa",
             "%% %hd %hi %hi %hi %hu %ho %hx", &s21_hd, &s21_hi1, &s21_hi2,
             &s21_hi3, &s21_hu, &s21_ho, &s21_hx);

  ck_assert_int_eq(s21_hd, hd);
  ck_assert_int_eq(s21_hi1, hi1);
  ck_assert_int_eq(s21_hi2, hi2);
  ck_assert_int_eq(s21_hi3, hi3);
  ck_assert_int_eq(s21_hu, hu);
  ck_assert_int_eq(s21_ho, ho);
  ck_assert_int_eq(s21_hx, hx);
}
END_TEST

int main() {
  Suite* s = suite_create("s21_string");
  TCase* tc = tcase_create("s21_string");
  SRunner* sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memchr_test);
  tcase_add_test(tc, s21_memcmp_test);
  tcase_add_test(tc, s21_memcpy_test);
  tcase_add_test(tc, s21_memset_test);
  tcase_add_test(tc, s21_strlen_test);
  tcase_add_test(tc, s21_strcspn_test);
  tcase_add_test(tc, s21_strerror_test);
  tcase_add_test(tc, s21_strpbrk_test);
  tcase_add_test(tc, s21_sprintf_test);
  tcase_add_test(tc, test_s21_strrchr);
  tcase_add_test(tc, test_s21_strstr);
  tcase_add_test(tc, test_s21_strtok);
  tcase_add_test(tc, s21_strchr_test);
  tcase_add_test(tc, s21_strncat_test);
  tcase_add_test(tc, s21_strncmp_test);
  tcase_add_test(tc, s21_strncpy_test);
  tcase_add_test(tc, s21_to_upper_test);
  tcase_add_test(tc, s21_to_lower_test);
  tcase_add_test(tc, s21_insert_test);
  tcase_add_test(tc, s21_trim_test);
  tcase_add_test(tc, s21_sscanf_test);
  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);
  return 0;
}