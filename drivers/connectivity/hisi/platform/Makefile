HI1102_DRIVER_BUILTIN_PATH := drivers/connectivity/hisi
DRIVER_FLODER = platform

export _PRE_PRODUCT_VERSION  ?= 1102
export HI1102_BOARD_VERSION ?= v8r2
export PLAT_DEFCONFIG_FILE ?= plat_$(_PRE_PRODUCT_VERSION)_$(HI1102_BOARD_VERSION)_defconfig

HI1102_COMM_DEFCONFIG := hi$(_PRE_PRODUCT_VERSION)_comm_defconfig

CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT ?= no

ifneq ($(KERNELRELEASE),)
ifeq ($(HI1102_MAKE_FLAG),)
KERNEL_DIR := $(srctree)
HI1102_DRIVER_SRC_PATH=$(KERNEL_DIR)/$(HI1102_DRIVER_BUILTIN_PATH)
endif

DRIVER_PATH=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER)

include $(DRIVER_PATH)/$(HI1102_COMM_DEFCONFIG)
include $(DRIVER_PATH)/$(PLAT_DEFCONFIG_FILE)

$(warning defconfig: $(DRIVER_PATH)/$(PLAT_DEFCONFIG_FILE))

oal-objs := oal_bus_if.o oal_main.o oal_mem.o oal_net.o oal_hardware.o oal_schedule.o oal_pci_if.o oal_aes.o oal_kernel_file.o oal_cfg80211.o oal_sdio_host.o oal_profiling.o oal_hcc_host.o oal_hcc_test.o oal_softwdt.o oal_dft.o
oal-objs := $(addprefix oal/,$(oal-objs))

frw-objs := frw_event_deploy.o frw_event_main.o frw_event_sched.o frw_ipc_msgqueue.o frw_main.o frw_task.o frw_timer.o
frw-objs := $(addprefix frw/,$(frw-objs))

oam-objs := oam_main.o oam_alarm.o oam_event.o oam_log.o oam_trace.o oam_statistics.o oam_config.o oam_register.o oam_linux_netlink.o
oam-objs := $(addprefix oam/,$(oam-objs))

sdt-objs := sdt_drv.o
sdt-objs := $(addprefix sdt/,$(sdt-objs))

customize-objs := hisi_ini.o hisi_customize_wifi.o
customize-objs := $(addprefix ../common/customize/,$(customize-objs))

chr_devs-objs := chr_devs.o
chr_devs-objs := $(addprefix ../common/chr_log/,$(chr_devs-objs))

main-objs := plat_main.o
main-objs := $(addprefix main/,$(main-objs))

pm-objs :=  plat_firmware.o plat_pm.o  plat_pm_wlan.o plat_cali.o plat_efuse.o

ifeq ($(CONFIG_HISI_GPS_REF_CLK),y)
ifeq ($(CONFIG_ARCH_HI6250),y)
pm-objs += gps_plat_hi6250.o
endif
ifeq ($(CONFIG_ARCH_HI3650),y)
pm-objs += gps_plat_hi3650.o
endif
endif

ifeq ($(CONFIG_CONNECTIVITY_HI110X_HI6250),y)
pm-objs += gps_plat_hi6250.o
endif
ifeq ($(CONFIG_CONNECTIVITY_HI110X_HI3650),y)
pm-objs += gps_plat_hi3650.o
endif
ifeq ($(CONFIG_CONNECTIVITY_HI110X_HI3660),y)
pm-objs += gps_plat_hi3660.o
endif
ifeq ($(CONFIG_CONNECTIVITY_HI110X_KIRIN970),y)
pm-objs += gps_plat_hi3660.o
endif

pm-objs := $(addprefix pm/,$(pm-objs))

driver-objs :=  plat_sdio.o plat_uart.o
driver-objs := $(addprefix driver/,$(driver-objs))

#obj-$(CONFIG_HI1102_PLAT_PS) +=ps.o 
bfgx-objs := bfgx_low_power.o bfgx_exception_rst.o bfgx_data_parse.o bfgx_dev.o bfgx_user_ctrl.o
bfgx-objs := $(addprefix ../bfgx/,$(bfgx-objs))

board-objs := board.o board-hi1102.o board-hi1103.o
board-objs := $(addprefix board/,$(board-objs))

oneimage-objs := oneimage.o
oneimage-objs := $(addprefix ../common/oneimage/,$(oneimage-objs))

plat-objs += $(oal-objs)

plat-objs += $(frw-objs)

plat-objs += $(oam-objs)

plat-objs += $(sdt-objs)

plat-objs += $(pm-objs)

plat-objs += $(main-objs)

plat-objs += $(bfgx-objs)

plat-objs += $(chr_devs-objs)

plat-objs += $(board-objs)
plat-objs += $(oneimage-objs)
plat-objs += $(customize-objs)
plat-objs += $(driver-objs)

#plat ko
ifeq ($(CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT), yes)
obj-m += plat.o
else
obj-y += plat.o
endif

HI1102_INCLUDES := -I$(DRIVER_PATH)/inc
HI1102_INCLUDES += -I$(DRIVER_PATH)/inc/frw
HI1102_INCLUDES += -I$(DRIVER_PATH)/inc/oal
HI1102_INCLUDES += -I$(DRIVER_PATH)/inc/oal/linux
HI1102_INCLUDES += -I$(DRIVER_PATH)/inc/oam
HI1102_INCLUDES += -I$(DRIVER_PATH)/inc/pm
HI1102_INCLUDES += -I$(DRIVER_PATH)/frw
HI1102_INCLUDES += -I$(DRIVER_PATH)/oal
HI1102_INCLUDES += -I$(DRIVER_PATH)/oam
HI1102_INCLUDES += -I$(DRIVER_PATH)/pm
HI1102_INCLUDES += -I$(DRIVER_PATH)/../bfgx
HI1102_INCLUDES += -I$(DRIVER_PATH)/sdt
HI1102_INCLUDES += -I$(DRIVER_PATH)/board
HI1102_INCLUDES += -I$(DRIVER_PATH)/driver
HI1102_INCLUDES += -I$(DRIVER_PATH)/../common/oneimage
HI1102_INCLUDES += -I$(DRIVER_PATH)/../common/customize
HI1102_INCLUDES += -I$(DRIVER_PATH)/../common/inc
HI1102_INCLUDES += -I$(DRIVER_PATH)/../common/chr_log

#This is not good
HI1102_INCLUDES += -I$(KERNEL_DIR)
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/inc
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/inc/hal
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/inc/dmac
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/inc/wal
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/hal/hal_verify/
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/hmac/hmac_verify/
HI1102_INCLUDES += -I$(HI1102_DRIVER_SRC_PATH)/wifi/dmac/dmac_verify/

KBUILD_CFLAGS += -DPLATFORM_TYPE_FOR_HI110X=0
KBUILD_CFLAGS += -DPLATFORM_HI110X_k3v2oem1=1
KBUILD_CFLAGS += -DPLATFORM_HI110X_UEDGE=2  

ifneq ($(TARGET_BUILD_VARIANT),user)
KBUILD_CFLAGS += -DPLATFORM_DEBUG_ENABLE
endif

ifeq ($(HAVE_HISI_FEATURE_IR),true)
KBUILD_CFLAGS += -DHAVE_HISI_IR
endif

ifeq ($(HAVE_HISI_FEATURE_NFC),true)
KBUILD_CFLAGS += -DHAVE_HISI_NFC
endif

HI110X_VER_COMMIT_ID = $(shell cd $(HI1102_DRIVER_SRC_PATH);if test -d .git;then git rev-parse --verify --short HEAD 2>/dev/null;fi)
ifneq ($(HI110X_VER_COMMIT_ID),)
HI110X_VER_COMMIT_TIME = $(shell cd $(HI1102_DRIVER_SRC_PATH);git log -1 --pretty=format:%ci)

HI110X_VERSION="\"commitId:$(HI110X_VER_COMMIT_ID), commitTime:$(HI110X_VER_COMMIT_TIME)\""

KBUILD_CFLAGS += -DHI110X_DRV_VERSION=$(HI110X_VERSION)
endif
$(warning HI110X_VER_COMMIT_ID: $(HI110X_VER_COMMIT_ID))
$(warning HI110X_VER_COMMIT_TIME: $(HI110X_VER_COMMIT_TIME))
$(warning HI110X_VERSION: $(HI110X_VERSION))
#$(warning INCLUDE: $(HI1102_INCLUDES))

EXTRA_CFLAGS = $(HI1102_INCLUDES)
EXTRA_CFLAGS += $(COPTS) $(KBUILD_CFLAGS)
EXTRA_CFLAGS += $(COMM_COPTS)
EXTRA_CFLAGS += -Werror -Wuninitialized -Wempty-body -Woverride-init -Wtype-limits

EXTRA_CFLAGS +=  -fno-pic
MODFLAGS = -fno-pic
else

#make modules
export HI1102_MAKE_FLAG=MODULES
export HI1102_DRIVER_SRC_PATH ?= $(shell pwd)/..

ANDROID_PRODUCT=hi6210sft
ifeq ($(ARCH),arm64)
ANDROID_PATH ?= /home/dengwenhua/zhouxinfeng/k3v5
MODULE_PARAM ?= ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
else
ANDROID_PATH ?= /home/zhouxinfeng/1102/v8r2-checkin
MODULE_PARAM ?= ARCH=arm CROSS_COMPILE=arm-eabi-
endif

KERNEL_DIR ?= $(ANDROID_PATH)/out/target/product/$(ANDROID_PRODUCT)/obj/KERNEL_OBJ
CROSS_DIR ?= $(ANDROID_PATH)/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin:$(ANDROID_PATH)/prebuilts/gcc/linux-x86/arm/gcc-linaro-aarch64-linux-gnu-4.8/bin
PATH := $(CROSS_DIR):$(PATH)
CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT ?= yes

default:
	$(MAKE) -C $(KERNEL_DIR) $(MODULE_PARAM)  M=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(HI1102_DRIVER_SRC_PATH)/$(DRIVER_FLODER) clean
	-find ../bfgx/ -type f -name "*.o" -exec rm -f {} \;
	-find ../bfgx/ -type f -name "*.o.cmd" -exec rm -f {} \;
	-find ../common/ -type f -name "*.o" -exec rm -f {} \;
	-find ../common/ -type f -name "*.o.cmd" -exec rm -f {} \;
	
endif
