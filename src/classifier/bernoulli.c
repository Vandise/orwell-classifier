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
  Converts a hexadecimal-like encoded string into a byte array
  in: "FFEEDAC"
  out: [0xFF, 0xEE, 0xDA, 0x0F]
*/
unsigned char* vocab_to_bin_array(const char *b_doc_vocab, const unsigned long int word_count) {
  const char *pos = b_doc_vocab;

  unsigned char* byte_array = __MALLOC__(word_count * sizeof(char));

  log_info("vocab_to_bin_array doc_vocab(%d) word_count(%lu)",
    strlen(b_doc_vocab),
    word_count
  );

  for (size_t count = 0; count < word_count; count++) {
    sscanf(pos, "%2hhx", &byte_array[count]);
    pos += 2;
  }

  return byte_array;
}

/*
  b_t
    returns whether or not a word exists in the binary string b_doc_vocab
*/
BOOLEAN b_t(const unsigned long int word_id, const char *b_doc_vocab) {
  const unsigned long int word_count = ceil( strlen(b_doc_vocab) / 2.0 );
  unsigned char* byte_array = vocab_to_bin_array(b_doc_vocab, word_count);

  //
  // if an id was requested higher than
  // the amount of bits present
  //
  if (word_id > (word_count * 8)) {
    log_info("b_t invalid word id requested id(%d) on bits(%d)",
      word_id,
      (word_count * 8)
    );
    return FALSE;
  }

  short int word_position = floor(word_id / 8);
  short int bit_position = word_id % 8;
  short int found = ((byte_array[word_position]) >> bit_position) & 1;

  log_info("b_t bit status id(%d) idx(%d) position(%d) found(%d)",
    word_id,
    word_position,
    bit_position,
    found
  );

  __FREE__(byte_array);

  if (found == 1) {
    return TRUE;
  }

  /*
  printf("0x\n");

  for(size_t count = 0; count < word_count; count++) {
      printf("%02x\n", byte_array[count]);
  }

  printf("\n");
  */

  return FALSE;
}