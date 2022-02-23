#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "ferramentas.h"
#include "funcoesiniciais.h"
#include "funcoesavancadas.h"


void complemento_jogo(Listjogos* games, int posicao, numero carta_numero, naipe carta_naipe, char* carta_valor){
  games->jogos[posicao].cards[games->jogos[posicao].tam].numero = carta_numero;
  games->jogos[posicao].cards[games->jogos[posicao].tam].naipe = carta_naipe;
  strcpy(games->jogos[posicao].cards[games->jogos[posicao].tam].valor,carta_valor);
  games->jogos[posicao].tam++;
}

void baixar_jogos(Listcards *hand,Listjogos* games){
  char p1[10];
  char p2[10];
  char p3[10];
  int a,b,c,d;
  for(int i=0;i<hand->tam;i++){ 
    for(int j=i + 1;j< hand->tam;j++){
      if((hand->cards[i].naipe == hand->cards[j].naipe) && ( hand->cards[j].naipe == hand->cards[j+1].naipe)){
        if((hand->cards[i].numero == hand->cards[j].numero - 1) && (hand->cards[j].numero - 1 == hand->cards[j+1].numero-2)){ 
          a = hand->cards[j].numero;
          b = hand->cards[j].naipe;
          c = hand->cards[j+1].numero;
          d = hand->cards[j+1].naipe;
          strcpy(p1, hand->cards[i].valor);
          strcpy(p2, hand->cards[j].valor);
          strcpy(p3, hand->cards[j + 1].valor);
          complemento_jogo(games,games->tam1, hand->cards[i].numero , hand->cards[i].naipe, hand->cards[i].valor);
          complemento_jogo(games,games->tam1, hand->cards[j].numero , hand->cards[j].naipe, hand->cards[j].valor);
          complemento_jogo(games,games->tam1, hand->cards[j+1].numero , hand->cards[j+1].naipe, hand->cards[j+1].valor);
          games->tam1++;
          printf("MELD_NEW [ %s %s %s ]\n",p1, p2,p3);
          remover_carta(hand, hand->cards[i].numero, hand->cards[i].naipe);
          remover_carta(hand, a, b);
          remover_carta(hand, c, d);
          return;
        }
      }
    }
  }
}

int acrescentar_jogos(Listcards *hand,Listjogos* games){
  for(int i=0;i < games->tam1;i++){
    ordenacao(&games->jogos[i]);
  }
  for(int a = 0; a < hand->tam; a++){
    for(int i=0;i<games->tam1;i++){
      if(games->jogos[i].cards[0].numero != 2){
        if(hand->cards[a].naipe == games->jogos[i].cards[0].naipe){
          if(hand->cards[a].numero == games->jogos[i].cards[0].numero - 1 || hand->cards[a].numero == games->jogos[i].cards[games->jogos[i].tam].numero + 1){
            printf("MELD_JOIN %d [ %s ]\n",i,hand->cards[a].valor);
            complemento_jogo(games, i , hand->cards[a].numero, hand->cards[a].naipe, hand->cards[a].valor);
            remover_carta(hand, hand->cards[a].numero, hand->cards[a].naipe);
            return 0;
          }
        }
      }
      else if(hand->cards[a].naipe == games->jogos[i].cards[games->jogos[i].tam].naipe){
          if((hand->cards[a].numero == games->jogos[i].cards[0].numero - 1 && hand->cards[a].numero==games->jogos[i].cards[1].numero-2 ) || (hand->cards[a].numero == games->jogos[i].cards[games->jogos[i].tam].numero + 1 && hand->cards[a].numero == games->jogos[i].cards[games->jogos[i].tam].numero+2)){
          printf("MELD_JOIN %d [ %s ]\n",i,hand->cards[a].valor);
            complemento_jogo(games, i , hand->cards[a].numero, hand->cards[a].naipe, hand->cards[a].valor);
            remover_carta(hand, hand->cards[a].numero, hand->cards[a].naipe);
            return 0;
        }
      }
    }
  }
  return 1;
}