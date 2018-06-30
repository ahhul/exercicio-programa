#include "encryption.h"

/* encripta um bloco uint128 a partir da geração da chave intermediaria e
  de UMA ITERACAO em cima do bloco */
uint128 block_encrypt_k128 (uint128 block, uint128 key) {
  uint128 encrypted_block, int_key;
  int i;
  encrypted_block = block;
  for (i = 0; i < 12; i++) {
    /* cria a chave intermediaria e aplica uma iteracao do algoritmo com ela */
    int_key = intermediary_key (key, i);
    encrypted_block = one_iteration (i, int_key, encrypted_block);
    key = int_key;
  }
  return encrypted_block;
}

/* decripta um bloco uint128 a partir da geração de todas as subchaves e da
  inversa de UMA ITERACAO em cima do bloco encriptado. O laço ocorre de forma
  inversa a da encriptacao de um bloco */
uint128 block_decrypt_k128 (uint128 block, uint128 key) {
  uint128 decrypted_block, int_key[12];
  int i;

  decrypted_block = block;
  /* gera todas as subchaves primeiro*/
  for (i = 0; i < 12; i++) {
    int_key[i] = intermediary_key (key, i);
    /* pega a ultima chave gerada para gerar a proxima*/
    key = int_key[i];
  }

  for (i = 11; i >= 0; i--) {
    decrypted_block = reverse_one_iteration (i, int_key[i], decrypted_block);
  }
  return decrypted_block;
}

/* faz a encriptacao do arquivo de entrada */
void encryption (long file_size, byte_t *file_bytes, char* password, char* output) {
  uint128 *blocks, *encrypted, aux, VI_cbc, key;
  byte_t *encrypted_bytes;
  long i, n_blocks;

  /* array de blocks uint128 para blocos do arquivo original  */
  blocks = block_generation (file_size, file_bytes, &n_blocks, 1);
  /* cria o primeiro bloco com UMs do cbc */
  VI_cbc = block_VI_cbc();
  /* cria a chave */
  key = key_creation (password);
  /* array para blocos encriptados */
  encrypted = malloc (n_blocks * sizeof(uint128));

  /* faz o xor do cbc, encripta o bloco e atualiza o próximo bloco que será usado
  para */
  for (i = 0; i < n_blocks; i++) {
    aux = xor (blocks[i], VI_cbc);
    encrypted[i] = block_encrypt_k128 (aux, key);
    VI_cbc = encrypted[i];
  }

  /* transforma o vetor de blocos encriptados em um vetor de bytes */
  encrypted_bytes = blocks_to_bytes (encrypted, n_blocks);
  /* salva no arquivo de saida*/
  write_array_to_file (output, encrypted_bytes, 16 * n_blocks);

}

/* faz a decriptacao do arquivo de entrada */
void decryption (long file_size, byte_t *file_bytes, char* password, char* output) {
  uint128 *blocks, *decrypted, aux, VI_cbc, key;
  byte_t *decrypted_bytes;
  long i, n_blocks, size_decrypted;
  n_blocks = 0;

  /* array de blocks uint128 para blocos do arquivo original a ser
  descriptografado  */
  blocks = block_generation (file_size, file_bytes, &n_blocks, 0);
  /* cria o primeiro bloco com UMs do cbc */
  VI_cbc = block_VI_cbc();
  /* cria a chave */
  key = key_creation (password);
  /* array para blocos encriptados */
  decrypted = malloc (n_blocks * sizeof(uint128));

  /* faz o xor do cbc, encripta o bloco e atualiza o próximo bloco que será usado
  para */
  for (i = 0; i < n_blocks; i++) {
    /* precisa guardar esse bloco se não o valor é perdido */
    aux = blocks[i];
    decrypted[i] = block_decrypt_k128 (blocks[i], key);
    decrypted[i] = xor (decrypted[i], VI_cbc);
    VI_cbc = aux;
  }
  /* pega o tamanho do arquivo original para */
  size_decrypted = decrypted[n_blocks - 1].Z;
  free(blocks);
  /* transforma o vetor de blocos encriptados em um vetor de bytes */
  decrypted_bytes = blocks_to_bytes (decrypted, n_blocks);
  /* salva no arquivo de saida */
  write_array_to_file (output, decrypted_bytes, size_decrypted);
  free(decrypted);
}
