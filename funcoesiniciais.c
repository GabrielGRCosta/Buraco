#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "ferramentas.h"
#include "funcoesiniciais.h"
#include "funcoesavancadas.h"


void escolher_descarte(Listcards* hand,Listcards* lixo){ 
  int a=0;
  int i;
  for(i = 0; i< hand->tam;i++){
    a+=1;
    if(hand->tam<2){
      printf("DISCARD %s\n", hand->cards[0].valor);
      lixo->cards[lixo->tam] = hand->cards[0];
      lixo->tam++; 
      remover_carta(hand, hand->cards[0].numero, hand->cards[0].naipe);
      return;
    }
    if(hand->cards[i].numero == 2 && i != hand->tam-1)
      continue;
    if( (i>0) && (hand->cards[i].numero == hand->cards[i-1].numero && hand->cards[i].naipe == hand->cards[i-1].naipe))
      break;
    if( (i<hand->tam-1) && (hand->cards[i].numero == hand->cards[i+1].numero && hand->cards[i].naipe == hand->cards[i+1].naipe))
      break;    
    if((hand->cards[i].numero == hand->cards[i+1].numero-1 || hand->cards[i].numero == hand->cards[i+1].numero+1) && (hand->cards[i].naipe == hand->cards[i+1].naipe ))  
      continue;
    if((i>0) && (hand->cards[i].numero == hand->cards[i-1].numero-1 || hand->cards[i].numero == hand->cards[i-1].numero+1) && (hand->cards[i].naipe == hand->cards[i-1].naipe ))
      continue;  
    if((hand->cards[i].numero == hand->cards[i+1].numero-2 || hand->cards[i].numero == hand->cards[i+1].numero+2) && (hand->cards[i].naipe == hand->cards[i+1].naipe))
      continue;    
    if( (i<hand->tam-1) && (hand->cards[i].numero == hand->cards[i-1].numero-2 || hand->cards[i].numero == hand->cards[i-1].numero+2) && (hand->cards[i].naipe == hand->cards[i-1].naipe))
      continue;
    break;
  }
  if(i<hand->tam){ 
    printf("DISCARD %s\n", hand->cards[i].valor);
    lixo->cards[lixo->tam] = hand->cards[0];
    lixo->tam++; 
    remover_carta(hand, hand->cards[i].numero, hand->cards[i].naipe);
    return;
  }  
  for(int davus = 0; davus < hand->tam;davus++){
    if(hand->cards[davus].numero != 2){
      printf("DISCARD %s\n", hand->cards[davus].valor);
      lixo->cards[lixo->tam] = hand->cards[0];
      lixo->tam++; 
      remover_carta(hand, hand->cards[davus].numero, hand->cards[davus].naipe);
      return;
    } else {
        printf("DISCARD %s\n", hand->cards[davus].valor);
        lixo->cards[lixo->tam] = hand->cards[0];
        lixo->tam++; 
        remover_carta(hand, hand->cards[davus].numero, hand->cards[davus].naipe);
        return;
      }
  }
}

void verificar(Carta descarte, Listcards* hand, Listjogos* games){
  char line[MAX_LINE];
  char card3[10];
  int m1,m2;
  

  for(int i=0;i< hand->tam;i++){
    if(descarte.naipe == hand->cards[i].naipe){
      if(descarte.numero == hand->cards[i].numero + 1){
        for(int j=0;j< hand->tam;j++){
          if(hand->cards[j].naipe == hand->cards[i].naipe){
            if(hand->cards[i].numero == hand->cards[j].numero + 1){
             printf("GET_DISCARD [ %s %s ]\n",hand->cards[i].valor ,hand->cards[j].valor);
             
             complemento_jogo(games, games->tam1, hand->cards[i].numero, hand->cards[i].naipe, hand->cards[i].valor);
             complemento_jogo(games,games->tam1, hand->cards[j].numero, hand->cards[j].naipe, hand->cards[j].valor);
             complemento_jogo(games,games->tam1, descarte.numero, descarte.naipe, descarte.valor);
             games->tam1++;


             readline(line);
             nossa_mao(line, hand);
             m1=hand->cards[j].numero;
             m2=hand->cards[j].naipe;
             remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
             remover_carta(hand,m1, m2);
             return;
            }
          }
        }
      }
    }
  }
 
  for(int i=0;i< hand->tam;i++){
    if(descarte.naipe == hand->cards[i].naipe){
      if(descarte.numero == hand->cards[i].numero - 1){
        for(int j=0;j< hand->tam;j++){
          if(hand->cards[j].naipe == hand->cards[i].naipe){
            if(hand->cards[i].numero == hand->cards[j].numero - 1){
              printf("GET_DISCARD [ %s %s ]\n",hand->cards[i].valor ,hand->cards[j].valor);

              
              complemento_jogo(games,games->tam1, hand->cards[i].numero, hand->cards[i].naipe, hand->cards[i].valor);
              complemento_jogo(games,games->tam1, hand->cards[j].numero, hand->cards[j].naipe, hand->cards[j].valor);
              complemento_jogo(games,games->tam1, descarte.numero, descarte.naipe, descarte.valor);
              games->tam1++;

              readline(line);
              nossa_mao(line, hand);
              m1=hand->cards[j].numero;
              m2=hand->cards[j].naipe;
              remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
              remover_carta(hand,m1, m2);
              return;
            }
          }
        }
      }
    }
  }

  for(int i=0;i< hand->tam;i++){
    if(descarte.naipe == hand->cards[i].naipe){
      if(descarte.numero == hand->cards[i].numero + 1){ 
        for(int j=0;j< hand->tam;j++){
          if(descarte.naipe == hand->cards[j].naipe){
            if(descarte.numero == hand->cards[j].numero - 1){
             printf("GET_DISCARD [ %s %s ]\n",hand->cards[i].valor ,hand->cards[j].valor);
             
              complemento_jogo(games,games->tam1, hand->cards[i].numero, hand->cards[i].naipe, hand->cards[i].valor);
              complemento_jogo(games,games->tam1, hand->cards[j].numero, hand->cards[j].naipe, hand->cards[j].valor);
              complemento_jogo(games,games->tam1, descarte.numero, descarte.naipe, descarte.valor);
              games->tam1++;
  
             readline(line);
             nossa_mao(line, hand);
             m1=hand->cards[j].numero;
             m2=hand->cards[j].naipe;
             remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
             remover_carta(hand,m1, m2);
             return;
            }
          }
        }
      }
    }
  }
  
  if(tem_coringa(hand) == 1){
    for(int i = 0; i < hand->tam; i++){
      if(descarte.naipe == hand->cards[i].naipe){ 
        if((descarte.numero == hand->cards[i].numero + 1 || descarte.numero == hand->cards[i].numero - 1) && (descarte.numero == hand->cards[i+1].numero + 2 || descarte.numero == hand->cards[i+1].numero - 2)){ 
          for(int j=0;j< hand->tam;j++){
            if(hand->cards[j].numero == 2){
              printf("GET_DISCARD [ %s %s ]\n",hand->cards[i].valor ,hand->cards[j].valor);

              complemento_jogo(games,games->tam1, hand->cards[i].numero, hand->cards[i].naipe, hand->cards[i].valor);
              complemento_jogo(games,games->tam1, hand->cards[j].numero, hand->cards[j].naipe, hand->cards[j].valor);
              complemento_jogo(games,games->tam1, descarte.numero, descarte.naipe, descarte.valor);
              games->tam1++;

              readline(line);
              nossa_mao(line, hand);
              m1=hand->cards[j].numero;
              m2=hand->cards[j].naipe;
              remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
              remover_carta(hand,m1, m2);
              return;
            }
          }
        }
      }
    }
  }

	printf("GET_STOCK\n");
	readline(card3);
	Carta aux = string2carta(card3);
	hand->cards[hand->tam] = aux;
  hand->tam++;
  
}