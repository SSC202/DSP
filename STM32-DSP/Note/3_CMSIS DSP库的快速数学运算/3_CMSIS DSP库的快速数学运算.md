# DSP STM32 3_CMSIS DSP库的快速数学运算

## 1. 三角函数

三角函数的计算是通过查表并配合直线插补实现的。

```c
float32_t arm_cos_f32(float32_t x);
q31_t arm_cos_q31(q31_t x);
q15_t arm_cos_q15(q15_t x);
float32_t arm_sin_f32(float32_t x);
q31_t arm_sin_q31(q31_t x);
q15_t arm_cos_q15(q15_t x);
```

三角函数计算使用弧度制。

## 2. 平方根

```c
__STATIC_FORCEINLINE arm_status arm_sqrt_f32(float32_t in, float32_t * pOut);
```

> - 对于带 FPU 的处理器来说，浮点数的平方根求解只需调用指令`__sqrtf`，仅需要 14 个时钟周期就可以完成。

```c
arm_status arm_sqrt_q31(q31_t in, q31_t * pOut);
```

> - `in`的输入范围是`0x00000000` 到 `0x7FFFFFFF`，转化成浮点数范围就是[0 +1)。

```c
arm_status arm_sqrt_q15(q15_t in, q15_t * pOut);
```

