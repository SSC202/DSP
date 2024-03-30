################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User/%.obj: ../User/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/3_F28335_LED_Demo/BSP/LED" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_common/include" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_headers/include" --include_path="D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="User/$(basename $(<F)).d_raw" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


