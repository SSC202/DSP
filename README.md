# DSP

DSP(数字信号处理器)，由于其较快的数学计算速度，成为电机控制，音频处理，图像处理等需要大量运算的主要器件。

本库主要包括两个部分，第一部分是关于TI C2000系列DSP的使用笔记(编写中)，第二部分是STM32中Arm_DSP库的使用(未编写)。

## TI C2000 使用笔记

- 关于此笔记

TI C2000系列笔记是基于HITsz DSP原理与应用 这门课程为基础记录的，包括并超过了这门课程的涉及范围，使用此库的Note**足以应对这门课程的考试**，但是对DSP的使用还是建议购入TMS320F28335开发板(普中，成本270RMB)并配合Code使用。

- 使用指南

| Note                                                         | 简介                            | Code                                                         |
| ------------------------------------------------------------ | ------------------------------- | ------------------------------------------------------------ |
| [1_DSP概论](https://github.com/SSC202/DSP/blob/main/TI-C2000-TMS320F28335/Note/1_DSP概论/1_DSP概论.md) | DSP概论，架构介绍（1-4）        |                                                              |
| [2_DSP环境配置及工程创建](https://github.com/SSC202/DSP/blob/main/TI-C2000-TMS320F28335/Note/2_DSP环境配置及工程创建/2_DSP环境配置和工程构建.md) | DSP工程配置（5-6）              | [1_F28335_Test_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/1_F28335_Test_demo) |
| [3_DSP的数字处理](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/3_DSP的数字处理) | DSP的数字处理（7）              |                                                              |
| [4_DSP时钟系统](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/4_DSP时钟系统) | DSP的时钟系统（8）              | [2_F28335_ClockConfig_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/2_F28335_ClockConfig_demo) |
| [5_DSP_GPIO](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/5_DSP_GPIO) | DSP的通用输入输出接口（未讲解） | [3_F28335_LED_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/3_F28335_LED_Demo)<br/>[4_F28335_BEEP_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/4_F28335_BEEP_demo)<br/>[5_F28335_KEY_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/5_F28335_KEY_demo) |
| [6_DSP_ISR](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/6_DSP_ISR) | DSP的中断系统（9）              |                                                              |
| [7_DSP_EXTI](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/7_DSP_EXTI) | DSP的外部中断（未讲解）         | [6_F28335_EXTI_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/6_F28335_EXTI_Demo) |
| [8_DSP_ADC](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/8_DSP_ADC) | DSP的模数转换器（10-11）        | [7_F28335_ADC_demo](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Code/7_F28335_ADC_Demo) |
| [9_DSP_ePWM](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/9_DSP_ePWM) | DSP的ePWM模块                   |                                                              |
| [10_DSP_CPU_Timer](https://github.com/SSC202/DSP/tree/main/TI-C2000-TMS320F28335/Note/10_DSP_CPU_TIM)|DSP的CPU时钟| |

STM32 Arm_DSP库的使用主要基于B站UP主 zeshoufx 的DSP库使用视频。
