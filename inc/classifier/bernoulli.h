#ifndef __CLASSIFIER_BERNOULLI__
#define __CLASSIFIER_BERNOULLI__ 1

#include <math.h>
#include <string.h>
#include "common.h"
#include "util/log.h"

float phat_ck(const unsigned long int Nk, const unsigned long int N);
BOOLEAN b_t(const unsigned long int word_id, const char *soup);

#endif