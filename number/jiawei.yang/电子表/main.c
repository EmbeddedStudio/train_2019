#include <reg51.h>

u8 ;SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
 
int main()
	{ 
		int i; 
		while(1)
			{ 
				
				P1 = ~0x01; 
			
				
				P0 = 0x87; 
				for(i = 1000; i > 0; i--); 
				//P0 =0x00;
				
			P1 = ~0x02; 
			P0 = SegCode[5];  
			for(i = 1000000; i > 0; i--);
			} 
	} 