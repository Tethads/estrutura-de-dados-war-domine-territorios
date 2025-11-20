#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Estrutura que representa um território
typedef struct {
char nome[MAX_NOME];
char cor[MAX_COR];
int tropas;
} Territorio;

// Função para cadastrar territórios dinamicamente
Territorio* cadastrarTerritorios(int qtd) {
Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
if (!mapa) {
printf("Erro ao alocar memoria.\n");
exit(1);
}

for (int i = 0; i < qtd; i++) {
    printf("Cadastro do Territorio %d\n", i + 1);
    printf("Nome: ");
    scanf(" %29[^\n]", mapa[i].nome); // lê até 29 caracteres ou espaço
    printf("Cor do Exército: ");
    scanf(" %9s", mapa[i].cor);
    printf("Número de Tropas: ");
    scanf("%d", &mapa[i].tropas);
    printf("\n");
}
return mapa;
}

// Função para exibir o mapa de territórios
void exibirMapa(Territorio* mapa, int qtd) {
printf("===== MAPA DE TERRITORIOS =====\n");
for (int i = 0; i < qtd; i++) {
printf("Territorio %d:\n", i + 1);
printf(" Nome: %s\n", mapa[i].nome);
printf(" Cor: %s\n", mapa[i].cor);
printf(" Tropas: %d\n\n", mapa[i].tropas);
}
}

// Função que simula ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
int dadoAtacante = rand() % 6 + 1; // 1 a 6
int dadoDefensor = rand() % 6 + 1; // 1 a 6

printf("%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

if (dadoAtacante > dadoDefensor) {
    printf("Ataque bem sucedido! %s agora pertence a %s\n", defensor->nome, atacante->cor);
    defensor->tropas = atacante->tropas / 2;
    strcpy(defensor->cor, atacante->cor);
} else {
    printf("Ataque falhou! %s perde 1 tropa.\n", atacante->nome);
    if (atacante->tropas > 0) atacante->tropas--;
}
printf("\n");
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* mapa) {
free(mapa);
}

// Função para atribuir missão a um jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
int indice = rand() % totalMissoes;
strcpy(destino, missoes[indice]);
}

// Função inicial simples para verificar missão (exemplo)
int verificarMissao(char* missao, Territorio* mapa, int qtd) {
// Aqui você pode implementar lógica real de verificação
// Por enquanto, retorna 0 (não cumprida)
return 0;
}

int main() {
srand(time(NULL));

int numTerritorios;
printf("Digite o número de territórios a cadastrar: ");
scanf("%d", &numTerritorios);

// Cadastro de territórios
Territorio* mapa = cadastrarTerritorios(numTerritorios);

// Exibição inicial
exibirMapa(mapa, numTerritorios);

// Vetor de missões pré-definidas
char* missoes[] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar todos os territórios de um continente",
    "Acumular 10 tropas em um territorio",
    "Vencer dois ataques consecutivos"
};
int totalMissoes = 5;

// Atribuição de missão a um jogador
char* missaoJogador = (char*) malloc(MAX_NOME * sizeof(char));
atribuirMissao(missaoJogador, missoes, totalMissoes);
printf("Missao do jogador: %s\n\n", missaoJogador);

// Simulação de ataque (exemplo: jogador ataca primeiro território contra segundo)
if (numTerritorios > 1) {
    atacar(&mapa[0], &mapa[1]);
    exibirMapa(mapa, numTerritorios);
}

// Verificação de missão (exemplo)
if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
    printf("Missao cumprida!\n");
} else {
    printf("Missao ainda nao cumprida.\n");
}

// Liberar memória
free(missaoJogador);
liberarMemoria(mapa);

return 0;
}
