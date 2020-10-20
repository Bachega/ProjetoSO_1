#include "queue.h"

/*
* Cira um ponteiro para um noh de fila vazio e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para um noh de fila vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para um noh de fila vazio eh criado e retornado.
*/
Node* createNode() {
    Node* n = (Node*)malloc(sizeof(Node));
    n->pcb = NULL;
    n->next = n->prev = NULL;
    return n;
}

/*
* Cira um ponteiro para uma fila vazia e retorna;
* Entrada: nenhuma;
* Retorno: ponteiro para uma fila vazia;
* Pre-condicao: nenhuma;
* Pos-condicao: um ponteiro para uma fila vazia eh criado e retornado.
*/
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    q->lenght = 0;
    q->creationTime = 0;
    return q;
}

/*
* Testa se uma fila eh vazia;
* Entrada: fila a ser testada;
* Retorno: 1 para vazia e 0 para nao vazia;
* Pre-condicao: nenhuma;
* Pos-condicao: nenhuma.
*/
int isEmpty(Queue* q) {
    return (q==NULL || q->lenght==0);
}

/*
* Insere um PCB na fila de processos prontos;
* Entrada: fila e PCB a ser inserido;
* Retorno: nenhum;
* Pre-condicao: pcb nao pode ser nulo;
* Pos-condicao: pcb eh inserido na fila de processos prontos.
*/
void insert(Queue* q, PCB* pcb) {
    if(q == NULL)
        q = createQueue();

    if(q->lenght == 0) {
        q->head = q->tail = createNode();
        q->head->pcb = pcb;
        q->head->prev = q->head->next = q->tail;
    } else {
        q->tail->next = createNode();
        q->tail->next->pcb = pcb;
        q->tail->next->prev = q->tail;
        q->tail->next->next = q->head;
        q->tail = q->tail->next;
        q->head->prev = q->tail;
    }
    q->lenght++;
}

/*
* Remove um elemento da fila;
* Entrada: nenhuma;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: um elemento eh removido da fila.
*/
void removeElement(Queue* q, int pid) {
    int i;
    Node* aux;

    if(q == NULL || q->lenght == 0)
        return;

    for(i=0, aux = q->head; i<q->lenght; i++, aux = aux->next) {

        if(aux->pcb->pid == pid) {
            if(q->lenght == 1) {
                aux = q->head;
                q->head = q->tail = NULL;
            } else {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                if (aux == q->head)
                    q->head = q->head->next;
                else if (aux == q->tail)
                    q->tail = q->tail->prev;
            }

            free(aux);
            q->lenght--;
            break;
        }
    }
    
}

/*
* Insere um PCB na fila de processos nao criados, ordenados pelo seu tempo de criacao;
* Entrada: fila e PCB;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: um PCB eh inserido na fila de processos nao criados.
*/
void insertPendingQueue(Queue* t, PCB* pcb) {
    Node* aux;
    Node* n;
    int i;

    if(t == NULL)
        t = createQueue();

    if(t->lenght == 0) {
        t->head = t->tail = createNode();
        t->head->pcb = pcb;
        t->head->prev = t->head->next = t->tail;
        t->creationTime = pcb->creationTime;
    } else {

        aux = t->head;
        for(i = 0; i < t->lenght; i++) {
            if(pcb->creationTime < aux->pcb->creationTime)
                break;
            aux = aux->next;
        }

        n = createNode();
        n->pcb = pcb;
        n->prev = aux->prev;
        n->next = aux;
        n->prev->next = n;
        n->next->prev = n;
        if(i == 0) {
            t->head = n;
            t->creationTime = n->pcb->creationTime;
        } else if(i == t->lenght)
            t->tail = n;
    }
    t->lenght++;
}

/*
* Envia o primeiro elemento da fila de processos nao criados,
  e todos os outros que possuem o mesmo tempo de criacao que o primeiro, para o final da fila de processos criados;
* Entrada: fila de processos prontos e fila de processos nao criados;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: o primeiro PCB (e todos os outros que possuirem o mesmo tempo de criacao que este) eh enviado para o final da fila de processos prontos.
*/
void sendPendingToReady(Queue* q, Queue* t) {
    int ct;
    Node* aux;

    if(t == NULL)
        return;
    if(q == NULL)
        q = createQueue();

    aux = t->head;
    ct = t->creationTime;
 
    while((t->lenght > 0) && (aux->pcb->creationTime == ct)) {
        
        if(q->lenght == 0) {

            // Faz a fila de processos prontos apontar para o noh
            q->head = q->tail = aux;

            // Atualiza a fila de processos pendentes T
            if(t->lenght > 1) {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                t->head = aux->next;
            } else {
                t->head = t->tail = NULL;
            }

            // Mantem a condicao circular da lista Q
            aux->prev = aux->next = aux;

        } else {
            
            // Coloca o processo novo entre a cabeca e a cauda da lista Q (sendo ele a nova cauda)
            q->tail->next = aux;
            q->head->prev = aux;

            // Atualiza a fila de processos pendentes T
            if(t->lenght > 1) {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                t->head = aux->next;
            } else {
                t->head = t->tail = NULL;
            }

            // Mantem a condicao circular da fila Q
            aux->prev = q->tail;
            aux->next = q->head;

            // Faz a cauda da fila Q apontar para o ultimo noh da fila Q
            q->tail = aux;

        }

        aux->pcb->creationTime = 0;
        aux->pcb->state = READY;

        // A cada iteracao, a fila Q aumenta e a fila T diminui
        q->lenght++;
        t->lenght--;

        // Faz aux apontar para a nova cabeca da fila T
        aux = t->head;
    }

    // Guarda o tempo do proximo processo pendente
    if(t->lenght > 0)
        t->creationTime = t->head->pcb->creationTime;
    else
        t->creationTime = 0;
    
}

/*
* Envia o PCB que esta no comeco da fila para o final da fila;
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: o primeiro elemento da fila vai para o final da fila.
*/
void sendFirstToEnd(Queue* q) {
    if(q->lenght > 1) {
        q->head = q->head->next;
        q->tail = q->tail->next;
    }
}

/*
* Imprime a fila no console (para testes);
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: fila eh impressa no console.
*/
void printQueue(Queue* q) {
    int i;
    Node* aux;  

    if(q->lenght>0) {
        aux = q->head;
        for(i=0; i<q->lenght; i++) {
            printf("PCB[%d] ", aux->pcb->pid);
            aux = aux->next;
        }
        printf("Previous from head [%d] || After tail [%d]", q->head->prev->pcb->pid, q->tail->next->pcb->pid);
    } else
        printf("Queue is empty");
    printf("\n");
}

/*
* Imprime a fila no console de tras pra frente (para testes);
* Entrada: fila;
* Retorno: nenhum;
* Pre-condicao: nenhuma;
* Pos-condicao: fila eh impressa no console de tras pra frente.
*/
void printQueueBackwards(Queue* q) {
    int i;
    Node* aux;  

    if(q->lenght>0) {
        aux = q->tail;
        for(i=0; i<q->lenght; i++) {
            printf("PCB[%d] ", aux->pcb->pid);
            aux = aux->prev;
        }
        printf("Previous from head [%d] || After tail [%d]", q->head->prev->pcb->pid, q->tail->next->pcb->pid);
    } else
        printf("Queue is empty");
    printf("\n");
}
