
/*
 * board/khadas/configs/kvim2.h
 *
 * Copyright (C) 2019 Wesion, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __KVIM2_H__
#define __KVIM2_H__

#ifndef __SUSPEND_FIRMWARE__
#include <asm/arch/cpu.h>
#endif		/* for compile problem of A53 and m3 */

#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef __SUSPEND_FIRMWARE__
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif
#endif		/* for compile problem of A53 and m3 */

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCKA_INIT_VOLTAGE	1120		// cluster_0 Big cpu
#define CONFIG_VCCKB_INIT_VOLTAGE	1050		// cluster_1 Little cpu
#define CONFIG_VDDEE_INIT_VOLTAGE	1000		// voltage for power up
#define CONFIG_VDDEE_SLEEP_VOLTAGE	 850		// voltage for suspend

/* configs for CEC */
#define CONFIG_CEC_OSD_NAME		"Kvim2"
#define CONFIG_CEC_WAKEUP
#define CONFIG_BT_WAKEUP
#define CONFIG_INSTABOOT

/* Khadas commands */
#define CONFIG_KHADAS_KBI 1
#define CONFIG_KHADAS_CFGLOAD 1
#define CONFIG_KHADAS_SCRIPT 1

#ifdef CONFIG_OF_LIBFDT_OVERLAY
#undef CONFIG_OF_LIBFDT_OVERLAY
#endif

/* support ext4*/
#define CONFIG_CMD_EXT4 1

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#define CONFIG_BOOTLOADER_CONTROL_BLOCK

#define CONFIG_CMD_SARADC 1
#define CONFIG_SARADC_CH  0
#define CONFIG_PHY_REALTEK 1

/*a/b update */
/*#define CONFIG_CMD_BOOTCTOL_DEFAULT 1*/
#define CONFIG_CMD_BOOTCTOL_AVB

/* SMP Definitinos */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

//Enable ir remote wake up for bl30
//#define CONFIG_IR_REMOTE
//#define CONFIG_AML_IRDETECT_EARLY
#define CONFIG_IR_REMOTE_POWER_UP_KEY_CNT 4
#define CONFIG_IR_REMOTE_USE_PROTOCOL 0         // 0:nec  1:duokan  2:Toshiba 3:rca 4:rcmm
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0XEB14FF00 //khadas ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0Xffffffff //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xffffffff //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0xBA45BD02

#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xffffffff
/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=0\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=1080000\0"\
        "outputmode=1080p60hz\0" \
        "hdmimode=1080p60hz\0" \
        "colorattribute=444,8bit\0"\
        "cvbsmode=576cvbs\0" \
        "display_width=1920\0" \
        "display_height=1080\0" \
        "display_bpp=16\0" \
        "display_color_index=16\0" \
        "display_layer=osd1\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
        "dtb_mem_addr=0x1000000\0" \
        "fb_addr=0x3d800000\0" \
        "fb_width=1920\0" \
        "fb_height=1080\0" \
        "sdr2hdr=0\0" \
        "usb_burning=update 1000\0" \
        "otg_device=1\0"\
        "fdt_high=0x20000000\0"\
        "try_auto_burn=update 700 750;\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "sdc_burning=sdc_burn ${sdcburncfg}\0"\
        "wipe_data=successful\0"\
        "wipe_cache=successful\0"\
        "EnableSelinux=enforcing\0"\
        "recovery_part=recovery\0"\
        "lock=10001000\0"\
        "recovery_offset=0\0"\
        "cvbs_drv=0\0"\
        "active_slot=normal\0"\
        "boot_part=boot\0"\
        "reboot_mode_android=""normal""\0"\
        "fs_type=""rootfstype=ramfs""\0"\
        "initargs="\
            "root=LABEL=ROOTFS rootflags=data=writeback rw console=ttyS0,115200n8 console=tty0 no_console_suspend consoleblank=0 fsck.repair=yes net.ifnames=0 "\
            "\0"\
        "upgrade_check="\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then "\
                "run init_display; run storeargs; run update;"\
            "else fi;"\
            "\0"\
        "storeargs="\
            "setenv bootargs ${initargs} logo=${display_layer},loaded,${fb_addr},${outputmode} maxcpus=${maxcpus} vout=${outputmode},enable hdmimode=${hdmimode} cvbsmode=${cvbsmode} hdmitx=${cecconfig} ddr_size=${ddr_size} cvbsdrv=${cvbs_drv} jtag=${jtag} fan=${fan_mode}; "\
            "run cmdline_keys;"\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
                    "run update;"\
            "else if test ${reboot_mode} = quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                    "setenv reboot_mode_android ""normal"";"\
                    "run storeargs;"\
            "else if test ${reboot_mode} = fastboot; then "\
                "setenv reboot_mode_android ""normal"";"\
                "run storeargs;"\
                "fastboot;"\
            "fi;fi;fi;fi;fi;fi;"\
            "\0" \
        "storeboot="\
            "kbi resetflag 0;"\
            "run setup_ethmac; " \
            "cfgload;" \
            "if load mmc 0:1 1020000 s905_autoscript || load mmc 1:1 1020000 s905_autoscript || load mmc 1:5 1020000 /boot/s905_autoscript; then autoscr 1020000; fi;"\
            "ext4load mmc 1:5 1080000 zImage;ext4load mmc 1:5 10000000 uInitrd;ext4load mmc 1:5 20000000 dtb.img;booti 1080000 10000000 20000000;" \
            "run update;"\
            "\0"\
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run sdc_burning; "\
            "if mmcinfo; then "\
                "run recovery_from_sdcard;"\
            "fi;"\
            "if usb start 0; then "\
                "run recovery_from_udisk;"\
            "fi;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_sdcard="\
            "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
            "if fatload mmc 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload mmc 0 ${loadaddr} recovery.img; then "\
                    "if fatload mmc 0 ${dtb_mem_addr} dtb.img; then echo sd dtb.img loaded; fi;"\
                    "wipeisb; "\
                    "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_udisk="\
            "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
            "if fatload usb 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload usb 0 ${loadaddr} recovery.img; then "\
                "if fatload usb 0 ${dtb_mem_addr} dtb.img; then echo udisk dtb.img loaded; fi;"\
                "wipeisb; "\
                "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_flash="\
            "get_valid_slot;"\
            "echo active_slot: ${active_slot};"\
            "if test ${active_slot} = normal; then "\
                "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
                "if itest ${upgrade_step} == 3; then "\
                    "if ext4load mmc 1:2 ${dtb_mem_addr} /recovery/dtb.img; then echo cache dtb.img loaded; fi;"\
                    "if ext4load mmc 1:2 ${loadaddr} /recovery/recovery.img; then echo cache recovery.img loaded; wipeisb; bootm ${loadaddr}; fi;"\
                "else fi;"\
                "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
            "else "\
                "setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
                "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "fi;"\
            "\0"\
        "init_display="\
            "get_rebootmode;"\
            "echo reboot_mode:::: ${reboot_mode};"\
            "if test ${reboot_mode} = quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "osd open;osd clear;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv reboot_mode_android ""quiescent"";"\
                    "run storeargs;"\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "osd open;osd clear;"\
            "else "\
                "setenv reboot_mode_android ""normal"";"\
                "run storeargs;"\
                "hdmitx get_preferred_mode;"\
                "hdmitx edid;"\
                "hdmitx hpd;"\
                "osd open;osd clear;imgread pic logo bootup $loadaddr;bmp display $bootup_offset;bmp scale; "\
            "fi;fi;"\
            "\0"\
        "cmdline_keys="\
            "if keyman init 0x1234; then "\
                "if keyman read usid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
                    "setenv serial ${usid};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.serialno=1234567890;"\
                    "setenv serial 1234567890;"\
                "fi;"\
                "if keyman read mac ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} mac=${mac} androidboot.mac=${mac};"\
                "fi;"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
            "fi;"\
            "\0"\
        "combine_key="\
            "saradc open 0;"\
            "if saradc get_in_range 0x0 0x92; then "\
                "echo Detect function key;"\
                "if gpio input GPIOAO_2; then "\
                    "echo Detect combine keys;"\
                    "store init 3; " \
                "fi;"\
            "fi;"\
            "\0"\
        "upgrade_key="\
             "if gpio input GPIOAO_2; then "\
                 "echo detect upgrade key; sleep 3;"\
                 "if gpio input GPIOAO_2; then run update; fi;"\
             "fi;"\
             "\0"\
        "vim2_check="\
             "kbi hwver; "\
             "if test ${hwver} != Unknow; then " \
                 "echo Product checking: pass! Hardware version: ${hwver};" \
             "else " \
                 "echo Product checking: fail!; sleep 5; reboot;" \
             "fi;" \
             "setenv bootargs ${bootargs} hwver=${hwver};"\
             "\0"\
        "wol_init="\
             "kbi init;"\
             "kbi powerstate;"\
             "kbi trigger wol r;"\
             "setenv bootargs ${bootargs} wol_enable=${wol_enable};"\
             "if test ${power_state} = 1; then "\
             "kbi trigger wol w 1;"\
             "gpio set GPIODV_2;"\
             "fi;"\
             "\0"\
        "setup_ethmac=" \
             "kbi ethmac;" \
             "if test X${custom_ethmac} != X; then " \
                 "echo Found custom ethmac: ${custom_ethmac}, overwrite eth_mac!; " \
                 "setenv eth_mac ${custom_ethmac}; " \
             "fi;" \
             "setenv bootargs ${bootargs} mac=${eth_mac} androidboot.mac=${eth_mac};"\
             "\0" \
        "uboot_update_check=" \
             "get_rebootmode;" \
             "print reboot_mode;" \
             "if test ${reboot_mode} = uboot_updated; then "\
                 "echo u-boot updated, pass to kernel...;" \
                 "env default -a;" \
                 "saveenv;" \
             "else "\
                 "if test -e mmc 1:5 /usr/lib/u-boot/.UBOOT-NEED-UPDATE; then " \
                     "echo New u-boot found!Try to upgrade u-boot...;" \
                     "if load mmc 1:5 1080000 /usr/lib/u-boot/u-boot.bin; then " \
                         "store rom_write 1080000 0 $filesize;" \
                         "store erase partition env;"\
                         "echo u-boot upgrade done, reboot...;" \
                         "reboot uboot_updated;" \
                     "fi;"\
                 "fi;"\
             "fi;"\
             "\0" \
        "updateu="\
             "tftp 1080000 u-boot.bin;"\
             "mmc dev 1;"\
             "store rom_write 1080000 0 ${filesize}"\
             "\0" 

#define CONFIG_PREBOOT  \
            "run upgrade_check;"\
            "run init_display;"\
            "run storeargs;"\
            "run combine_key;" \
            "run upgrade_key;" \
            "run vim2_check;" \
            "run uboot_update_check;" \
            "run wol_init;"\
            "forceupdate;" \
            "run switch_bootmode;"
#define CONFIG_BOOTCOMMAND "run storeboot"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK					1200 //MHz. Range: 600-1800, should be multiple of 24

/* ddr */
#define CONFIG_DDR_AUTO_DTB             1
#define CONFIG_DDR_SIZE					0 //MB //0 means ddr size auto-detect
#define CONFIG_DDR_CLK					912  //MHz, Range: 384-1200, should be multiple of 24
#define CONFIG_DDR4_CLK					1008  //MHz, for boards which use different ddr chip
#define CONFIG_NR_DRAM_BANKS			1
/* DDR type setting
 *    CONFIG_DDR_TYPE_LPDDR3   : LPDDR3
 *    CONFIG_DDR_TYPE_DDR3     : DDR3
 *    CONFIG_DDR_TYPE_DDR4     : DDR4
 *    CONFIG_DDR_TYPE_AUTO     : DDR3/DDR4 auto detect */
#define CONFIG_DDR_TYPE					0x0F /* CONFIG_DDR_TYPE_AUTO */
/* DDR channel setting, please refer hardware design.
 *    CONFIG_DDR0_RANK0        : DDR0 rank0
 *    CONFIG_DDR0_RANK01       : DDR0 rank0+1
 *    CONFIG_DDR0_16BIT        : DDR0 16bit mode
 *    CONFIG_DDR0_16BIT_2      : DDR0 16bit mode, 2ranks
 *    CONFIG_DDR_CHL_AUTO      : auto detect RANK0 / RANK0+1 */
#define CONFIG_DDR_CHANNEL_SET			0x0F /* CONFIG_DDR0_RANK01 */
/* ddr functions */
#define CONFIG_DDR_FULL_TEST			0 //0:disable, 1:enable. ddr full test
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_LOW_POWER			0 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR4_TIMING_TEST			0 //0:disable, 1:enable. ddr4 timing test function
#define CONFIG_DDR_PLL_BYPASS			0 //0:disable, 1:enable. ddr pll bypass function

/* storage: emmc/nand/sd */
#define	CONFIG_STORE_COMPATIBLE 1
/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/

/* swither for mtd nand which is for slc only. */
/* support for mtd */
//#define CONFIG_AML_MTD 1

#ifdef CONFIG_AML_MTD
#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
#define CONFIFG_AML_MTDPART	1
/* mtd parts by env default way.*/
/*
#define MTDIDS_NAME_STR		"aml_nand.0"
#define MTDIDS_DEFAULT		"nand1=" MTDIDS_NAME_STR
#define MTDPARTS_DEFAULT	"mtdparts=" MTDIDS_NAME_STR ":" \
					"3M@8192K(logo),"	\
					"10M(recovery),"	\
					"8M(kernel),"	\
					"40M(rootfs),"	\
					"-(data)"
*/
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_CMD_MTDPARTS   1
#define CONFIG_MTD_PARTITIONS 1
#endif
/* endof CONFIG_AML_MTD */

#define CONFIG_AML_SD_EMMC 1
#ifdef	CONFIG_AML_SD_EMMC
	#define CONFIG_GENERIC_MMC 1
	#define CONFIG_CMD_MMC 1
    #define CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000
#endif

/* env */
#define 	CONFIG_ENV_OVERWRITE
#define 	CONFIG_CMD_SAVEENV


#define	CONFIG_PARTITIONS 1
#define CONFIG_SYS_NO_FLASH  1
//#define     CONFIG_AML_GPT

/* meson SPI */
#define CONFIG_AML_SPIFC
#if defined CONFIG_AML_SPIFC || defined CONFIG_AML_SPICC
    #define CONFIG_OF_SPI
    #define CONFIG_DM_SPI
    #define CONFIG_CMD_SPI
#endif
/* SPI flash config */
#ifdef CONFIG_AML_SPIFC
//    #define CONFIG_SPIFC_COMPATIBLE_TO_APPOLO
    #define CONFIG_SPI_FLASH
    #define CONFIG_DM_SPI_FLASH
    #define CONFIG_CMD_SF
    /* SPI flash surpport list */
    #define CONFIG_SPI_FLASH_ATMEL
    #define CONFIG_SPI_FLASH_EON
    #define CONFIG_SPI_FLASH_GIGADEVICE
    #define CONFIG_SPI_FLASH_MACRONIX
    #define CONFIG_SPI_FLASH_SPANSION
    #define CONFIG_SPI_FLASH_STMICRO
    #define CONFIG_SPI_FLASH_SST
    #define CONFIG_SPI_FLASH_WINBOND
    #define CONFIG_SPI_FRAM_RAMTRON
    #define CONFIG_SPI_M95XXX
    #define CONFIG_SPI_FLASH_ESMT
#endif

/* vpu */
#define CONFIG_AML_VPU 1
#define CONFIG_VPU_CLK_LEVEL_DFT 7

/* DISPLAY & HDMITX */
#define CONFIG_AML_HDMITX20 1
#define CONFIG_AML_CANVAS 1
#define CONFIG_AML_VOUT 1
#define CONFIG_AML_OSD 1
#define CONFIG_AML_MINUI 1
#define CONFIG_OSD_SCALE_ENABLE 1
#define CONFIG_CMD_BMP 1

#if defined(CONFIG_AML_VOUT)
#define CONFIG_AML_CVBS 1
#endif

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
#define CONFIG_CMD_USB 1
#if defined(CONFIG_CMD_USB)
	#define CONFIG_GXL_XHCI_BASE		0xc9000000
	#define CONFIG_GXL_USB_PHY2_BASE	0xd0078000
	#define CONFIG_GXL_USB_PHY3_BASE	0xd0078080
	#define CONFIG_USB_STORAGE      1
	#define CONFIG_USB_XHCI		1
	#define CONFIG_USB_XHCI_AMLOGIC_GXL 1
#endif //#if defined(CONFIG_CMD_USB)

//UBOOT fastboot config
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#ifdef CONFIG_AML_MTD
#endif
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1
#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0x8000000
#define CONFIG_DEVICE_PRODUCT	"q200"

//UBOOT Facotry usb/sdcard burning config
#define CONFIG_AML_V2_FACTORY_BURN              1       //support facotry usb burning
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1       //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1       //There isn't power-key for factory sdcard burning
#define CONFIG_SD_BURNING_SUPPORT_UI            1       //Displaying upgrading progress bar when sdcard/udisk burning

#define CONFIG_AML_SECURITY_KEY                 1
#define CONFIG_UNIFY_KEY_MANAGE                 1

/* net */
#define CONFIG_CMD_NET   1
#define CONFIG_PHY_REALTEK 1
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        KVIM2
	#define CONFIG_RANDOM_ETHADDR  1				   /* use random eth addr, or default */
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          192.168.1.200       /* Our ip address */
	#define CONFIG_GATEWAYIP       192.168.1.1         /* Our getway ip address */
	#define CONFIG_SERVERIP        192.168.1.230       /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/* other devices */
#define CONFIG_EFUSE 1
#define CONFIG_SYS_I2C_AML 1
#define CONFIG_SYS_I2C_SPEED     400000

/* commands */
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_BOOTI 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_I2C 1
#define CONFIG_CMD_MEMORY 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_JTAG	1
#define CONFIG_CMD_AUTOSCRIPT 1
#define CONFIG_CMD_MISC 1
#define CONFIG_CMD_FS_GENERIC 1
//#define CONFIG_PARTITION_UUIDS 1
#define CONFIG_CMD_PART 1
#define CONFIG_CMD_ENV_EXISTS 1


/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1
#define CONFIG_CMD_EXT2 1
#define CONFIG_CMD_UNZIP    1
#define CONFIG_LZMA         1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
#define CONFIG_BOOTDELAY	1 //delay 1s
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC     1
#define CONFIG_CMD_ITEST    1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_SYS_MEM_TOP_HIDE 0x08000000 //hide 128MB for kernel reserve
#define CONFIG_CMD_CHIPID 1
#define CONFIG_CMDLINE_EDITING 1
#define CONFIG_AUTO_COMPLETE 1


/* debug mode defines */
//#define CONFIG_DEBUG_MODE           1
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG        636
#define CONFIG_CPU_CLK_DEBUG        600
#endif

//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   1

//unify build for generate encrypted kernel image
//SRC : "board/amlogic/(board)/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG       1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif
//#define CONFIG_INTERNAL_PHY
#define CONFIG_EXTERNAL_PHY
#endif
