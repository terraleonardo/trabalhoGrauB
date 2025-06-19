#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

int selecionaAtacante(Personagem equipe[]){
    int idSelecionado = -1;
    float maiorRazao = -1;
    for (int i = 0; i < 5; i++) {
        if (equipe[i].vida >0){
            float razao = (float)equipe[i].vida / equipe[i].ataque;
            if (razao > maiorRazao){
                maiorRazao = razao;
                idSelecionado = i;
            }
        }
    }
    return idSelecionado;
}

int selecionaAlvo(){
    int idSelecionado = randomInt(0,4);
    return idSelecionado;
}

bool verificarErroAtaque(){     //verifica chance 20% erro ataque
    int chance = randomInt(0,100);
    if (chance <= 20) return true;
    return false;
}

bool verificarFalhaDefesa(){     //verifica chance 20% falha defesa
    int chance = randomInt(0,100);
    if (chance <= 20) return true;
    return false;
}

void chanceHabilidadeAtacante(Personagem *atacante, int idxAtacante){
    int chance = randomInt(0,100);
    switch (idxAtacante)
    {
    case 0:     //guerreiro - somente ataque
        if (chance <= 20) {
            atacante->habilidade_ativa = 1;
        }
        break;
    case 1:     //mago - somente ataque
        if (chance > 20 && chance <=45) {
            atacante->habilidade_ativa = 1;
        }
        break;
    case 2:     //caçador - somente ataque
        if (chance > 45 && chance <=60) {
            atacante->habilidade_ativa = 1;
        }
        break;
    case 3:     //paladino - somente defesa
        atacante->habilidade_ativa = 0;
        break;
    case 4:     //barbaro - somente ataque
        atacante->habilidade_ativa = 1;
        break;
    

    default:
        break;
    }
}

void aplicarHabilidadeEspecialAtacante(Personagem *atacante, Personagem *defensor, int idxAtacante, int idxAlvo){
    int dano =0;
    switch (idxAtacante) {
    case 0:     //guerreiro - dano dobrado
        dano = 2*(atacante->ataque  - defensor->defesa);
        if (dano <0) dano =0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida =0;
        break;

    case 1:     //mago - ignora defesa
        dano = atacante->ataque;
        if (dano <0) dano =0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida =0;
        break;

    case 2:     //caçador - ataca duas vezes
        dano = atacante->ataque  - defensor->defesa;
        if (dano <0) dano =0;
        defensor->vida -= dano;
        dano = atacante->ataque  - defensor->defesa;
        if (dano <0) dano =0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida =0;
        break;

    case 3:     // paladino - ataque normal + chance de regeneração
        dano = atacante->ataque - defensor->defesa;
        if (dano < 0) dano = 0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida = 0;

        printf("%s atacou %s causando %d de dano. Vida restante do defensor: %d\n",
            atacante->classe, defensor->classe, dano, defensor->vida);


        if (defensor->vida > 0) { // Paladino sobrevive, então a habilidade é testada
            int chance = randomInt(0, 100);
            if (chance < 30) {
                int vida_perdida = 100 - defensor->vida;
                int vida_regenerada = vida_perdida * 20 / 100;
                defensor->vida += vida_regenerada;
                if (defensor->vida > 100)
                    defensor->vida = 100;
                printf("%s regenerou %d de vida! Vida atual: %d\n",
                        defensor->classe, vida_regenerada, defensor->vida);
            }
        break;
    }
    case 4:     //barbaro - somente ataque
        dano = atacante->ataque  - defensor->defesa;
        if (dano <0) dano =0;
        defensor->vida -= dano;
        break;

    default:
        break;
    }
}

void ataque(Personagem *atacante, Personagem *defensor, int idxAtacante, int idxAlvo){
    int chanceErroAtaque = verificarErroAtaque();
    if (idxAtacante == 4) { // Bárbaro ignora falha no ataque
        chanceErroAtaque = 0; // força ataque sem erro
    }
    chanceHabilidadeAtacante(atacante, idxAtacante);        //testa se a habilidade especial vai ser ativada do atacante

    if (atacante->habilidade_ativa && !chanceErroAtaque) {
        aplicarHabilidadeEspecialAtacante(atacante, defensor, idxAtacante, idxAlvo);    //o ataque sera nessa funcao caso tenha habilidade especial
        

    } else if (!chanceErroAtaque){     // o ataque sera normalmente caso nao tenha habilidade especial
        int dano = atacante->ataque  - defensor->defesa;
        if (dano <0) dano =0;
        defensor->vida -= dano;
        if (defensor->vida < 0) defensor->vida =0;
         printf("%s atacou %s causando %d de dano. Vida restante do defensor: %d\n",
           atacante->classe, defensor->classe, dano, defensor->vida);
    }

    

    //aplicar a funcao de zerar habilidade especial no final do ataque
}

int main() {
    srand(time(NULL)); // Inicializando seed da função random

    #define TAMANHO_EQUIPE 5

    Personagem equipe1[TAMANHO_EQUIPE];
    Personagem equipe2[TAMANHO_EQUIPE];

    inicializaEquipe(equipe1);
    inicializaEquipe(equipe2);

    int timeAtacante = sorteiaPrimeiro(); // Flag que alterna a cada jogada de um dos lados para exibir qual time está atacando.

    while (timeVivo(equipe1) && timeVivo(equipe2)) {    //enquanto as duas equipes estiverem vivas
         Personagem *timeAtual = (timeAtacante == 1) ? equipe1 : equipe2;
        Personagem *timeInimigo = (timeAtacante == 1) ? equipe2 : equipe1;

        int idxAtacante = selecionaAtacante(timeAtual);
        int idxAlvo = selecionaAlvo();
        ataque(&timeAtual[idxAtacante], &timeInimigo[idxAlvo], idxAtacante, idxAlvo);
    }

    /*
    Grasi: falta fazer logica da habilidade do barbaro + logica da chance de falha da defesa 
    Grasi: falta fazer logica da habilidade do barbaro + logica da chance de falha da defesa
    */


    //for(int i = 0;) {
    //}
    /* for(int i=0; i<TAMANHO_EQUIPE; i++) { // TESTANDO SE TODAS AS CLASSES FORAM CRIADAS
        printf("\n%s\nHP:%d ATK:%d DEF:%d HAB_BOOL:%d\n", equipe1[i].classe, equipe1[i].vida, equipe1[i].ataque, equipe1[i].defesa, equipe1[i].habilidade_ativa);
    }
    printf("\n"); */
    return 0;
}