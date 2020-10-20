#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

#include "pcb.h"

// Estrutura para noh da lista
typedef struct node{
    PCB* pcb;
    struct node* next;
    struct node* prev;
}Node;

// Estrutura para lista duplamente encadeada circular
typedef struct queue {
    struct node* head;
    struct node* tail;
    int lenght;
    int creationTime;
}Queue;

/*
* Cira um ponteiro para um noh de fila vazio e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para um noh de fila vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para um noh de fila vazio eh criado e retornado.
*/
Node* createNode();

/*
* Cira um ponteiro para uma fila vazia e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para uma fila vazia;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para uma fila vazia eh criado e retornado.
*/
Queue* createQueue();

/*
* Testa se uma fila eh vazia;
* Entrada: fila a ser testada;
* Retorno: 1 para vazia e 0 para nao vazia;
* Pre-condicao: nenhuma;
* Pos-condicao: nenhuma.
*/
int isEmpty(Queue* q);

/*
* Insere um PCB na fila de processos prontos;
* Entrada: fila e PCB a ser inserido;
* Retorno: nenhum;
* Pre-condicao: pcb nao pode ser nulo;
* Pos-condicao: pcb eh inserido na fila de processos prontos.
*/
void insert(Queue* q, PCB* pcb);

/*
* Remove um elemento da fila;
* Entrada: nenhuma;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: um elemento eh removido da fila.
*/
void removeElement(Queue* q, int pid);

/*
* Insere um PCB na fila de processos nao criados, ordenados pelo seu tempo de criacao;
* Entrada: fila e PCB;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: um PCB eh inserido na fila de processos nao criados.
*/
void insertPendingQueue(Queue* t, PCB* pcb);

/*
* Envia o primeiro elemento da fila de processos nao criados,
  e todos os outros que possuem o mesmo tempo de criacao que o primeiro, para o final da fila de processos criados;
* Entrada: fila de processos prontos e fila de processos nao criados;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: o primeiro PCB (e todos os outros que possuirem o mesmo tempo de criacao que este) eh enviado para o final da fila de processos prontos.
*/
void sendPendingToReady(Queue* q, Queue* t);

/*
* Envia o PCB que esta no comeco da fila para o final da fila;
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: o primeiro elemento da fila vai para o final da fila.
*/
void sendFirstToEnd(Queue* q);

/*
* Imprime a fila no console (para testes);
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: fila eh impressa no console.
*/
void printQueue(Queue* q);

/*
* Imprime a fila no console de tras pra frente (para testes);
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: fila eh impressa no console de tras pra frente.
*/
void printQueueBackwards(Queue* q);

#endif // QUEUE_H