################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Library/%.obj: ../Library/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/Lib" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/LED" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/BEEP" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/KEY" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/SMG" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_common/include" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_headers/include" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Library/$(basename $(<F)).d_raw" --obj_directory="Library" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Library/%.obj: ../Library/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/Lib" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/LED" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/BEEP" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/KEY" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/8_F28335_PWM_Demo/BSP/SMG" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_common/include" --include_path="E:/STM32SSC/TI/DSP/TI-C2000-TMS320F28335/Code/Library/DSP2833x_headers/include" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Library/$(basename $(<F)).d_raw" --obj_directory="Library" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


