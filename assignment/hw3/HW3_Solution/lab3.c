#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#define BUFFER_LENGTH 50

static char msg[BUFFER_LENGTH];

void GetTime(int *phour, int *pmin, int *psec)
{
    long long ts;
    long long secs_per_day = 60*60*24;

	ts = ktime_get_real_seconds();

	ts = ts%secs_per_day;

	*phour = ts/3600;
	*pmin  = (ts-*phour*3600)/60;
	*psec  = (ts-*phour*3600-*pmin*60);

	/* subtract 4 hours to get eastern time (works only in summer) */
	*phour-=4;
	if(*phour<0) *phour=*phour+24;

}

static int device_open(struct inode *pinode, struct file *pfile){
	int hour, min, sec;

    GetTime(&hour, &min, &sec);

    /* Essentially printk with Kernel Info priority */
    pr_info("Device has been opened \n");

	sprintf(msg, "Hello world, the time now is %02d:%02d:%02d\n", hour, min, sec);

	return 0;
}

static ssize_t device_read(struct file* filp, char* buffer, size_t length, loff_t* offset){
	int remaininglength;
	int readlength;
	
	/* If offset equals length of string then stop reading */
	if (*offset == strlen(msg)){
		return 0;
	}
	
	/* Calculate the length of remaining string to read */
	remaininglength = strlen(msg) - *offset;
	
	readlength = remaininglength;

	if (remaininglength >= length){
		readlength = length;
	}
	
	copy_to_user(buffer, msg+*offset, readlength);
	*offset += readlength;
	
	return readlength;
}

static int device_release(struct inode *inode, struct file *file){
	pr_info("Device released \n");
	return 0;
}

static struct file_operations fops = {
  .open = device_open,
  .read = device_read,
  .release = device_release
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "lab3",
	.fops = &fops,
};

/* This function is called when the module is loaded. */
int device_init(void){
	int retval;
	if ((retval = misc_register(&misc))){
		printk(KERN_ERR "Failed to register device\n");
		return retval;
	}
	
	return 0;
}

/* This function is called when the module is removed. */
void device_exit(void){
	misc_deregister(&misc);
}

/* Macros for registering module entry and exit points. */
module_init(device_init)
module_exit(device_exit)

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Assignment 3 - CS-GY6233, Fall 2020");
MODULE_AUTHOR("Reuben Varghese");