#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H

typedef enum {
    Zero,Um,Dois,Tres,Quatro,Cinco,Seis,Sete,Oito,Nove,Dez,valete,rainha,rei,as
} numero;

typedef enum {
    espadas,paus,ouros,copas
} naipe;

typedef struct card{
	char valor[5];
  numero numero;
  naipe naipe;
} Carta; 

typedef struct mem{
  Carta cards[104]; 
  int tam;
} Listcards;

typedef struct visao{
  Listcards jogos[50];
  int tam1;
} Listjogos;

void readline(char *line);
Carta string2carta(char *carta_str);
void ordenacao(Listcards* hand);
void remover_carta(Listcards* hand, numero carta, naipe carta1);
void nossa_mao(char *line,  Listcards* hand);
void printHandCards_s(Listcards hand);
int tem_coringa(Listcards* hand);

#endif