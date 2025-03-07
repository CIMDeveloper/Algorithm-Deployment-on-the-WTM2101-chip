/**
* @file    main.c
* @brief   This example describes how to use the I2S to transfer/receive continuously converted data.
* @date    2023-02-07
* Copyright (c) 2023 Witmem Technology Co., Ltd
* All rights reserved.
*
******************************************************************************
*/

#include "main.h"

#define I2SCLK_DIV  (16)
#define TX_LEN      (10)

static void system_clock_init(void);
static void i2s0_config(void);
static void i2s1_config(void);
static int i2s_test(void);
static void uart0_config(void);

uint32_t tx_buffer[TX_LEN] = {0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x88888888};
volatile uint32_t rx_buffer[sizeof(tx_buffer) / sizeof(uint32_t)] = {0};
volatile uint32_t rx_index = 0;

void I2S1_IRQHandler(void)
{
    if (I2S_IT_GetStatBit(I2S1, I2S_IT_TXFO))
    {
        I2S_IT_TORClr(I2S0);
    }
}

void I2S0_IRQHandler(void)
{
    while (I2S_IT_GetStatBit(I2S0, I2S_IT_RXDA)) 
    {
        I2S_ReceiveData(I2S0, (uint32_t *)(&rx_buffer[rx_index]), 2);

        if (rx_buffer[rx_index] != 0) /* filter  0*/ 
        {    
            rx_index += 2;
        }
    }

    if (I2S_IT_GetStatBit(I2S0, I2S_IT_RXFO)) 
    {
        I2S_IT_RORClr(I2S0);
    }
}

void main(void)
{
    /* retarget printf to NONE */      
    printf_output_redirect_set(PRINTF_RETARGET_NONE);
 
      /*Reset i2s0 and i2s1 */
    RCC_Peri_Rst(RCC_I2S0_RSTN);
    RCC_Peri_Rst(RCC_I2S1_RSTN);

    /* Enable N307 Interrupt */
    __enable_irq();
    __enable_mcycle_counter();
   
    /* retarget printf to segger UATR0 */      
    printf_output_redirect_set(PRINTF_RETARGET_UART0);
 
    /* Initial clock */
    system_clock_init();

    /* config uart0 for print */
    uart0_config();

    /* Config i2s0 and i2s1 */
    i2s0_config();
    i2s1_config();

    /* Show message */
    printf("BUILD: %s %s\r\n", __DATE__, __TIME__);
    
    /*Application entry */
    while (1) 
    {
        if (i2s_test() == 0) 
        {
            printf("i2s_test ok\r\n");
        } 
        else 
        {
            printf("i2s_test err\r\n");
        }
        system_delay_ms(100);
    }
}

static void uart0_config(void)
{
    UART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_CLK_EN_Ctl(RCC_UART0_CLKEN,ENABLE);

    GPIO_InitStructure.Pin = GPIO_PIN_16 | GPIO_PIN_17;    /* uart0 pin config */
    GPIO_InitStructure.Alternate = GPIO_AF16_UART0 | GPIO_AF17_UART0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.Parity = UART_PARITY_NONE;
    USART_InitStructure.StopBits = UART_STOPBITS_1;
    USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
    USART_InitStructure.Mode = UART_MODE_UART;
    USART_InitStructure.FIFOCtl = DISABLE;
    UART_Init(UART0, &USART_InitStructure);

    UART_IT_Cfg(UART0, UART_IT_ERBFI, DISABLE);
}

static void i2s1_config(void)
{
    uint32_t clk_num = 0;
    GPIO_InitTypeDef GPIO_I2S1InitStructure;

    /* Initialize gpio */
    GPIO_I2S1InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_I2S1InitStructure.Alternate = GPIO_AF10_I2S1 | GPIO_AF11_I2S1 | GPIO_AF12_I2S1 | GPIO_AF13_I2S1;
    GPIO_Init(GPIOA, &GPIO_I2S1InitStructure);

    RCC_CLK_EN_Ctl(RCC_I2S1_CLKEN, ENABLE);
    I2S_Ctl(I2S1, DISABLE);

    /* Select i2s1 mode */
    I2S_Mode_Sel(I2S1, I2S_MASTER);

    /* Set clknum of sampling */
    I2S_ClkCfg(I2S1, I2S_SCLKNUM_32, I2S_GATESCLKNUM_NONE);
    RCC_I2S1_Set_ClkDiv(I2SCLK_DIV);   /* I2SCLK_DIV = SYSTEM_CLK / (SAMPLE_RATE *32*2) */

    /* Config data length*/
    I2S_TxCfg(I2S1, I2S_RES_LEN_32);

    /*Set TX level of interrupt */
    I2S_TxFIFO_LVLCfg(I2S1, 7);
    I2S_TxFIFO_Flush(I2S1);
    
    /* Enable TX interrupt */
    I2S_IT_MskCtl(I2S1, I2S_IT_TXFO, DISABLE);
    ECLIC_ClearPendingIRQ(I2S1_IRQn);
    ECLIC_SetPriorityIRQ(I2S1_IRQn, 2);
    ECLIC_SetTrigIRQ(I2S1_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(I2S1_IRQn);

    /* Enable i2s1 */
    I2S_Ctl(I2S1, ENABLE);
    I2S_TxBlkCtl(I2S1, ENABLE);
    I2S_RxChlCtl(I2S1, DISABLE);
    I2S_TxChlCtl(I2S1, ENABLE);
    I2S_ClkCtl(I2S1, ENABLE);
}

static void i2s0_config(void)
{
    uint32_t clk_num = 0;
    GPIO_InitTypeDef GPIO_I2S0InitStructure;

    /* Initial gpio */
    GPIO_I2S0InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_I2S0InitStructure.Alternate = GPIO_AF0_I2S0 | GPIO_AF1_I2S0 | GPIO_AF2_I2S0 | GPIO_AF3_I2S0;
    GPIO_Init(GPIOA, &GPIO_I2S0InitStructure);

    RCC_CLK_EN_Ctl(RCC_I2S0_CLKEN, ENABLE);
    I2S_Ctl(I2S0, DISABLE);

    /* Select i2s0 mode */
    I2S_Mode_Sel(I2S0, I2S_SLAVE);

    /* Set clknum of sampling */
    I2S_ClkCfg(I2S0, I2S_SCLKNUM_32, I2S_GATESCLKNUM_NONE);
    RCC_I2S0_Set_ClkDiv(I2SCLK_DIV);   /* I2SCLK_DIV = SYSTEM_CLK / (SAMPLE_RATE *32*2) */

    /* Config data length*/
    I2S_RxCfg(I2S0, I2S_RES_LEN_32);

    /*Set TX level of interrupt */
    I2S_RxFIFO_LVLCfg(I2S0, 1);
    I2S_RxFIFO_Flush(I2S0);

    /* Enable TX interrupt */
    I2S_IT_MskCtl(I2S0, I2S_IT_RXDA, DISABLE);
    ECLIC_ClearPendingIRQ(I2S0_IRQn);
    ECLIC_SetPriorityIRQ(I2S0_IRQn, 1);
    ECLIC_SetTrigIRQ(I2S0_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
    ECLIC_EnableIRQ(I2S0_IRQn);

    /* Enable i2s0 */
    I2S_Ctl(I2S0, ENABLE);
    I2S_TxBlkCtl(I2S0, DISABLE);
    I2S_RxBlkCtl(I2S0, ENABLE);
    I2S_RxChlCtl(I2S0, ENABLE);
    I2S_TxChlCtl(I2S0, DISABLE);
}

static int i2s_test(void)
{
    for (uint32_t i = 0; i < sizeof(tx_buffer) / sizeof(tx_buffer[0]); i++) 
	{
        tx_buffer[i] = i + 1;
    }

    memset((void *)(rx_buffer), 0, sizeof(rx_buffer));

    uint8_t run = 0;

    rx_index = 0;
    I2S_TransmitData(I2S1, tx_buffer, 8);
    system_delay_ms(1);
    int ret = memcmp((void *)(tx_buffer), (void *)(rx_buffer), 8 * 4);
    return ret;
}

static void system_clock_init(void)
{
    int ret = 0; 
    /*The clock instance*/
    Hal_Clock_InitTypeDef* hal_clock_instance = hal_clock_instance_get();
    Hal_Clock_24mosc_Configuration hal_clock_24mosc_Configuration;

    /*Construct 24mosc related configuration parameters*/
    hal_clock_24mosc_Configuration.use_24mosc_way = HAL_CLOCK_24MOSC_EXTERNAL;
    hal_clock_24mosc_Configuration.clock_hz = 24576000;
    hal_clock_24mosc_Configuration.clock_divider = 1;
    hal_clock_24mosc_Configuration.internal_24mosc_calibration_flag = DISABLE;
    hal_clock_24mosc_Configuration.calibration_way = HAL_CLOCK_24MOSC_USE_32KOSC_CALIBRATION_PARAMETER;

    /*Initialize the clock instance.the system clock is from external 24576000 crystal oscillator.*/
    ret = hal_clock_init(hal_clock_instance,HAL_CLOCK_24MOSC,HAL_CLOCK_24MOSC,&hal_clock_24mosc_Configuration,0,1,1);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }

    /*According to the clock instance, initialize the hardware*/
    ret = hal_clock_open(hal_clock_instance);
    if(ret <= 0)
    {
        printf("hal_clock_init error:%d\r\n", ret);
    }
}
