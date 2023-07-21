/*

Funcionalidade:
   Desenvolver um módulo de kernel que exiba os processos do sistema com as seguintes informações:
      NOME DO PROCESSO
      PID
      STATE
      RT_PRIORITY
      PARENT_PID (PPID)
      NIVEL DE PRIORIDADE
      ACTIVE_MEMORY
      CPU_RUNNABLE
      FILHOS (0..N)

Comandos para execução:
   CRIAR MODULO:
      $ make
   INSTALAR O MODULO:
      $ sudo insmod simple.ko
   REMOVER O MODULO:
      $ sudo rmmod simple
   VERIFICAR SE O MODULO ESTA INSTALADO:
      $ lsmod | grep simple
   VERIFICAR O LOG DO KERNEL:
      $ sudo tail -n 100 /var/log/kern.log
      obs. O comando tail exibe as ultimas 10 linhas do arquivo.
      obs. O comando head -n <value> exibe as primeiras VALUE linhas do arquivo.

Autores:
   Felipe Archanjo da Cunha Mendes,    RA: 2252740
   Breno Farias da Silva,              RA: 2300516
   Pamella Lissa Sato Tamura,          RA: 2254107

Data:
   04/06/2022

Diciplina:
   Sistemas Operacionais

Professor:
   Rodrigo Campiolo

*/


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felipe-Breno-Pamella");
MODULE_DESCRIPTION("Exibe os processos do sistema e seus filhos");
MODULE_VERSION("0.1");


/*DEFINIÇÃO DAS CORES

   \033[1;31m = vermelho
   \033[1;32m = verde
   \033[1;33m = amarelo
   \033[1;34m = azul
   \033[1;35m = magenta
   \033[1;36m = ciano
   \033[1;37m = branco
   \033[0m = fim de cor

*/


// Definição da struct
typedef struct{
   int count_running;
   int count_stopped;
   int count_interrupted;
   int count_zombie;
}process_info_count;


// Função de inicialização do da struct process_info_count
void init_process_info_count(process_info_count *info){
   info->count_running = 0;
   info->count_stopped = 0;
   info->count_interrupted = 0;
   info->count_zombie = 0;
}


// Função que define o estado do processo
char* getState(int state, process_info_count *info){

   switch(state)
   {
      case TASK_RUNNING:                  // TASK_RUNNING: 0
         info->count_running++;
         return "TASK_RUNNING";
      case TASK_INTERRUPTIBLE:            // TASK_INTERRUPTIBLE: 1
         info->count_interrupted++;
         return "TASK_INTERRUPTIBLE";
      case TASK_UNINTERRUPTIBLE:          // TASK_UNINTERRUPTIBLE: 2
         return "TASK_UNINTERRUPTIBLE";
      case __TASK_STOPPED:                // __TASK_STOPPED: 4
         info->count_stopped++;
         return "TASK_STOPPED";
      case __TASK_TRACED:                 // __TASK_TRACED: 8
         return "TASK_TRACED";
      case EXIT_ZOMBIE:                   // EXIT_ZOMBIE: 16
         info->count_zombie++;
         return "EXIT_ZOMBIE";
      case EXIT_DEAD:                     // EXIT_DEAD: 32
         return "EXIT_DEAD";
      case TASK_DEAD:                     // TASK_DEAD: 64
         return "TASK_DEAD";
      case TASK_WAKEKILL:                 // TASK_WAKEKILL: 128
         return "TASK_WAKEKILL";
      case TASK_WAKING:                   // TASK_WAKING: 256
         return "TASK_WAKING";
      case TASK_PARKED:                   // TASK_PARKED: 512
         return "TASK_PARKED";
      case TASK_NOLOAD:                   // TASK_NOLOAD: 1024
         return "TASK_NOLOAD";
      case TASK_STATE_MAX:                // TASK_STATE_MAX: 2048
         return "TASK_STATE_MAX";
      default:
         return "UNKNOWN";
   }
}

// Função inicial do modulo
static int __init simple_init(void)
{
   struct task_struct *task;  // Ponteiro para o processo
   struct task_struct *child; // Ponteiro para o filho do processo
   struct list_head *list;    // Ponteiro para a lista de filhos do processo

   process_info_count info;   // Struct que armazena os contadores de processos

   init_process_info_count(&info);  // Inicializa a struct process_info_count

   printk(KERN_INFO "Exibindo os processos do sistema\n");

   // Percorre todos os processos do sistema
   for_each_process(task) {

      printk(KERN_INFO "\033[1;36mProcesso: \033[1;34m%-10s\033[0m\n", task->comm);
      printk(KERN_INFO "\t\033[1;35mPID: \033[1;32m%-10d\033[0m\n", task->pid);
      printk(KERN_INFO "\t\033[1;35mState: \033[1;32m%-10s\033[0m\n", getState(task->state, &info));
      printk(KERN_INFO "\t\033[1;35mrt_priority: \033[1;32m%-10d\033[0m\n", task->rt_priority);
      printk(KERN_INFO "\t\033[1;35mparent_pid: \033[1;32m%-10d\033[0m\n", task->parent->pid);
      printk(KERN_INFO "\t\033[1;35mnice: \033[1;32m%-10d\033[0m\n", task->static_prio);
      printk(KERN_INFO "\t\033[1;35mactive_mm: \033[1;32m%-10p\033[0m\n", task->active_mm);
      printk(KERN_INFO "\t\033[1;35mCPU_runnable: \033[1;32m%-10d\033[0m\n", task->on_cpu);

      // Percorre todos os filhos do processo      
      list_for_each(list, &task->children) {
         child = list_entry(list, struct task_struct, sibling);
         printk(KERN_INFO "\t\033[1;33mFilho: \033[1;32m%s\033[0m\n", child->comm);
      }
   }

   // Exibe os contadores de alguns estados dos processos
   printk(KERN_INFO "\033[1;36mQuantidade de processos em estado TASK_RUNNING: \033[1;32m%d\033[0m\n", info.count_running);
   printk(KERN_INFO "\033[1;36mQuantidade de processos em estado TASK_STOPPED: \033[1;32m%d\033[0m\n", info.count_stopped);
   printk(KERN_INFO "\033[1;36mQuantidade de processos em estado EXIT_ZOMBIE: \033[1;32m%d\033[0m\n", info.count_zombie);
   printk(KERN_INFO "\033[1;36mQuantidade de processos em estado TASK_INTERRUPTIBLE: \033[1;32m%d\033[0m\n", info.count_interrupted);

   return 0;
}


// Função final do modulo
static void __exit simple_exit(void)
{
   printk(KERN_INFO "Desligando o modulo\n");
}


// Registra as funcoes do modulo
module_init(simple_init);
module_exit(simple_exit);
