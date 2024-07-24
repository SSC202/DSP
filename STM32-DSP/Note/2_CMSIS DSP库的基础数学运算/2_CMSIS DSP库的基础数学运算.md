# DSP STM32 2_CMSIS DSP库的基础数学运算

> **DSP 库函数的通用规则**
>
> 1. 基本所有的函数都是可重入的。
> 2. 大部分函数都支持批量计算，比如求绝对值函数`arm_abs_f32`。所以如果只是就几个数的绝对值，用这个库函数就没有什么优势了。
> 3. DSP 库函数基本是CM0，CM0+，CM3，CM4和CM7内核都是支持的，不限制厂家。
> 4. 每组数据基本上都是以4个数为一个单位进行计算，不够四个再单独计算。大部分函数都是配有`f32`，`q31`，`q15` 和 `q7` 四种格式。  可以统一采用一个程序设计架构，便于管理。更重要的是可以在`q15`和`q7`数据处理中很好的发挥SIMD指令的作用（因为4个为一组的话，可以用SIMD指令正好处理2个`q15`数据或者4个`q7`数据）。

## 1. DSP 基础运算指令

<font color=LightGreen>1. 基础运算指令</font>

> -  绝对值函数用到`QSUB`，`QSUB16`和`QSUB8`。
> -  求和函数用到`QADD`，`QADD16`和`QADD8`。
> -  点乘函数用到`SMLALD`和`SMLAD`。
> -  乘法用到`__PKHBT`和__`SSAT`。
> -  相反数函数用到`QSUB`，`QSUB16`和`QSUB8`。
> -  偏移函数用到`QADD`，`QADD16`和`QADD8`。
> -  移位函数用到`PKHBT`和`SSAT`。
> -  减法函数用到`QSUB`，`QSUB16`和`QSUB8`。
> -  比例因子函数用到`PKHBT`和`SSAT`。

<font color=LightGreen>2. 饱和计算</font>

`Q*`的指令是饱和运算指令，**饱和的意思超过所能表示的数值范围时，将直接取最大/小值**。

比如`QSUB16`减法指令，如果是正数，那么最大值是`0x7FF`（32767），大于这个值将直接取`0x7FFF`，如果是负数，那么最小值是`0x8000`（-32768），比这个值还小将直接取值`0x8000`。

## 2. 绝对值函数

### `arm_abs_f32`函数

```c
/**
  * @brief	用于求32位浮点数的绝对值
  *	@param  pSrc	原数据地址	
  * @param	pDst	求绝对值后目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_abs_f32(const float32_t *pSrc, float32_t *pDst, uint32_t blockSize)
{
    uint32_t blkCnt; /* Loop counter */
    // 用于NEON指令集，当前的CM内核不支持
#if defined(ARM_MATH_NEON)
    float32x4_t vec1;
    float32x4_t res;
    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 2U;
    while (blkCnt > 0U)
    {
        /* C = |A| */
        /* Calculate absolute values and then store the results in the destination buffer. */
        vec1 = vld1q_f32(pSrc);
        res = vabsq_f32(vec1);
        vst1q_f32(pDst, res);
        /* Increment pointers */
        pSrc += 4;
        pDst += 4;
        /* Decrement the loop counter */
        blkCnt--;
    }
    /* Tail */
    blkCnt = blockSize & 0x3;
#else
    // 实现四个为一组进行计数，好处是加快执行速度，降低while循环占用时间
#if defined(ARM_MATH_LOOPUNROLL)
    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = blockSize >> 2U;
    while (blkCnt > 0U)
    {
        /* C = |A| */
        /* Calculate absolute and store result in destination buffer. */
        // fabsf不是用Cortex-M内核支持的DSP指令实现的，而是用C库函数实现的
        *pDst++ = fabsf(*pSrc++);
        *pDst++ = fabsf(*pSrc++);
        *pDst++ = fabsf(*pSrc++);
        *pDst++ = fabsf(*pSrc++);
        /* Decrement loop counter */
        blkCnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    blkCnt = blockSize % 0x4U;
#else
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON) */
    // 四个为一组剩余数据的处理或者不采用四个为一组时数据处理
    while (blkCnt > 0U)
    {
        /* C = |A| */
        /* Calculate absolute and store result in destination buffer. */
        *pDst++ = fabsf(*pSrc++);
        /* Decrement loop counter */
        blkCnt--;
    }
}
```

### `arm_abs_q31`函数

```c
/**
  * @brief	用于求32位定点数的绝对值
  *	@param  pSrc	原数据地址	
  * @param	pDst	求绝对值后目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_abs_q31(const q31_t *pSrc, q31_t *pDst, uint32_t blockSize)
{
    uint32_t blkCnt; /* Loop counter */
    q31_t in;        /* Temporary variable */

#if defined(ARM_MATH_LOOPUNROLL)
    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = blockSize >> 2U;
    while (blkCnt > 0U)
    {
        /* C = |A| */
        /* Calculate absolute of input (if -1 then saturated to 0x7fffffff) and store result in destination buffer. */
        in = *pSrc++;
#if defined(ARM_MATH_DSP)
        *pDst++ = (in > 0) ? in : (q31_t)__QSUB(0, in);
#else
        *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
#endif
        in = *pSrc++;
#if defined(ARM_MATH_DSP)
        *pDst++ = (in > 0) ? in : (q31_t)__QSUB(0, in);
#else
        *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
#endif
        in = *pSrc++;
#if defined(ARM_MATH_DSP)
        *pDst++ = (in > 0) ? in : (q31_t)__QSUB(0, in);
#else
        *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
#endif
        in = *pSrc++;
#if defined(ARM_MATH_DSP)
        *pDst++ = (in > 0) ? in : (q31_t)__QSUB(0, in);
#else
        *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
#endif
        /* Decrement loop counter */
        blkCnt--;
    }
    /* Loop unrolling: Compute remaining outputs */
    blkCnt = blockSize % 0x4U;
#else
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
    while (blkCnt > 0U)
    {
        /* C = |A| */
        /* Calculate absolute of input (if -1 then saturated to 0x7fffffff) and store result in destination buffer. */
        in = *pSrc++;
#if defined(ARM_MATH_DSP)
        *pDst++ = (in > 0) ? in : (q31_t)__QSUB(0, in);
#else
        *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
#endif

        /* Decrement loop counter */
        blkCnt--;
    }
}
```

> - 对于`q31`格式的数据，饱和运算会使得数据`0x80000000`变成`0x7fffffff`。
> - 函数`__QSUB`用于实现饱和减法。

### `arm_abs_q15`函数

```c
/**
  * @brief	用于求15位定点数的绝对值
  *	@param  pSrc	原数据地址	
  * @param	pDst	求绝对值后目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_abs_q15(const q15_t *pSrc, q15_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q15_t in;        /* Temporary input variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = |A| */
                /* Calculate absolute of input (if -1 then saturated to 0x7fff) and store result in destination buffer.
                 */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q15_t)__QSUB16(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q15_t)0x8000) ? 0x7fff : -in);
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q15_t)__QSUB16(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q15_t)0x8000) ? 0x7fff : -in);
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q15_t)__QSUB16(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q15_t)0x8000) ? 0x7fff : -in);
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q15_t)__QSUB16(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q15_t)0x8000) ? 0x7fff : -in);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = |A| */
                /* Calculate absolute of input (if -1 then saturated to 0x7fff) and store result in destination buffer.
                 */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q15_t)__QSUB16(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q15_t)0x8000) ? 0x7fff : -in);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - 对于`q15`格式的数据，饱和运算会使得数据`0x8000`变成`0x7fff`。
> - 函数`__QSUB16`用于实现饱和减法。

### `arm_abs_q7`函数

```c
/**
  * @brief	用于求7位定点数的绝对值
  *	@param  pSrc	原数据地址	
  * @param	pDst	求绝对值后目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_abs_q7(const q7_t *pSrc, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q7_t in;         /* Temporary input variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = |A| */
                /* Calculate absolute of input (if -1 then saturated to 0x7f) and store result in destination buffer.
                 */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q7_t)__QSUB(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q7_t)0x80) ? (q7_t)0x7f : -in);
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q7_t)__QSUB(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q7_t)0x80) ? (q7_t)0x7f : -in);
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q7_t)__QSUB(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q7_t)0x80) ? (q7_t)0x7f : -in);
#endif
                in = *pSrc++;
                ezi le mexia
#if defined(ARM_MATH_DSP)
                    *pDst++ = (in > 0) ? in : (q7_t)__QSUB(0, in);
#else
                    *pDst++ = (in > 0) ? in : ((in == (q7_t)0x80) ? (q7_t)0x7f : -in);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = |A| */
                /* Calculate absolute of input (if -1 then saturated to 0x7f) and store result in destination buffer.
                 */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (in > 0) ? in : (q7_t)__QSUB(0, in);
#else
                *pDst++ = (in > 0) ? in : ((in == (q7_t)0x80) ? (q7_t)0x7f : -in);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - 对于`q7`格式的数据，饱和运算会使得数据`0x80`变成`0x7f`。
> - 函数`__QSUB`用于实现饱和减法。**当前的DSP库版本却将其用到了`q7`函数中，导致`0x80`的饱和出错。**

## 3. 求和函数

### `arm_add_f32`函数

```c
/**
  * @brief	用于求32位浮点数的和
  *	@param  pSrcA	加数地址	
  * @param	pSrcB	被加数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行加法的次数
  */ 
void arm_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */

#if defined(ARM_MATH_NEON)
        float32x4_t vec1;
        float32x4_t vec2;
        float32x4_t res;
        /* Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and then store the results in the destination buffer. */
                vec1 = vld1q_f32(pSrcA);
                vec2 = vld1q_f32(pSrcB);
                res = vaddq_f32(vec1, vec2);
                vst1q_f32(pDst, res);
                /* Increment pointers */
                pSrcA += 4;
                pSrcB += 4;
                pDst += 4;
                /* Decrement the loop counter */
                blkCnt--;
        }
        /* Tail */
        blkCnt = blockSize & 0x3;
#else
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
                *pDst++ = (*pSrcA++) + (*pSrcB++);
                *pDst++ = (*pSrcA++) + (*pSrcB++);
                *pDst++ = (*pSrcA++) + (*pSrcB++);
                *pDst++ = (*pSrcA++) + (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON) */

        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
                *pDst++ = (*pSrcA++) + (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

### `arm_add_q31`函数

```c
/**
  * @brief	用于求31位定点数的和
  *	@param  pSrcA	加数地址	
  * @param	pSrcB	被加数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行加法的次数
  */ 
void arm_add_q31(const q31_t *pSrcA, const q31_t *pSrcB, q31_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */

#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
                *pDst++ = __QADD(*pSrcA++, *pSrcB++);
                *pDst++ = __QADD(*pSrcA++, *pSrcB++);
                *pDst++ = __QADD(*pSrcA++, *pSrcB++);
                *pDst++ = __QADD(*pSrcA++, *pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
                *pDst++ = __QADD(*pSrcA++, *pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - `__QADD`实现32位数的加法饱和运算。输出结果的范围[`0x80000000 `，`0x7FFFFFFF`]，超出这个结果将产生饱和结果，负数饱和到`0x80000000`，正数饱和到`0x7FFFFFFF`。

### `arm_add_q15`函数

```c
/**
  * @brief	用于求15位定点数的和
  *	@param  pSrcA	加数地址	
  * @param	pSrcB	被加数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行加法的次数
  */ 
void arm_add_q15(const q15_t *pSrcA, const q15_t *pSrcB, q15_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_LOOPUNROLL)

#if defined(ARM_MATH_DSP)
        q31_t inA1, inA2;
        q31_t inB1, inB2;
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A + B */
#if defined(ARM_MATH_DSP) // 对于M4和M7带DSP单元的芯片使用
                /* read 2 times 2 samples at a time from sourceA */
                inA1 = read_q15x2_ia((q15_t **)&pSrcA);
                inA2 = read_q15x2_ia((q15_t **)&pSrcA);
                /* read 2 times 2 samples at a time from sourceB */
                inB1 = read_q15x2_ia((q15_t **)&pSrcB);
                inB2 = read_q15x2_ia((q15_t **)&pSrcB);
                /* Add and store 2 times 2 samples at a time */
                write_q15x2_ia(&pDst, __QADD16(inA1, inB1));
                write_q15x2_ia(&pDst, __QADD16(inA2, inB2));
#else			// 对于不带DSP单元的M0，M0+和M3使用
                *pDst++ = (q15_t)__SSAT(((q31_t)*pSrcA++ + *pSrcB++), 16);
                *pDst++ = (q15_t)__SSAT(((q31_t)*pSrcA++ + *pSrcB++), 16);
                *pDst++ = (q15_t)__SSAT(((q31_t)*pSrcA++ + *pSrcB++), 16);
                *pDst++ = (q15_t)__SSAT(((q31_t)*pSrcA++ + *pSrcB++), 16);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;

#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
#if defined(ARM_MATH_DSP)
                *pDst++ = (q15_t)__QADD16(*pSrcA++, *pSrcB++);
#else
                *pDst++ = (q15_t)__SSAT(((q31_t)*pSrcA++ + *pSrcB++), 16);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - 函数`read_q15x2_ia`作用是读取两次16位数据，返回一个32位数据，并将数据地址递增，方便下次读取。
>
> ```c
> __STATIC_FORCEINLINE q31_t read_q15x2_ia (q15_t ** pQ15)
> {
>   q31_t val;
> 
>   memcpy (&val, *pQ15, 4);
>   *pQ15 += 2;
> 
>   return (val);
> }
> ```
>
> - ` __QADD16`实现两次16位数的加法饱和运算。输出结果的范围[`0x8000`， `0x7FFF`]，超出这个结果将产生饱和结果，负数饱和到`0x8000`，正数饱和到`0x7FFF`。
> - `__SSAT`也是`SIMD`指令，这里是将结果饱和到16位精度。

### `arm_add_q7`函数

```c
/**
  * @brief	用于求7位定点数的和
  *	@param  pSrcA	加数地址	
  * @param	pSrcB	被加数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行加法的次数
  */ 
void arm_add_q7(const q7_t *pSrcA, const q7_t *pSrcB, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A + B */
#if defined(ARM_MATH_DSP)
                /* Add and store result in destination buffer (4 samples at a time). */
                write_q7x4_ia(&pDst, __QADD8(read_q7x4_ia((q7_t **)&pSrcA), read_q7x4_ia((q7_t **)&pSrcB)));
#else
                *pDst++ = (q7_t)__SSAT((q15_t)*pSrcA++ + *pSrcB++, 8);
                *pDst++ = (q7_t)__SSAT((q15_t)*pSrcA++ + *pSrcB++, 8);
                *pDst++ = (q7_t)__SSAT((q15_t)*pSrcA++ + *pSrcB++, 8);
                *pDst++ = (q7_t)__SSAT((q15_t)*pSrcA++ + *pSrcB++, 8);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A + B */
                /* Add and store result in destination buffer. */
                *pDst++ = (q7_t)__SSAT((q15_t)*pSrcA++ + *pSrcB++, 8);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - 函数`read_q15x2_ia`读取4次8位数据，返回一个32位数据，并将数据地址递增，方便下次读取。
>
> ```c
> __STATIC_FORCEINLINE void write_q7x4_ia (q7_t ** pQ7,q31_t   value)
> {
>   q31_t val = value;
> 
>   memcpy (*pQ7, &val, 4);
>   *pQ7 += 4;
> }
> ```
>
> - `__QADD8`实现四次8位数的加法饱和运算。输出结果的范围[`0x80` ，`0x7F`]，超出这个结果将产生饱和结果，负数饱和到`0x80`，正数饱和到`0x7F`。

## 4. 点乘函数

### `arm_dot_prod_f32`函数

```c
/**
  * @brief	用于求32位浮点数的点乘
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	result	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_dot_prod_f32(const float32_t *pSrcA, const float32_t *pSrcB, uint32_t blockSize, float32_t *result)
{
        uint32_t blkCnt;      /* Loop counter */
        float32_t sum = 0.0f; /* Temporary return variable */
#if defined(ARM_MATH_NEON)
        float32x4_t vec1;
        float32x4_t vec2;
        float32x4_t res;
        float32x4_t accum = vdupq_n_f32(0);
        /* Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        vec1 = vld1q_f32(pSrcA);
        vec2 = vld1q_f32(pSrcB);
        while (blkCnt > 0U)
        {
                /* C = A[0]*B[0] + A[1]*B[1] + A[2]*B[2] + ... + A[blockSize-1]*B[blockSize-1] */
                /* Calculate dot product and then store the result in a temporary buffer. */
                accum = vmlaq_f32(accum, vec1, vec2);
                /* Increment pointers */
                pSrcA += 4;
                pSrcB += 4;
                vec1 = vld1q_f32(pSrcA);
                vec2 = vld1q_f32(pSrcB);
                /* Decrement the loop counter */
                blkCnt--;
        }
#if __aarch64__
        sum = vpadds_f32(vpadd_f32(vget_low_f32(accum), vget_high_f32(accum)));
#else
        sum = (vpadd_f32(vget_low_f32(accum), vget_high_f32(accum)))[0] + (vpadd_f32(vget_low_f32(accum),
                                                                                     vget_high_f32(accum)))[1];
#endif
        /* Tail */
        blkCnt = blockSize & 0x3;
#else
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        /* First part of the processing with loop unrolling. Compute 4 outputs at a time.
         ** a second loop below computes the remaining 1 to 3 samples. */
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                sum += (*pSrcA++) * (*pSrcB++);
                sum += (*pSrcA++) * (*pSrcB++);
                sum += (*pSrcA++) * (*pSrcB++);
                sum += (*pSrcA++) * (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON) */
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                sum += (*pSrcA++) * (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Store result in destination buffer */
        *result = sum;
}
```

### `arm_dot_prod_q31`函数

```c
/**
  * @brief	用于求31位定点数的点乘
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	result	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_dot_prod_q31(const q31_t *pSrcA,const q31_t *pSrcB,uint32_t blockSize,q63_t *result)
{
        uint32_t blkCnt; /* Loop counter */
        q63_t sum = 0;   /* Temporary return variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                sum += ((q63_t)*pSrcA++ * *pSrcB++) >> 14U;
                sum += ((q63_t)*pSrcA++ * *pSrcB++) >> 14U;
                sum += ((q63_t)*pSrcA++ * *pSrcB++) >> 14U;
                sum += ((q63_t)*pSrcA++ * *pSrcB++) >> 14U;
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                sum += ((q63_t)*pSrcA++ * *pSrcB++) >> 14U;
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Store result in destination buffer in 16.48 format */
        *result = sum;
}
```

> - 两个`q31`格式的32位数相乘，那么输出结果的格式是 1.31*1.31 = 2.62。实际应用中基本不需要这么高的精度，这个函数将低14位的数据截取掉，反应在函数中就是两个数的乘积左移14位，也就是定点数的小数点也左移14位，那么最终的结果的格式是16.48。所以只要乘累加的个数小于$2^{16}$就没有输出结果溢出的危险。

### `arm_dot_prod_q15`函数

```c
/**
  * @brief	用于求15位定点数的点乘
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	result	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_dot_prod_q15(const q15_t *pSrcA, const q15_t *pSrcB, uint32_t blockSize, q63_t *result)
{
        uint32_t blkCnt; /* Loop counter */
        q63_t sum = 0;   /* Temporary return variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
#if defined(ARM_MATH_DSP)
                /* Calculate dot product and store result in a temporary buffer. */
                sum = __SMLALD(read_q15x2_ia((q15_t **)&pSrcA), read_q15x2_ia((q15_t **)&pSrcB), sum);
                sum = __SMLALD(read_q15x2_ia((q15_t **)&pSrcA), read_q15x2_ia((q15_t **)&pSrcB), sum);
#else
                sum += (q63_t)((q31_t)*pSrcA++ * *pSrcB++);
                sum += (q63_t)((q31_t)*pSrcA++ * *pSrcB++);
                sum += (q63_t)((q31_t)*pSrcA++ * *pSrcB++);
                sum += (q63_t)((q31_t)*pSrcA++ * *pSrcB++);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                // #if defined (ARM_MATH_DSP)
                //     sum  = __SMLALD(*pSrcA++, *pSrcB++, sum);
                // #else
                sum += (q63_t)((q31_t)*pSrcA++ * *pSrcB++);
                // #endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Store result in destination buffer in 34.30 format */
        *result = sum;
}
```

> -  两个`q15`格式的数据相乘，那么输出结果的格式是1.15*1.15 = 2.30，这个函数将输出结果赋值给了64位变量，那么输出结果就是34.30格式。所以基本没有溢出的危险。
> -  `__SMLALD`是`SIMD`指令，实现两个16位数相乘，并把结果累加给64位变量。

### `arm_dot_prod_q7`函数

```c
/**
  * @brief	用于求7位定点数的点乘
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	result	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_dot_prod_q7(const q7_t *pSrcA, const q7_t *pSrcB, uint32_t blockSize, q31_t *result)
{
        uint32_t blkCnt; /* Loop counter */
        q31_t sum = 0;   /* Temporary return variable */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q31_t input1, input2;         /* Temporary variables */
        q31_t inA1, inA2, inB1, inB2; /* Temporary variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
#if defined(ARM_MATH_DSP)
                /* read 4 samples at a time from sourceA */
                input1 = read_q7x4_ia((q7_t **)&pSrcA);
                /* read 4 samples at a time from sourceB */
                input2 = read_q7x4_ia((q7_t **)&pSrcB);
                /* extract two q7_t samples to q15_t samples */
                inA1 = __SXTB16(__ROR(input1, 8));
                /* extract reminaing two samples */
                inA2 = __SXTB16(input1);
                /* extract two q7_t samples to q15_t samples */
                inB1 = __SXTB16(__ROR(input2, 8));
                /* extract reminaing two samples */
                inB2 = __SXTB16(input2);
                /* multiply and accumulate two samples at a time */
                sum = __SMLAD(inA1, inB1, sum);
                sum = __SMLAD(inA2, inB2, sum);
#else
                sum += (q31_t)((q15_t)*pSrcA++ * *pSrcB++);
                sum += (q31_t)((q15_t)*pSrcA++ * *pSrcB++);
                sum += (q31_t)((q15_t)*pSrcA++ * *pSrcB++);
                sum += (q31_t)((q15_t)*pSrcA++ * *pSrcB++);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
                /* Calculate dot product and store result in a temporary buffer. */
                // #if defined (ARM_MATH_DSP)
                //     sum  = __SMLAD(*pSrcA++, *pSrcB++, sum);
                // #else
                sum += (q31_t)((q15_t)*pSrcA++ * *pSrcB++);
                // #endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Store result in destination buffer in 18.14 format */
        *result = sum;
}
```

> - 两个Q8格式的数据相乘，那么输出结果就是1.7*1.7 = 2.14格式。这里将最终结果赋值给了32位的变量，那么最终的格式就是18.14。如果乘累加的个数小于$2^{18}$那么就不会有溢出的危险。
> -  ` __SXTB16`也是`SIMD`指令，用于将两个8位的有符号数扩展成16位。`__ROR`用于实现数据的循环右移。
> -   `__SMLAD`也是`SIMD`指令，用于实现如下功能：
> ```c
>  sum = __SMLAD(x, y, z)
>  sum = z + ((short)(x>>16) * (short)(y>>16)) + ((short)x * (short)y)
> ```

## 5. 乘法函数

### `arm_mult_f32`函数

```c
/**
  * @brief	用于求32位浮点数的乘积
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_mult_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_NEON)
        float32x4_t vec1;
        float32x4_t vec2;
        float32x4_t res;
        /* Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply the inputs and then store the results in the destination buffer. */
                vec1 = vld1q_f32(pSrcA);
                vec2 = vld1q_f32(pSrcB);
                res = vmulq_f32(vec1, vec2);
                vst1q_f32(pDst, res);
                /* Increment pointers */
                pSrcA += 4;
                pSrcB += 4;
                pDst += 4;
                /* Decrement the loop counter */
                blkCnt--;
        }
        /* Tail */
        blkCnt = blockSize & 0x3;
#else
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply inputs and store result in destination buffer. */
                *pDst++ = (*pSrcA++) * (*pSrcB++);
                *pDst++ = (*pSrcA++) * (*pSrcB++);
                *pDst++ = (*pSrcA++) * (*pSrcB++);
                *pDst++ = (*pSrcA++) * (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON) */
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply input and store result in destination buffer. */
                *pDst++ = (*pSrcA++) * (*pSrcB++);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

### `arm_mult_q31`函数

```c
/**
  * @brief	用于求31位定点数的乘积
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_mult_q31(const q31_t *pSrcA, const q31_t *pSrcB, q31_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q31_t out;       /* Temporary output variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply inputs and store result in destination buffer. */
            	// 所得乘积左移32位
                out = ((q63_t)*pSrcA++ * *pSrcB++) >> 32;
            	// 实现31位精度的饱和运算
                out = __SSAT(out, 31);
            	// 右移一位，保证所得结果是Q31格式
                *pDst++ = out << 1U;
                out = ((q63_t)*pSrcA++ * *pSrcB++) >> 32;
                out = __SSAT(out, 31);
                *pDst++ = out << 1U;
                out = ((q63_t)*pSrcA++ * *pSrcB++) >> 32;
                out = __SSAT(out, 31);
                *pDst++ = out << 1U;
                out = ((q63_t)*pSrcA++ * *pSrcB++) >> 32;
                out = __SSAT(out, 31);
                *pDst++ = out << 1U;
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply inputs and store result in destination buffer. */
                out = ((q63_t)*pSrcA++ * *pSrcB++) >> 32;
                out = __SSAT(out, 31);
                *pDst++ = out << 1U;
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - 饱和运算`__SSAT`，所得结果是`q31`格式。

### `arm_mult_q15`函数

```c
/**
  * @brief	用于求15位定点数的乘积
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_mult_q15(const q15_t *pSrcA, const q15_t *pSrcB, q15_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q31_t inA1, inA2, inB1, inB2; /* Temporary input variables */
        q15_t out1, out2, out3, out4; /* Temporary output variables */
        q31_t mul1, mul2, mul3, mul4; /* Temporary variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * B */
#if defined(ARM_MATH_DSP)
                /* read 2 samples at a time from sourceA */
            	// 一次读取两个Q15格式的数据
                inA1 = read_q15x2_ia((q15_t **)&pSrcA);
                /* read 2 samples at a time from sourceB */
                inB1 = read_q15x2_ia((q15_t **)&pSrcB);
                /* read 2 samples at a time from sourceA */
                inA2 = read_q15x2_ia((q15_t **)&pSrcA);
                /* read 2 samples at a time from sourceB */
                inB2 = read_q15x2_ia((q15_t **)&pSrcB);
                /* multiply mul = sourceA * sourceB */
            	// 将四组数的乘积保存到Q31格式的变量mul1，mul2，mul3，mul4
                mul1 = (q31_t)((q15_t)(inA1 >> 16) * (q15_t)(inB1 >> 16));
                mul2 = (q31_t)((q15_t)(inA1) * (q15_t)(inB1));
                mul3 = (q31_t)((q15_t)(inA2 >> 16) * (q15_t)(inB2 >> 16));
                mul4 = (q31_t)((q15_t)(inA2) * (q15_t)(inB2));
                /* saturate result to 16 bit */
            	// 丢弃32位数据的低15位，并把最终结果饱和到16位精度
                out1 = (q15_t)__SSAT(mul1 >> 15, 16);
                out2 = (q15_t)__SSAT(mul2 >> 15, 16);
                out3 = (q15_t)__SSAT(mul3 >> 15, 16);
                out4 = (q15_t)__SSAT(mul4 >> 15, 16);
                /* store result to destination */
#ifndef ARM_MATH_BIG_ENDIAN
                write_q15x2_ia(&pDst, __PKHBT(out2, out1, 16));
                write_q15x2_ia(&pDst, __PKHBT(out4, out3, 16));
#else
                write_q15x2_ia(&pDst, __PKHBT(out1, out2, 16));
                write_q15x2_ia(&pDst, __PKHBT(out3, out4, 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
#else
                *pDst++ = (q15_t)__SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
                *pDst++ = (q15_t)__SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
                *pDst++ = (q15_t)__SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
                *pDst++ = (q15_t)__SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply inputs and store result in destination buffer. */
                *pDst++ = (q15_t)__SSAT((((q31_t)(*pSrcA++) * (*pSrcB++)) >> 15), 16);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> - `SIMD`指令`__PKHBT`，将两个`q15`格式的数据保存的结果数组中，从而一个指令周期就能完成两个数据的存储。

### `arm_mult_q7`函数

```c
/**
  * @brief	用于求7位定点数的乘积
  *	@param  pSrcA	乘数地址	
  * @param	pSrcB	被乘数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行乘法的次数
  */ 
void arm_mult_q7(const q7_t *pSrcA, const q7_t *pSrcB, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q7_t out1, out2, out3, out4; /* Temporary output variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * B */
#if defined(ARM_MATH_DSP)
            	// 将两个Q7格式的数据乘积左移7位，也就是丢掉低7位的数据，并将所得结果饱和到8位精度。
                /* Multiply inputs and store results in temporary variables */
                out1 = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                out2 = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                out3 = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                out4 = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                /* Pack and store result in destination buffer (in single write) */
            	// __PACKq7函数可以在一个时钟周期就能完成相应操作
                write_q7x4_ia(&pDst, __PACKq7(out1, out2, out3, out4));
#else
                *pDst++ = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                *pDst++ = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                *pDst++ = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                *pDst++ = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A * B */
                /* Multiply input and store result in destination buffer. */
                *pDst++ = (q7_t)__SSAT((((q15_t)(*pSrcA++) * (*pSrcB++)) >> 7), 8);
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

## 6. 相反数函数

### `arm_negate_f32`函数

```c
/**
  * @brief	用于求32位浮点数的相反数
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_negate_f32(const float32_t *pSrc, float32_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
#if defined(ARM_MATH_NEON_EXPERIMENTAL)
        float32x4_t vec1;
        float32x4_t res;
        /* Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and then store the results in the destination buffer. */
                vec1 = vld1q_f32(pSrc);
                res = vnegq_f32(vec1);
                vst1q_f32(pDst, res);
                /* Increment pointers */
                pSrc += 4;
                pDst += 4;
                /* Decrement the loop counter */
                blkCnt--;
        }
        /* Tail */
        blkCnt = blockSize & 0x3;
#else
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                *pDst++ = -*pSrc++;
                *pDst++ = -*pSrc++;
                *pDst++ = -*pSrc++;
                *pDst++ = -*pSrc++;
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON_EXPERIMENTAL) */
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                *pDst++ = -*pSrc++;
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

> -  浮点数的相反数求解比较简单，直接在相应的变量前加上负号即可。

### `arm_negate_q31`函数

```c
/**
  * @brief	用于求31位定点数的相反数
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_negate_q31(const q31_t *pSrc, q31_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q31_t in;        /* Temporary input variable */
#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = __QSUB(0, in);
#else
                *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = __QSUB(0, in);
#else
                *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = __QSUB(0, in);
#else
                *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
#endif
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = __QSUB(0, in);
#else
                *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = __QSUB(0, in);
#else
                *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

###  `arm_negate_q15`函数

```c
/**
  * @brief	用于求15位定点数的相反数
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_negate_q15(const q15_t *pSrc,q15_t *pDst,uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q15_t in;        /* Temporary input variable */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q31_t in1; /* Temporary input variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = -A */
#if defined(ARM_MATH_DSP)
                /* Negate and store result in destination buffer (2 samples at a time). */
                in1 = read_q15x2_ia((q15_t **)&pSrc);
                write_q15x2_ia(&pDst, __QSUB16(0, in1));
                in1 = read_q15x2_ia((q15_t **)&pSrc);
                write_q15x2_ia(&pDst, __QSUB16(0, in1));
#else
                in = *pSrc++;
                *pDst++ = (in == (q15_t)0x8000) ? (q15_t)0x7fff : -in;
                in = *pSrc++;
                *pDst++ = (in == (q15_t)0x8000) ? (q15_t)0x7fff : -in;
                in = *pSrc++;
                *pDst++ = (in == (q15_t)0x8000) ? (q15_t)0x7fff : -in;
                in = *pSrc++;
                *pDst++ = (in == (q15_t)0x8000) ? (q15_t)0x7fff : -in;
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                in = *pSrc++;
                *pDst++ = (in == (q15_t)0x8000) ? (q15_t)0x7fff : -in;
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

### `arm_negate_q7`函数

```c
/**
  * @brief	用于求7位定点数的相反数
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	blockSize 转换的数据个数
  */ 
void arm_negate_q7(const q7_t *pSrc, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt; /* Loop counter */
        q7_t in;         /* Temporary input variable */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q31_t in1; /* Temporary input variable */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = -A */
#if defined(ARM_MATH_DSP)
                /* Negate and store result in destination buffer (4 samples at a time). */
                in1 = read_q7x4_ia((q7_t **)&pSrc);
                write_q7x4_ia(&pDst, __QSUB8(0, in1));
#else
                in = *pSrc++;
                *pDst++ = (in == (q7_t)0x80) ? (q7_t)0x7f : -in;
                in = *pSrc++;
                *pDst++ = (in == (q7_t)0x80) ? (q7_t)0x7f : -in;
                in = *pSrc++;
                *pDst++ = (in == (q7_t)0x80) ? (q7_t)0x7f : -in;
                in = *pSrc++;
                *pDst++ = (in == (q7_t)0x80) ? (q7_t)0x7f : -in;
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = -A */
                /* Negate and store result in destination buffer. */
                in = *pSrc++;
#if defined(ARM_MATH_DSP)
                *pDst++ = (q7_t)__QSUB(0, in);
#else
                *pDst++ = (in == (q7_t)0x80) ? (q7_t)0x7f : -in;
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

## 7. 偏移函数

加入偏移量。

```c
/**
  * @brief	用于求加入偏移后的值
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	offset 	偏移量
  * @param	blockSize 加入偏移量的次数
  */ 
void arm_offset_f32(const float32_t *pSrc,float32_t offset,float32_t *pDst, uint32_t blockSize);
void arm_offset_q31(const q31_t *pSrc,q31_t offset,q31_t *pDst, uint32_t blockSize);
void arm_offset_q15(const q15_t *pSrc,q15_t offset,q15_t *pDst, uint32_t blockSize);
void arm_offset_q7(const q7_t *pSrc,q7_t offset,q7_t *pDst, uint32_t blockSize);
```

## 8. 比例函数

乘以一个固定值。

### `arm_scale_f32` 函数

```c
/**
  * @brief	用于求比例因子作用后的值
  *	@param  pSrc	原数据地址	
  * @param	pDst	目的数据地址
  * @param	scale 	比例值
  * @param	blockSize 乘以比例因子的次数
  * @note	pDst[n] = pSrc[n] * scale,   0 <= n < blockSize.   
  */ 
void arm_scale_f32(const float32_t *pSrc,float32_t scale,float32_t *pDst, uint32_t blockSize);
```

### `arm_scale_q31`函数

对于定点数：

```c
pDst[n] = (pSrc[n] * scaleFract) << shift,   0 <= n < blockSize.  
scale = scaleFract * (2^shift).   
```

```c
/**
  * @brief	用于求比例因子作用后的值
  *	@param  pSrc		原数据地址	
  * @param	scaleFact 	比例因子
  * @param	shift		移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	乘以比例因子的次数  
  */ 
void arm_scale_q31(const q31_t *pSrc, q31_t scaleFract, int8_t shift, q31_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;           /* Loop counter */
        q31_t in, out;             /* Temporary variables */
        int8_t kShift = shift + 1; /* Shift to apply after scaling */
        int8_t sign = (kShift & 0x80);

#if defined(ARM_MATH_LOOPUNROLL)
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        // 如果函数的移位形参shiftBits是正数，执行左移。
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A * scale */
                        /* Scale input and store result in destination buffer. */
                        in = *pSrc++;                        /* read input from source */
                        in = ((q63_t)in * scaleFract) >> 32; /* multiply input with scaler value */
                        out = in << kShift;                  /* apply shifting */
                        if (in != (out >> kShift))           /* saturate the result */
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out; /* Store result destination */
                        in = *pSrc++;
                    	// 左移32位，那么结果就是q30格式
                        in = ((q63_t)in * scaleFract) >> 32;
                    	// 多执行了一次左移操作，相当于q30格式，转换为q31格式。
                        out = in << kShift;
                    	// q31的饱和处理
                    	// 数值的左移仅支持将其左移后再右移相应的位数后数值不变的情况，如果不满足这个条件，那么要对输出结果做饱和运算
                        if (in != (out >> kShift))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in << kShift;
                        if (in != (out >> kShift))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in << kShift;
                        if (in != (out >> kShift))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
    	// 如果函数的移位形参shiftBits是负数，执行右移。
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A * scale */
                        /* Scale input and store result in destination buffer. */
                        in = *pSrc++;                        /* read four inputs from source */
                        in = ((q63_t)in * scaleFract) >> 32; /* multiply input with scaler value */
                        out = in >> -kShift;                 /* apply shifting */
                        *pDst++ = out;                       /* Store result destination */
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in >> -kShift;
                        *pDst++ = out;
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in >> -kShift;
                        *pDst++ = out;
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in >> -kShift;
                        *pDst++ = out;
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A * scale */
                        /* Scale input and store result in destination buffer. */
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in << kShift;
                        if (in != (out >> kShift))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A * scale */
                        /* Scale input and store result in destination buffer. */
                        in = *pSrc++;
                        in = ((q63_t)in * scaleFract) >> 32;
                        out = in >> -kShift;
                        *pDst++ = out;
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
}
```

### `arm_scale_q15` 函数

```c
/**
  * @brief	用于求比例因子作用后的值
  *	@param  pSrc		原数据地址	
  * @param	scaleFact 	比例因子
  * @param	shift		移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	乘以比例因子的次数  
  */ 
void arm_scale_q15(const q15_t *pSrc, q15_t scaleFract, int8_t shift, q15_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;                   /* Loop counter */
        uint8_t sign = (shiftBits & 0x80); /* Sign of shiftBits */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q15_t in1, in2; /* Temporary input variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
#if defined(ARM_MATH_DSP)
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        /* Shift the inputs and then store the results in the destination buffer. */
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in1 << shiftBits), 16),
                                                      __SSAT((in2 << shiftBits), 16), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in2 << shiftBits), 16),
                                                      __SSAT((in1 << shiftBits), 16), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in1 << shiftBits), 16),
                                                      __SSAT((in2 << shiftBits), 16), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in2 << shiftBits), 16),
                                                      __SSAT((in1 << shiftBits), 16), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
#else
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
#if defined(ARM_MATH_DSP)
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        /* Shift the inputs and then store the results in the destination buffer. */
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT((in1 >> -shiftBits),
                                                      (in2 >> -shiftBits), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT((in2 >> -shiftBits),
                                                      (in1 >> -shiftBits), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT((in1 >> -shiftBits),
                                                      (in2 >> -shiftBits), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT((in2 >> -shiftBits),
                                                      (in1 >> -shiftBits), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
#else
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
}
```

### `arm_scale_q7`函数

```c
/**
  * @brief	用于求比例因子作用后的值
  *	@param  pSrc		原数据地址	
  * @param	scaleFact 	比例因子
  * @param	shift		移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	乘以比例因子的次数  
  */ 
void arm_scale_q7(const q7_t *pSrc, q7_t scaleFract, int8_t shift, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;           /* Loop counter */
    	// 便于处理正数左移和负数右移，可以直接使用一个右移就可以实现。
        int8_t kShift = 7 - shift; /* Shift to apply after scaling */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q7_t in1, in2, in3, in4;     /* Temporary input variables */
        q7_t out1, out2, out3, out4; /* Temporary output variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        while (blkCnt > 0U)
        {
                /* C = A * scale */
#if defined(ARM_MATH_DSP)
                /* Reading 4 inputs from memory */
                in1 = *pSrc++;
                in2 = *pSrc++;
                in3 = *pSrc++;
                in4 = *pSrc++;
                /* Scale inputs and store result in the temporary variable. */
            	// 对输入的数据做8位的饱和处理
                out1 = (q7_t)(__SSAT(((in1)*scaleFract) >> kShift, 8));
                out2 = (q7_t)(__SSAT(((in2)*scaleFract) >> kShift, 8));
                out3 = (q7_t)(__SSAT(((in3)*scaleFract) >> kShift, 8));
                out4 = (q7_t)(__SSAT(((in4)*scaleFract) >> kShift, 8));
                /* Pack and store result in destination buffer (in single write) */
                write_q7x4_ia(&pDst, __PACKq7(out1, out2, out3, out4));
#else
                *pDst++ = (q7_t)(__SSAT((((q15_t)*pSrc++ * scaleFract) >> kShift), 8));
                *pDst++ = (q7_t)(__SSAT((((q15_t)*pSrc++ * scaleFract) >> kShift), 8));
                *pDst++ = (q7_t)(__SSAT((((q15_t)*pSrc++ * scaleFract) >> kShift), 8));
                *pDst++ = (q7_t)(__SSAT((((q15_t)*pSrc++ * scaleFract) >> kShift), 8));
#endif
                /* Decrement loop counter */
                blkCnt--;
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        while (blkCnt > 0U)
        {
                /* C = A * scale */
                /* Scale input and store result in destination buffer. */
                *pDst++ = (q7_t)(__SSAT((((q15_t)*pSrc++ * scaleFract) >> kShift), 8));
                /* Decrement loop counter */
                blkCnt--;
        }
}
```

## 9. 移位函数

### `arm_shift_q31`函数

```c
/**
  * @brief	用于求定点数移位后的值
  *	@param  pSrc		原数据地址	
  * @param	shiftBits 	移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	移位的次数  
  */ 
void arm_shift_q31(const q31_t *pSrc, int8_t shiftBits, q31_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;                   /* Loop counter */
        uint8_t sign = (shiftBits & 0x80); /* Sign of shiftBits */
#if defined(ARM_MATH_LOOPUNROLL)
        q31_t in, out; /* Temporary variables */
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
                        /* Shift input and store result in destination buffer. */
                        in = *pSrc++;
                        out = in << shiftBits;
                        if (in != (out >> shiftBits))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        in = *pSrc++;
                        out = in << shiftBits;
                        if (in != (out >> shiftBits))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        in = *pSrc++;
                        out = in << shiftBits;
                        if (in != (out >> shiftBits))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        in = *pSrc++;
                        out = in << shiftBits;
                        if (in != (out >> shiftBits))
                                out = 0x7FFFFFFF ^ (in >> 31);
                        *pDst++ = out;
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
                        /* Shift input and store results in destination buffer. */
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = clip_q63_to_q31((q63_t)*pSrc++ << shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
}
```

> - 函数`clip_q63_to_q31`：
>```c
> __STATIC_FORCEINLINE q31_t clip_q63_to_q31(q63_t x)
> {
>    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ? ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
> }
> ```

### `arm_shift_q15`函数

```c
/**
  * @brief	用于求定点数移位后的值
  *	@param  pSrc		原数据地址	
  * @param	shiftBits 	移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	移位的次数  
  */ 
void arm_shift_q15(const q15_t *pSrc, int8_t shiftBits, q15_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;                   /* Loop counter */
        uint8_t sign = (shiftBits & 0x80); /* Sign of shiftBits */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q15_t in1, in2; /* Temporary input variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
#if defined(ARM_MATH_DSP)
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        /* Shift the inputs and then store the results in the destination buffer. */
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in1 << shiftBits), 16),
                                                      __SSAT((in2 << shiftBits), 16), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in2 << shiftBits), 16),
                                                      __SSAT((in1 << shiftBits), 16), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in1 << shiftBits), 16),
                                                      __SSAT((in2 << shiftBits), 16), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT(__SSAT((in2 << shiftBits), 16),
                                                      __SSAT((in1 << shiftBits), 16), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
#else
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
#if defined(ARM_MATH_DSP)
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        /* Shift the inputs and then store the results in the destination buffer. */
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT((in1 >> -shiftBits),
                                                      (in2 >> -shiftBits), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT((in2 >> -shiftBits),
                                                      (in1 >> -shiftBits), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
                        /* read 2 samples from source */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
#ifndef ARM_MATH_BIG_ENDIAN
                        write_q15x2_ia(&pDst, __PKHBT((in1 >> -shiftBits),
                                                      (in2 >> -shiftBits), 16));
#else
                        write_q15x2_ia(&pDst, __PKHBT((in2 >> -shiftBits),
                                                      (in1 >> -shiftBits), 16));
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */
#else
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = __SSAT(((q31_t)*pSrc++ << shiftBits), 16);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
}
```

### `arm_shift_q7` 函数

```c
/**
  * @brief	用于求定点数移位后的值
  *	@param  pSrc		原数据地址	
  * @param	shiftBits 	移位参数，正数表示右移，负数表示左移
  * @param	blockSize 	移位的次数  
  */ 
void arm_shift_q7(const q7_t *pSrc, int8_t shiftBits, q7_t *pDst, uint32_t blockSize)
{
        uint32_t blkCnt;                   /* Loop counter */
        uint8_t sign = (shiftBits & 0x80); /* Sign of shiftBits */
#if defined(ARM_MATH_LOOPUNROLL)
#if defined(ARM_MATH_DSP)
        q7_t in1, in2, in3, in4; /* Temporary input variables */
#endif
        /* Loop unrolling: Compute 4 outputs at a time */
        blkCnt = blockSize >> 2U;
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
#if defined(ARM_MATH_DSP)
                        /* Read 4 inputs */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        in3 = *pSrc++;
                        in4 = *pSrc++;
                        /* Pack and store result in destination buffer (in single write) */
                        write_q7x4_ia(&pDst, __PACKq7(__SSAT((in1 << shiftBits), 8),
                                                      __SSAT((in2 << shiftBits), 8),
                                                      __SSAT((in3 << shiftBits), 8),
                                                      __SSAT((in4 << shiftBits), 8)));
#else
                        *pDst++ = (q7_t)__SSAT(((q15_t)*pSrc++ << shiftBits), 8);
                        *pDst++ = (q7_t)__SSAT(((q15_t)*pSrc++ << shiftBits), 8);
                        *pDst++ = (q7_t)__SSAT(((q15_t)*pSrc++ << shiftBits), 8);
                        *pDst++ = (q7_t)__SSAT(((q15_t)*pSrc++ << shiftBits), 8);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
#if defined(ARM_MATH_DSP)
                        /* Read 4 inputs */
                        in1 = *pSrc++;
                        in2 = *pSrc++;
                        in3 = *pSrc++;
                        in4 = *pSrc++;
                        /* Pack and store result in destination buffer (in single write) */
                        write_q7x4_ia(&pDst, __PACKq7((in1 >> -shiftBits),
                                                      (in2 >> -shiftBits),
                                                      (in3 >> -shiftBits),
                                                      (in4 >> -shiftBits)));
#else
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        *pDst++ = (*pSrc++ >> -shiftBits);
#endif
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        /* Loop unrolling: Compute remaining outputs */
        blkCnt = blockSize % 0x4U;
#else
        /* Initialize blkCnt with number of samples */
        blkCnt = blockSize;
#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
        /* If the shift value is positive then do right shift else left shift */
        if (sign == 0U)
        {
                while (blkCnt > 0U)
                {
                        /* C = A << shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = (q7_t)__SSAT(((q15_t)*pSrc++ << shiftBits), 8);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
        else
        {
                while (blkCnt > 0U)
                {
                        /* C = A >> shiftBits */
                        /* Shift input and store result in destination buffer. */
                        *pDst++ = (*pSrc++ >> -shiftBits);
                        /* Decrement loop counter */
                        blkCnt--;
                }
        }
}
```

> - `__PACKq7`作用是将将4个8位的数据合并成32位数据，实现代码如下：
>
> ```c
> #define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) | \
>                                   (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) | \
>                                   (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | \
>                                   (((int32_t)(v3) << 24) & (int32_t)0xFF000000)  )
> ```

## 10. 减法函数

```c
/**
  * @brief	用于求减法
  *	@param  pSrcA	被减数地址	
  * @param	pSrcB	减数地址
  * @param	pDst	目的数据地址
  * @param	blockSize 执行减法的次数
  */ 
void arm_sub_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t blockSize);
void arm_sub_q31(const q31_t *pSrcA, const q31_t *pSrcB, q31_t *pDst, uint32_t blockSize);
void arm_sub_q15(const q15_t *pSrcA, const q15_t *pSrcB, q15_t *pDst, uint32_t blockSize);
void arm_sub_q7(const q7_t *pSrcA, const q7_t *pSrcB, q7_t *pDst, uint32_t blockSize);
```

