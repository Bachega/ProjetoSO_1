#include "fcfs.h"

/*
* Executa o algoritmo First Come First Served para as filas de processos prontos e nao criados, imprime as informacoes de sua execucao no console e no arquivo de saida;
* Entrada: Fila Q de processos prontos e Fila T de processos nao criados;
* Retorno: vazio;
* Pre-condicao: nenhuma;
* Pos-condicao: o resultado da execucao eh impresso no console e no arquivo de saida.
*/
void fcfs(Queue* q, Queue* t) {
    PCB* pcb;
    int responseTime = 0;
    int averageResponseTime = 0;
    int contextSwitch = 0;
    int num = q->lenght;

    createOutputFile(0);

    printf("\nFIRST COME FIRST SERVED\n\n");
    while(q->lenght) {
        contextSwitch++;

        pcb = q->head->pcb;

        writeExecutionMessage(pcb->pid, pcb->execTime, 0);
        responseTime += executeProcess(pcb, pcb->execTime);

        if((t->creationTime > 0) && (responseTime >= t->creationTime)) {
            sendPendingToReady(q, t);
            num++;
        }

        if(pcb->state == TERMINATED) {
            averageResponseTime += responseTime;
            writeOneFinishedMessage(pcb->pid, responseTime, 0);
            printf("PID [%d] FINISHED\tResponse time: %d milliseconds [%.1f seconds]\n", pcb->pid, responseTime, ((float)responseTime)/1000);
            removeElement(q, pcb->pid);
        }
        
    }

    averageResponseTime /= num;
    writeAllFinishedMessage(averageResponseTime, contextSwitch, 0);
    printf("\nAll processes finished\nAverage response time: %d milliseconds [%.1f seconds]\nNumber of context switches: %d", averageResponseTime, ((float)averageResponseTime)/1000, contextSwitch);
}