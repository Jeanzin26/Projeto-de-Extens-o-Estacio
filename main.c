#include <ctype.h> // Biblioteca para manipulação de caracteres, como verificar se um caractere é um dígito.
#include <stdio.h>  // Biblioteca para entrada e saída padrão (printf, scanf, etc.).
#include <stdlib.h> // Biblioteca para funções de utilidade geral, como alocação de memória.
#include <string.h>  // Biblioteca para manipulação de strings (strcpy, strlen, etc.).
#include <time.h> // Biblioteca para manipulação de data e hora.

#define MAX_CLIENTES 100        
#define MAX_INTERACOES 1000
#define MAX_COMPRAS 1000

// Estruturas
typedef struct {
  int id;  // Identificador único do cliente.
  char nome[100];
  char telefone[15];
  char email[100];
  char endereco[200];
  time_t data_cadastro;
} Cliente;

typedef struct {
  int id_cliente; // Identificador do cliente relacionado à interação.
  char descricao_interacao[200];
  time_t data_interacao;
} Interacao;

typedef struct {
  int id_cliente; // Identificador do cliente relacionado à compra.
  char descricao_compra[100];
  double valor_compra;
  time_t data_compra;
} Compra;

// Variáveis globais
Cliente clientes[MAX_CLIENTES]; // Array para armazenar clientes.
Interacao interacoes[MAX_INTERACOES]; // Array para armazenar interações.
Compra compras[MAX_COMPRAS]; // Array para armazenar compras.
int total_clientes = 0, total_interacoes = 0, total_compras = 0; // Contadores de total de clientes, interações e compras.

// Função para registrar um cliente
void registrar_cliente() {
  Cliente novo_cliente; // Declaração de um novo cliente a ser registrado
  novo_cliente.id = total_clientes + 1; // Atribui um ID ao cliente com base no total atual de clientes

  printf("Nome do cliente: ");
  scanf(" %[^\n]s", novo_cliente.nome); // Lê o nome do cliente, permitindo espaços

  // Loop para garantir a entrada correta do telefone
  char telefone_temp[15]; // Variável temporária para armazenar o telefone antes da formatação
  int valido = 0; // Flag para verificar se o telefone é válido
  while (!valido) { // Continua pedindo o telefone até que seja válido
    printf("Telefone (DDD) e Número (ex: (11) 91234-5678 ESCREVA IGUAL AO EXEMPLO): ");
    scanf(" %[^\n]s", telefone_temp); // Lê a entrada do telefone

    // Verifica se o telefone contém apenas números, espaços, parênteses e hífens
    valido = 1; // Assume que é válido até encontrar um inválido
    for (int i = 0; telefone_temp[i] != '\0'; i++) { // Itera sobre cada caractere do telefone
      if (!isdigit(telefone_temp[i]) && telefone_temp[i] != '-' && // Verifica se é número ou hífen
          telefone_temp[i] != '(' && telefone_temp[i] != ')' && // Verifica se é parêntese
          telefone_temp[i] != ' ') { // Verifica se é espaço
        valido = 0; // Se encontrar um caractere inválido, marca como não válido
        break; // Sai do loop
      }
    }

    // Verifica o formato do telefone
    if (valido && (strlen(telefone_temp) < 14 || strlen(telefone_temp) > 15)) {
      printf("Formato de telefone inválido. Tente novamente.\n"); // Mensagem se o comprimento for inválido
      valido = 0; // Marca como não válido
    }
  }

  // Armazena o telefone formatado no cliente
  strcpy(novo_cliente.telefone, telefone_temp); // Copia o telefone validado para a estrutura do cliente

  printf("Email: ");
  scanf(" %[^\n]s", novo_cliente.email); // Lê o email do cliente

  printf("Endereco: ");
  scanf(" %[^\n]s", novo_cliente.endereco); // Lê o endereço do cliente

  novo_cliente.data_cadastro = time(NULL); // Armazena a data e hora atuais como data de cadastro

  clientes[total_clientes] = novo_cliente; // Adiciona o novo cliente ao array de clientes
  total_clientes++; // Incrementa o contador de clientes

  printf("Cliente registrado com sucesso!\n"); // Mensagem de confirmação
}


void listar_clientes() {  // Função para listar todos os clientes registrados.
  for (int i = 0; i < total_clientes; i++) {  // Itera por todos os clientes.
    char buffer[11]; // Buffer para armazenar a data formatada.
    strftime(buffer, sizeof(buffer), "%d-%m-%Y",
             localtime(&clientes[i].data_cadastro)); // Formata a data de cadastro.
    printf("ID: %d, Nome: %s, Telefone: %s, Email: %s, Endereco: %s, Data de "
           "Cadastro: %s\n",
           clientes[i].id, clientes[i].nome, clientes[i].telefone,
           clientes[i].email, clientes[i].endereco, buffer); // Exibe as informações do cliente.
  }
}

// Funções para gerenciamento de interações
void registrar_interacao() {
  Interacao nova_interacao; // Estrutura para a nova interação.
  int id_cliente;

  printf("ID do cliente: ");
  scanf("%d", &id_cliente);

  nova_interacao.id_cliente = id_cliente; // Atribui o ID ao nova interação.
  printf("Descricao da interacao: ");
  scanf(" %[^\n]s", nova_interacao.descricao_interacao);
  nova_interacao.data_interacao = time(NULL); // Define a data da interação como a data atual.

  interacoes[total_interacoes] = nova_interacao; // Adiciona a nova interação ao array de interações.  
  total_interacoes++; // Incrementa o contador de interações.

  printf("Interacao registrada com sucesso!\n");
}

void listar_interacoes(int id_cliente) { // Função para listar todos os clientes registrados.
  printf("Interacoes do cliente %d:\n", id_cliente); 
  for (int i = 0; i < total_interacoes; i++) {
    if (interacoes[i].id_cliente == id_cliente) { // Verifica se a interação pertence ao cliente.
      char buffer[11]; // Buffer para armazenar a data formatada.
      strftime(
          buffer, sizeof(buffer), "%d-%m-%Y",
          localtime(&interacoes[i].data_interacao)); // Apenas dia, mês e ano
      printf("Descricao: %s, Data: %s\n", interacoes[i].descricao_interacao,
             buffer); // Exibe a descrição e a data da interação.
    }
  }
}

// Funções para gerenciamento de compras
void registrar_compra() {
  Compra nova_compra;
  int id_cliente;
  char valor_str[20]; // String para armazenar o valor da compra

  printf("ID do cliente: ");
  scanf("%d", &id_cliente);

  nova_compra.id_cliente = id_cliente; // Atribui o ID ao nova compra.
  printf("Descricao da compra: ");
  scanf(" %[^\n]s", nova_compra.descricao_compra);

  printf("Valor da compra (ex: R$ 100,50): ");
  scanf(" %[^\n]s", valor_str); // Lê o valor como string

  // Remove "R$" e converte para double
  double valor_num = 0.0;
  if (sscanf(valor_str, "R$ %lf", &valor_num) == 1) { // Verifica se o formato é válido.
    nova_compra.valor_compra = valor_num; // Atribui o valor convertido à nova compra.
  } else {
    printf("Formato de valor inválido. A compra não será registrada.\n");
    return; // Retorna sem registrar a compra se o formato estiver incorreto
  }

  nova_compra.data_compra = time(NULL);

  compras[total_compras] = nova_compra; // Adiciona a nova compra ao array de compras.
  total_compras++; // Incrementa o contador de compras.

  printf("Compra registrada com sucesso!\n");
}

void listar_compras(int id_cliente) { // Função para listar compras de um cliente específico.
  printf("Compras do cliente %d:\n", id_cliente);
  for (int i = 0; i < total_compras; i++) {
    if (compras[i].id_cliente == id_cliente) { // Verifica se a compra pertence ao cliente.
      char buffer[11];
      strftime(buffer, sizeof(buffer), "%d-%m-%Y",
               localtime(&compras[i].data_compra)); // Apenas dia, mês e ano
      printf("Descricao: %s, Valor: R$ %.2f, Data: %s\n",
             compras[i].descricao_compra, compras[i].valor_compra, buffer);
    }
  }
}

// Relatórios
void gerar_relatorio_clientes() { // Função para gerar um relatório de clientes em formato CSV.
  FILE *relatorio = fopen("relatorio_clientes.csv", "w"); // Abre (ou cria) um arquivo CSV para escrita.
  fprintf(relatorio, "ID,Nome,Telefone,Email,Endereco,Data de Cadastro\n"); // Escreve o cabeçalho no arquivo.

  for (int i = 0; i < total_clientes; i++) { // Itera sobre todos os clientes.
    char buffer[11]; // Buffer para armazenar a data formatada.
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", 
             localtime(&clientes[i].data_cadastro)); // Formata a data de cadastro (apenas dia, mês e ano).
    fprintf(relatorio, "%d,%s,%s,%s,%s,%s\n", clientes[i].id, clientes[i].nome,
            clientes[i].telefone, clientes[i].email, clientes[i].endereco,
            buffer); // Escreve os dados do cliente no arquivo CSV.
  }

  fclose(relatorio); // Fecha o arquivo CSV.
  printf("Relatorio de clientes gerado com sucesso!\n"); // Exibe uma mensagem de sucesso.
}

void gerar_relatorio_compras() { // Função para gerar um relatório de compras em formato CSV.
  FILE *relatorio = fopen("relatorio_compras.csv", "w"); // Abre (ou cria) um arquivo CSV para escrita.
  fprintf(relatorio, "ID Cliente,Descricao,Valor,Data\n"); // Escreve o cabeçalho no arquivo.

  for (int i = 0; i < total_compras; i++) { // Itera sobre todas as compras.
    char buffer[11]; // Buffer para armazenar a data formatada.
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", 
             localtime(&compras[i].data_compra)); // Formata a data da compra (apenas dia, mês e ano).
    fprintf(relatorio, "%d,%s,R$ %.2f,%s\n", compras[i].id_cliente,
            compras[i].descricao_compra, compras[i].valor_compra, buffer); // Escreve os dados da compra no arquivo CSV.
  }

  fclose(relatorio); // Fecha o arquivo CSV.
  printf("Relatorio de compras gerado com sucesso!\n"); // Exibe uma mensagem de sucesso.
}

// Funções para salvar e carregar dados
void salvar_clientes() { // Função para salvar os dados dos clientes em um arquivo binário.
  FILE *arquivo = fopen("clientes.dat", "wb"); // Abre (ou cria) o arquivo binário para escrita.
  if (arquivo == NULL) { // Verifica se houve erro ao abrir o arquivo.
    perror("Erro ao abrir o arquivo clientes.dat"); // Exibe uma mensagem de erro.
    return; // Sai da função se não conseguiu abrir o arquivo.
  }

  fwrite(&total_clientes, sizeof(int), 1, arquivo); // Salva o número total de clientes.
  fwrite(clientes, sizeof(Cliente), total_clientes, arquivo); // Salva os dados dos clientes no arquivo.
  fclose(arquivo); // Fecha o arquivo.
}

void carregar_clientes() { // Função para carregar os dados dos clientes de um arquivo binário.
  FILE *arquivo = fopen("clientes.dat", "rb"); // Abre o arquivo binário para leitura.
  if (arquivo != NULL) { // Verifica se o arquivo foi aberto corretamente.
    fread(&total_clientes, sizeof(int), 1, arquivo); // Carrega o número total de clientes.
    fread(clientes, sizeof(Cliente), total_clientes, arquivo); // Carrega os dados dos clientes do arquivo.
    fclose(arquivo); // Fecha o arquivo.
  }
}

void salvar_compras() { // Função para salvar os dados das compras em um arquivo binário.
  FILE *arquivo = fopen("compras.dat", "wb"); // Abre (ou cria) o arquivo binário para escrita.
  if (arquivo == NULL) { // Verifica se houve erro ao abrir o arquivo.
    perror("Erro ao abrir o arquivo compras.dat"); // Exibe uma mensagem de erro.
    return; // Sai da função se não conseguiu abrir o arquivo.
  }

  fwrite(&total_compras, sizeof(int), 1, arquivo); // Salva o número total de compras.
  fwrite(compras, sizeof(Compra), total_compras, arquivo); // Salva os dados das compras no arquivo.
  fclose(arquivo); // Fecha o arquivo.
}

void carregar_compras() { // Função para carregar os dados das compras de um arquivo binário.
  FILE *arquivo = fopen("compras.dat", "rb"); // Abre o arquivo binário para leitura.
  if (arquivo != NULL) { // Verifica se o arquivo foi aberto corretamente.
    fread(&total_compras, sizeof(int), 1, arquivo); // Carrega o número total de compras.
    fread(compras, sizeof(Compra), total_compras, arquivo); // Carrega os dados das compras do arquivo.
    fclose(arquivo); // Fecha o arquivo.
  }
}

void salvar_interacoes() { // Função para salvar os dados das interações em um arquivo binário.
  FILE *arquivo = fopen("interacoes.dat", "wb"); // Abre (ou cria) o arquivo binário para escrita.
  if (arquivo == NULL) { // Verifica se houve erro ao abrir o arquivo.
    perror("Erro ao abrir o arquivo interacoes.dat"); // Exibe uma mensagem de erro.
    return; // Sai da função se não conseguiu abrir o arquivo.
  }

  fwrite(&total_interacoes, sizeof(int), 1, arquivo); // Salva o número total de interações.
  fwrite(interacoes, sizeof(Interacao), total_interacoes, arquivo); // Salva os dados das interações no arquivo.
  fclose(arquivo); // Fecha o arquivo.
}

void carregar_interacoes() { // Função para carregar os dados das interações de um arquivo binário.
  FILE *arquivo = fopen("interacoes.dat", "rb"); // Abre o arquivo binário para leitura.
  if (arquivo != NULL) { // Verifica se o arquivo foi aberto corretamente.
    fread(&total_interacoes, sizeof(int), 1, arquivo); // Carrega o número total de interações.
    fread(interacoes, sizeof(Interacao), total_interacoes, arquivo); // Carrega os dados das interações do arquivo.
    fclose(arquivo); // Fecha o arquivo.
  }
}

// Função para limpar o buffer de entrada (stdin)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer até o final da linha
}

// Menu
void menu() {
    int opcao;
    int sucesso;

    do {
        printf("\n-------- SISTEMA M.J.J.C --------\n");
        printf("1. Registrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Registrar Interacao\n");
        printf("4. Listar Interacoes\n");
        printf("5. Registrar Compra\n");
        printf("6. Listar Compras\n");
        printf("7. Gerar Relatorio de Clientes\n");
        printf("8. Gerar Relatorio de Compras\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");

        sucesso = scanf("%d", &opcao);

        if (sucesso != 1) { // Verifica se a entrada é válida
            printf("Entrada invalida! Por favor, insira um número.\n");
            limpar_buffer(); // Limpa o buffer de entrada para evitar loops infinitos
            continue; // Volta ao início do loop para solicitar nova entrada
        }

        switch (opcao) {
        case 1:
            registrar_cliente();
            break;
        case 2:
            listar_clientes();
            break;
        case 3:
            registrar_interacao();
            break;
        case 4: {
            int id_cliente;
            printf("ID do cliente: ");
            sucesso = scanf("%d", &id_cliente);
            if (sucesso != 1) {
                printf("ID inválido! Por favor, insira um número.\n");
                limpar_buffer(); // Limpa o buffer se o ID for inválido
                continue;
            }
            listar_interacoes(id_cliente);
            break;
        }
        case 5:
            registrar_compra();
            break;
        case 6: {
            int id_cliente;
            printf("ID do cliente: ");
            sucesso = scanf("%d", &id_cliente);
            if (sucesso != 1) {
                printf("ID inválido! Por favor, insira um número.\n");
                limpar_buffer(); // Limpa o buffer se o ID for inválido
                continue;
            }
            listar_compras(id_cliente);
            break;
        }
        case 7:
            gerar_relatorio_clientes();
            break;
        case 8:
            gerar_relatorio_compras();
            break;
        case 9:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida! Por favor, escolha uma opcao valida.\n");
            break;
        }

    } while (opcao != 9); // Repete até a opção ser 9 (Sair)
}

// Função principal
int main() {
  
    // Define o fuso horário para o horário de Brasília
    setenv("TZ", "America/Sao_Paulo", 1);
    tzset(); // Aplica a nova configuração de fuso horário

    carregar_clientes();
    carregar_compras();
    carregar_interacoes();

    menu();

    salvar_clientes();
    salvar_compras();
    salvar_interacoes();

    return 0;
}