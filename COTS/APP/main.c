#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ClockControl_Private.h"
#include "ClockControl_Configuration.h"
#include "ClockControl_Interface.h"
#include "GPIO_Private.h"
#include "GPIO_Configuration.h"
#include "GPIO_Interface.h"
#include "SysTick_Private.h"
#include "SysTick_Configuration.h"
#include "SysTick_Interface.h"
#include "Interrupt_Private.h"
#include "Interrupt_Configuration.h"
#include "Interrupt_Interface.h"
#include "Led_Private.h"
#include "Led_Configuration.h"
#include "Led_Interface.h"
static u32 OnTime  = 1;
static u32 OffTime = 1;
static u8 OnStatus = 0;
static u8 OffStatus = 1;
static u32 i = 0;
static u32 j = 0;
void SysTick(void);                                     /*prototype for systick isr																																	 */
extern void SysTick_SetCallBack(void (*fun_ptr) (void));/*extern SysTick_SetCallBack function which defined in another .c file (Interrupt_Program.c) */ 
int main(void)
{
	SysTick_SetCallBack(SysTick);
	ClockControl_int();
	GPIO_Init();
	Led_Init();
  SysTick_Init();
	SysTickI_Enable();
	SysTick_Enable();
	while (1)
	{	
		if(i >= (OffTime*100))
		{
			i = 0;
			OnStatus = 1;
			OffStatus = 0;
			Led_On();
		}
		else if(j >= (OnTime*100))
		{
			j = 0;
			OnStatus = 0;
			OffStatus = 1;
			Led_Off();
		}
		
	}
}

void SysTick(void)
{
	if(OffStatus == 1 && OnStatus == 0)
	{
		i++;
	}
	else if (OffStatus == 0 && OnStatus == 1)
	{
		j++;
	} 
}







