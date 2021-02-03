/*
This homework requires you to develop a Linux kernel module including print hello world things and current
time while inserting and quitting the module.
This homework contains c file and Makefile, c file is to describe the module and Makefile is to launch it.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/time.h>

MODULE_LICENSE("Dual BSD/GPL");   //Your should not change the license
MODULE_AUTHOR("Bryan_flx");       //Please modify this part or delete it
MODULE_DESCRIPTION("CS6233_hw2"); //Information could be modified or deleted



static int hello_init(void)
	{
/****code used to extract the time and convert it into required format********/
		struct timespec ts;      //difine the timespec
		getnstimeofday(&ts);		 //use getnstimeofday to acquire time
		printk(KERN_ALERT "%02ld" ":""%02ld"":""%02ld GMT",(ts.tv_sec / 3600) % (24),
					(ts.tv_sec / 60) % (60), ts.tv_sec % 60);		//print the timespec in format


		printk(KERN_ALERT "Hello, world\n");

		return 0;
	}


static void hello_exit(void)
	{
/************same process as above to extract time*****************************/
		struct timespec ts;
		getnstimeofday(&ts);
		printk(KERN_ALERT "%02ld" ":""%02ld"":""%02ld GMT",(ts.tv_sec / 3600) % (24),
					(ts.tv_sec / 60) % (60), ts.tv_sec % 60);

		printk(KERN_ALERT "Goodbye, cruel world\n");
	}


module_init(hello_init);
module_exit(hello_exit);
