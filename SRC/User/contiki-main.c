/*
#include <stm32f10x_map.h>
#include <stm32f10x_dma.h>
#include <gpio.h>
#include <nvic.h>
*/

//替换头文件
#include "stm32f10x.h"
#include "processlist.h"//任务列表

#include <stdint.h>
#include <stdio.h>

#include <debug-uart.h>
#include <clock.h>

#include <sys/process.h>
#include <sys/procinit.h>
#include <etimer.h>
#include <sys/autostart.h>

unsigned int idle_count = 0;

void led_init();

AUTOSTART_PROCESSES(&blink_process,&receive_process);

/*  HSE = 12 MHz*/
/*  PLLCLK = HSE * 6 = 72 MHz*/
int main()
{
  dbg_setup_uart();
  led_init();
  printf("Initialising\r\n");
  
  clock_init();
  process_init();
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  //process_start(&blink_process,NULL);
  printf("Processes running\r\n");
  while(1) {
    do 
    {
    } 
    while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */ 
  }
  return 0;
}

void led_init()
{
  /*
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  
  //PC6 推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  */
  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
    //PB5 推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}