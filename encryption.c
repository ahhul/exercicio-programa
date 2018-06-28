#include "encryption.h"


uint128 block_encrypt_k128 (uint128 block, uint128 key) {
  uint128 encrypted_block, int_key;
  int i;
  for (i = 0; i < 12; i++) {
    /* cria a chave intermediaria e aplica uma iteracao do algoritmo com ela */
    int_key = intermediary_key (key, i);
    encrypted_block = one_iteration (i, int_key, block);
    key = int_key;
  }
  return encrypted_block;
}


/* in_blocks - blocos uint128 do arquivo de entrada */
void encryption (long file_size, byte_t *file_bytes, uint128 *in_blocks, char* password) {
  uint128 *encrypted;
  uint128 VI_cbc, key;

  block_generation (file_size, file_bytes, 1);
  VI_cbc = block_VI_cbc();

  /* cria a chave */
  key = key_creation (password);

}
