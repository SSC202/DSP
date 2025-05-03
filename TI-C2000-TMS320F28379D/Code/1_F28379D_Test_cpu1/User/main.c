#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"

void main(void) {
    Device_init();
    Device_initGPIO();
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setDirectionMode(35, GPIO_DIR_MODE_OUT);

    while(1) {
        GPIO_writePin(35, 1);
        DELAY_US(500000);
        GPIO_writePin(35, 0);
        DELAY_US(500000);
    }
}
