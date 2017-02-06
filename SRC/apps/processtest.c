#include "stm32f10x_it.h"

#include "contiki.h"
#include <stdio.h>


PROCESS(blink_process, "Blink");
//AUTOSTART_PROCESSES(&blink_process);
PROCESS_THREAD(blink_process, ev, data)
{
  
  PROCESS_BEGIN();
  while(1) 
  {
    static struct etimer et;
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    //打开LED
   // GPIO_ResetBits(GPIOC,GPIO_Pin_6);
    GPIO_SetBits(GPIOB,GPIO_Pin_15);
    printf("LED ON\r\n");
    
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    //关闭LED
    //GPIO_SetBits(GPIOC,GPIO_Pin_6);
    GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    printf("LED OFF\r\n");
    
    
  }
   PROCESS_END();
}



//测试任务1

PROCESS(task1_process, "task1");

PROCESS_THREAD(task1_process, ev, data)
{
  
  PROCESS_BEGIN();
  static struct etimer et2;
  etimer_set(&et2, CLOCK_SECOND/4);
  while(1) 
  {
    
    static u8 led1 = 0;
    
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et2));
    
    //打开LED
   // GPIO_ResetBits(GPIOC,GPIO_Pin_6);
    if(led1==0)
    {
      led1 = 1;
      GPIO_SetBits(GPIOB,GPIO_Pin_15);
    }
    else
    {
      led1 = 0;
      GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    }
    printf("led1: %d \r\n",led1); 
    etimer_reset(&et2);//重启etimer
  }
   PROCESS_END();
}