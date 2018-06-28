#include "utils.h"


/* Funcoes para senha e geracao da chave */
int password_check (char *password) {
  int i, d, a, len;
  len = strlen (password);
  d = a = 0;
  for (i = 0; i < len; i++) {
    if (isdigit (password[i]))  d++;
    else if (isalpha (password[i]))  a++;
  }
  if (d == 2 || a == 2) return 1;
  return 0;
}

char* password_concat (char *password) {
  int i, j, len;
  char *new_pass = malloc (16 * sizeof (char));
  len = strlen (password);
  j = 0;
  for (i = 0; i < 16; i++){
    new_pass[i] = password[j];
    j = i % len;
  }
  return new_pass;
}


/* funcoes para manipulacao de bytes */

/* converte um vetor de bytes em um inteiro de 32 bits */
uint32 byte_to_uint32 (byte_t bytes[]) {
  uint32 num_int32;
  num_int32 = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3] << 0);
  return num_int32;
}

/* converte um inteiro de 32 bits em um vetor de bytes*/
byte_t* uint32_to_byte (uint32 num_int32) {
  byte_t *bytes = malloc (4 * sizeof (byte_t));
  bytes[0] = (num_int32 >> 24) & 0xFF;
  bytes[1] = (num_int32 >> 16) & 0xFF;
  bytes[2] = (num_int32 >> 8) & 0xFF;
  bytes[3] = (num_int32 >> 0) & 0xFF;
  return bytes;
}

/* pega os 5 bits da direita do valor */
byte_t five_bits_right (uint32 num_int32) {
  return num_int32 & ((1 << 5) - 1);
}


/* cria um vetor de blocos de 128bits a partir de um vetor de bytes */
uint128* block_generation (long file_size, byte_t *file_bytes, int cripto) {
  /* variaveis para andar no laço e n_blocks = numero de blocos dentro da funcao,
    esse valor precisa ser passado para fora da funcao depois */
  long i, j, k, n_blocks;
  long size_array;
  /* vetor de blocks que será retornado*/
  uint128* array_blocks;
  /* vetores de bytes e uint32 para auxiliar na composicao dos blocos */
  byte_t four_bytes[4];
  uint32 four_32bits[4];

  /* calcula qual o tamanho o vetor de blocos deve ter e o aloca */
  if (file_size % 16 == 0)  size_array = file_size / 16;
  else  size_array = file_size / 16 + 1;
  array_blocks = malloc (size_array * sizeof (uint128));

  j = k = n_blocks = 0;
  /* anda pelo vetor de bytes do arquivo de entrada. armazena quatro bytes
    converte esses bytes em um uint32. Quando temos 4 uint32 criamos um uint128
    que é um bloco. No final um vetor de uint128 baseado no arquivo de arquivo
    de entrada é criado*/
  for (i = 0; i < size_array; i++) {
    four_bytes[j++] = file_bytes[i];
    if (j == 4) {
      four_32bits[k++] = byte_to_uint32 (four_bytes);
      if (k == 4) {
        array_blocks[n_blocks].X = four_32bits[0];
        array_blocks[n_blocks].Y = four_32bits[1];
        array_blocks[n_blocks].Z = four_32bits[2];
        array_blocks[n_blocks].W = four_32bits[3];
        k = 0;
        n_blocks++;
      }
      j = 0;
    }
  }

  /*  repetimos o fim do laço anterior adicionando bits iguais a 1 para arquivos
    em que o ultimo bloco tem tamanho menor que 128bits. Se k nao for igual a
    zero, o ultimo bloco não foi completado */
  if (k != 0) {
    while (k < 4) {
      four_bytes[j++] = 0xFF;
      if (j == 4) {
        four_32bits[k++] = byte_to_uint32 (four_bytes);
        if (k == 4) {
          array_blocks[n_blocks].X = four_32bits[0];
          array_blocks[n_blocks].Y = four_32bits[1];
          array_blocks[n_blocks].Z = four_32bits[2];
          array_blocks[n_blocks].W = four_32bits[3];
          n_blocks++;
        }
        j = 0;
      }
    }
  }

  /* Se a variavel cripto dos argumentos da funcao estiver setada para 1,
  significa que estamos criando blocos para a criptografia, entao o ultimo bloco
  deve ter o tamanho */

  

  return array_blocks;
}
