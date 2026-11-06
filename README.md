# STM32L476 Bare-Metal UART Debugger

UART transmit over the ST-Link virtual COM port on the **NUCLEO-L476RG**, written in C with **no HAL**. Only raw register access.

## What it does

Sends text from the STM32 to a PC terminal through **USART2**, so the firmware can print debug messages.

## How it works

| Step | Details |
|---|---|
| Pins | PA2 = `USART2_TX`, PA3 = `USART2_RX`, both set to alternate function **AF7** (`MODER`, `AFRL`) |
| Clocks | GPIOA (`RCC_AHB2ENR`) and USART2 (`RCC_APB1ENR1`, bit 17) |
| Baud rate | 115200, 8N1, `BRR = 35` on the default 4 MHz MSI clock (about 0.8 % error) |
| Enable | Transmitter (`TE`) and USART (`UE`) in `USART_CR1` |
| Send a byte | Poll the `TXE` flag in `USART_ISR`, then write the byte to `USART_TDR` |
| Print | A loop that sends one character at a time until the string ends |

The ST-Link chip on the board collects the bytes from PA2 and forwards them over USB, so no extra hardware is needed.

## Build and run

```bash
make
make flash
sudo picocom -b 115200 /dev/ttyACM0     # exit with Ctrl+A, Ctrl+X
```

On WSL, the ST-Link has to be passed through from Windows with [usbipd-win](https://github.com/dorssel/usbipd-win).

## References

- RM0351: STM32L47x/L48x/L49x/L4Axx reference manual (USART chapter)
- DS10198: STM32L476xx datasheet (alternate function table)
