#include "device_file.h"
#include <linux/init.h>       
#include <linux/module.h> 
#include <linux/time.h>    

MODULE_DESCRIPTION("CS6223_hw3");
MODULE_LICENSE("Duel BSD/GPL");


static int driver_init(void)
{
    int result = 0;
    
    struct timespec ts;
    getnstimeofday(&ts);
	
    
    printk(KERN_NOTICE "hw3: Initialization started\n" );

    printk(KERN_NOTICE "Hello world the time now is ""%02ld" ":""%02ld"":""%02ld GMT",(ts.tv_sec / 3600) % (24), 
					(ts.tv_sec / 60) % (60), ts.tv_sec % 60);
    result = register_device();
    return result;
}


static void driver_exit(void)
{
    printk( KERN_NOTICE "hw3: Exiting\n" );
    unregister_device();
}


module_init(driver_init);
module_exit(driver_exit);
