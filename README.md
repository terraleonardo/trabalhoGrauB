# Simulador de Combate por Turnos
Trabalho desenvolvido para a disciplina Algoritmos e Programação: Fundamentos.

## 👥 Integrantes do Grupo
- Grasieli Wiedthauger

- Leonardo Terra

- Rafael Medina

## 🚀 Como executar
Este programa foi feito em linguagem C e pode ser executado no OnlineGDB ou em um editor como o VS Code (com compilador instalado).

### No OnlineGDB:
1. Copie e cole o código no site
2. Clique em "Run"

### No seu computador (VS Code ou outro editor):
1. Compile o código: gcc main.c -o batalha
2. Execute: ./batalha (Linux/Mac) ou batalha.exe (Windows)

## 🎮 Sobre o Jogo
Simulação de batalha entre duas equipes de personagens com características únicas. Cada equipe possui 5 personagens (Guerreiro, Mago, Caçador, Paladino e Bárbaro) que se enfrentam em turnos aleatórios. O jogo inclui:

* Habilidades especiais únicas para cada classe

* Mecânicas de combate com chance de erro e falha na defesa

* Sistema de vida/ataque/defesa individual

* Regeneração para o Paladino

* Exibição do status das equipes após cada rodada

## ⚔️ Tabela de Atributos

| Personagem  | Ataque | Defesa | Vida | Habilidade Especial       | Ativação | Falha Ataque | Falha Defesa |
|-------------|--------|--------|------|---------------------------|----------|--------------|--------------|
| Guerreiro   | 20     | 10     | 100  | Dano Dobrado              | 20%      | 20%          | 20%          |
| Mago        | 30     | 5      | 100  | Ignora Defesa             | 25%      | 20%          | 20%          |
| Caçador     | 18     | 8      | 100  | Ataque Duplo              | 15%      | 20%          | 20%          |
| Paladino    | 15     | 12     | 100  | Regeneração               | 30%      | 20%          | 20%          |
| Bárbaro     | 25     | 6      | 100  | Ataque Certeiro           | 100%     | 0%           | 20%          |

## 📌 Observações
* O código está no arquivo main.c

* Não requer instalação de bibliotecas extras

* A aleatoriedade é garantida por srand(time(NULL))

* O jogo termina quando todos os membros de uma equipe são derrotados

## 📚 Referências

Documentação da linguagem C - DevDocs

Guia de estilo de código C - GNU
