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

#define JYAAC_CHARDEV_UNREGISTERED (-1)
#define JYAAC_DRIVER_FULL_VERSION (-2)

static int jyaac_cfg_major = JYAAC_CHARDEV_UNREGISTERED;
char jyaac_driver_version[] = JYAAC_DRIVER_FULL_VERSION;


static const struct pci_device_id aac_pci_tbl[]{
{ 0x9005, 0x028d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 }, /* Adaptec PMC Series 8 */
{ 0,}
}

int  aac_probe_one(struct pci_dev *dev, const struct pci_device_id *id)	/* New device inserted */
{

}

void aac_remove_one(struct pci_dev * pdev)
{

}

void aac_shutdown(struct pci_dev * dev)
{

}


static struct pci_driver aac_pci_driver = {
	.name		= AAC_DRIVERNAME,
	.id_table	= aac_pci_tbl,
	.probe		= aac_probe_one,
	.remove		= aac_remove_one,
#if (defined(CONFIG_PM))
	.suspend	= aac_suspend,
	.resume		= aac_resume,
#endif
	.shutdown	= aac_shutdown,
/*	.err_handler    = &aac_pci_err_handler, */
};


static int __init aac_init(void)
{
	int error;

	printk(KERN_INFO "Adaptec %s driver %s\n",
	  "aacarid_jy", "0.0.1");

	error = pci_register_driver(&aac_pci_driver);
	if (error < 0)
		return error;

	aac_init_char();


	return 0;
}

static void __exit aac_exit(void)
{
	if (aac_cfg_major > -1)
		unregister_chrdev(jyaac_cfg_major, "aac");
	pci_unregister_driver(&aac_pci_driver);
}

module_init(aac_init);
module_exit(aac_exit);


