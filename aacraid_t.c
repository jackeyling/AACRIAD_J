/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver for Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Module Name:
 *   aacraid_t.c
 *
 * Abstract: Linux Driver entry module for Adaptec RAID Array Controller
 */


#include <linux/compat.h>
#include <linux/blkdev.h>
#include <linux/completion.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/aer.h>
#include <linux/pci-aspm.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include <scsi/scsi.h>
#include <scsi/scsi_cmnd.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_tcq.h>
#include <scsi/scsicam.h>
#include <scsi/scsi_eh.h>

#include "aacraid_t.h"

#define AAC_CHARDEV_UNREGISTERED (-1)
#define AAC_DRIVER_FULL_VERSION (-2)

static int aac_cfg_major = AAC_CHARDEV_UNREGISTERED;
char aac_driver_version[] = "0.0.1";


struct list_head aac_devices;
LIST_HEAD(aac_devices);


static const struct pci_device_id aac_pci_tbl[]= {
{ 0x9005, 0x028d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 }, /* Adaptec PMC Series 8 */
{ 0,}
};
MODULE_DEVICE_TABLE(pci,aac_pci_tbl);


static int aac_probe_one(struct pci_dev *pdev, const struct pci_device_id *id)	/* New device inserted */
{
	unsigned index = id->driver_data;
	struct Scsi_host *shost;
	struct aac_dev *aac;
	struct list_head *insert = &aac_devices;
	int error = -ENODEV;
	int unique_id = 0;
	u32 i = 0;
	u32 nr_cpu = 0;
    
    printk(KERN_INFO, "enter aac_probe_one %d  unique_id %d", __LINE__, unique_id);
	
    list_for_each_entry(aac,&aac_devices, entry){
		printk(KERN_INFO "aac_probe unique_id: %d", unique_id);
		if(aac->id > unique_id)
			break;
		insert = &aac->entry;
		unique_id++;
	}
    
    pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
					PCIE_LINK_STATE_CLKPM);
	
    error = pci_enable_device(pdev);
	if(error){
		printk(KERN_ERR " %s: PCI deivce not enabled", __FUNCTION__ );
		goto out;
	}


	out:
		return error;	
	
}

void aac_remove_one(struct pci_dev * pdev)
{

}

void aac_shutdown(struct pci_dev * dev)
{

}


static struct pci_driver aac_pci_driver = {
	.name		= "aacraid",
	.id_table	= aac_pci_tbl,
	.probe		= aac_probe_one,
	.remove		= aac_remove_one,
//#if (defined(CONFIG_PM))
//	.suspend	= aac_suspend,
//	.resume		= aac_resume,
//#endif
	.shutdown	= aac_shutdown,
//	.err_handler    = &aac_pci_err_handler, 
};


static void aac_init_char(void)
{
	return 0;
}


static int __init aac_init(void)
{
	int error;

	printk(KERN_INFO "Adaptec %s driver %s\n","aacarid", "0.0.1");

    error = pci_register_driver(&aac_pci_driver);
    
    printk(KERN_INFO "aac_init register error :%d", error);

	if (error < 0 || list_empty(&aac_devices)){
		
        if(error >= 0){
			pci_unregister_driver(&aac_pci_driver);
		}
		return error;
	}
    printk(KERN_INFO "Adaptic probe init end!! %d", __LINE__);
    //aac_init_char();

	return 0;
}

static void __exit aac_exit(void)
{
	//if (aac_cfg_major > -1)
	//	unregister_chrdev(aac_cfg_major, "aac");
	//pci_unregister_driver(&aac_pci_driver);
	printk(KERN_INFO "aacraid aac_exit");
}

module_init(aac_init);
module_exit(aac_exit);

MODULE_AUTHOR("Jackey Ling <jackey.ling@microchip.com>");
MODULE_DESCRIPTION("Aacraid driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:HBA1000");

