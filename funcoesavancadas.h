#ifndef FUNCOESAVANCADAS_H
#define FUNCOESAVANCADAS_H

void baixar_jogos(Listcards *hand,Listjogos* games);
void complemento_jogo(Listjogos* games, int posicao, numero carta_numero, naipe carta_naipe, char* carta_valor);
int acrescentar_jogos(Listcards *hand,Listjogos* games);

#endif