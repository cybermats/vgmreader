#include <criterion/criterion.h>
#include <signal.h>

#include "vgm.h"

Test(core, test_check_header_null)
{
  cr_assert(!vgm_validate_buffer(NULL, 0));
}


Test(core, test_check_header_wrong)
{
  char buffer[] = "Vgma";
  cr_assert(!vgm_validate_buffer(buffer, 4));  
}

Test(core, test_check_header_success)
{
  char buffer[] = "Vgm ";
  cr_assert(vgm_validate_buffer(buffer, 4));  
}


Test(core, test_parse_int_fail, .signal = SIGABRT)
{  
  parse_uint(NULL, 0, 0);
  cr_assert(0);
}


Test(core, test_parse_int_success)
{
  char buffer[] = {4, 3, 2, 1};
  cr_assert_eq(parse_uint(buffer, 0, 4), 0x1020304);
}


Test(core, test_parse_short_fail, .signal = SIGABRT)
{  
  parse_ushort(NULL, 0, 0);
  cr_assert(0);
}


Test(core, test_parse_short_success)
{
  char buffer[] = {4, 3, 2, 1};
  cr_assert_eq(parse_ushort(buffer, 1, 4), 0x203);
}


Test(core, test_parse_char_fail, .signal = SIGABRT)
{  
  parse_uchar(NULL, 0, 0);
  cr_assert(0);
}


Test(core, test_parse_char_success)
{
  char buffer[] = {4, 3, 2, 1};
  cr_assert_eq(parse_uchar(buffer, 2, 4), 0x2);

}


Test(core, test_parse_bcd_fail, .signal = SIGABRT)
{
  parse_bcd(NULL, 0, 0);
  cr_assert(0);
}


Test(core, test_parse_bcd_success)
{
  char buffer[] = {0x12, 0x34, 0x56, 0x78};
  cr_assert_eq(parse_bcd(buffer, 0, 4), 12345678);
}

