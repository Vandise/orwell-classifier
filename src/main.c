#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_test_record() {
  FILE *fp;
  char buff[3];

  fp = fopen("docs/record.classify", "w");

  buff[0] = 0x01;
  buff[1] = '\n';
  fwrite(buff, 1, sizeof(buff) - 1, fp);

  char head_1[] = "1|6|11\n";
  fwrite(head_1, 1, sizeof(head_1) - 1, fp);

  char head_2[] = "9A\n";
  fwrite(head_2, 1, sizeof(head_2) - 1, fp);

  buff[0] = 0x02;
  buff[1] = '\n';
  fwrite(buff, 1, sizeof(buff) - 1, fp);

  char body[] = "3\n1\n2\n3\n3\n4\n4\n4\n";
  fwrite(body, 1, sizeof(body) - 1, fp);

  buff[0] = 0x03;
  buff[1] = '\n';
  fwrite(buff, 1, sizeof(buff) - 1, fp);

  char notes[] = "This should be classified as sports\n";
  fwrite(notes, 1, sizeof(notes) - 1, fp);

  buff[0] = 0x04;
  buff[1] = '\n';
  fwrite(buff, 1, sizeof(buff) - 1, fp);

  fclose(fp);
}

int main(int argc, const char* argv[]) {
  generate_test_record();

  char c = getchar();

  if (c != 0x01) {
    printf("\n Not a valid classification file \n");
    return -1;
  }

  getchar();

  char k_nk_n[128] = {0};
  int i = 0;
  while ((c=getchar()) != '\n') {
    printf("\n k_nk_n: %c (%x) \n", c, c);
    if (c != 0x00) {
      k_nk_n[i] = c;
      i++;
    }
  }

  printf("\n k_nk_n: %s \n", k_nk_n);

  char classification_str[1024] = {0};
  i = 0;
  while ((c=getchar()) != '\n') {
    printf("\n classification_str: %c (%x) \n", c, c);
    classification_str[i] = c;
    i++;
  }

  printf("\n classification_str: %c \n", classification_str[1]);

  return 0;
}