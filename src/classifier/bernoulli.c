#include "classifier/bernoulli.h"

/*
  P_hat(Ck)
    returns number of documents with class "k" divided by the number of documents
            in the entire vocabulary ( set )
*/
float phat_ck(const unsigned long int Nk, const unsigned long int N) {
  log_info("P_hat(Ck) Nk(%lu) N(%lu)", Nk, N);

  return ceil(((float)Nk / (float)N) * 1000.0) / 1000.0;
}

/*
  b_t
    returns whether or not a word exists in the binary string b_doc_vocab
*/
BOOLEAN b_t(const unsigned long int word_id, const char *b_doc_vocab) {
  int word_count = ceil( strlen(b_doc_vocab) / 2.0 );
  const char *pos = b_doc_vocab;

  unsigned char byte_array[word_count];

  log_info("b_t doc_vocab(%d) word_count(%d)",
    strlen(b_doc_vocab),
    word_count
  );

  for (size_t count = 0; count < sizeof byte_array / sizeof *byte_array; count++) {
    sscanf(pos, "%2hhx", &byte_array[count]);
    pos += 2;
  }

  printf("0x\n");

  for(size_t count = 0; count < sizeof byte_array / sizeof *byte_array; count++) {
      printf("%02x\n", byte_array[count]);
  }

  printf("\n");

  return FALSE;
}