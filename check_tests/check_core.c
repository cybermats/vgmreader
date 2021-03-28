#include <stdlib.h>
#include <check.h>

#include "vgm.h"

START_TEST(test_check_header_null)
{
  ck_assert(!vgm_validate_buffer(NULL, 0));  
}
END_TEST

START_TEST(test_check_header_wrong)
{
  char buffer[] = "Vgma";
  ck_assert(!vgm_validate_buffer(buffer, 4));  
}
END_TEST

START_TEST(test_check_header_success)
{
  char buffer[] = "Vgm ";
  ck_assert(vgm_validate_buffer(buffer, 4));  
}
END_TEST

START_TEST(test_parse_int_fail)
{  
  parse_uint(NULL, 0, 0);
  ck_assert(0);
}
END_TEST

START_TEST(test_parse_int_success)
{
  char buffer[] = {4, 3, 2, 1};
  ck_assert_uint_eq(parse_uint(buffer, 0, 4), 0x1020304);
}
END_TEST

START_TEST(test_parse_short_fail)
{  
  parse_ushort(NULL, 0, 0);
  ck_assert(0);
}
END_TEST

START_TEST(test_parse_short_success)
{
  char buffer[] = {4, 3, 2, 1};
  ck_assert_uint_eq(parse_ushort(buffer, 1, 4), 0x203);
}
END_TEST

START_TEST(test_parse_char_fail)
{  
  parse_uchar(NULL, 0, 0);
  ck_assert(0);
}
END_TEST

START_TEST(test_parse_char_success)
{
  char buffer[] = {4, 3, 2, 1};
  ck_assert_uint_eq(parse_uchar(buffer, 2, 4), 0x2);

}
END_TEST

START_TEST(test_parse_bcd_fail)
{
  parse_bcd(NULL, 0, 0);
  ck_assert(0);
}
END_TEST

START_TEST(test_parse_bcd_success)
{
  char buffer[] = {0x12, 0x34, 0x56, 0x78};
  ck_assert_uint_eq(parse_bcd(buffer, 0, 4), 12345678);
}
END_TEST

Suite *make_core_suite(void)
{
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Empty");

  tcase_add_test(tc, test_check_header_null);
  tcase_add_test(tc, test_check_header_wrong);
  tcase_add_test(tc, test_check_header_success);
  tcase_add_test_raise_signal(tc, test_parse_int_fail, 6);
  tcase_add_test(tc, test_parse_int_success);
  tcase_add_test_raise_signal(tc, test_parse_short_fail, 6);
  tcase_add_test(tc, test_parse_short_success);
  tcase_add_test_raise_signal(tc, test_parse_char_fail, 6);
  tcase_add_test(tc, test_parse_char_success);
  tcase_add_test_raise_signal(tc, test_parse_bcd_fail, 6);
  tcase_add_test(tc, test_parse_bcd_success);

  suite_add_tcase(s, tc);
  
  return s;
}
