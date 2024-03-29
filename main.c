/* Criptografia e Segurança de Dados  */
/* Exercício-programa 2018 - K128     */
/* Ludmila Ferreira Vicente e Silva   */

#include "utils.h"
#include "encryption.h"

int main (int argc, char *argv[]) {
  long file_size;
  byte_t *file_bytes;
  char *password; /* armazena a senha */

  /* abertura e leitura do arquivo a partir do hexdump */
  file_size = get_file_size (argv[3]);
  file_bytes = malloc (file_size * sizeof (*file_bytes));
  read_file_to_array (argv[3], file_bytes, file_size);

  /* Concatenação da senha e geração da chave */
  password = argv[7]; /* pega a senha da linha de comando */
  if (password_check (password) == 1) {
    password = password_concat (password); /* gera a chave K */
  }else {
    printf ("A senha digitada nao esta dentro da especificacao.\n");
  }

  /* encriptacao */
  if (strcmp (argv[1], "-c") == 0) {
    printf("Iniciando a criptografia do arquivo: %s.\n", argv[3]);
    encryption (file_size, file_bytes, password, argv[5]);
    printf("Fim da criptografia.\n");
  }
  /* decriptacao */
  if (strcmp (argv[1], "-d") == 0) {
    printf("Iniciando a decriptografia do arquivo: %s.\n", argv[3]);
    decryption (file_size, file_bytes, password, argv[5]);
    printf("Fim da decriptografia.\n");
  }
  /* apaga o arquivo de entrada caso seja passado o argumento -a */
  if (strcmp (argv[8], "-a") == 0) {
    byte_t* blanks = calloc (file_size, sizeof(byte_t));
    write_array_to_file(argv[3], blanks, file_size);
    remove(argv[3]);
  }

  return 0;
}
