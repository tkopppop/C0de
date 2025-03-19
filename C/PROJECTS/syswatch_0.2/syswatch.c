/*
  ############################################################

         Linux System Protection Project ( LSP2 )
              Ver Scenario #5

         Platform : LINUX 2.4.24 KERNEL
         Compilier : .. GCC-2.95.4 or GCC-3.33 ..

  ############################################################

 (Protect Features)
 1. RaceCondtion Bug
 2. Ptrace
 3. Gain root shell
 4. chroot break
 5. Socketcall Listen ACL
 
*/

/* Defining KERNEL MODULE */
#define MODULE
#define __KERNEL__

#define DEVICE_ "logwatch"

/* IOCTL Command */

// Driver Command(cmd)
#define DRIVER_DEC_COUNT		0
#define DRIVER_INC_COUNT		1
#define DRIVER_FUNC_CONT		2
#define DRIVER_SET_NSG			3
#define DRIVER_GET_FUNC			4
#define DRIVER_GET_OPT			5
#define DRIVER_GET_LOG_HIT	    6

// Driver Control Args(arg)
#define	SYMLINK_DISABLE 	 210
#define	SYMLINK_ENABLE		 211
#define	PTRACE_DISABLE		 220
#define	PTRACE_ENABLE		 221
#define	EXECVE_DISABLE		 230
#define	EXECVE_ENABLE		 231
#define	CHROOT_DISABLE		 240
#define	CHROOT_ENABLE		 241
#define	SOCKETCALL_DISABLE	 250
#define	SOCKETCALL_ENABLE	 251

#define	NO_ACT		0
#define	KILL		9
#define	SEGV		11
#define	DENY_LISTEN	13

// Module_pointer 
#define	MOD_SYMLINK	0
#define	MOD_PTRACE	1
#define	MOD_EXECVE	2
#define	MOD_CHROOT	3
#define	MOD_SOCKETCALL	4


#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/stat.h>
#include <linux/file.h>
#include <linux/utsname.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/mman.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/string.h>
#include <asm/module.h>
#include <sys/syscall.h>
#include <linux/delay.h>
#include <linux/ptrace.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/signal.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <asm/system.h>
#include <asm/processor.h>
#include <asm/pgtable.h>
#include <linux/config.h>
#include <linux/unistd.h>
#include <asm/unistd.h>
#include <linux/fs.h>
#include <linux/smp_lock.h>
#include <linux/cache.h>
#include <linux/socket.h>
#include <linux/vmalloc.h>
#include <linux/ide.h>
#include <asm/semaphore.h>
#include <asm/atomic.h>

extern void *sys_call_table[];
extern int path_lookup(const char *, unsigned, struct nameidata *);

long (*orig_symlink)(const char * oldname, const char * newname);
int (*orig_ptrace)(long request, long pid, long addr, long data);
int (*orig_execve)(struct pt_regs regs);
long (*orig_chroot)(const char * filename);
long (*orig_socketcall)(int call, unsigned long *args);

long (*orig_getcwd)(char *buf, unsigned long size);

/* Global Variables */
#define MAXFUNC 5
#define MAXOPT 2
#define MAXFIELD 7

static DECLARE_MUTEX(my_sem);

struct log_format{
        __u8    log_symlink:1,
                log_ptrace:1,
                log_execve:1,
                log_chroot:1,
                log_socketcall:1,
                res1:1,
                res2:1,
                res3:1;
unsigned long uid, gid, euid, egid, pid, action;
char MAGIC[4];
};

struct log_format *clog;

static unsigned long ioctl_func[MAXFUNC]={1,1,1,1,1};   // Default is All true. 
static unsigned long ioctl_option[MAXOPT]={0,3333}; // [0]: MODULE COUNT [1] : NSG
static unsigned long log_hit[2]={0,0};


ssize_t wrap_symlink(const char * oldname, const char * newname){
		if(down_trylock(&my_sem)) down_interruptible(&my_sem);
		 set_clog(MOD_SYMLINK, current->uid, current->gid, current->euid, current->egid, current->pid, NO_ACT);
         up(&my_sem);
 		 log_hit[0] = 1;

        __delay(1000000000);
        return orig_symlink(oldname, newname);
}

int wrap_ptrace(long request, long pid, long addr, long data){
        if(current->gid==0 || in_group_p(0)){  
                if(request == PTRACE_TRACEME){
					 	 if(down_trylock(&my_sem)) down_interruptible(&my_sem);
						 set_clog(MOD_PTRACE, current->uid, current->gid, current->euid, current->egid, current->pid, NO_ACT);
				         up(&my_sem);
						 log_hit[0] = 1;

				}

                return orig_ptrace(request, pid, addr, data);
                
        }
        else{

					 	 if(down_trylock(&my_sem)) down_interruptible(&my_sem);
 						 set_clog(MOD_PTRACE, current->uid, current->gid, current->euid, current->egid, current->pid, KILL);
						 up(&my_sem);
						 log_hit[0] = 1;

				send_sig(SIGKILL, current, SIGKILL);
				return(-90);
        }

}


int wrap_execve(struct pt_regs regs){
int error;
char * filename;

if((current->uid==0 || current->gid==0 || current->euid==0 || current->egid==0) && 
  !(current->uid == 0 && current->uid == current->gid && current->gid == current->euid && current->euid == current->egid)){


        if(current->p_pptr->uid != 0){
			 if(down_trylock(&my_sem)) down_interruptible(&my_sem);
			 set_clog(MOD_EXECVE, current->uid, current->gid, current->euid, current->egid, current->pid, SEGV);
			 up(&my_sem);
			 log_hit[0] = 1;

        send_sig(SIGSEGV, current, SIGSEGV);
        return(-90);
        }

}
else{
      filename = getname((char *) regs.ebx);
      error = PTR_ERR(filename);
       if (IS_ERR(filename))
               goto out;
       error = do_execve(filename, (char **) regs.ecx, (char **) regs.edx, &regs);
       if (error == 0)
              current->ptrace &= ~PT_DTRACE;
       putname(filename);
}

out: return error;
}

long wrap_chroot(const char * filename){
char setdir[5];
struct vfsmount *pwdmnt, *rootmnt;
struct dentry *pwd, *root; 
struct nameidata *nd;
struct dentry *dir;

pwdmnt = mntget(current->fs->pwdmnt); 
pwd = dget(current->fs->pwd); 

	copy_from_user(setdir, filename, 5);
	
	if(strcmp(pwd->d_name.name, "/")){
				 	 if(down_trylock(&my_sem)) down_interruptible(&my_sem);
					 set_clog(MOD_CHROOT, current->uid, current->gid, current->euid, current->egid, current->pid, KILL);
					 up(&my_sem);
					 log_hit[0] = 1;

			send_sig(SIGKILL, current, SIGKILL);
            return(-90);
        }
        
	return orig_chroot(filename);

}


#define AL(x) ((x) * sizeof(unsigned long))
static unsigned char nargs[18]={AL(0),AL(3),AL(3),AL(3),AL(2),AL(3),
                                AL(3),AL(3),AL(4),AL(4),AL(4),AL(6),
                                AL(6),AL(2),AL(5),AL(5),AL(3),AL(3)};
#undef AL


// NSG(Non-Server-Group) is Don't Permit listen(socket) Function

long wrap_socketcall(int call, unsigned long *args){
	
    switch(call)
    {
            case SYS_LISTEN:
		if(current->uid==0 || (int)current->user->processes.counter == 1){
                 // Reserved.
                }else if(in_group_p(ioctl_option[1])){
					if(down_trylock(&my_sem)) down_interruptible(&my_sem);
					 set_clog(MOD_SOCKETCALL, current->uid, current->gid, current->euid, current->egid, current->pid, DENY_LISTEN);
					 up(&my_sem);
					 log_hit[0] = 1;

					return(-1);
			}
            break;
        }
        return orig_socketcall(call, args);

}




int set_clog(unsigned int log_bit, unsigned long uid, unsigned long gid, unsigned long euid, unsigned long egid, unsigned long pid, unsigned long action){

memset(clog, 0x0, sizeof(struct log_format));

	switch(log_bit){
		case	90 : break;
		case	0 : clog->log_symlink = 1;
					break;
		case	1 : clog->log_ptrace = 1;
					break;
		case	2 : clog->log_execve = 1;
					break;
		case	3 : clog->log_chroot = 1;
					break;
		case	4 : clog->log_socketcall = 1;
					break;
	}

clog->uid = uid;
clog->gid = gid;
clog->euid = euid;
clog->egid = egid;
clog->pid = pid;
clog->action = action;

clog->MAGIC[0]='x';
clog->MAGIC[1]='9';
clog->MAGIC[2]='0';
clog->MAGIC[3]='c';

return(0);
}

static int dev_write(void){
printk(KERN_DEBUG "write\n");
return 0;
}

static int dev_read(struct file *file, struct log_format *log, size_t nbytes, loff_t *ppos){
	__copy_to_user(log, clog, sizeof(struct log_format));
	return 0;
}

static int dev_ioctl(struct inode *inode, struct file *file, unsigned int cmd, void *arg){
int pid;

lock_kernel();
		switch(cmd){
			case    DRIVER_DEC_COUNT : MOD_DEC_USE_COUNT;  
									   ioctl_option[0]--;
									   break;
            case    DRIVER_INC_COUNT : MOD_INC_USE_COUNT;  
                                       ioctl_option[0]++;
                                       break;
            case    DRIVER_FUNC_CONT : 
					switch ((int)arg){ // ON/OFF Module 
						    case SYMLINK_DISABLE : 
								sys_call_table[SYS_symlink] = orig_symlink;
								ioctl_func[0] = 0;
                                break;
                            case SYMLINK_ENABLE : 
								sys_call_table[SYS_symlink] = wrap_symlink;
								ioctl_func[0] = 1;
                                break;
		                    case PTRACE_DISABLE : 
								sys_call_table[SYS_ptrace] = orig_ptrace;
								ioctl_func[1] = 0;
                                break;
                            case PTRACE_ENABLE : 
								sys_call_table[SYS_ptrace] = wrap_ptrace;
								ioctl_func[1] = 1;
                                break;
                            case EXECVE_DISABLE : 
								sys_call_table[SYS_execve] = orig_execve;
								ioctl_func[2] = 0;
                                break;
				            case EXECVE_ENABLE : 
								sys_call_table[SYS_execve] = wrap_execve;
								ioctl_func[2] = 1;
                                break;
		                    case CHROOT_DISABLE : 
								sys_call_table[SYS_chroot] = orig_chroot;
								ioctl_func[3] = 0;
                                break;
                            case CHROOT_ENABLE : 
								sys_call_table[SYS_chroot] = wrap_chroot;
								ioctl_func[3] = 1;
                                break;
                            case SOCKETCALL_DISABLE : 
								sys_call_table[SYS_socketcall] = orig_socketcall;
								ioctl_func[4] = 0;
                                break;
                            case SOCKETCALL_ENABLE : 
								sys_call_table[SYS_socketcall] = wrap_socketcall;
								ioctl_func[4] = 1;
                                break;
                            }
                            return((int)arg);

                        case    DRIVER_SET_NSG : 
									ioctl_option[1] = (int)arg;
                                    break;
                        case    DRIVER_GET_FUNC : 
									__copy_to_user(arg, ioctl_func, sizeof(ioctl_func));
                                    break;
	  				    case    DRIVER_GET_OPT : 
									__copy_to_user(arg, ioctl_option, sizeof(ioctl_option));
	  					  	        break;
						case	DRIVER_GET_LOG_HIT :
									__copy_to_user(arg, log_hit, sizeof(log_hit));
									log_hit[0]=0;
									break;
        }

unlock_kernel();
return(cmd);

}

static int dev_open(struct inode *node, struct file *file){
	return 0;
}

static int dev_close(struct inode *node, struct file *file){
	return 0;
}


struct file_operations fops = {
NULL,
dev_write,
dev_read,
NULL,
NULL,
NULL,
dev_ioctl,
NULL,
dev_open,
NULL,
dev_close
};




/* Driver EntryPoint(EP...) */
int __init DriverEntry(void){

	init_MUTEX(&my_sem); 
	
	clog = vmalloc(sizeof(struct log_format));

	set_clog(90, 0, 0, 0, 0, 0, NO_ACT);

	printk(KERN_DEBUG "SYS-WATCH /dev/logwatch Device Register\n");

    if(register_chrdev(213, DEVICE_, &fops)<0) return -1;

        printk(KERN_DEBUG "SYS-WATCH Module -- Started..\n");
		
        orig_symlink = sys_call_table[SYS_symlink];
        sys_call_table[SYS_symlink] = wrap_symlink;

        orig_ptrace = sys_call_table[SYS_ptrace];
        sys_call_table[SYS_ptrace] = wrap_ptrace;

        orig_execve = sys_call_table[SYS_execve];
        sys_call_table[SYS_execve] = wrap_execve;

        orig_chroot = sys_call_table[SYS_chroot];
        sys_call_table[SYS_chroot] = wrap_chroot;

        orig_getcwd = sys_call_table[SYS_getcwd];

        orig_socketcall = sys_call_table[SYS_socketcall];
        sys_call_table[SYS_socketcall] = wrap_socketcall;

return 0;
}

/* Driver Ending... (Point not important for hackers) */
void __exit DriverX(void){
	
	if(down_trylock(&my_sem)) down_interruptible(&my_sem);
		vfree(clog);
	up(&my_sem);
	
        sys_call_table[SYS_symlink] = orig_symlink;
        sys_call_table[SYS_ptrace] = orig_ptrace;
        sys_call_table[SYS_execve] = orig_execve;
        sys_call_table[SYS_chroot] = orig_chroot;
        sys_call_table[SYS_socketcall] = orig_socketcall;

	printk(KERN_DEBUG "SYS-WATCH /dev/logwatch Device Unload\n");
	unregister_chrdev(213, DEVICE_);

	printk(KERN_DEBUG "SYS-WATCH Module -- Halted..\n");


}

module_init(DriverEntry);
module_exit(DriverX);

/* License GPL */
MODULE_LICENSE("GPL"); 

// LGPL? also *1yes

// EoF

// EoC

// EoM

// EoB

// EoBits

