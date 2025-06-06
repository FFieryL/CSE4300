#ifndef _THREAD_H_
#define _THREAD_H_

/*
 * Definition of a thread.
 */

/* Get machine-dependent stuff */
#include <machine/pcb.h>


struct addrspace;

struct thread {
	/**********************************************************/
	/* Private thread members - internal to the thread system */
	/**********************************************************/
	
	struct pcb t_pcb;
	char *t_name;
	const void *t_sleepaddr;
	char *t_stack;
	
	/**********************************************************/
	/* Public thread members - can be used by other code      */
	/**********************************************************/
	
	/*
	 * This is public because it isn't part of the thread system,
	 * and will need to be manipulated by the userprog and/or vm
	 * code.
	 */
	struct addrspace *t_vmspace;

	/*
	 * This is public because it isn't part of the thread system,
	 * and is manipulated by the virtual filesystem (VFS) code.
	 */
	struct vnode *t_cwd;
};

/* Call once during startup to allocate data structures. */
struct thread *thread_bootstrap(void);

/* Call during panic to stop other threads in their tracks */
void thread_panic(void);

/* Call during shutdown to clean up (must be called by initial thread) */
void thread_shutdown(void);

/*
 * Make a new thread, which will start executing at "func".  The
 * "data" arguments (one pointer, one integer) are passed to the
 * function.  The current thread is used as a prototype for creating
 * the new one. If "ret" is non-null, the thread structure for the new
 * thread is handed back. (Note that using said thread structure from
 * the parent thread should be done only with caution, because in
 * general the child thread might exit at any time.) Returns an error
 * code.
 */
int thread_fork(const char *name, 
		void *data1, unsigned long data2, 
		void (*func)(void *, unsigned long),
		struct thread **ret);

/*
 * Cause the current thread to exit.
 * Interrupts need not be disabled.
 */
void thread_exit(void);

/*
 * Cause the current thread to yield to the next runnable thread, but
 * itself stay runnable.
 * Interrupts need not be disabled.
 */
void thread_yield(void);

/*
 * Cause the current thread to yield to the next runnable thread, and
 * go to sleep until wakeup() is called on the same address. The
 * address is treated as a key and is not interpreted or dereferenced.
 * Interrupts must be disabled.
 */
void thread_sleep(const void *addr);

/*
 * Cause all threads sleeping on the specified address to wake up.
 * Interrupts must be disabled.
 */
void thread_wakeup(const void *addr);
void thread_wakeup_single(const void *addr);
/*
 * Return nonzero if there are any threads sleeping on the specified
 * address. Meant only for diagnostic purposes.
 */
int thread_hassleepers(const void *addr);

/*
 * returns true (1) if the number of threads in the system is
 * equal to 1, otherwise returns fals (0).
 * 
 * Usage Note: if this function returns 0 (false), the actual thread
 * count in the system may have changed by the time the calling 
 * function is able to use the returned value.  Thus, a return value
 * of 0 provides little information to the caller.
 * However, if the return value is 1 (true), then the calling thread
 * is the only thread in the system.  Unless the caller itself
 * creates new threads (or unless the kernel spontaneously lauches
 * new threads, e.g., in response to interrupts), the caller will
 * know that it is the only thread in the system.
 *
 * This function is NOT intended for general use in the kernel.
 * It is intended to be used only to simplify the early
 * testing of the kernel.   Specifically, it is intended to be used
 * to allow the kernel's menu thread to wait for the completion of
 * a user-level program that it launches via the kernel menu "p"
 * command.  Once A2 has been completed there will probably be a
 * better way to make the menu thread wait, and this function will
 * no longer be needed.
 */
int one_thread_only(void);

/*
 * Private thread functions.
 */

/* Machine independent entry point for new threads. */
void mi_threadstart(void *data1, unsigned long data2, 
		    void (*func)(void *, unsigned long));

/* Machine dependent context switch. */
void md_switch(struct pcb *old, struct pcb *nu);


#endif /* _THREAD_H_ */
