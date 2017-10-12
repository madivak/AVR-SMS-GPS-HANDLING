// /*
//  * GPS-UART-BUF.c
//  *
//  * Created: 9/23/2017 5:37:46 PM
//  * Author : madiv
//  */ 
// #define F_CPU 1000000UL 
// #include <avr/io.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "AT-SMS.h"
// 
// #define FOSC 2000000UL // Clock Speed
// #define BAUD 9600
// #define MYUBRR (((FOSC / (BAUD * 16UL))) - 1)
// 
// static FILE uart0_output = FDEV_SETUP_STREAM(USART0_Transmit, NULL, _FDEV_SETUP_WRITE);
// //static FILE uart1_output = FDEV_SETUP_STREAM(USART1_Transmit, NULL, _FDEV_SETUP_WRITE);
// static FILE uart1_input = FDEV_SETUP_STREAM(NULL, USART1_Receive, _FDEV_SETUP_READ);
// static FILE uart0_input = FDEV_SETUP_STREAM(NULL, USART0_Receive, _FDEV_SETUP_READ);
// 
// int CheckSMS();
// void checkOKstatus();
// char sample_GPS_data (void);//int t);
// void SendToTCP(int x);
// int CarStatus(int n);
// 
// int a; char w; int y;
// char input;
// char buff[5];
// 
// #define CAR_ON	PORTB |= (1<<PORTB1)
// #define CAR_OFF	PORTB &= ~(1<<PORTB1)
// 
// int main( void )
// {
// 	USART1_Init(MYUBRR);
// 	USART0_Init(MYUBRR);
// 	DDRB |= (1<<DDB1); //set PORTB1 as output
// 	
// 	
//  	stdin = &uart1_input;
//  	stdout = &uart0_output;
// //	sei();
// 	
// 	_delay_ms(1000);
// 	CAR_ON;
// 	y = 0;
// 
// 	while(1) 
// 	{
// 		CheckSMS();
// 		y = buff[0];
// 		CarStatus(y);
// 		
//  		fdev_close();
// 		stdout = &uart0_output;
// 		stdin = &uart0_input;
//  		
// 		_delay_ms(3000);
// // 		CarStatus(y);
// 		sample_GPS_data ();
// 		SendToTCP(y);
// // 		printf("\r\nPrinting buffer\n");
// // 		printf("\r\nValue of Buffer [0] = %d", buff[0]);
// //		i=0;
// 
// 		fdev_close();
// 		stdout = &uart0_output;
// 		stdin = &uart1_input;
//  		_delay_ms(500);
// 	}
// 	return 0;
// }
// 
// int CheckSMS()
// {
// 	//char w; 
// 	a=0;
// 	printf("AT\r\n");
// 	checkOKstatus();
// 	
// 	printf("AT+CMGF=1\r\n");
// 	checkOKstatus();
// 	
// 	printf("AT+CMGL=\"REC UNREAD\"\r\n");
// 	while (a < 2) //skip the <LF>
// 	{
// 		w = getchar();
// 		if (w==0x0A)
// 		{ a++; } 
// 		else
// 		{}
// 	}
// 	w = getchar();
// 	
// 	if (w==0x02B) // if w = +
// 	{	
// 		w = getchar();
// 		while (w !=  0x0A) //w is not <LF> 
// 		{ w = getchar();}
// 			
// 		w = getchar();
// 		if (w == 0x030)//w is '0' 
// 		{ buff[0] = 1;  } 
// 		else if(w == 0x031)//w is '1' 
// 		{ buff[0] = 2;  } 
// 		else{buff[0] = 9;}
// 	} 
// 	else if(w==0x04F) // if w = 'O'
// 	{
// 		w = getchar();
// 		if (w==0x04B) // if w = 'K'
// 		{ buff[0] = 3; } 
// 		else
// 		{ buff[0] = 4; }
// 	}
// 	else
// 	{buff[0] = 5;}
//  	printf("AT+CMGF=1\r\n");
//  	printf("AT+CMGD=1,4\r\n"); //clearing all SMS in storage AREA
// 	return *buff;
// }
// // 
// void checkOKstatus()
// {
// 		w = getchar();
// 		while (w!=0x04F) // if w = O
// 		{	w = getchar();	}
// 			
// 		while (w!=0x04B) // if w = K
// 		{	w = getchar();	}
// }
// // 
// int CarStatus(int n)
// {
// 	int c;
// 	c = n;
// 	if (c == 1)
// 	{ CAR_OFF; } 
// 	else if (c == 2)
// 	{ CAR_ON; }
// 	else
// 	{} 
// 	return 0;
// }
// 
// char sample_GPS_data (void)
// {
// //	int i=0;
// 	printf("AT\r\n");
// 	_delay_ms(1000);
// 	printf("AT+CGATT=1\r\n");
// 	_delay_ms(2000);
// 	printf("AT+CIPMUX=0\r\n");
// 	_delay_ms(1000);
// 	printf("AT+CSTT=\"safaricom\",\"\",\"\"\r\n");
// 	_delay_ms(2000);
// 	printf("AT+CIICR\r\n");
// 	_delay_ms(3000);
// 	printf("AT+CIFSR\r\n");
// 	_delay_ms(2000);
// 	printf("AT+CIPSTART=\"TCP\",\"163.172.186.181\",\"9000\"\r\n");
// 	_delay_ms(1000);
// // 	printf("AT+CIPSEND\r\n");
// // 	_delay_ms(2000);
// // 	printf("\r\n$GPGG");
// // 	while(i == 0)
// // 	{
// // 		input = getchar();
// // 		if (input == 0x024) //if the character is "$"
// // 		{
// // 			input = getchar();
// // 			if (input == 0x047) //if the character is "G"
// // 			{
// // 				input = getchar();
// // 				if (input == 0x050) //if the character is "P"
// // 				{
// // 					input = getchar();
// // 					if (input != 0x047) //if the character is not "G"
// // 					{}
// // 					else
// // 					{
// // 						input = getchar();
// // 						if (input != 0x047) //if the character is not "G"
// // 						{}
// // 						else
// // 						{
// // 							input = getchar();
// // 							while (input != 0x024)  //if the character is not "$"
// // 							{
// // 								putchar(input);
// // 								input = getchar();
// // 								i=1;
// // 							}
// // 						}
// // 					}
// // 				}
// // 				else{}
// // 			}
// // 			else{}
// // 		}
// // 		else{}
// // 	}
// // 	printf("\r\nsStatus = %d", x);
// // 	putchar(0x1A); //putting AT-MSG termination CTRL+Z in USART0
// // 	_delay_ms(2000);
// // 	printf("AT+CIPCLOSE\r\n");
// // 	_delay_ms(2000);
// 	return 0;
// }
// 
// void SendToTCP(int x)
// {
// 	int i=0;
// 		printf("AT+CIPSEND\r\n");
// 		_delay_ms(2000);
// 		printf("\r\n$GPGG");
// 		while(i == 0)
// 		{
// 			input = getchar();
// 			if (input == 0x024) //if the character is "$"
// 			{
// 				input = getchar();
// 				if (input == 0x047) //if the character is "G"
// 				{
// 					input = getchar();
// 					if (input == 0x050) //if the character is "P"
// 					{
// 						input = getchar();
// 						if (input != 0x047) //if the character is not "G"
// 						{}
// 						else
// 						{
// 							input = getchar();
// 							if (input != 0x047) //if the character is not "G"
// 							{}
// 							else
// 							{
// 								input = getchar();
// 								while (input != 0x024)  //if the character is not "$"
// 								{
// 									putchar(input);
// 									input = getchar();
// 									i=1;
// 								}
// 							}
// 						}
// 					}
// 					else{}
// 				}
// 				else{}
// 			}
// 			else{}
// 		}
// 		printf("\r\nStatus = %d", x);
// 		putchar(0x1A); //putting AT-MSG termination CTRL+Z in USART0
// 		_delay_ms(1000);
// 		printf("AT+CIPCLOSE\r\n");
// 		_delay_ms(2000);
// }

/*
 * GPS-UART-BUF.c
 *
 * Created: 9/23/2017 5:37:46 PM
 * Author : madiv
 */ 
#define F_CPU 1000000UL 
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AT-SMS.h"

#define FOSC 2000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR (((FOSC / (BAUD * 16UL))) - 1)

static FILE uart0_output = FDEV_SETUP_STREAM(USART0_Transmit, NULL, _FDEV_SETUP_WRITE);
static FILE uart1_output = FDEV_SETUP_STREAM(USART1_Transmit, NULL, _FDEV_SETUP_WRITE);
static FILE uart1_input = FDEV_SETUP_STREAM(NULL, USART1_Receive, _FDEV_SETUP_READ);
static FILE uart0_input = FDEV_SETUP_STREAM(NULL, USART0_Receive, _FDEV_SETUP_READ);

int CheckSMS();
void checkOKstatus();
int CarStatus(int n);
char sample_GPS_data (void);

#define CAR_ON	PORTB |= (1<<PORTB1)
#define CAR_OFF	PORTB &= ~(1<<PORTB1)

int a; int i; char w; int y;
char input;
char buff[250];

int main( void )
{
	CAR_ON;
	
	USART1_Init(MYUBRR);
	USART0_Init(MYUBRR);
	DDRB |= (1<<DDB1); //set PORTB1 as output
	
 	stdin = &uart0_input;
 	stdout = &uart0_output;
//	sei();
	
	_delay_ms(1000);
/*	printf("\r\n STARTING SYSTEM \r\n");*/

	while(1) 
	{
		CheckSMS();
		int w = buff[0];
		CarStatus(w);		
		
		fdev_close();
		stdout = &uart0_output;
		stdin = &uart1_input;
		sample_GPS_data ();

//		i=0;		
		fdev_close(); // monitor proceedings 
		stdout = &uart1_output;
		printf("\r\nPrinting buffer\n");
		printf("\r\nValue of Buffer [0] = %d", buff[0]);
		
		fdev_close();
		stdout = &uart0_output;
		stdin = &uart0_input;
		_delay_ms(4000);
	}
	return 0;
}

int CheckSMS()
{
	//char w; 
	y=0;
	a=0;
	printf("AT\r\n");
	checkOKstatus();
	
	printf("AT+CMGF=1\r\n");
	checkOKstatus();
	
	printf("AT+CMGL=\"REC UNREAD\"\r\n");
	while (a < 2) //skip the <LF>
	{
		w = getchar();
		if (w==0x0A)
		{ a++; } 
		else
		{}
	}
	w = getchar();
	
	if (w==0x02B) // if w = +
	{	
		w = getchar();
		while (w !=  0x0A) //w is not <LF> 
		{ w = getchar();}
			
		w = getchar();
		if (w == 0x030)//w is '0' 
		{ buff[0] = 1;  } 
		else if(w == 0x031)//w is '1' 
		{ buff[0] = 2;  } 
		else{buff[0] = 6;}
	} 
	else if(w==0x04F) // if w = 'O'
	{
		w = getchar();
		if (w==0x04B) // if w = 'K'
		{ buff[0] = 3; } 
		else
		{ buff[0] = 4; }
	}
	else
	{buff[0] = 5;}
		
		if (buff[0]<3) // clear sms storage area if 0/1 is received
		{
			printf("AT+CMGF=1\r\n");
			printf("AT+CMGD=1,4\r\n"); //clearing all SMS in storage AREA
		} 
		else
		{}

	return *buff;
}

void checkOKstatus()
{
		w = getchar();
		while (w!=0x04F) // if w = O
		{	w = getchar();	}
			
		while (w!=0x04B) // if w = K
		{	w = getchar();	}
}

int CarStatus(int n)
{
	int c;
	c = n;
	if (c == 1)
	{ CAR_OFF; }
	else if (c == 2)
	{ CAR_ON; }
	else
	{}
	return 0;
}

char sample_GPS_data (void)
{
	int i=0;
	printf("AT\r\n");
	_delay_ms(1000);
	printf("AT+CGATT=1\r\n");
	_delay_ms(2000);
	printf("AT+CIPMUX=0\r\n");
	_delay_ms(1000);
	printf("AT+CSTT=\"safaricom\",\"\",\"\"\r\n");
	_delay_ms(2000);
	printf("AT+CIICR\r\n");
	_delay_ms(3000);
	printf("AT+CIFSR\r\n");
	_delay_ms(2000);
	printf("AT+CIPSTART=\"TCP\",\"163.172.186.181\",\"9000\"\r\n");
	_delay_ms(1000);
	printf("AT+CIPSEND\r\n");
	_delay_ms(2000);
	printf("\r\n$GPGG");
	while(i == 0)
	{
		input = getchar();
		if (input == 0x024) //if the character is "$"
		{
			input = getchar();
			if (input == 0x047) //if the character is "G"
			{
				input = getchar();
				if (input == 0x050) //if the character is "P"
				{
					input = getchar();
					if (input != 0x047) //if the character is not "G"
					{}
					else
					{
						input = getchar();
						if (input != 0x047) //if the character is not "G"
						{}
						else
						{
							input = getchar();
							while (input != 0x024)  //if the character is not "$"
							{
								putchar(input);
								input = getchar();
								i=1;
							}
						}
					}
				}
				else{}
			}
			else{}
		}
		else{}
	}
//	printf("\r\nsStatus = %d", x);
	putchar(0x1A); //putting AT-MSG termination CTRL+Z in USART0
	_delay_ms(2000);
	printf("AT+CIPCLOSE\r\n");
	_delay_ms(2000);
	return 0;
}