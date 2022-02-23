#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "ferramentas.h"
#include "funcoesiniciais.h"
#include "funcoesavancadas.h"


int main(void) {
  
  char line[MAX_LINE];   // dados temporários
  char myId[ID_SIZE];    // identificador do bot em questão

  Carta descarte;
  Listcards lixo;
  lixo.tam = 0;
  Listjogos games;
  games.tam1 = 0;
  
  for(int i = 0; i < 50; i++) {
    games.jogos[i].tam = 0;
  }

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

                         // DADOS DO INÍCIO DA PARTIDA
  readline(line);        // lê os identificadores dos jogadores
  readline(line);        // lê o identificador do bot (seu id)
  strncpy(myId, line, ID_SIZE);
	fprintf(stderr, "My ID::%s\n", myId); // guarda para uso futuro
  readline(line);        // lê as cartas que o bot tem na mão
  fprintf(stderr, "My Hand::%s\n", line);
	Listcards mycard;
  mycard.tam=0;
	nossa_mao(line, &mycard);
  
	readline(line);        // lê a carta inicial da pilha de descarte.
	char* card3 = strtok(line,"DISCARD p1 p2 G");
	descarte = string2carta(card3);
  lixo.cards[lixo.tam] = string2carta(card3);
  lixo.tam++;
      
  
  while(1) {              // DADOS DURANTE A PARTIDA
    do {    
			/*vez do adversario*/              // lê e descarta os dados até chegar sua vez
      readline(line);     // sai do laço quando for enviado seu id
      fprintf(stderr, "DEBUG::%s\n", line);  // exemplo de saída para debugar
      if(strstr(line, myId) != NULL ){
        //ordenacao(&mycard);
      }
      if(strncmp(line, "DISCARD",7) == 0 ){
        char* card2 = strtok(line,"DISCARD ");
        fprintf(stderr, " %s\n", card2);
        descarte = string2carta(card2);
        lixo.cards[lixo.tam] = string2carta(card2);
        lixo.tam++;
      }

    } while (strcmp(line, myId)); // sai do laço quando for a sua vez!
		/*sua vez*/
     
      ordenacao(&mycard);
      verificar(descarte, &mycard, &games);
      ordenacao(&mycard);
      while(acrescentar_jogos(&mycard, &games) == 0){
        acrescentar_jogos(&mycard, &games);
      }
      baixar_jogos(&mycard, &games);
      escolher_descarte(&mycard,&lixo);

      //printHandCards_s(mycard);
      //printHandCards_s(lixo);
  }
  return 0;
  
}