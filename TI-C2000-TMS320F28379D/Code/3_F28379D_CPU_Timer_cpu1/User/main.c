#include "device.h"
#include "driverlib.h"
#include "F28x_Project.h"

__interrupt void cpuTimer0_ISR(void);

void initCPUTimer(void);
void configCPUTimer(uint32_t cpuTimer, float freq, float period);

void main()
{
    Device_init();

    // GPIO init
    Device_initGPIO();
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setDirectionMode(35, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(35, GPIO_PIN_TYPE_PULLUP);

    // PIE and PIE vector init
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // CPU Timer init
    Interrupt_register(INT_TIMER0, &cpuTimer0_ISR);
    initCPUTimer();
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000000);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);
    CPUTimer_startTimer(CPUTIMER0_BASE);
    EINT;
    ERTM;

    while(1)
    {
        ;
    }
}

__interrupt void cpuTimer0_ISR(void)
{
    GPIO_togglePin(35);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

void initCPUTimer(void)
{
    // Set Max Period
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    // Set Prescaler 0
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    // Stop Timer
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    // Reload Counter
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
}

/**
 * @brief   initializes the selected timer
 * @param   freq    entered as Hz
 * @param   period  uSeconds
 */
void configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);
    CPUTimer_setPreScaler(cpuTimer, 0);
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    // Set Emulation Mode
    CPUTimer_setEmulationMode(cpuTimer, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    // Enable interrupt
    CPUTimer_enableInterrupt(cpuTimer);
}
