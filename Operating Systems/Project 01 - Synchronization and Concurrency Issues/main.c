/*
Alunos de SO irão apresentar o conteúdo para alunos da computação.
O professor controla o numero de alunos de SO irão apresentar e o numero de alunos da computação que irão assistir.
A ordem da apresentação é a ordem de chegada na sala.
Todo aluno que irá apresentar deve assinar a lista na entrada da sala.
***Quando o professor avisa que as apresentação vão começar, a sala fecha e ninguém mais pode entrar.***
Os alunos que estão assistindo podem sair a qualquer momento.
Após todas as apresentações, o professor atribui uma nota aos alunos de SO.
Após os alunos receberem a nota, eles devem assinar uma lista de saida e sair da sala.
O professor volta e espera os novos alunos de SO entrarem e os alunos de computação entrarem na sala.
Quando todas as apresentações acabaram, o professor espera todos sairem da sala.
Usar semáforos, variáveis de condição (cond) e mutex para simular e controlar o comportamento das entidades: professor, alunos SO e alunos Computação
Há N alunos de SO e somente uma parte deve entrar por vez na sala (o professor controla por meio do iniciar apresentações).
Professor executa as ações: iniciar_apresentacoes, liberar_entrada, atribuir_nota, fechar_porta.
Alunos SO executam as ações: entrar_sala, assinar_lista_entrada, aguardar_apresentacoes, apresentar, assinar_lista_saida.
Alunos de Computação executam as ações: entrar_sala, assistir_apresentacao, sair_apresentacao.
Exiba mensagens para mostrar as ações, por exemplo, alunoSO_1 entra na sala, professor inicia apresentacoes, alunoComputacao_3 entra na sala, e assim por diante.
*/

// PAluno Campiolo 27/05 -
// https://drive.google.com/file/d/11fgDG5eJ1zcsRLQJq3xPfqQo_inEiW6W/view?usp=sharing

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include "fila.h"

#define N_ALUNOS_SO 10
#define N_ALUNOS_COMPUTACAO 10
#define N_VAGAS_APRESENTACAO 5
#define N_CADEIRAS_SALA 5

// Variáveis globais
int n_alunos_so = N_ALUNOS_SO;
int n_alunos_computacao = N_ALUNOS_COMPUTACAO;
int n_apresentacoes = N_ALUNOS_SO / N_VAGAS_APRESENTACAO;

// Semáforos
sem_t sem_alunos_so;
sem_t sem_alunos_computacao;
sem_t sem_apresentacoes;
sem_t sem_fechar_porta;
sem_t sem_liberar_entrada;
sem_t sem_atribuir_nota;
sem_t sem_assinar_lista_entrada; // printf("") e proteger com mutex
sem_t sem_assinar_lista_saida;	 // printf("")
sem_t sem_aguardar_apresentacoes;
sem_t sem_apresentar;
sem_t sem_sair_apresentacao;
// Declaração fila
Fila *alunosSo;

char str[200];

// Structs
typedef struct aluno_so
{
	int id;
	bool apresentou;
} AlunoSO;

typedef struct aluno_computacao
{
	int id;
	bool assistiu;
} AlunoComputacao;

typedef struct professor
{
	int id;
	bool iniciou_apresentacoes;
} Professor;

// Funções
void *functionAlunoDeSO(void *arg)
{
	AlunoSO *aluno_so = (AlunoSO *)arg;

	while (n_alunos_so > 0)
	{
		// a porta aberta -> sem wait porta
		sem_wait(&sem_alunos_so);
		printf("Aluno de SO %d entra na sala\n", aluno_so->id);
		fila_inserir(alunosSo, aluno_so->id);
		fila_toString(alunosSo, str);
		printf("%s after insertion\n", str);
		sleep(1);
		sem_post(&sem_assinar_lista_entrada); // Usar controle por variáveis protegidas por mutex.
		sem_wait(&sem_apresentar);
		int alunoAtual;
		fila_remover(alunosSo, &alunoAtual);
		fila_toString(alunosSo, str);
		printf("%s - primeiro\n", str);
		if (alunoAtual == aluno_so->id){
			printf("Aluno de SO %d apresenta\n", aluno_so->id);
			sleep(1);
			aluno_so->apresentou = true;
			sem_post(&sem_apresentar);
			sem_post(&sem_assinar_lista_saida);
			sem_wait(&sem_sair_apresentacao);
			printf("Aluno de SO %d sai da sala\n", aluno_so->id);
			sleep(1);
			n_alunos_so--;
			fila_remover(alunosSo, &alunoAtual);
			sem_post(&sem_sair_apresentacao);
		}
	}

	return NULL;
}

void *functionAlunoDeComputacao(void *arg)
{
	AlunoComputacao *aluno_computacao = (AlunoComputacao *)arg;

	while (n_alunos_computacao > 0)
	{
		sem_wait(&sem_alunos_computacao);
		printf("Aluno de Computacao %d entra na sala\n", aluno_computacao->id);
		sleep(1);
		sem_wait(&sem_apresentar);
		printf("Aluno de Computacao %d assiste a apresentacao\n", aluno_computacao->id);
		sleep(1);
		aluno_computacao->assistiu = true;
		sem_post(&sem_apresentar);
		sem_post(&sem_sair_apresentacao);
		sem_wait(&sem_sair_apresentacao);
		printf("AlunoComputacao %d sai da sala\n", aluno_computacao->id);
		sleep(1);
		n_alunos_computacao--;
		sem_post(&sem_sair_apresentacao);
	}

	return NULL;
}

// TODO: fila de controle -> bibliotecas.

void *functionProfessor(void *arg)
{
	Professor *professor = (Professor *)arg;

	while (n_apresentacoes > 0)
	{
		sem_wait(&sem_apresentacoes);
		// fechar a porta -> sem porta.
		professor->iniciou_apresentacoes = true;
		printf("Professor iniciou apresentacoes\n");
		sem_wait(&sem_liberar_entrada);
		printf("Professor liberou entrada\n");
		// Professor espera a sala ficar cheia
		sem_wait(&sem_assinar_lista_entrada);
		// liberar a porta -> sem porta.
		n_apresentacoes--;
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	// Inicializando semáforos
	sem_init(&sem_alunos_so, 0, N_VAGAS_APRESENTACAO);
	sem_init(&sem_alunos_computacao, 0, N_CADEIRAS_SALA);
	sem_init(&sem_apresentacoes, 0, 1);
	sem_init(&sem_fechar_porta, 0, 1);
	sem_init(&sem_liberar_entrada, 0, 1);
	sem_init(&sem_atribuir_nota, 0, 1);
	sem_init(&sem_assinar_lista_entrada, 0, 1);
	sem_init(&sem_assinar_lista_saida, 0, 1);
	sem_init(&sem_aguardar_apresentacoes, 0, 1);
	sem_init(&sem_apresentar, 0, 1);
	sem_init(&sem_sair_apresentacao, 0, 1);

  	// Fila
	Fila *alunosSo = fila_criar();

  fila_inserir(alunosSo, 10);
  
	// Criando alunos
	AlunoSO *alunos_de_so = (AlunoSO *)malloc(sizeof(AlunoSO) * n_alunos_so);
	AlunoComputacao *alunos_de_computacao = (AlunoComputacao *)malloc(sizeof(AlunoComputacao) * n_alunos_computacao);
	Professor *professor = (Professor *)malloc(sizeof(Professor));

	// Inicializando alunos de SO
	for (int i = 0; i < n_alunos_so; i++)
	{
		alunos_de_so[i].id = i + 1;
		alunos_de_so[i].apresentou = false;
	}

	// Inicializando alunos de Computacao
	for (int i = 0; i < n_alunos_computacao; i++)
	{
		alunos_de_computacao[i].id = i + 1;
		alunos_de_computacao[i].assistiu = false;
	}

	// Inicializando professor
	professor->id = 0;
	professor->iniciou_apresentacoes = false;

	// Criando threads
	pthread_t threads_alunos_so[n_alunos_so];
	pthread_t threads_alunos_computacao[n_alunos_computacao];
	pthread_t thread_professor;

	// Criando thrads dos alunos
	for (int i = 0; i < n_alunos_so; i++)
	{
		pthread_create(&threads_alunos_so[i], NULL, functionAlunoDeSO, (void *)&alunos_de_so[i]);
	}

	for (int i = 0; i < n_alunos_computacao; i++)
	{
		pthread_create(&threads_alunos_computacao[i], NULL, functionAlunoDeComputacao, (void *)&alunos_de_computacao[i]);
	}

	// Criando thread do professor
	pthread_create(&thread_professor, NULL, functionProfessor, (void *)professor);

	// Esperando threads dos alunos
	for (int i = 0; i < n_alunos_so; i++)
	{
		pthread_join(threads_alunos_so[i], NULL);
	}

	for (int i = 0; i < n_alunos_computacao; i++)
	{
		pthread_join(threads_alunos_computacao[i], NULL);
	}

	// Esperando thread do professor
	pthread_join(thread_professor, NULL);

	// Liberando memória
	free(alunos_de_so);
	free(alunos_de_computacao);
	free(professor);

	// Destruindo semáforos
	sem_destroy(&sem_alunos_so);
	sem_destroy(&sem_alunos_computacao);
	sem_destroy(&sem_apresentacoes);
	sem_destroy(&sem_fechar_porta);
	sem_destroy(&sem_liberar_entrada);
	sem_destroy(&sem_atribuir_nota);
	sem_destroy(&sem_assinar_lista_entrada);
	sem_destroy(&sem_assinar_lista_saida);
	sem_destroy(&sem_aguardar_apresentacoes);
	sem_destroy(&sem_apresentar);
	sem_destroy(&sem_sair_apresentacao);

	return 0;
}