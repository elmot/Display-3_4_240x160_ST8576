//----------------------------------------------------------------------
/*EASTRISING TECHNOLOGY CO,.LTD.*/
// Module    : ERC240160-2 Series   4 gray scale
// Create    : JAVEN
// Date      : Jul-3-2017
// Drive IC  : ST7586
// INTERFACE : 4 wire SPI
// MCU 		 : STC89LE516
// VDD		 : 3.0V   VLCD: 16.5V   
//----------------------------------------------------------------------
//////////////////////////////////



#include "main.h"
#include "pins.h"

#define uint unsigned int
#define uchar unsigned char

#define code const
#define idata


uchar Contrast_level = 0x3a;

void init();

void test();

void display_black();

void display_white();

void frame();

void all_v1();

void all_v2();

void text_dot(uchar, uchar);

void delayms(uint t);

void write_com(unsigned char idata cmd);

void write_data(unsigned char dat);

void Delay(uint n);

void delay1(uint n);

void Data_processing(uchar temp);

void adj_Contrast(void);

void display_Contrast_level(uchar number);

void write_com_number(uchar x, uchar y, uchar code *n, uchar k);

void display_address(uchar x, uchar y);

void display_gray();

unsigned char code pic_data[];
unsigned char code pic_data1[];
unsigned char code pic_data2[];
unsigned char code pic_data3[];
unsigned char code pic_data4[];
uchar code num[];


void delay1(uint n) {
    while (n--);
}


void Delay(uint n) {
    uint num;
    delayms(n);
//	while(n--)
//
//		{ for(num=0;num<10;num++)
//		if((key_add==0)||(key_dec==0)) adj_Contrast();
//		}
//
//	 	for(;log==1;);
//	return;
}


void delayms(uint t) {
    HAL_Delay(t);
}

void write_com_number(uchar x, uchar y, uchar code *n, uchar k) {
    uchar i, j;

    write_com(0x2c);
    for (i = 0; i < 14; i++) {

        display_address(x, y);

        {
            j = (*(n + 14 * k + i));
            Data_processing(j);
        }
        write_data(0x00);
        y++;
    }
}


void display_Contrast_level(uchar number) {
    uchar number1, number2, number3;
    number1 = number / 100;
    number2 = number % 100 / 10;
    number3 = number % 100 % 10;

    write_com_number(0, 0, num, number1);

    write_com_number(4, 0, num, number2);

    write_com_number(8, 0, num, number3);

}


/*
void adj_Contrast(void)
{	delay1(300);
 	 if((key_add==0)||(key_dec==0))
		{		
		 if	(key_add==0) 
			{if(Contrast_level==0xff)	{display_Contrast_level(Contrast_level); return;}		
			Contrast_level+=1; 
			write_com(0xC1);					
//			display_Contrast_level(Contrast_level);
			delay1(18000);
			if(key_add==0)
				{delay1(18000);
					if(key_add==0)			
						{delay1(18000);
							if(key_add==0)
								{delay1(18000);
									if(key_add==0)

										{while(key_add==0)
											{
												write_com(0xC1);
											//	display_Contrast_level(Contrast_level);
							 					delay1(20000); 
											}
										}
								}				
						}						
				}												
			}
	


		  
	
		 if	(key_dec==0) 
			{if(Contrast_level==0x00)	{display_Contrast_level(Contrast_level); return;}
			Contrast_level-=1; 
			write_com(0xC2);				
//			display_Contrast_level(Contrast_level);
			delay1(18000);
			if(key_dec==0)
				{delay1(18000);
					if(key_dec==0)			
						{delay1(18000);
							if(key_dec==0)
								{delay1(18000);
									if(key_dec==0)

										{while(key_dec==0)
											{
												write_com(0xC2);
												display_Contrast_level(Contrast_level);
							 					delay1(20000); 
											}
										}
								}				
						}
		
				}												
			}

	  	}
	 return;
}
*/






void init() {
    delayms(5);
    setRES(1);
    delayms(5);
    setRES(0);
    delayms(10);
    setRES(1);
    delayms(200);


/*	write_com( 0xD7); // Disable Auto Read
	write_data( 0x9F);
	write_com(0xE0); // Enable OTP Read
	write_data(0x00);
	delayms(10);
	write_com( 0xE3); // OTP Up-Load
	delayms(20);
	write_com( 0xE1); // OTP Control Out
*/
    write_com(0x11); // Sleep Out
    write_com(0x28); // Display OFF
    delayms(50);
    write_com(0xC0); // Vop = B9h
    write_data(Contrast_level);
    write_data(0x01);
    write_com(0xC3); // BIAS = 1/14
    write_data(0x00);
    write_com(0xC4); // Booster = x8
    write_data(0x07);
    write_com(0xD0); // Enable Analog Circuit
    write_data(0x1D);
    write_com(0xB5); // N-Line = 0
    write_data(0x00);
    write_com(0x39); // Monochrome Mode
    write_com(0x3A); // Enable DDRAM Interface
    write_data(0x02);
    write_com(0x36); // Scan Direction Setting
    write_data(0xc0);   //COM:C160--C1   SEG: SEG384-SEG1
    write_com(0xB0); // Duty Setting
    write_data(0x9F);

    write_com(0x20); // Display Inversion OFF
    write_com(0x2A); // Column Address Setting
    write_data(0x00); // SEG0 -> SEG384
    write_data(0x00);
    write_data(0x00);
    write_data(0x7F);
    write_com(0x2B); // Row Address Setting
    write_data(0x00); // COM0 -> COM160
    write_data(0x00);
    write_data(0x00);
    write_data(0x9F);
//	display_white(); // Clear whole DDRAM by ※0§ (384 x 160 x 2)

    write_com(0x29); // Display ON


}


void display_address(uchar x, uchar y) {
    write_com(0x2A); // Column Address Setting
    write_data(0x00); // SEG0 -> SEG240
    write_data(x + 8);// SEG8*3=24
    write_data(0x00);
    write_data(0x7f); // SEG128*3=384  seg x(dont use)  seg n  seg n
    write_com(0x2B); // Row Address Setting
    write_data(0x00); // COM0 -> COM160
    write_data(y);
    write_data(0x00);
    write_data(0x9F);
}

void display_black()  //all  display
{
    uint i, j;
    write_com(0x2C);
    for (i = 0; i < 160; i++) {
        for (j = 0; j < 120; j++)        //1byte data or 2 dot  120*2=240dot
        {
            write_data(0xff);

        }
    }
}

void display_white()        //clear display
{
    uint i, j;
    write_com(0x2C);
    for (i = 0; i < 160; i++) {
        for (j = 0; j < 120; j++)        //1byte data or 2 dot  120*2=240dot
        {
            write_data(0x00);

        }
    }
}


void text_dot(uchar data1, uchar data2) {
    uint i, j;
    write_com(0x2C);
    for (i = 0; i < 80; i++) {
        for (j = 0; j < 120; j++)            //1byte data or 2 dot  120*2=240dot
        {
            write_data(data1);

        }
        for (j = 0; j < 120; j++) {
            write_data(data2);
        }
    }
}


#pragma disable

void write_data(unsigned char dat) {
    unsigned char idata i;
    setDC(1);
    setSCK(0);
    setCS(0);
    for (i = 0; i < 8; i++) {
        setSCK(0);
        _nop_();
        _nop_();
        setSDA(dat & 0x80u);
        dat = dat << 1;
        _nop_();
        _nop_();
        setSCK(1);
        _nop_();
        _nop_();
    }
    setCS(1);
    return;
}


#pragma disable

void write_com(unsigned char idata cmd) {
    unsigned char idata i;
    setDC(0);
    setSCK(0);
    setCS(0);
    for (i = 0; i < 8; i++) {
        setSCK(0);
        _nop_();
        _nop_();
        setSDA(cmd & 0x80u);
        cmd = cmd << 1;
        _nop_();
        _nop_();
        setSCK(1);
        _nop_();
        _nop_();
    }
    setCS(1);
    return;
}


void disppic(unsigned char code *pic) {
    uint k = 0;
    uint i, j;
    uchar temp;
    write_com(0x2C);
    for (i = 0; i < 160; i++) // 240*160 B/W picture for example
    {
        for (j = 0; j < 30; j++) // 240 dot/ 8 bite=30 byte
        {
            temp = pic[k++];

            Data_processing(temp);
        }
    }

}


void Data_processing(uchar temp)  // 4byte  data 8 dot  (B B X - A A X - X X X)   
{
    unsigned char t1, t2;
    unsigned char d1, d2, d3, d4;


    t1 = (temp & 0x80) >> 3;
    t2 = (temp & 0x40) << 1;
    t1 = t1 | t1 >> 1;
    t2 = t2 | t2 >> 1;
    d1 = t1 | t2;

    t1 = (temp & 0x20) >> 1;
    t2 = (temp & 0x10) << 3;
    t1 = t1 | t1 >> 1;
    t2 = t2 | t2 >> 1;
    d2 = t1 | t2;

    t1 = (temp & 0x08) << 1;
    t2 = (temp & 0x04) << 5;
    t1 = t1 | t1 >> 1;
    t2 = t2 | t2 >> 1;
    d3 = t1 | t2;

    t1 = (temp & 0x02) << 3;
    t2 = (temp & 0x01) << 7;
    t1 = t1 | t1 >> 1;
    t2 = t2 | t2 >> 1;
    d4 = t1 | t2;

    write_data(d1);
    write_data(d2);
    write_data(d3);
    write_data(d4);


}


/*
void display_gray()
{uchar j,c,k,b=0;
	write_com(0xaf);
	for(c=0;c<160;c++)
	{	for(k=0;k<16;k++)
		{	for(j=0;j<5;j++)
			{
			write_data(b);
			}
			b=b+0x11;
		}	write_data(00);//There are 162-160=2 segment need to write data

	}
	write_com(0xad);

}

*/
void screenMain() {
//    IE=0x81;
//	IP=0x01;
//	TCON=0x01;
//	int0=1;
    init();
    while (1) {
        display_address(0, 0);
        display_black();
        Delay(6000);
        display_address(0, 0);
        display_white();
        Delay(6000);
        /*         	display_address(0,0);
                   text_dot(0xc0,0x18);
                  Delay(60000);
                  text_dot(0x18,0xc0);
                   Delay(60000);
                   text_dot(0xff,0x00);
                   Delay(60000);
                   text_dot(0x00,0xff);
                   Delay(60000);
                   text_dot(0xc0,0xc0);
                   Delay(60000);
                   text_dot(0x18,0x18);
                   Delay(60000);
                   display_address(0,0);
       */
        disppic(pic_data);
        Delay(6000);
        Delay(6000);
        write_com(0x21);
        Delay(6000);
        Delay(6000);
        write_com(0x20);

        display_address(0, 0);
        disppic(pic_data1);
        Delay(6000);
        Delay(6000);
        write_com(0x21);
        Delay(6000);
        Delay(6000);
        write_com(0x20);

        display_address(0, 0);
        disppic(pic_data2);
        Delay(6000);
        Delay(6000);
        write_com(0x21);
        Delay(6000);
        Delay(6000);
        write_com(0x20);


        display_address(0, 0);
        disppic(pic_data3);
        Delay(6000);
        Delay(6000);
        write_com(0x21);
        Delay(6000);
        Delay(6000);
        write_com(0x20);

        display_address(0, 0);
        disppic(pic_data4);
        Delay(6000);
        Delay(6000);
        write_com(0x21);
        Delay(6000);
        Delay(6000);
        write_com(0x20);


    }
}

#include "data.inc"