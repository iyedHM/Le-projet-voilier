#include "MyGPIO.h"

// Initialize GPIO configuration
void MyGPIO_Init(MyGPIO_Struct_TypeDef *GPIOStructPtr) {
    // Clear and set GPIO configuration for pin 1 of port A (example)
    GPIOA->CRL &= ~(0xF << 4);  // Clear config
    GPIOA->CRL |= (0x2 << 4);   // Set new config
    
    // Enable clocks for the selected GPIO port
    if (GPIOStructPtr->GPIO == GPIOA) {
        RCC->APB2ENR |= (0x01 << 2);  // Enable clock for GPIOA
    }
    if (GPIOStructPtr->GPIO == GPIOB) {
        RCC->APB2ENR |= (0x01 << 3);  // Enable clock for GPIOB
    }
    if (GPIOStructPtr->GPIO == GPIOC) {
        RCC->APB2ENR |= (0x01 << 4);  // Enable clock for GPIOC
    }

    // Initialize the GPIO pin configuration
    if (GPIOStructPtr->GPIO_Pin < 8) { // For Pin form 0 to 7
        GPIOStructPtr->GPIO->CRL &= ~(0xF << (GPIOStructPtr->GPIO_Pin * 4));  // Clear config for CRL (pins 0-7)
        
        // Configure mode and pull settings
        if (GPIOStructPtr->GPIO_Conf == In_PullDown) {
            GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4));  // Set pull-down
            GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);  // Reset ODR pin to 0 so that he can see the difference between pull_up and pull_down
        } else if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
            GPIOStructPtr->GPIO->CRL |= ((GPIOStructPtr->GPIO_Conf - 2) << (GPIOStructPtr->GPIO_Pin * 4));  // Set pull-up
            GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);  // Set ODR pin to 1
        } else {
            GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin * 4));  // Set other configuration
        }
    } else { // from 8 to 15
        GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Clear config for CRH (pins 8-15)

        // Configure mode and pull settings
        if (GPIOStructPtr->GPIO_Conf == In_PullDown) {
            GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Set pull-down
            GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);  // Reset pin to 0
        } else if (GPIOStructPtr->GPIO_Conf == In_PullUp) {
            GPIOStructPtr->GPIO->CRH |= ((GPIOStructPtr->GPIO_Conf - 2) << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Set pull-up
            GPIOStructPtr->GPIO->ODR |= (0x1 << (GPIOStructPtr->GPIO_Pin - 2));  // Set pin to 1
        } else {
            GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << ((GPIOStructPtr->GPIO_Pin - 8) * 4));  // Set other configuration
        }
    }
}

// Read GPIO pin value
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    // Return the pin value (0 or 1)
    return (GPIO->IDR >> GPIO_Pin) & 0x1;
}

// Set a GPIO pin high
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->ODR |= (0x1 << GPIO_Pin);  // Set the pin to high (1)
}

// Set a GPIO pin low
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->ODR &= ~(0x1 << GPIO_Pin);  // Set the pin to low (0)
}

// Toggle a GPIO pin state
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin) {
    GPIO->ODR ^= (0x1 << GPIO_Pin);  // Toggle the pin state (0 -> 1, 1 -> 0)
}
