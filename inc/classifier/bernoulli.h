#ifndef __CLASSIFIER_BERNOULLI__
#define __CLASSIFIER_BERNOULLI__ 1

#include <math.h>
#include <string.h>
#include "common.h"
#include "util/log.h"

float phat_ck(const unsigned long int Nk, const unsigned long int N);
unsigned char* vocab_to_bin_array(const char *b_doc_vocab, const unsigned long int word_count);
const unsigned short int b_t(const unsigned long int word_id, const char *soup);
float phat_wt_ck(const unsigned long int Nk_wt, const unsigned long int Nk);

#endif