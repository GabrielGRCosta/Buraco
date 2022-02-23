#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "ferramentas.h"


void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

Carta string2carta(char *carta_str){
  Carta c;

  strcpy(c.valor,carta_str);
  if(strstr(carta_str,"♣") != NULL)
    c.naipe = paus;
  if(strstr(carta_str,"♠") != NULL)
    c.naipe = espadas;
  if(strstr(carta_str,"♥") != NULL)
    c.naipe = copas;
  if(strstr(carta_str,"♦") != NULL)
    c.naipe = ouros;

  c.numero = atoi(carta_str);
  if(c.numero == 0){ 
    if(carta_str[0] == 'A')
      c.numero = as;
    else if(carta_str[0] == 'J')
      c.numero = valete;
    else if(carta_str[0] == 'Q')
      c.numero = rainha;
    else if(carta_str[0] == 'K')
      c.numero = rei;
  }
  return c;
}

void ordenacao(Listcards* hand){
  int auxnumero, auxnaipe;
  char auxvalor[5];

  for(int i=0; i<hand->tam; i++){  
    for(int j=0; j<hand->tam; j++){
      if(hand->cards[i].numero < hand->cards[j].numero){
        auxnumero = hand->cards[i].numero;
        hand->cards[i].numero = hand->cards[j].numero;
        hand->cards[j].numero = auxnumero;
        auxnaipe = hand->cards[i].naipe;
        hand->cards[i].naipe = hand->cards[j].naipe;
        hand->cards[j].naipe = auxnaipe;
        strcpy(auxvalor, hand->cards[i].valor);
        strcpy(hand->cards[i].valor, hand->cards[j].valor);
        strcpy(hand->cards[j].valor, auxvalor);  
      }
      if(hand->cards[i].naipe < hand->cards[j].naipe){
        auxnumero = hand->cards[i].numero;
        hand->cards[i].numero = hand->cards[j].numero;
        hand->cards[j].numero = auxnumero;
        auxnaipe = hand->cards[i].naipe;
        hand->cards[i].naipe = hand->cards[j].naipe;
        hand->cards[j].naipe = auxnaipe;
        strcpy(auxvalor, hand->cards[i].valor);
        strcpy(hand->cards[i].valor, hand->cards[j].valor);
        strcpy(hand->cards[j].valor, auxvalor);  
      }         
    }
  }
}  

void remover_carta(Listcards* hand, numero carta, naipe carta1){
  for(int i=0; i<(hand->tam); i++){
    if(carta == hand->cards[i].numero && carta1 == hand->cards[i].naipe){
      for(int j=i; j<(hand->tam+1); j++){
        hand->cards[j] = hand->cards[j+1];
      }
      break;
    }
  }

  (hand->tam)--;
}


void nossa_mao(char *line,  Listcards* hand){
  char *card = strtok(line,"[] ");
  

  int cont = hand->tam;
  while(card != NULL){
    if(card == NULL) 
      break;  
    hand->cards[cont]=string2carta(card);
    card = strtok(NULL, "[] ");
    cont++;
  }  
  hand->tam = cont ;
  
}  

void printHandCards_s(Listcards hand){
	for(int i=0; i<hand.tam ; i++){
		fprintf(stderr, "%s ", hand.cards[i].valor);
  }
}


int tem_coringa(Listcards* hand){
  for(int k = 0; k < hand->tam; k++){
    if(hand->cards[k].numero == 2){
      return 1;
    }
  }
  return 0;
} 