################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1562936111:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1562936111-inproc

build-1562936111-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_51_03_28_core/xs" --xdcpath="C:/ti/bios_6_76_00_08/packages;" xdc.tools.configuro -o configPkg -t ti.targets.C28_float -p ti.platforms.tms320x28:TMS320F28379D -r release -c "D:/software/ti-cgt-c2000_18.12.1.LTS" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1562936111 ../app.cfg
configPkg/compiler.opt: build-1562936111
configPkg/: build-1562936111


