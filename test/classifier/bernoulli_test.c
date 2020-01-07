#include "cspec.h"
#include "cspec_output_header.h"
#include "cspec_output_verbose.h"
#include "cspec_output_unit.h"

#include "classifier/bernoulli.h"

extern int status;

DESCRIBE(classifier_bernoulli_phat_ck, "Bernoulli Classifier P_hat(Ck)")

  IT("Returns a float to three decimal places")
    int Nk = 2;
    int N  = 11;
    float v = phat_ck(Nk, N);

    SHOULD_BE_TRUE(
      (fabs(v - 0.182000) < 0.0001)
    );
  END_IT

END_DESCRIBE

DESCRIBE(classifier_bernoulli_b_t, "Bernoulli Classifier b_t")

  // 12 - 00010010
  // 0A - 00001010
  IT("Returns 1 if the word is present")
    SHOULD_EQUAL(b_t(11, "12A"), 1);
  END_IT

  IT("Returns 0 if the word is not present")
    SHOULD_EQUAL(b_t(4, "8F"), 0);
  END_IT

  IT("Returns 0 if an invalid word is specified")
    SHOULD_EQUAL(b_t(8, "0F"), 0);
  END_IT
END_DESCRIBE

DESCRIBE(classifier_bernoulli, "Bernoulli Classifier")
  status += CSpec_Run( DESCRIPTION( classifier_bernoulli_phat_ck ), CSpec_NewOutputVerbose() );
  status += CSpec_Run( DESCRIPTION( classifier_bernoulli_b_t ), CSpec_NewOutputVerbose() );
END_DESCRIBE