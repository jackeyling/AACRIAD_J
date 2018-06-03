/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.	<alan@redhat.com>
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver for Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc. (aacraid@adaptec.com)
 * Copyright (c) 2010-2015 PMC-Sierra, Inc.
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
 *  adbg.h
 *
 * Abstract: Contains all routines for control of the debug data.
 *
 */

#ifndef _ADBG_H_
#define _ADBG_H_



/*Used to suppress unused variable warning*/
#define UNUSED(x)       (void)(x)

#define FLAG_SIZE(x)	((uint64_t)x)

#define AAC_STATUS_INFO                 FLAG_SIZE(1<<0)
#define AAC_DEBUG_INIT                  FLAG_SIZE(1<<1)
#define AAC_DEBUG_SETUP                 FLAG_SIZE(1<<2)
#define AAC_DEBUG_TIMING                FLAG_SIZE(1<<3)
#define AAC_DEBUG_AIF                   FLAG_SIZE(1<<4)
#define AAC_DEBUG_IOCTL                 FLAG_SIZE(1<<5)
#define AAC_DEBUG_IOCTL_SENDFIB         FLAG_SIZE(1<<6)
#define AAC_DEBUG_AAC_CONFIG            FLAG_SIZE(1<<7)
#define AAC_DEBUG_RESET                 FLAG_SIZE(1<<8)
#define AAC_DEBUG_FIB                   FLAG_SIZE(1<<9)
#define AAC_DEBUG_CONTEXT               FLAG_SIZE(1<<10)
#define AAC_DEBUG_2TB                   FLAG_SIZE(1<<11)
#define AAC_DEBUG_SENDFIB               FLAG_SIZE(1<<12)
#define AAC_DEBUG_IO                    FLAG_SIZE(1<<13)
#define AAC_DEBUG_PENDING               FLAG_SIZE(1<<14)
#define AAC_DEBUG_SG                    FLAG_SIZE(1<<15)
#define AAC_DEBUG_SG_PROBE              FLAG_SIZE(1<<16)
#define AAC_DEBUG_VM_NAMESERVE          FLAG_SIZE(1<<17)
#define AAC_DEBUG_SERIAL                FLAG_SIZE(1<<18)
#define AAC_DEBUG_SYNCHRONIZE           FLAG_SIZE(1<<19)
#define AAC_DEBUG_SHUTDOWN              FLAG_SIZE(1<<20)
#define AAC_DEBUG_MSIX                  FLAG_SIZE(1<<21)
#define AAC_DEBUG_LOG			FLAG_SIZE(1<<22)

/*
 * 23 to 31 bits are for future debug
 */

#define AAC_PCI_HAS_MSI			FLAG_SIZE(1<<32)
#define AAC_SUPPORTED_POWER_MANAGEMENT  FLAG_SIZE(1<<33)
#define AAC_SUPPORTED_JBOD		FLAG_SIZE(1<<34)
#define AAC_BOOTCD			FLAG_SIZE(1<<35)
#define AAC_SCSI_HAS_DUMP		FLAG_SIZE(1<<36)
#define AAC_SCSI_HAS_VARY_IO		FLAG_SIZE(1<<37)
#define AAC_SAI_READ_CAPACITY_16	FLAG_SIZE(1<<38)
#define AAC_FWPRINTF			FLAG_SIZE(1<<39)
#define AAC_DPRINTK			FLAG_SIZE(1<<40)

#define LOG_SETUP  (AAC_DEBUG_INIT| AAC_DEBUG_IOCTL)

//#define CONFIG_SCSI_AACRAID_LOGGING
#define CONFIG_SCSI_AACRAID_LOGGING_PRINTK


#ifdef CONFIG_SCSI_AACRAID_LOGGING
#define AAC_CHECK_LOGGING(DEV, BITS, LVL, TEST, ...)   \
({                                          \
    if(DEV->logging_level & BITS)           \
    {                                       \
      printk(LVL "%s%u: " TEST,DEV->name,DEV->id, ##__VA_ARGS__);      \
     fwprintf((DEV, HBA_FLAGS_DBG_FW_PRINT_B, ##__VA_ARGS__));\
    }\
})
#elif  defined(CONFIG_SCSI_AACRAID_LOGGING_PRINTK)
#define AAC_CHECK_LOGGING(DEV, BITS, LVL, TEST, ...) \
({                                              \
	printk(LVL "%s:%s%u: " TEST,AAC_DRIVERNAME,DEV->name,DEV->id,##__VA_ARGS__);        \
})
#else
#define AAC_CHECK_LOGGING(DEV, BITS, CMD, TEST,...)
#endif


#define adbg_dev() \
    printk(KERN_ERR,"Line-%d,Function-%s,File-%s",__LINE__,__FUNCTION__,__FILE__);

#define adbg(DEV, LVL, TEST,...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_LOG, LVL, TEST, ##__VA_ARGS__)

#if defined(AAC_DETAILED_STATUS_INFO)
#define adbg_info(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_STATUS_INFO, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_info(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_INIT)
#define adbg_init(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_INIT,  LVL, TEST,##__VA_ARGS__)
#else
#define     adbg_init(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SETUP)
#define adbg_setup(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_SETUP, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_setup(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_TIMING)
#define adbg_time(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_TIMING,  LVL, TEST,##__VA_ARGS__)
#else
#define adbg_time(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_AIF)
#define adbg_aif(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_AIF, LVL ,TEST,##__VA_ARGS__)
#else
#define adbg_aif(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_IOCTL)
#define adbg_ioctl(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_IOCTL, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_ioctl(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_IOCTL_SENDFIB)
#define adbg_ioctl_sendfib(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_IOCTL_SENDFIB, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_ioctl_sendfib(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_AAC_CONFIG)
#define adbg_conf(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_AAC_CONFIG, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_conf(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_RESET)
#define adbg_reset(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_RESET, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_reset(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_FIB)
#define adbg_fib(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_FIB, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_fib(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_CONTEXT)
#define adbg_context(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_CONTEXT, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_context(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_2TB)
#define adbg_2tb(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_2TB,  LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_2tb(DEV, LVL, TEST, ...)
#endif


#if defined(AAC_DEBUG_INSTRUMENT_SENDFIB)
#define adbg_sendfib(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_SENDFIB, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_sendfib(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_IO)
#define adbg_io(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_IO, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_io(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_PENDING)
#define adbg_pending(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_PENDING, LVL, TEST,  ##__VA_ARGS__)
#else
#define adbg_pending(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SG)
#define adbg_sg(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_SG,  LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_sg(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SG_PROBE)
#define adbg_sg_probe(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,  AAC_DEBUG_SG_PROBE,  LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_sg_probe(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_VM_NAMESERVE)
#define adbg_vm(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_VM_NAMESERVE, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_vm(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SERIAL)
#define adbg_serial(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV,AAC_DEBUG_SERIAL, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_serial(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SYNCHRONIZE)
#define adbg_sync(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_SYNCHRONIZE, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_sync(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_SHUTDOWN)
#define adbg_shut(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_SHUTDOWN, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_shut(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_MSIX)
#define adbg_msix(DEV, LVL, TEST, ...) \
    AAC_CHECK_LOGGING(DEV, AAC_DEBUG_MSIX, LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_msix(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_FIB) || defined(AAC_DEBUG_INSTRUMENT_MSIX)
#define adbg_fib_or_msix(DEV, LVL,TEST, ...) \
    AAC_CHECK_LOGGING(DEV, (AAC_DEBUG_FIB|AAC_DEBUG_MSIX), LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_fib_or_msix(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_IOCTL) && defined(AAC_DEBUG_INSTRUMENT_AIF)
#define adbg_ioctl_and_aif(DEV, LVL, TEST, ...)\
    AAC_CHECK_LOGGING(DEV, (AAC_DEBUG_IOCTL|AAC_DEBUG_AIF), LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_ioctl_and_aif(DEV, LVL, TEST, ...)
#endif

#if defined(AAC_DEBUG_INSTRUMENT_INIT) && defined(AAC_DEBUG_INSTRUMENT_VM_NAMESERVE)
#define adbg_init_or_vm(DEV, LVL, TEST, ...)\
    AAC_CHECK_LOGGING(DEV, (AAC_DEBUG_INIT|AAC_DEBUG_VM), LVL, TEST, ##__VA_ARGS__)
#else
#define adbg_init_or_vm(DEV, LVL, TEST, ...)
#endif


#define aac_emerg(a, fmt, ...)\
	dev_emerg(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_alert(a, fmt, ...)\
	dev_alert(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_crit(a, fmt, ...)\
	dev_crit(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_err(a, fmt, ...)\
	dev_err(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_warn(a, fmt, ...)\
	dev_warn(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_notice(a, fmt, ...)\
	dev_notice(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)
#define aac_info(a, fmt, ...)\
	dev_info(&(a)->pdev->dev,"%s%d:"fmt,a->name,a->id,##__VA_ARGS__)
#define aac_dbg(a, fmt, ...)\
	dev_dbg(&(a)->pdev->dev,"%s%d:%s:"fmt,a->name,a->id,__FUNCTION__,##__VA_ARGS__)


/********** Below contains struct definitions  ***********/
struct scsi_cmnd;
struct aac_dev;

/********** Use below section for adding debug routines & macros ***********/
#if defined(AAC_DEBUG_INSTRUMENT_RESET)

void dump_pending_fibs(struct aac_dev *aac, struct scsi_cmnd *cmd);
int dump_command_queue(struct scsi_cmnd* cmd);

#define DBG_OVERFLOW_CHK(dev, vno) \
{\
	if(atomic_read(&dev->rrq_outstanding[vno]) > dev->vector_cap)\
		adbg_reset(dev, KERN_ERR, \
		"%s:%d, Host RRQ overloaded vec: %u, Outstanding IOs: %u\n",\
		__FUNCTION__,__LINE__, \
		vno,\
		atomic_read(&dev->rrq_outstanding[vno])); \
}
#define DBG_SET_STATE(FIB, S)	atomic_set(&FIB->state, S);
#define adbg_dump_pending_fibs(AAC, CMD) dump_pending_fibs(AAC, CMD)
#define adbg_dump_command_queue(CMD) dump_command_queue(CMD)
#else
#define DBG_SET_STATE(FIB, S)
#define DBG_OVERFLOW_CHK(dev, vno)
#define adbg_dump_pending_fibs(AAC, CMD)
#define adbg_dump_command_queue(CMD) (0)
#endif


#if defined(AAC_DEBUG_INSTRUMENT_TIMING)

void queuecmd_debug_timing(struct scsi_cmnd *cmd);

#define adbg_queuecmd_debug_timing(CMD) queuecmd_debug_timing(CMD)
#else
#define adbg_queuecmd_debug_timing(CMD)
#endif

#if (defined(AAC_DEBUG_INSTRUMENT_AAC_CONFIG))

void debug_aac_config(struct scsi_cmnd* scsicmd, __le32 count,
                      unsigned long byte_count);

#define adbg_debug_aac_config(CMD,COUNT,BYTE_COUNT) \
            debug_aac_config(CMD,COUNT,BYTE_COUNT)
#else
#define adbg_debug_aac_config(CMD,COUNT,BYTE_COUNT)
#endif

#endif


