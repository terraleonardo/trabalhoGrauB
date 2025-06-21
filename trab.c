#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int rodadaGlobal = 1;

int randomInt(int min, int max) { // Definindo função random
    return min + rand() % (max - min + 1);
}

typedef struct { // Definindo struct Personagem
    char classe[16];
    int vida;
    int ataque;
    int defesa;
    bool habilidade_ativa;
} Personagem;

typedef struct {
    Personagem equipe[5];
} Equipe;

Personagem personagem(char classe[16], int ataque, int defesa) { // Definindo construtor de Personagem
    Personagem p;
    strcpy(p.classe, classe);
    p.ataque = ataque;
    p.defesa = defesa;
    p.vida = 100;
    p.habilidade_ativa = false;
    return p;
}

void inicializaEquipe(Personagem equipe[]) { // Definindo inicializador de equipe
    equipe[0] = personagem("Guerreiro", 20, 10);
    equipe[1] = personagem("Mago", 30, 5);
    equipe[2] = personagem("Cacador", 18, 8);
    equipe[3] = personagem("Paladino", 15, 12);
    equipe[4] = personagem("Barbaro", 25, 6);
}

int sorteiaPrimeiro() {
    return randomInt(1, 2);
}

bool timeVivo(Personagem equipe[]) {   //Testando se o o time está vivo
    for (int i = 0; i < 5; i++) {
        if (equipe[i].vida > 0)
            return true;
    }
    return false;
}

int selecionaAtacante(Personagem equipe[]) {
    int personagensVivos[5];
    int numVivos = 0;
    
    // Conta quantos personagens estão vivos
    for (int i = 0; i < 5; i++) {
        if (equipe[i].vida > 0) {
            personagensVivos[numVivos] = i;
            numVivos++;
        }
    }
    
    // Seleciona aleatoriamente entre os vivos
    if (numVivos > 0) {
        int indexAleatorio = randomInt(0, numVivos - 1);
        return personagensVivos[indexAleatorio];
    }
    
    return -1;
}

int selecionaAlvo() {
    int idSelecionado = randomInt(0,4);
    return idSelecionado;
}

bool verificarErroAtaque() {     //verifica chance 20% erro ataque
    int chance = randomInt(0,100);
    if (chance <= 20) return true;
    return false;
}

bool verificarFalhaDefesa() {     //verifica chance 20% falha defesa
    int chance = randomInt(0,100);
    if (chance <= 20) return true;
    return false;
}

void chanceHabilidadeAtacante(Personagem *atacante, int idxAtacante) {
    int chance = randomInt(0,100);

    switch (idxAtacante) {
        case 0:     //guerreiro - somente ataque
            if (chance <= 20) atacante->habilidade_ativa = true;
            break;
        case 1:     //mago - somente ataque
            if (chance > 20 && chance <=45) atacante->habilidade_ativa = true;
            break;
        case 2:     //caçador - somente ataque
            if (chance > 45 && chance <=60) atacante->habilidade_ativa = true;
            break;
        case 3:     //paladino - não tem habilidade ao atacar
            atacante->habilidade_ativa = false;
            break;
        case 4:     //barbaro - somente ataque
            atacante->habilidade_ativa = true;
            break;
        default:
            break;
    }
}

void aplicarHabilidadeEspecialAtacante(Personagem *atacante, Personagem *defensor, int idxAtacante, int idxAlvo) {
    int dano = 0;
    int vidaAntesDoAtaque = defensor->vida; // Guarda a vida antes do ataque

    switch (idxAtacante) {
        case 0:     //guerreiro - dano dobrado
            dano = 2 * (atacante->ataque - defensor->defesa);
            if (dano < 0) dano = 0;
            defensor->vida -= dano;
            if (defensor->vida < 0) defensor->vida = 0;
            break;

        case 1:     //mago - ignora defesa
            dano = atacante->ataque;
            if (dano < 0) dano = 0;
            defensor->vida -= dano;
            if (defensor->vida < 0) defensor->vida = 0;
            break;

        case 2:     //caçador - ataca duas vezes
            dano = atacante->ataque - defensor->defesa;
            if (dano < 0) dano = 0;
            defensor->vida -= dano;

            dano = atacante->ataque - defensor->defesa;
            if (dano < 0) dano = 0;
            defensor->vida -= dano;
            if (defensor->vida < 0) defensor->vida = 0;
            break;

        case 3:     // paladino - apenas ataque normal (sem regeneração)
            dano = atacante->ataque - defensor->defesa;
            if (dano < 0) dano = 0;
            defensor->vida -= dano;
            if (defensor->vida < 0) defensor->vida = 0;
            break;

        case 4:     //barbaro - somente ataque
            dano = atacante->ataque - defensor->defesa;
            if (dano < 0) dano = 0;
            defensor->vida -= dano;
            if (defensor->vida < 0) defensor->vida = 0;
            break;

        default:
            break;
    }

    printf("\n→ Dano aplicado: %d", vidaAntesDoAtaque - defensor->vida);
    printf("\n→ %s agora com [%d/100] de vida", defensor->classe, defensor->vida);

    // Verifica se o defensor é um Paladino e se ele ainda está vivo após o ataque
    if (strcmp(defensor->classe, "Paladino") == 0 && defensor->vida > 0) {
        int chance = randomInt(0, 100);
        if (chance <= 30) { // 30% de chance de ativar a regeneração
            int vida_regenerada = (100 - defensor->vida) * 0.2; // 20% de 100 (vida total)
            defensor->vida += vida_regenerada;
            if (defensor->vida > 100) defensor->vida = 100;
            printf("\n→ Habilidade especial do Paladino ativada: regeneração");
            printf("\n→ Paladino regenerou %d de vida! Vida atual: %d",
                    vida_regenerada, defensor->vida);
        }
    }
}

void mostrarStatusEquipes(Personagem equipe1[], Personagem equipe2[]) {
    printf("\n\n==========Estado atual==========");
    printf("\nTime 1:");
    for(int i = 0; i < 5; i++) {
        printf("\n%s (%d/100)", equipe1[i].classe, equipe1[i].vida);
    }
    printf("\n\nTime 2:");
    for(int i = 0; i < 5; i++) {
        printf("\n%s (%d/100)", equipe2[i].classe, equipe2[i].vida);
    }
    printf("\n================================");
}

void ataque(Personagem *atacante, Personagem *defensor, int idxAtacante, int numTimeAtacante){
    printf("\n\n>>> Rodada %d: ", rodadaGlobal); // Variável 'rodadaGlobal' definida no começo do arquivo

    printf("\nTime %d - %s (%d/100) ataca %s do Time %d (%d/100)",
            numTimeAtacante, atacante->classe, atacante->vida,
            defensor->classe, (numTimeAtacante == 1) ? 2 : 1, defensor->vida);

    int chanceErroAtaque = verificarErroAtaque();
    int chanceFalhaDefesa = verificarFalhaDefesa();

    if (idxAtacante == 4) { // Bárbaro (idx=4) ignora falha no ataque
        chanceErroAtaque = 0; // força ataque sem erro
    }

    chanceHabilidadeAtacante(atacante, idxAtacante);        //testa se a habilidade especial vai ser ativada do atacante

    if (chanceErroAtaque) {
        printf("\n→ Ataque errou! Nenhum dano aplicado.");
        return;
    }

    if (atacante->habilidade_ativa && !chanceErroAtaque) {
        printf("\n→ Ataque bem sucedido!");
        
        int vidaAntes = defensor->vida;

        aplicarHabilidadeEspecialAtacante(atacante, defensor, idxAtacante, idxAtacante);    //o ataque sera nessa funcao caso tenha habilidade especial
        printf("\n→ Habilidade especial do %s ativada: ", atacante->classe);

        switch (idxAtacante) {
            case 0: printf("dano dobrado"); break;
            case 1: printf("ignorar defesa"); break;
            case 2: printf("ataque duplo"); break;
            case 3: printf("regeneração"); break;
            case 4: printf("ataque certeiro"); break;
        }

    } else if (!chanceErroAtaque){     // o ataque sera normalmente caso nao tenha habilidade especial
        printf("\nAtaque bem sucedido! ");

        int vidaAntes = defensor->vida;

        int dano;
        if(chanceFalhaDefesa) { // Verifica falha defesa
            dano = atacante->ataque;
            printf("%s falhou na defesa! ", defensor->classe);
        } else {
            dano = atacante->ataque - defensor->defesa;
        }
        if (dano < 0) dano = 0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida = 0; 
        
        printf("\n→ Dano aplicado: %d", dano);
        printf("\n→ %s agora com [%d/100] de vida", defensor->classe, defensor->vida);
    }

    atacante->habilidade_ativa = false;     // Reseta habilidade ativa
}

int main() {
    srand(time(NULL)); // Inicializando seed da função random

    #define TAMANHO_EQUIPE 5

    Personagem equipe1[TAMANHO_EQUIPE];
    Personagem equipe2[TAMANHO_EQUIPE];

    int rodada = 1;

    inicializaEquipe(equipe1);
    inicializaEquipe(equipe2);

    int timeAtacante = sorteiaPrimeiro(); // Flag que alterna a cada jogada de um dos lados para exibir qual time está atacando.

    while (timeVivo(equipe1) && timeVivo(equipe2)) {    //enquanto as duas equipes estiverem vivas
        if (timeAtacante == 1) {
            int idxAtacante = selecionaAtacante(equipe1);
            int idxAlvo = selecionaAlvo();

            while (equipe2[idxAlvo].vida <= 0) {
                idxAlvo = selecionaAlvo();
            }

            ataque(&equipe1[idxAtacante], &equipe2[idxAlvo], idxAtacante, 1);
        } else {
            int idxAtacante = selecionaAtacante(equipe2);
            int idxAlvo = selecionaAlvo();

            while (equipe1[idxAlvo].vida <= 0) {
                idxAlvo = selecionaAlvo();
            }
            
            ataque(&equipe2[idxAtacante], &equipe1[idxAlvo], idxAtacante, 2);
        }

        mostrarStatusEquipes(equipe1, equipe2);

        timeAtacante = (timeAtacante == 1) ? 2 : 1; // Alterna o time atacante para a próxima rodada
        rodadaGlobal++;

        printf("\nPressione [Enter] para continuar...");
        while (getchar() != '\n'); // Limpa o buffer e espera pelo Enter
    }

    if (timeVivo(equipe1)) { // Mostrar resultado final
        printf("\n=== TIME 1 VENCEU A BATALHA! ===\n");
    } else {
        printf("\n=== TIME 2 VENCEU A BATALHA! ===\n");
    }

    return 0;
}