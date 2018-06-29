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

  /*encryption (file_size, file_bytes, password, argv[5]);*/
  decryption (file_size, file_bytes, password, argv[5]);

  /* TODO: OPCAO -a, ta escrito na agenda. Colocar brancos no arquivo e apaga-lo da maquina */

  /* encriptacao */
  if (strcmp (argv[1], "-c") == 1){
    printf("PASSEI HUE");
      encryption (file_size, file_bytes, password, argv[5]);
  }




  return 0;
}
