#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
	
void PortF_init();
void systick_init (void);
void SYS_TICK_Wait_10ms(uint32_t delay);
void SYS_TICK_Wait(uint32_t delay);

int main()
{
	PortF_init();
	systick_init();
	GPIO_PORTF_DATA_R = 0; 
	while(1)
	{	int i;
    	for( i=1;i<=15 ;i+=2)
		{
			GPIO_PORTF_DATA_R = i;
			SYS_TICK_Wait(100);

		}
	}		
}

void PortF_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000020; //portF activated
	while( (SYSCTL_RCGCGPIO_R & 0x20)==0 ) {};   
	GPIO_PORTF_DIR_R = 0X0E ; //output pf1,pf2,pf3
	GPIO_PORTF_DEN_R = 0X0E;   
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock portF
}

	
void systick_init (void)
{
		NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R = 0x00FFFFFF;
		NVIC_ST_CURRENT_R = 0;   
		NVIC_ST_CTRL_R = 0x00000005;
}


void SYS_TICK_Wait(uint32_t delay)
{        
    NVIC_ST_RELOAD_R = delay-1; 
    NVIC_ST_CURRENT_R = 0; 
    while((NVIC_ST_CTRL_R&0x00010000)==0) {}; //bit 16 count
}

void SYS_TICK_Wait_10ms(uint32_t delay){
	uint32_t i;
	for (i =0; i<delay;i++){
		SYS_TICK_Wait(800000);
	}
}
