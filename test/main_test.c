#include <stdio.h>
#include <string.h>

#include "cspec.h"
#include "cspec_output_header.h"
#include "cspec_output_verbose.h"
#include "cspec_output_unit.h"
#include "util/memory.h"

DEFINE_DESCRIPTION(initial_test)
DEFINE_DESCRIPTION(utility_generic_linked_list)
DEFINE_DESCRIPTION(classifier_bernoulli)

int status = 0;

int main(int argc, const char* argv[]) {

  /*
  
    CSpec Lib Section
  
  */


    status += CSpec_Run( DESCRIPTION( initial_test ), CSpec_NewOutputVerbose() );

  /*
  
    Utilities Section
  
  */
    status += CSpec_Run( DESCRIPTION( utility_generic_linked_list ), CSpec_NewOutputVerbose() );


  /*
  
    Classifier
  
  */
    status += CSpec_Run( DESCRIPTION( classifier_bernoulli ), CSpec_NewOutputVerbose() );


  print_memory_summary();

  return status;
}