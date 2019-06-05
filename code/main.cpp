#include "hwlib.hpp"

#include <base_module.hpp>
#include <hardware_usart.hpp>

#include <cstring>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    // Wait 1 second before running the program
    hwlib::wait_ms(1000);

    r2d2::uart_ports_c uart_port_one = r2d2::uart_ports_c::uart1;
    r2d2::hardware_usart_c uart(9600, uart_port_one);

    uart << "AT";
    char buffer[10] = {};
    int counter = 0;
    hwlib::wait_ms(1000);
    
    while (uart.available() > 0){
        buffer[counter] = uart.getc();
        counter++;
    }
    for(auto i : buffer){
        hwlib::cout << i;
    }
    hwlib::cout << '\n';
    

}
