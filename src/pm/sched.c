#include <kvnix/pm/sched.h>
#include <kvnix/pm/const.h>
#include <kvnix/pm/types.h>
#include <kvnix/mm/mm.h>
#include <kvnix/mm/alloc.h>
#include <kvnix/util.h>
#include <kvnix/clock.h>
#include <minilib/stdio.h>
#include <minilib/stdlib.h>
#include <minilib/stdbool.h>

#include "../drivers/tty/tty.h"
    
__asm__(".code16gcc\n");

proc_t system_proc;
proc_t *current_proc;

task_t *dispatcher_task;
task_t *current_task;

list_t ready_tasks;
list_t sleeping_tasks;
list_t active_tasks;

bool preemption_enabled;

long last_pid;
long last_tid;

void create_dispatcher_task();
void setup_new_task(char *name, proc_t *proc, task_t *new_task);

PUBLIC void sched_init()
{
    last_pid = 0;
    last_tid = 0;

    //lists initialization
    list_init(&ready_tasks);
    list_init(&active_tasks);
    list_init(&sleeping_tasks);

    //system process setup
    system_proc.pid = last_pid++;
    system_proc.parent_pid = system_proc.pid;
    system_proc.name = "System";
    
    //kernel heap and processes memory initialization
    system_proc.memory.heap = init_memory_area((void *) KERNEL_HEAP_BEGIN, KERNEL_HEAP_SIZE);

    //system main task definition
    system_proc.main_task = kmalloc(sizeof(task_t));
    getcontext(&system_proc.main_task->context);
    setup_new_task("Kernel init", &system_proc, system_proc.main_task);

    current_proc = &system_proc;
    current_task = system_proc.main_task;
    task_add(current_task);

    //switching to dispatcher task
    create_dispatcher_task();
    task_yield();
}

void create_dispatcher_task()
{
    void *dispatcher_stack = kmalloc(PROC_STACK_SIZE);

    //dispatcher task
    dispatcher_task = task_create(&system_proc, &dispatcher_body, dispatcher_stack, PROC_STACK_SIZE, NULL);
    dispatcher_task->name = "Dispatcher";
}

void setup_new_task(char *name, proc_t *proc, task_t *new_task)
{
    new_task->tid = last_tid++;
    new_task->proc = proc;
    new_task->name = name;
    new_task->start_time = time_now();
    new_task->cpu_time = 0;
    new_task->nr_activations = 0;
    new_task->status = TASK_CREATED;

    list_init(&new_task->join_list);
}

PUBLIC task_t * task_create(proc_t *proc, int (*func)(void *), void *child_stack, size_t child_stack_size, void *arg)
{                         
    enable_preemption(false);
    
    //task creation and setup
    task_t *new_task = kmalloc(sizeof(task_t));
    setup_new_task(proc->name, proc, new_task);

    //current user/machine context
    ucontext_t *context = &new_task->context;
    getcontext(context);

    //stack definition
    context->uc_stack.ss_sp = child_stack;
    context->uc_stack.ss_size = child_stack_size;

    //new context creation
    //TODO pass the parameter
    makecontext(context, func, 0);

    //adding to active tasks
    list_elem_t *new_task_active_list_elem = kmalloc(sizeof(list_elem_t));
    new_task_active_list_elem->prev = NULL;
    new_task_active_list_elem->next = NULL;
    new_task_active_list_elem->value = new_task;
    list_append(&active_tasks, new_task_active_list_elem);

    return new_task;
}

PUBLIC void task_add(task_t *new_task)
{
    enable_preemption(false);
    
    list_elem_t *new_task_list_elem = kmalloc(sizeof(list_elem_t));
	if (new_task_list_elem == NULL) {
		panic(PM_NAME, "Unable to allocate memory at sched_add_task().");
	}
    new_task_list_elem->prev = NULL;
    new_task_list_elem->next = NULL;
    new_task_list_elem->value = new_task; 
    
    new_task->status = TASK_READY;

    if (list_append(&ready_tasks, new_task_list_elem) == NULL) {
        panic(PM_NAME, "Adding a task to the list at sched_add_task().");
    }
    
    enable_preemption(true);
}

PUBLIC void task_yield()
{
	 task_switch(dispatcher_task);
}

PUBLIC void task_switch(task_t *task)
{  
    enable_preemption(false);
	
    long time = time_now();
                                        
    //the current task is now the previous
    task_t *previous_task = current_task;
    
    //cpu time update
    previous_task->cpu_time += (time - previous_task->last_run_time);

    //setting the current task and its time information
    current_task = task;
    current_task->nr_activations++;
    current_task->last_run_time = time;

    //setting the current process
    current_proc = current_task->proc;
   
	if (task != dispatcher_task) { 
	    enable_preemption(true);
	}
	
	//context switch
    swapcontext(&previous_task->context, &current_task->context);
}

PUBLIC int task_join(task_t *task)
{    
    enable_preemption(false);
    
    
//TODO check if the task exists
 
    list_elem_t *elem = kmalloc(sizeof(list_elem_t));

	if (elem == NULL)
		panic(PM_NAME, "Unable to allocate memory at sched_task_join().");

    elem->prev = NULL;
    elem->next = NULL;
    elem->value = current_task; 
 
    current_task->status = TASK_WAITING;
    list_append(&task->join_list, elem);

	//returning to dispatcher
    task_yield();

    int exit_code = task->exit_code;

    return exit_code;
}

PUBLIC void task_sleep(long ticks)
{                                                         
    enable_preemption(false);
    
    //TODO check if the task exists
 
    list_elem_t *elem = kmalloc(sizeof(list_elem_t));
    elem->prev = NULL;
    elem->next = NULL;
    elem->value = current_task; 
 
    current_task->status = TASK_SLEEPING;
    current_task->wake_up_time = time_now() + ticks;
    list_append(&sleeping_tasks, elem);

    //returning to dispatcher
    task_yield();
}

PUBLIC void task_exit(int exit_code)
{
    enable_preemption(false);

    current_task->status = TASK_ZOMBIE;
    list_elem_t *elem = current_task->join_list.head;

    while (elem != NULL) {
        //adding the tasks to the ready list
        task_t *waiting_task = elem->value;
        task_add(waiting_task);
                    
        list_elem_t *prev_elem = elem;
        elem = prev_elem->next;
    
        list_remove(&current_task->join_list, prev_elem);
        kfree(prev_elem);
    }
	
    task_yield();
}

PUBLIC task_t * get_task_by_pid(int pid)
{
    list_elem_t *active_list_elem = active_tasks.head;

    while (active_list_elem != NULL) {
        task_t *active_task = active_list_elem->value;

        if (active_task->tid == pid) {
            return active_task;
        }

        active_list_elem = active_list_elem->next;
    }

    return NULL;
}

PUBLIC list_elem_t * schedule()
{
    list_elem_t *task_list_elem = ready_tasks.head;

    if (task_list_elem != NULL) {
        list_remove(&ready_tasks, task_list_elem);
    }

    return task_list_elem;
}

PUBLIC void dispatcher_body()
{
    enable_preemption(false);
    
    list_elem_t *selected_task_list_elem;
    list_elem_t *sleeping_task_list_elem;
    list_elem_t *active_list_elem;
    list_elem_t *prev_elem;
    
    task_t *selected_task;
    task_t *sleeping_task;

    bool has_active_tasks;
    
    while (1) {
        //do_write(1, "D", 1);

		//wake up tasks
        sleeping_task_list_elem = sleeping_tasks.head;
        while (sleeping_task_list_elem != NULL) {
            sleeping_task = sleeping_task_list_elem->value;
            
            prev_elem = sleeping_task_list_elem;
            sleeping_task_list_elem = prev_elem->next; 

            //is it time to wake up?
            if (sleeping_task->wake_up_time <= time_now()) {
                list_remove(&sleeping_tasks, prev_elem);
                kfree(prev_elem); 
                
                //adding the tasks to the ready list
                task_add(sleeping_task);
            }
        }

        //selected task to run
        selected_task_list_elem = schedule();

        //if there aren't active tasks then the dispatcher can exit
        has_active_tasks = (active_tasks.head != NULL);
        if (!has_active_tasks) {
            break;
        }

        if (selected_task_list_elem != NULL) {
            //if there is a ready task...
            selected_task = selected_task_list_elem->value;
 
            //run the task
            selected_task->status = TASK_RUNNING;
            task_switch(selected_task);
            
            //after the task run
            if (selected_task->status == TASK_RUNNING) {
                selected_task->status = TASK_READY;

                //adding the task to the ready list
                if (list_append(&ready_tasks, selected_task_list_elem) == NULL) {
                    panic(PM_NAME, "Adding a task to the list in dispatcher_body().");
                }
            } else {
                //the task was removed from the ready list. so, it is possible
                //to free its list element
                kfree(selected_task_list_elem);
                
                if (selected_task->status == TASK_ZOMBIE) {
					//removing task from active list
                    active_list_elem = list_search(&active_tasks, selected_task);

                    if (active_list_elem == NULL) {
                        panic(PM_NAME, "Task was not in active list at dispatcher_body().");
                    }

                    list_remove(&active_tasks, active_list_elem);

                    //it is possible to free the task because it is done
                    kfree(active_list_elem);
                    kfree(selected_task);
                }
            }
        } else {
            //TODO switch to IDLE thead
            //do_write(1, "idle", 4);
        }
	    
        enable_preemption(true);
    }
}

PUBLIC void sched_handle_timer()
{
    task_yield();
}

