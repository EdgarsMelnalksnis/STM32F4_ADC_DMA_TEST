/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"

void init_GPIOB(void);
void init_GPIOC(void);
void init_GPIOA(void);
void init_Interrupts(void);
void init_DMA2(void);
void init_ADC1(void);

uint16_t adc1[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //make new file for global variables

int main(void) {
	init_GPIOB();
	init_GPIOA();
	init_GPIOC();
	//init_Interrupts();
	init_ADC1();
	init_DMA2();

	(*((int *) (0x40012000u + 0x8u))) |= 1 << 30; //start ADC
	for (;;)
		;
}

void init_GPIOB(void) {
	//configure GPIOB
	GPIO_InitTypeDef GPIO_InitDef; //structure

	//enable clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitDef.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1);
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOB, &GPIO_InitDef); //pin 0, 1, 2 analog

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

}

void init_GPIOA(void) {
	//enable clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//configure GPIOB
	GPIO_InitTypeDef GPIO_InitDef; //structure

	GPIO_InitDef.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
			| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitDef); //pin 0, 1, 2 analog
}

void init_GPIOC(void) {
	//configure GPIOC
	GPIO_InitTypeDef GPIO_InitDef; //structure

	//enable clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitDef.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
			| GPIO_Pin_4 | GPIO_Pin_5);
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOB, &GPIO_InitDef);

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

}

void init_Interrupts(void) {
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//systick is here??
	//sysTick config
	SysTick_Config(SystemCoreClock / 1000);
}

void init_ADC1(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef ADC_InitStructure;

	//  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	//  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 14;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_3Cycles);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_480Cycles);
	// ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11,
			ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12,
			ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13,
			ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14,
			ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15,
			ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16,
			ADC_SampleTime_480Cycles);

	ADC_Cmd(ADC1, ENABLE);  //enable ADC1
	ADC_DMACmd(ADC1, ENABLE); //enable DMA for ADC
	// ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void init_DMA2(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	(*((uint32_t *) (0x40026400u + 0x18u))) = (uint32_t) 0x4001204cu; //set ADC1_DR port address DMA_SxPAR
	(*((uint32_t *) (0x40026400u + 0x1cu))) = (uint32_t) &adc1[0]; // SRAM adrese..vajag aspkatiities, vai stack kkur tur neparaskta
	(*((uint32_t *) (0x40026400u + 0x14u))) = 14; //number of data to be transferred
	(*((uint32_t *) (0x40026400u + 0x10u))) |= (1 << 8 | 1 << 10 | 1 << 11
			| 1 << 13); //(1<<8|1<<10|1<<12|1<<14);//circular mode,memory pointer is incremented,32 bit peripheral and 32 bit memory
	(*((uint32_t *) (0x40026400u + 0x10u))) |= 1 << 0; //starts DMA
// DMA_Cmd(DMA2_Channel1, ENABLE);
}
