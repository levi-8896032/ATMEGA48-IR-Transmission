/*********ͷ�ļ�����*************/
#include <iom48v.h>
#include <macros.h>
#include <stdio.h>
#include "config.h"
#include "HWFS.h"
#include "suma.h"
/***********�궨��*************/
#define  uchar unsigned char 
#define  uint unsigned int
void Delayus(uint US);
void port_init(void);
void Delay_ms (uint ms);
void init_devices(void);
uint mega48_ad(void);
unsigned int ada,k1,tempvalue=0;
/*******************************************
��������: Delayus
��    ��: ��ʱָ��΢�루8M����
��    ��: US--��ʱ��΢����(��Լ�����Ǻܾ�ȷ��MSԽ��Խ׼ȷ)
����ֵ  : ��
/********************************************/
void Delayus(uint US)		  
{
 int i;
 US=US*5/4;		  	 //5/4����8MHz�����£�ͨ���������淴��ʵ��õ�����ֵ
 for( i=0;i<US;i++); 
}

/*******************************************
��������: IO�ڳ�ʼ������
��    ��: ʵ��IO��ʼ��
��    ��: ��
�� �� ֵ: ��
/********************************************/
void port_init(void)
{
 DDRC  = 0x0E;  //PC0��ΪAD������
 PORTC = 0x0E;
DDRD  = 0xFF;
 PORTD = 0x00;
DDRB=BIT(0);
PORTB&=~BIT(0);
}
/*******************************************
��������: ������ʱ����
��    ��: ʵ��������ʱ
��    ��: ms--��ʱ�ĺ�����
�� �� ֵ: ��
/********************************************/
extern void Delay_ms (uint ms)
{
 	 unsigned int i,j;
	 for(i=0;i<ms;i++)
	 	for(j=0;j<1141;j++);
}

/*******************************************
��������: �豸��ʼ������
��    ��: ��AVR��Ƭ�����г�ʼ��
��    ��: ��
�� �� ֵ: ��
/********************************************/
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 port_init();
// timer1_init();

 MCUCR = 0x00;
 EICRA = 0x00; //extended ext ints
 EIMSK = 0x00;
 
 TIMSK0 = 0x00; //timer 0 interrupt sources
 TIMSK1 = 0x00; //timer 1 interrupt sources
 TIMSK2 = 0x00; //timer 2 interrupt sources
 
 PCMSK0 = 0x00; //pin change mask 0 
 PCMSK1 = 0x00; //pin change mask 1 
 PCMSK2 = 0x00; //pin change mask 2
 PCICR = 0x00; //pin change enable 
 PRR = 0x00; //power controller
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}
/*************************************************************
��������: AD����������
��    ��: ʵ�ֵ�ѹ��AD������
��    ��: ��
�� �� ֵ: addata--AD������ֵ��1
/************************************************************/
uint mega48_ad(void)
{
     uint addata;
	 ADCSRA = 0x00; //disable adc
	 //PORTA&=~BIT(PA4);
	 ADMUX=0x00;//ѡ���ⲿ�ο���ѹ
	 //ADMUX=0xC4;//ѡ���ڲ��ο���ѹ
	 ACSR=0X80;
	 //ADCSRB = 0x00;
	 ADCSRA = 0xC7;
	 while(!(ADCSRA&(BIT(ADIF))));
     addata=ADCL;
	 addata=addata+ADCH*256;
	 //ADCSRA = 0x00;
	 return addata;
}   

/********************************************
��������: ������
��    ��: ʵ�ֺ������幦�ܡ�
��    ��: ��
�� �� ֵ: ��
********************************************/
void main(void)
{
  uint temp_high,temp_middle,temp_low,tempvalue,k2;
  uchar al;
  init_devices();
  while(1)
    {
		k1=0;
		k2=0;
		ada=0;
      		ada=mega48_ad();  //����AD�Ĳ���ֵ
			while(ada<(NTCres[k2]))
			{
			 	k1=k1+2;
				k2++;
				if(k1>410) break;
				tempvalue=k1;
				}
		
		temp_high=tempvalue/100;//ʮλ
		temp_middle=tempvalue%100/10;//��λ
		temp_low=tempvalue%10;//С��     x
		al=k2%256;
        hongwaifashe(temp_high,temp_middle,temp_low,al);
	}
}
