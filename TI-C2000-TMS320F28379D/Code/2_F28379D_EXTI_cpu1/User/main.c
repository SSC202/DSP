#include "device.h"
#include "driverlib.h"
#include "F28x_Project.h"

interrupt void xint1_isr(void);

void main(void) {
    Device_init();                  // init system
    Device_initGPIO();              // init GPIO
    Interrupt_initModule();         // init Interrupt
    Interrupt_initVectorTable();    // init VectorTable

    // set interrupt
    Interrupt_register(INT_XINT1, &xint1_isr);
    Interrupt_enable(INT_XINT1);
    EINT;

    // Set GPIO
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setDirectionMode(35, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(35, GPIO_PIN_TYPE_PULLUP);

    GPIO_setPinConfig(GPIO_79_GPIO79);
    GPIO_setDirectionMode(79, GPIO_DIR_MODE_IN);
    GPIO_setQualificationMode(79, GPIO_QUAL_6SAMPLE);
    GPIO_setQualificationPeriod(79, 510);
    GPIO_setPadConfig(79, GPIO_PIN_TYPE_PULLUP);


    // Set X-BAR
    XBAR_setInputPin(XBAR_INPUT4, 79);

    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    while(1)
    {
        ;
    }
}


interrupt void xint1_isr(void)
{
    GPIO_togglePin(35);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
