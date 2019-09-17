################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
user/%.obj: ../user/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/software/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/project/TiRTOS/28379test/FlashAPI" --include_path="D:/project/TiRTOS/28379test/inc" --include_path="D:/project/TiRTOS/28379test/user" --include_path="D:/project/TiRTOS/28379test" --include_path="C:/ti/bios_6_76_00_08/packages/ti/posix/ccs" --include_path="D:/software/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="user/$(basename $(<F)).d_raw" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

user/%.obj: ../user/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/software/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/project/TiRTOS/28379test/FlashAPI" --include_path="D:/project/TiRTOS/28379test/inc" --include_path="D:/project/TiRTOS/28379test/user" --include_path="D:/project/TiRTOS/28379test" --include_path="C:/ti/bios_6_76_00_08/packages/ti/posix/ccs" --include_path="D:/software/ti-cgt-c2000_18.12.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=coffabi --preproc_with_compile --preproc_dependency="user/$(basename $(<F)).d_raw" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


