/* ============================================================
 * Trabalho Pratico - Calculadora de Matrizes
 * Disciplina: Algebra Linear / Desenvolvimento de Software Multiplataforma
 * Linguagem: C
 * ============================================================ */

#include <stdio.h> /*bibliotecas usadas para a execução do programa*/
#include <stdlib.h>
#include <time.h>

#define MAX_DIM 10      /* tamanho maximo permitido para linhas/colunas */
#define EPSILON 0.0001  /* tolerancia usada para comparar numeros decimais */

/* Estrutura que representa uma matriz.
 * "cadastrada" indica se a matriz ja foi preenchida pelo usuario,
 * evitando que o programa tente operar com uma matriz vazia. */
typedef struct {
    int linhas;
    int colunas;
    double dados[MAX_DIM][MAX_DIM];
    int cadastrada;
} Matriz;

/* ------------------------------------------------------------
 * Funcao auxiliar: limpa o buffer de entrada.
 * Usada apos leituras inválidas para evitar loop infinito ou
 * comportamento inesperado (crash) quando o usuario digita
 * algo que nao e numero.
 * ------------------------------------------------------------ */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta os caracteres restantes da linha */
    }
}

/* ------------------------------------------------------------
 * Funcao auxiliar: le um numero inteiro de forma segura.
 * Repete a leitura enquanto a entrada for invalida.
 * ------------------------------------------------------------ */
int lerInteiro(const char *mensagem) {
    int valor;
    int ok;

    do {
        printf("%s", mensagem);
        ok = scanf("%d", &valor);
        limparBuffer();

        if (ok != 1) {
            printf("Entrada invalida! Digite um numero inteiro.\n");
        }
    } while (ok != 1);

    return valor;
}

/* ------------------------------------------------------------
 * Funcao auxiliar: le um numero real (double) de forma segura.
 * ------------------------------------------------------------ */
double lerDouble(const char *mensagem) {
    double valor;
    int ok;

    do {
        printf("%s", mensagem);
        ok = scanf("%lf", &valor);
        limparBuffer();

        if (ok != 1) {
            printf("Entrada invalida! Digite um numero (ex: 3 ou 3.5).\n");
        }
    } while (ok != 1);

    return valor;
}

/* ------------------------------------------------------------
 * 4.1 Cadastro de matriz
 * Pergunta linhas e colunas (validando limites) e o modo de
 * preenchimento: manual (elemento por elemento) ou automatico
 * (valores aleatorios dentro de um intervalo definido).
 * ------------------------------------------------------------ */
void cadastrarMatriz(Matriz *m, const char *nome) {
    int opcao;

    printf("\n--- Cadastro da Matriz %s ---\n", nome);

    /* Le linhas e colunas garantindo que fiquem dentro do limite maximo */
    do {
        m->linhas = lerInteiro("Numero de linhas: ");
        if (m->linhas <= 0 || m->linhas > MAX_DIM) {
            printf("Valor invalido! Informe um numero entre 1 e %d.\n", MAX_DIM);
        }
    } while (m->linhas <= 0 || m->linhas > MAX_DIM);

    do {
        m->colunas = lerInteiro("Numero de colunas: ");
        if (m->colunas <= 0 || m->colunas > MAX_DIM) {
            printf("Valor invalido! Informe um numero entre 1 e %d.\n", MAX_DIM);
        }
    } while (m->colunas <= 0 || m->colunas > MAX_DIM);

    /* Escolha do modo de preenchimento */
    printf("Preenchimento:\n");
    printf("1 - Manual (digitar cada elemento)\n");
    printf("2 - Automatico (valores aleatorios em um intervalo)\n");

    do {
        opcao = lerInteiro("Escolha uma opcao (1 ou 2): ");
        if (opcao != 1 && opcao != 2) {
            printf("Opcao invalida!\n");
        }
    } while (opcao != 1 && opcao != 2);

    if (opcao == 1) {
        /* Preenchimento manual, elemento por elemento */
        int i, j;
        for (i = 0; i < m->linhas; i++) {
            for (j = 0; j < m->colunas; j++) {
                char msg[60];
                sprintf(msg, "Elemento [%d][%d]: ", i + 1, j + 1);
                m->dados[i][j] = lerDouble(msg);
            }
        }
    } else {
        /* Preenchimento automatico dentro de um intervalo definido pelo usuario */
        double min, max, amplitude;
        int i, j;

        do {
            min = lerDouble("Valor minimo do intervalo: ");
            max = lerDouble("Valor maximo do intervalo: ");
            if (max < min) {
                printf("O valor maximo deve ser maior ou igual ao minimo!\n");
            }
        } while (max < min);

        amplitude = max - min;

        for (i = 0; i < m->linhas; i++) {
            for (j = 0; j < m->colunas; j++) {
                /* gera valor real aleatorio dentro do intervalo [min, max] */
                double aleatorio = min + ((double) rand() / RAND_MAX) * amplitude;
                m->dados[i][j] = aleatorio;
            }
        }
        printf("Matriz %s preenchida automaticamente!\n", nome);
    }

    m->cadastrada = 1;
    printf("Matriz %s cadastrada com sucesso!\n", nome);
}

/* ------------------------------------------------------------
 * 4.2 Exibicao
 * Imprime a matriz de forma organizada e alinhada.
 * ------------------------------------------------------------ */
void exibirMatriz(Matriz m, const char *nome) {
    int i, j;

    if (!m.cadastrada) {
        printf("\nA matriz %s ainda nao foi cadastrada!\n", nome);
        return;
    }

    printf("\n--- Matriz %s (%dx%d) ---\n", nome, m.linhas, m.colunas);

    for (i = 0; i < m.linhas; i++) {
        for (j = 0; j < m.colunas; j++) {
            /* largura fixa para manter as colunas alinhadas */
            printf("%8.2f", m.dados[i][j]);
        }
        printf("\n");
    }
}

/* ------------------------------------------------------------
 * 4.5 Item opcional (bonus)
 * Funcoes que verificam propriedades de uma matriz: se e
 * quadrada, simetrica e/ou identidade. Sao usadas logo apos
 * cada operacao para analisar a matriz RESULTADO gerada.
 * ------------------------------------------------------------ */
int matrizQuadrada(Matriz m) {
    return (m.linhas == m.colunas);
}

int matrizSimetrica(Matriz m) {
    int i, j;

    /* so faz sentido falar em simetria se a matriz for quadrada */
    if (!matrizQuadrada(m)) {
        return 0;
    }

    for (i = 0; i < m.linhas; i++) {
        for (j = i + 1; j < m.colunas; j++) {
            double diferenca = m.dados[i][j] - m.dados[j][i];
            if (diferenca < 0) {
                diferenca = -diferenca; /* transforma em valor absoluto */
            }
            if (diferenca > EPSILON) {
                return 0;
            }
        }
    }
    return 1;
}

int matrizIdentidade(Matriz m) {
    int i, j;
    double esperado, diferenca;

    if (!matrizQuadrada(m)) {
        return 0;
    }

    for (i = 0; i < m.linhas; i++) {
        for (j = 0; j < m.colunas; j++) {
            /* na diagonal principal (i == j) o valor esperado e 1, fora dela e 0 */
            esperado = (i == j) ? 1.0 : 0.0;
            diferenca = m.dados[i][j] - esperado;
            if (diferenca < 0) {
                diferenca = -diferenca;
            }
            if (diferenca > EPSILON) {
                return 0;
            }
        }
    }
    return 1;
}

/* Imprime na tela se a matriz recebida e quadrada, simetrica e/ou identidade.
 * Quando a matriz nao e quadrada, simetria e identidade nao se aplicam. */
void verificarPropriedades(Matriz m, const char *nome) {
    if (!m.cadastrada) {
        printf("\nA matriz %s ainda nao foi cadastrada/gerada!\n", nome);
        return;
    }

    printf("\nPropriedades da matriz %s:\n", nome);

    if (matrizQuadrada(m)) {
        printf("- E quadrada?   Sim (%dx%d)\n", m.linhas, m.colunas);
        printf("- E simetrica?  %s\n", matrizSimetrica(m) ? "Sim" : "Nao");
        printf("- E identidade? %s\n", matrizIdentidade(m) ? "Sim" : "Nao");
    } else {
        printf("- E quadrada?   Nao (%dx%d)\n", m.linhas, m.colunas);
        printf("- E simetrica?  Nao se aplica (matriz nao quadrada)\n");
        printf("- E identidade? Nao se aplica (matriz nao quadrada)\n");
    }
}

/* ------------------------------------------------------------
 * 4.3 / 4.4 Soma de duas matrizes (A + B)
 * Verifica se as dimensoes sao iguais antes de operar.
 * ------------------------------------------------------------ */
void somarMatrizes(Matriz a, Matriz b, Matriz *ultimoResultado) {
    Matriz resultado;
    int i, j;

    if (!a.cadastrada || !b.cadastrada) {
        printf("\nCadastre as duas matrizes antes de somar!\n");
        return;
    }

    if (a.linhas != b.linhas || a.colunas != b.colunas) {
        printf("\nErro: as matrizes precisam ter as mesmas dimensoes para somar!\n");
        printf("Matriz A: %dx%d | Matriz B: %dx%d\n", a.linhas, a.colunas, b.linhas, b.colunas);
        return;
    }

    resultado.linhas = a.linhas;
    resultado.colunas = a.colunas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            resultado.dados[i][j] = a.dados[i][j] + b.dados[i][j];
        }
    }

    resultado.cadastrada = 1;
    exibirMatriz(resultado, "Resultado (A + B)");
    verificarPropriedades(resultado, "Resultado (A + B)"); /* bonus */

    /* guarda essa matriz na "Matriz Resultado" global, para que o usuario
     * possa exibi-la ou checar as propriedades dela de novo mais tarde,
     * sem precisar refazer a operacao (bonus: opcoes 10 e 11 do menu) */
    *ultimoResultado = resultado;
}

/* ------------------------------------------------------------
 * Subtracao de duas matrizes (A - B)
 * Mesma validacao de dimensoes que a soma.
 * ------------------------------------------------------------ */
void subtrairMatrizes(Matriz a, Matriz b, Matriz *ultimoResultado) {
    Matriz resultado;
    int i, j;

    if (!a.cadastrada || !b.cadastrada) {
        printf("\nCadastre as duas matrizes antes de subtrair!\n");
        return;
    }

    if (a.linhas != b.linhas || a.colunas != b.colunas) {
        printf("\nErro: as matrizes precisam ter as mesmas dimensoes para subtrair!\n");
        printf("Matriz A: %dx%d | Matriz B: %dx%d\n", a.linhas, a.colunas, b.linhas, b.colunas);
        return;
    }

    resultado.linhas = a.linhas;
    resultado.colunas = a.colunas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            resultado.dados[i][j] = a.dados[i][j] - b.dados[i][j];
        }
    }

    resultado.cadastrada = 1;
    exibirMatriz(resultado, "Resultado (A - B)");
    verificarPropriedades(resultado, "Resultado (A - B)"); /* bonus */

    /* guarda na "Matriz Resultado" global (bonus: opcoes 10 e 11 do menu) */
    *ultimoResultado = resultado;
}

/* ------------------------------------------------------------
 * Multiplicacao entre duas matrizes (A x B)
 * Verifica se colunas de A == linhas de B antes de operar.
 * ------------------------------------------------------------ */
void multiplicarMatrizes(Matriz a, Matriz b, Matriz *ultimoResultado) {
    Matriz resultado;
    int i, j, k;

    if (!a.cadastrada || !b.cadastrada) {
        printf("\nCadastre as duas matrizes antes de multiplicar!\n");
        return;
    }

    if (a.colunas != b.linhas) {
        printf("\nErro: para multiplicar A x B, o numero de colunas de A\n");
        printf("precisa ser igual ao numero de linhas de B!\n");
        printf("Matriz A: %dx%d | Matriz B: %dx%d\n", a.linhas, a.colunas, b.linhas, b.colunas);
        return;
    }

    resultado.linhas = a.linhas;
    resultado.colunas = b.colunas;

    for (i = 0; i < resultado.linhas; i++) {
        for (j = 0; j < resultado.colunas; j++) {
            double soma = 0;
            for (k = 0; k < a.colunas; k++) {
                soma += a.dados[i][k] * b.dados[k][j];
            }
            resultado.dados[i][j] = soma;
        }
    }

    resultado.cadastrada = 1;
    exibirMatriz(resultado, "Resultado (A x B)");
    verificarPropriedades(resultado, "Resultado (A x B)"); /* bonus */

    /* guarda na "Matriz Resultado" global (bonus: opcoes 10 e 11 do menu) */
    *ultimoResultado = resultado;
}

/* ------------------------------------------------------------
 * Multiplicacao da matriz A por um escalar.
 * ------------------------------------------------------------ */
void multiplicarPorEscalar(Matriz a, Matriz *ultimoResultado) {
    Matriz resultado;
    double escalar;
    int i, j;

    if (!a.cadastrada) {
        printf("\nCadastre a matriz A antes de multiplicar por escalar!\n");
        return;
    }

    escalar = lerDouble("Digite o valor do escalar: ");

    resultado.linhas = a.linhas;
    resultado.colunas = a.colunas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            resultado.dados[i][j] = a.dados[i][j] * escalar;
        }
    }

    resultado.cadastrada = 1;
    exibirMatriz(resultado, "Resultado (A x escalar)");
    verificarPropriedades(resultado, "Resultado (A x escalar)"); /* bonus */

    /* guarda na "Matriz Resultado" global (bonus: opcoes 10 e 11 do menu) */
    *ultimoResultado = resultado;
}

/* ------------------------------------------------------------
 * Transposta da matriz A.
 * ------------------------------------------------------------ */
void transporMatriz(Matriz a, Matriz *ultimoResultado) {
    Matriz resultado;
    int i, j;

    if (!a.cadastrada) {
        printf("\nCadastre a matriz A antes de transpor!\n");
        return;
    }

    resultado.linhas = a.colunas;
    resultado.colunas = a.linhas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            resultado.dados[j][i] = a.dados[i][j];
        }
    }

    resultado.cadastrada = 1;
    exibirMatriz(resultado, "Resultado (Transposta de A)");
    verificarPropriedades(resultado, "Resultado (Transposta de A)"); /* bonus */

    /* guarda na "Matriz Resultado" global (bonus: opcoes 10 e 11 do menu) */
    *ultimoResultado = resultado;
}

/* ------------------------------------------------------------
 * Funcao principal: exibe o menu e direciona para cada operacao.
 * O loop se repete ate o usuario escolher a opcao 0 (Sair).
 * ------------------------------------------------------------ */
int main(void) {
    Matriz A, B;
    Matriz Resultado; /* bonus: guarda a matriz gerada pela ultima operacao feita */
    int opcao;

    /* inicializa as matrizes como "nao cadastradas" */
    A.cadastrada = 0;
    B.cadastrada = 0;
    Resultado.cadastrada = 0;

    /* semente para geracao de numeros aleatorios (preenchimento automatico) */
    srand((unsigned int) time(NULL));

    do {
        printf("\n===== CALCULADORA DE MATRIZES =====\n");
        printf("1 - Cadastrar Matriz A\n");
        printf("2 - Cadastrar Matriz B\n");
        printf("3 - Exibir Matriz A\n");
        printf("4 - Exibir Matriz B\n");
        printf("5 - Somar A + B\n");
        printf("6 - Subtrair A - B\n");
        printf("7 - Multiplicar A x B\n");
        printf("8 - Multiplicar Matriz A por escalar\n");
        printf("9 - Transpor Matriz A\n");
        printf("10 - Exibir Matriz Resultado (ultima operacao)\n");   /* bonus */
        printf("11 - Verificar propriedades da Matriz Resultado\n");  /* bonus */
        printf("0 - Sair\n");

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarMatriz(&A, "A");
                break;
            case 2:
                cadastrarMatriz(&B, "B");
                break;
            case 3:
                exibirMatriz(A, "A");
                break;
            case 4:
                exibirMatriz(B, "B");
                break;
            case 5:
                /* o &Resultado passa o endereco da matriz para a funcao
                 * poder guardar o resultado dessa operacao nela (bonus) */
                somarMatrizes(A, B, &Resultado);
                break;
            case 6:
                subtrairMatrizes(A, B, &Resultado);
                break;
            case 7:
                multiplicarMatrizes(A, B, &Resultado);
                break;
            case 8:
                multiplicarPorEscalar(A, &Resultado);
                break;
            case 9:
                transporMatriz(A, &Resultado);
                break;
            case 10:
                /* bonus: mostra de novo a matriz da ultima operacao feita,
                 * sem precisar refazer a operacao */
                exibirMatriz(Resultado, "Resultado (ultima operacao)");
                break;
            case 11:
                /* bonus: verifica de novo as propriedades da matriz da
                 * ultima operacao feita (quadrada/simetrica/identidade) */
                verificarPropriedades(Resultado, "Resultado (ultima operacao)");
                break;
            case 0:
                printf("\nEncerrando o programa. Ate mais!\n");
                break;
            default:
                /* trata opcao invalida sem derrubar o programa */
                printf("\nOpcao invalida! Escolha um numero entre 0 e 11.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}