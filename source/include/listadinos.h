#ifndef LISTADINOS_H
#define LISTADINOS_H

#define NMAX 30

#include <stdlib.h>
#include <stdio.h>
#include "dinos.h"



typedef struct no{
	dinos dados;
	struct no *prox;	
}tp_lista_dinos;	

tp_lista_dinos *criar_lista();
tp_lista_dinos *aloca_no();
void inserir_no_fim(tp_lista_dinos **l, dinos d);
int remover_por_posicao(tp_lista_dinos **l, int p);
tp_lista_dinos *busca_por_posicao(tp_lista_dinos *l, int p);
int lista_vazia(tp_lista_dinos *l);
int tamanho_lista(tp_lista_dinos *l);
int inserir_por_posicao(tp_lista_dinos **l, dinos d, int posicao);
void imprimir_lista(tp_lista_dinos *l);


tp_lista_dinos *criar_lista(){
	return NULL;
}

tp_lista_dinos *aloca_no(){
	tp_lista_dinos *NovoNo;
	NovoNo = (tp_lista_dinos*) malloc(sizeof(tp_lista_dinos));
	return NovoNo;
}

void inserir_no_fim(tp_lista_dinos **l, dinos d){
	tp_lista_dinos *aux, *NovoNo;
	aux = *l;
	
	NovoNo = aloca_no();
	NovoNo->dados = d;
	NovoNo->prox = NULL;
	
	if(lista_vazia(*l)){
	*l = NovoNo;	
	}
	else{
		while(aux->prox != NULL){
		aux = aux->prox;
		}
		aux->prox = NovoNo;	
	}
	
}

void inserir_no_inicio(tp_lista_dinos **l, dinos d){
	tp_lista_dinos *aux, *NovoNo;
	aux = *l;
	
	NovoNo = aloca_no();
	NovoNo->dados = d;
	NovoNo->prox = NULL;
	
	if(lista_vazia(*l)){
	*l = NovoNo;	
	}
	else{	
	NovoNo->prox = aux;
	*l = NovoNo;		
	}
}

int remover_por_posicao(tp_lista_dinos **l, int p){
	tp_lista_dinos *aux, *ant;
	int cont=0;
	aux = *l;
	ant = NULL;
	
	while(aux != NULL && p != cont){
		ant = aux;
		aux = aux->prox;
		cont++;
	}

	if(lista_vazia(*l)){
	printf("LISTA VAZIA\n");
	return 0;	
	}
	if(ant == NULL){
	*l = aux->prox;	
	}
	else{
	ant->prox = aux->prox;
	}
	
	free(aux);
	aux = NULL;
	return 1;
}

tp_lista_dinos *busca_por_posicao(tp_lista_dinos *l, int p){
	tp_lista_dinos *aux;
	int cont=0;
	aux = l;
	
	while(aux != NULL && p != cont){
		aux = aux->prox;
		cont++;
	}	

		if(aux == NULL){
		return NULL;	
		}
		else{
		return aux;
		}		
				
}

int lista_vazia(tp_lista_dinos *l){
	if(l == NULL){
	return 1;	
	}
	else{
	return 0;	
	}
}

int tamanho_lista(tp_lista_dinos *l){
	tp_lista_dinos *aux;
	int cont = 0;
	aux = l;
	
	while(aux != NULL){
	cont++;
	aux = aux->prox;	
	}
	
	return cont;
	
}

void destruir_lista(tp_lista_dinos **l){
	tp_lista_dinos *aux;
	aux = *l;
	
	while(aux != NULL){
	*l = aux->prox;
	free(aux);
	aux = *l;	
	}
	*l = NULL;
}

int inserir_por_posicao(tp_lista_dinos **l, dinos d, int posicao){
	tp_lista_dinos *aux, *NovoNo;	
	int cont = 1;
	aux = *l;
	
	NovoNo = aloca_no();
	NovoNo->dados = d;
	NovoNo->prox = NULL;
	
	if(posicao == 0 || lista_vazia(*l)){
		NovoNo->prox = *l;
		*l = NovoNo;
		return 1;
	}
	
	while(aux != NULL && cont < posicao){
		aux = aux->prox;
		cont++;
	}
	
	if(aux == NULL || posicao < 0){
		free(NovoNo);
		return 0;
	}
	else{
	NovoNo->prox = aux->prox;
	aux->prox = NovoNo;
	return 1;	
	}
}

void compra(tp_lista_dinos **loja, tp_lista_dinos **grupo){
	tp_lista_dinos *aux;
	int p1, p2;
	
	printf("Digite a posicao do dinossauro a venda (0,1,...): ");
	scanf("%d", &p1);
	
	if(!lista_vazia(*loja)){
	aux = busca_por_posicao(*loja, p1);	
	}
	
	printf("Defina a posicao do dinossauro no time (0,1,...): ");
	scanf("%d", &p2);
	inserir_por_posicao(grupo, aux->dados, p2);
	remover_por_posicao(loja, p1);
}

void venda(tp_lista_dinos **l){
	int p;
	printf("Digite a posicao do dinossauro no time: ");
	scanf("%d", &p);
	
	remover_por_posicao(l, p);
}

void imprimir_lista(tp_lista_dinos *l){
	tp_lista_dinos *aux;
	aux = l;
	
	while(aux != NULL){
	printf("Nome: %s ", aux->dados.nome);
	printf("Dano: %d ", aux->dados.dano);
	printf("Vida: %d\n\n", aux->dados.vida);
	aux = aux->prox;	
	}	
	
}

tp_lista_dinos *copiar_lista(tp_lista_dinos *lista_original) {

    if (lista_vazia(lista_original)) {
        return criar_lista();  // Retorna uma lista vazia
    }

    tp_lista_dinos *aux_original = lista_original;
    tp_lista_dinos *nova_lista; nova_lista = criar_lista();
    tp_lista_dinos *aux_nova;  aux_nova = criar_lista();

    // Cria o primeiro nó da nova lista
    nova_lista = aloca_no();
    nova_lista->dados = aux_original->dados;
    nova_lista->prox = NULL;
    aux_nova = nova_lista;
    aux_original = aux_original->prox;

    // Percorre o restante da lista original, copiando cada nó
    while (aux_original != NULL) {
        aux_nova->prox = aloca_no();
        aux_nova = aux_nova->prox;
        aux_nova->dados = aux_original->dados;
        aux_nova->prox = NULL;
        aux_original = aux_original->prox;
    }

    return nova_lista;
}

#endif	
