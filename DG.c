
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Tamanho máximo de uma linha da entrada-padrão */
#define MAX_LINE 200
#define MAX_GROUP 52
/** Tamanho máximo do identificador do bot */
#define ID_SIZE 10
#define G(A) fprintf(stderr, A "\n");

/**
 * Lê uma linha da entrada padrão e remove o '\n' se necessário.
 * @param line string a ser alterada com o conteúdo da entrada-padrão.
 */
void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

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

void printHandCards_s(Listcards hand);

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
  if(c.numero == 0){ //as, valete, rainha ou rei
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
    //fprintf(stderr,"Carta pega: %s\n",card);
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
  //fprintf(stderr, " ola amigo: %d ", hand.tam);
}




int tem_coringa(Listcards* hand){
  for(int k = 0; k < hand->tam; k++){
    if(hand->cards[k].numero == 2){
      return 1;
    }
  }
  return 0;
} 

void escolher_descarte(Listcards* hand,Listcards* lixo){ 
  char descarte[5];
  int a=0,b=0;
  int i;
  for(i = 0; i< hand->tam;i++){
    a+=1;
    if(hand->tam<2){
      printf("DISCARD %s\n", hand->cards[0].valor);
      lixo->cards[lixo->tam] = hand->cards[0];
      lixo->tam++; 
      printHandCards_s(*lixo);
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
    fprintf(stderr, "LIXO:");
    printHandCards_s(*lixo);
    remover_carta(hand, hand->cards[i].numero, hand->cards[i].naipe);
    return;
  }  
  for(int davus = 0; davus < hand->tam;davus++){
    if(hand->cards[davus].numero != 2){
      //fprintf(stderr,"HELLLO ITS ME1: %d", hand->tam);
      printf("DISCARD %s\n", hand->cards[davus].valor);
      lixo->cards[lixo->tam] = hand->cards[0];
      lixo->tam++; 
      fprintf(stderr, "LIXO:");
      printHandCards_s(*lixo);
      remover_carta(hand, hand->cards[davus].numero, hand->cards[davus].naipe);
      return;
    } else {
        printf("DISCARD %s\n", hand->cards[davus].valor);
        lixo->cards[lixo->tam] = hand->cards[0];
        lixo->tam++; 
        fprintf(stderr, "LIXO:");
        printHandCards_s(*lixo);
        remover_carta(hand, hand->cards[davus].numero, hand->cards[davus].naipe);
        return;
      }
  }
}//ajeitar discard pra se sobrar só o 2 descartar o 2, ver se o meld join ta sendo feito o maximo possivel de vezes, ver se da pra fazer o A valendo 1., as vezes o meld new/meld join imprime cartas com naipe desconhecido, as vezes o discard bulga quando sobra so uma carta node buraco.js DG DG -d -seed 1213176201855283
// 3882354114075807

void complemento_jogo(Listjogos* games, int posicao, numero carta_numero, naipe carta_naipe, char* carta_valor){
  games->jogos[posicao].cards[games->jogos[posicao].tam].numero = carta_numero;
  games->jogos[posicao].cards[games->jogos[posicao].tam].naipe = carta_naipe;
  strcpy(games->jogos[posicao].cards[games->jogos[posicao].tam].valor,carta_valor);
  games->jogos[posicao].tam++;
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
             fprintf(stderr,"Linha:%s",line);
             nossa_mao(line, hand);
             //fprintf(stderr, "carta remove:%d %d", hand->cards[j].numero, hand->cards[j].naipe);
             m1=hand->cards[j].numero;
             m2=hand->cards[j].naipe;
             remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
             //fprintf(stderr, "carta remove:%d %d", m1 , m2);
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
              fprintf(stderr,"Linha:%s",line);
              nossa_mao(line, hand);
              //fprintf(stderr, "carta remove:%d %d", hand->cards[j].numero,hand->cards[j].naipe);
              m1=hand->cards[j].numero;
              m2=hand->cards[j].naipe;
              remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
              //fprintf(stderr, "carta remove:%d %d", m1, m2);
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
             fprintf(stderr,"Linha:%s",line);
             nossa_mao(line, hand);
             //fprintf(stderr, "carta remove:%d %d", hand->cards[j].numero, hand->cards[j].naipe);
             m1=hand->cards[j].numero;
             m2=hand->cards[j].naipe;
             remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
             //fprintf(stderr, "carta remove:%d %d", m1, m2);
             remover_carta(hand,m1, m2);
             return;
            }
          }
        }
      }
    }
  }//3espadas 2espadas ,3 2+1 ok
  
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
              fprintf(stderr,"Linha:%s",line);
              nossa_mao(line, hand);
              //fprintf(stderr, "carta remove:%d %d", hand->cards[j].numero,hand->cards[j].naipe);
              m1=hand->cards[j].numero;
              m2=hand->cards[j].naipe;
              remover_carta(hand,hand->cards[i].numero, hand->cards[i].naipe);
              //fprintf(stderr, "carta remove:%d %d", m1, m2);
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
	//gcc DG.c -o bot -fsanitize=address -g
	fprintf(stderr, "Carta recebida %s\n",aux.valor);
	hand->cards[hand->tam] = aux;
  hand->tam++;
  
}
//

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
          //fprintf(stderr, "rola: %s %s %s", p1,p2,p3);
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

void acrescentar_jogos(Listcards *hand,Listjogos* games){
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
            return;
          }
        }
      }
      else if(hand->cards[a].naipe == games->jogos[i].cards[games->jogos[i].tam].naipe){
          if((hand->cards[a].numero == games->jogos[i].cards[0].numero - 1 && hand->cards[a].numero==games->jogos[i].cards[1].numero-2 ) || (hand->cards[a].numero == games->jogos[i].cards[games->jogos[i].tam].numero + 1 && hand->cards[a].numero == games->jogos[i].cards[games->jogos[i].tam].numero+2)){
          printf("MELD_JOIN %d [ %s ]\n",i,hand->cards[a].valor);
            complemento_jogo(games, i , hand->cards[a].numero, hand->cards[a].naipe, hand->cards[a].valor);
            remover_carta(hand, hand->cards[a].numero, hand->cards[a].naipe);
            return;
        }
      }
    }
  }
}      
 //if((hand->cards[a].naipe == games->jogos[i].cards[0].naipe) || (hand->cards[a].naipe == games->jogos[i].cards[].naipe)) {
    //if((hand->cards[a].naipe == games->jogos[i].cards[0].naipe) ){ 
  //}


int main() {
  
  char line[MAX_LINE];   // dados temporários
  char myId[ID_SIZE];    // identificador do bot em questão
  int i = 0;
  Carta descarte;
  Carta cartaremove;
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
	//printHandCards_s(mycard);
  
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
        /*fprintf(stderr,"a carta do descarte é :%d %d\n",descarte.numero, descarte.naipe);*/
      }

    } while (strcmp(line, myId)); // sai do laço quando for a sua vez!
		/*sua vez*/
     
      ordenacao(&mycard);
      verificar(descarte, &mycard, &games);
      ordenacao(&mycard);
      fprintf(stderr, "nossa mão:\n");
      printHandCards_s(mycard); 
      acrescentar_jogos(&mycard, &games);
      baixar_jogos(&mycard, &games);
      escolher_descarte(&mycard,&lixo);
      printHandCards_s(mycard);
      printHandCards_s(lixo);
  }
  return 0;
  
}


/*1 - Get Discard OK e Meld New
2 - Modificar a struct "Listcards" para representar um conjunto generico de cartas
Criar as funções de remover e adicionar cartas nesse conjunto e usar ele para representar todos os conjuntos de cartas do programa.
3 - implementar meld_join*/



  /*void removecartasgrupo(Listcards* hand, char* card4){ 
    int i,k;
    char *parte, j[MAX_LINE], *ok;
    Listcards hand2;
    Listcards hand3;

    strcpy(j,card4);
    adicionarcartasgrupo(&hand2,j);
    for ( i=0; i< hand->tam ; i++) {
      for ( k=0; k< hand2.tam;k++) {
        if (hand2.cards[k].numero == hand->cards[i].numero && hand2.cards[k].naipe == hand->cards[i].naipe)
          break;
      }
      adicionarcartasimples(&hand3, hand->cards[i]); 
    }
    hand->tam = hand3.tam;
    for ( i=0; i< MAX_GROUP; i++)
      hand->cards[i] = hand3.cards[i];
  } 

  void removecartasimples(Listcards* hand, Carta a){

    char* ok;
    rs = carta2string(c);
    removecartasgrupo(hand, ok);
  }*/


/*void adicionarcartasgrupo(Listcards* hand, char* card4){

  int i,k;
  char *parte, j[MAX_LINE];

  strcpy(j,card4);
  parte = strtok(j, "[ ]\n");
  while (parte != NULL) {
    k = (parte[1] == '0') ? 2 : 1;
    i = hand->tam;
    hand->cards[i].naipe = string2carta(parte+k);
    hand->tam++;
    hand->cards[i].numero = string2carta(tok);
    parte = strtok(NULL, "[ ]\n");
  }
}

void adicionarcartasimples(Listcards* hand, Carta a){
  char *ok;

  ok = a.valor;
  adicionarcartasgrupo(hand,ok);
  free(ok);
}  

void rmJsonFromGroup(Listcards *hand, char *str){
    
  int i, k;
  char stringcopia[MAX_LINE];
  Listcards cartasruins, cartasboas;

  strcpy(stringcopia, str);
  adicionarcartasgrupo(&cartasruins, stringcopia);
  for (i = 0; i < hand->tam; i++) {
    for (k = 0; k < cartasruins.tam; k++) {
      if ( cartasruins.cards[k].numero == hand->cards[i].numero && cartasruins.cards[k].naipe == hand->cards[i].naipe ) {
        break;
      }
    }
    if (k<cartasruins.tam) {
      cartasruins.cards[k].numero = 1; 
    } else {
        adicionarcartasimples(&cartasboas,hand->cards[i]);
      }
  }
  hand->tam = cartasboas.tam;
  for (i = 0; i < cartasboas.tam; i++) {
    hand->cards[i].numero = cartasboas.cards[i].numero;
    hand->cards[i].naipe = cartasboas.cards[i].naipe;
  }
}*/


 /*if( (hand->cards[i].numero != hand->cards[i+1].numero-1 || hand->cards[i].numero != hand->cards[i+1].numero+1) && (hand->cards[i].naipe != hand->cards[i+1].naipe) && (hand->cards[i].numero != 2 && hand->cards[i].numero != 14)) {  
      printf("DISCARD %s\n", hand->cards[i].valor);
      fprintf(stderr, "ele printou:%d,%s",a,hand->cards[i].valor);
      remover_carta(hand, hand->cards[i].numero, hand->cards[i].naipe);
      return;
    }  
    else if((hand->cards[i].numero != hand->cards[i+1].numero-2 || hand->cards[i].numero != hand->cards[i+1].numero+2) && (hand->cards[i].naipe != hand->cards[i+1].naipe) && (hand->cards[i].numero != 2 || hand->cards[i].numero != 14)) {
      printf("DISCARD %s\n", hand->cards[i].valor);
      fprintf(stderr, "ele printou:%d,%s",a,hand->cards[i].valor);  
      remover_carta(hand, hand->cards[i].numero, hand->cards[i].naipe);
      return;
      }
      */