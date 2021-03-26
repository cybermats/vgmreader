#include <stdlib.h>
#include <check.h>

#include "check_check.h"

int main(void)
{
  int number_failed;
  SRunner *sr;

  sr = srunner_create(make_header_suite());
  srunner_add_suite(sr, make_core_suite());
  srunner_add_suite(sr, make_decode_file_suite());

  srunner_set_tap(sr, "testing.tap");
  
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
