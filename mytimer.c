#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mary Lukyanova");
MODULE_VERSION("0.01");

static struct timer_list my_timer;
static int delay = 7;
static int times_left = 4;

static void print_text(unsigned long data)
{
	if (times_left > 0) {
		printk(KERN_INFO "U r in lab 6\n");
		times_left--;
	} 
	//jiffies определяет количество временных тиков (тактов)
	//, прошедших после загрузки системы	
	mod_timer(&my_timer, jiffies + delay * HZ);
}

static ssize_t mytimer_read(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", times_left);
}

static ssize_t mytimer_write(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%d", &times_left);
	return count;
}


static int mytimer_init(void)
{
	return 0;
}

static void mytimer_exit(void)
{	

}

module_init(mytimer_init);
module_exit(mytimer_exit);
