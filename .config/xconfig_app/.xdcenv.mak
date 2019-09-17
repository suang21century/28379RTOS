#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_76_00_08/packages;D:/project/TiRTOS/28379test/.config
override XDCROOT = C:/ti/xdctools_3_51_03_28_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_76_00_08/packages;D:/project/TiRTOS/28379test/.config;C:/ti/xdctools_3_51_03_28_core/packages;..
HOSTOS = Windows
endif
