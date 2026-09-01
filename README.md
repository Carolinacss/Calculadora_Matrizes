# Calculadora de Matrizes — Trabalho Prático

Disciplina: Álgebra Linear // Desenvolvimento de Software Multiplataforma
Fatec Osasco — Prof. Dr. Eduardo — 1º Exercício Programa

## Funcionalidades

- Cadastro de matrizes com preenchimento **manual** (elemento por elemento)
  ou **automático** (valores aleatórios dentro de um intervalo definido pelo
  usuário).
- Exibição organizada e alinhada das matrizes no console.
- Soma de duas matrizes (A + B).
- Subtração de duas matrizes (A − B).
- Multiplicação de uma matriz por um escalar.
- Transposta de uma matriz.
- Multiplicação entre duas matrizes (A × B).
- Tratamento de erros: dimensões incompatíveis e entradas inválidas não
  derrubam o programa (sem crash).
- **Item opcional (bônus):** a cada operação realizada (soma, subtração,
  multiplicação por escalar, transposta ou multiplicação entre matrizes), o
  programa verifica se a **matriz resultado** é **quadrada**, **simétrica**
  e/ou **identidade**.

## Estrutura do repositório

```
.
├── README.md                # este arquivo
├── Relatorio_Calculadora.pdf # relatório do trabalho (decisões, dificuldades, itens opcionais)
└── calculadora_matrizes.c   # código-fonte completo, comentado
```

## Como compilar e executar (OnlineGDB)

1. Acesse [onlinegdb.com](https://www.onlinegdb.com/) e clique em **New Project** (ou **Online C Compiler**).
2. Selecione a linguagem **C**.
3. Apague o conteúdo padrão e cole o código de `calculadora_matrizes.c`.
4. Clique em **Run** para compilar e executar.
5. Digite as entradas solicitadas diretamente no console de execução, na
   parte inferior da tela (número de linhas/colunas, elementos das matrizes,
   opções do menu, etc.).

## Como usar

Ao rodar o programa, o menu abaixo é exibido e se repete até a opção `0`:

```
===== CALCULADORA DE MATRIZES =====
1  - Cadastrar Matriz A
2  - Cadastrar Matriz B
3  - Exibir Matriz A
4  - Exibir Matriz B
5  - Somar A + B
6  - Subtrair A - B
7  - Multiplicar A x B
8  - Multiplicar Matriz A por escalar
9  - Transpor Matriz A
10 - Exibir Matriz Resultado (ultima operacao)
11 - Verificar propriedades da Matriz Resultado (quadrada/simetrica/identidade) [BONUS]
0  - Sair
```

Fluxo básico sugerido:

1. Cadastre a Matriz A (opção 1) e a Matriz B (opção 2).
2. Exiba as matrizes cadastradas (opções 3 e 4) para conferir os valores.
3. Escolha a operação desejada (opções 5 a 9) — o resultado é exibido e suas
   propriedades já são verificadas automaticamente.
4. Use as opções 10 e 11 a qualquer momento para reexibir a última matriz
   resultado ou conferir novamente suas propriedades.
5. Escolha `0` para encerrar o programa.

## Observações técnicas

- O tamanho máximo de linhas/colunas é `10x10` (constante `MAX_DIM`,
  ajustável no início do código).
- Os elementos são armazenados como `double`, permitindo números decimais.
- Todas as leituras de teclado são validadas (`lerInteiro` / `lerDouble`);
  entradas não numéricas geram uma mensagem de erro e pedem a informação
  novamente, sem interromper o programa.
- A verificação de simetria e identidade usa uma pequena tolerância
  (`EPSILON = 0.0001`) na comparação de números decimais, para evitar falsos
  negativos causados por arredondamento.
- Quando a matriz resultado não é quadrada, os testes de simetria e
  identidade são exibidos como não aplicáveis (`N/A`).
