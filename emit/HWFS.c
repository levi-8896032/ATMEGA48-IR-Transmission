#include <iom48v.h>
#include <macros.h>
#include "HWFS.h"
#include "suma.h"
void hongwaifashe(uint a,uint b,uint c,uchar temp)
{ 
  
	BFS;		   //����˳��ߵ�ѹ
  ZZ(a,b,c,temp);
}


  void ZZ(uint a,uint b,uint c,uchar x)
{ 
  TTQ(a,b,c);
  /*������+�����*/
  Z0(a,b,c,x);
  Z0(a,b,c,~x);
}
/************************************************************
���ֽڷ��ͳ���
*************************************************************/
void Z0(uint a,uint b,uint c,uchar temp)
{ 
  uchar v;
  for (v=0;v<8;v++)                     //ѭ���˴�������λ 
       {     
	         TT0(a,b,c,1,6);
			 if(temp&0x01) TT0(a,b,c,0,12); //�������ź�12ms
			 else          TT0(a,b,c,0,6);  //�������ź�6ms   
			 temp >>= 1;                //����һλ
        }    
}

/************************************************************
1��38khz���巢��+��ʱ����
2�����Ƿ������壺1�����䡢0�������䣬��ʱx��us����
*************************************************************/
void TT0(uint a,uint b,uint c,uint BT,uint x)
{
  if(BT == 0)
  {		BFS;
  	    delay(a,b,c,x/6);
  }	//BT=0ʱ����������ֻ��ʱ��BT=1ʱ������������ʱ
  else {	   FS;
   	   		delay(a,b,c,x/6); }
  BFS;			        //����˳����ߵ�ѹ̬
}
void TTQ(uint a,uint b,uint c)
{
  FS;
  delay(a,b,c,10);
  BFS;
  delay(a,b,c,2);
}