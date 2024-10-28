#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    char nomeCliente[50];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

int buscarConta(Conta contas[], int quantidade, int numeroConta) {
    for (int i = 0; i < quantidade; i++) {
        if (contas[i].numeroConta == numeroConta) {
            return i;
        }
    }
    return (quantidade == 0) ? -1 : -2;
}

void cadastrarConta(Conta contas[], int *quantidade) {
    if (*quantidade >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }
    
    int numero;
    printf("Digite o número da nova conta: ");
    scanf("%d", &numero);
    
    if (buscarConta(contas, *quantidade, numero) >= 0) {
        printf("Conta com número repetido. Não é possível cadastrar.\n");
        return;
    }

    contas[*quantidade].numeroConta = numero;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", contas[*quantidade].nomeCliente);
    printf("Digite o CPF do cliente: ");
    scanf("%s", contas[*quantidade].cpf);
    printf("Digite o telefone de contato: ");
    scanf("%s", contas[*quantidade].telefone);
    contas[*quantidade].saldo = 0.0;
    (*quantidade)++;
}

void consultarSaldo(Conta contas[], int quantidade) {
    int numero;
    printf("Digite o número da conta para consultar o saldo: ");
    scanf("%d", &numero);
    
    int indice = buscarConta(contas, quantidade, numero);
    if (indice >= 0) {
        printf("Saldo da conta %d: %.2f\n", numero, contas[indice].saldo);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void depositar(Conta contas[], int quantidade) {
    int numero;
    float valor;
    printf("Digite o número da conta para depósito: ");
    scanf("%d", &numero);
    
    int indice = buscarConta(contas, quantidade, numero);
    if (indice >= 0) {
        printf("Digite o valor a depositar: ");
        scanf("%f", &valor);
        if (valor > 0) {
            contas[indice].saldo += valor;
            printf("Depósito realizado com sucesso. Novo saldo: %.2f\n", contas[indice].saldo);
        } else {
            printf("Valor inválido.\n");
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void sacar(Conta contas[], int quantidade) {
    int numero;
    float valor;
    printf("Digite o número da conta para saque: ");
    scanf("%d", &numero);
    
    int indice = buscarConta(contas, quantidade, numero);
    if (indice >= 0) {
        printf("Digite o valor a sacar: ");
        scanf("%f", &valor);
        if (valor > 0 && valor <= contas[indice].saldo) {
            contas[indice].saldo -= valor;
            printf("Saque realizado com sucesso. Novo saldo: %.2f\n", contas[indice].saldo);
        } else {
            printf("Saldo insuficiente ou valor inválido.\n");
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void exibirInformacoesContas(Conta contas[], int quantidade) {
    printf("Informações das contas cadastradas:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Conta: %d, Nome: %s, Telefone: %s\n", 
               contas[i].numeroConta, contas[i].nomeCliente, contas[i].telefone);
    }
}

int main() {
    Conta contasCorrente[MAX_CONTAS];
    Conta contasPoupanca[MAX_CONTAS];
    int quantidadeCorrente = 0, quantidadePoupanca = 0;

    cadastrarConta(contasCorrente, &quantidadeCorrente);
    consultarSaldo(contasCorrente, quantidadeCorrente);
    depositar(contasCorrente, quantidadeCorrente);
    sacar(contasCorrente, quantidadeCorrente);
    exibirInformacoesContas(contasCorrente, quantidadeCorrente);
    
    return 0;
}
