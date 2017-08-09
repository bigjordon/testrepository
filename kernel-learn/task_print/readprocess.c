#include <linux/sched.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
//#define for_each_process(p) 
static int hello_init(void)
{
        struct task_struct *p;
        printk("名称\t进程号\t状态\t");
//      p=NULL;
        for_each_process(p)
        {
                printk("%s\t%d\t%ld\n",p->comm, p->pid, p->state);
        }
        return 0;
}
static void hello_exit(void)
{
        printk("hello world exit\n");
}
module_init(hello_init);//加载函数
module_exit(hello_exit);                //卸载函数
MODULE_LICENSE("GPL");  //许可证申明
MODULE_DESCRIPTION("hello module");

MODULE_AUTHOR("fromnetwork");
