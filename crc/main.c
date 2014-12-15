
/************************************************************************************/
/*    Copyright 2014 Paolo Astegno													*/
/*    This file is part of 'crc_computation'.										*/
/*																					*/		
/*    'crc_computation' is free software: you can redistribute it and/or modify		*/
/*    it under the terms of the GNU General Public License as published by			*/
/*    the Free Software Foundation, either version 3 of the License, or				*/
/*    (at your option) any later version.											*/
/*																					*/					
/*    'crc_computation' is distributed in the hope that it will be useful,			*/	
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of				*/
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					*/
/*    GNU General Public License for more details.									*/	
/*																					*/	
/*    You should have received a copy of the GNU General Public License				*/	
/*    along with 'crc_computation'.  If not, see <http://www.gnu.org/licenses/>.	*/
/************************************************************************************/
/*    'main.c' compares the traditional solution (256 items lookup table) with a	*/
/*    faster solution (that requires a 65536 items lookup table);		            */
/*    the faster solution was tested with a DSP and the time required to process a	*/
/*    buffer of data was decreased by 80 percent;                         			*/
/*    the algorithm requires that the buffer size must be an even value; 			*/
/************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crctable16.h" 	
#include "crctable8.h"


int calc_with_crctable16 (char *blk_adr,long blk_len);
int calc_with_crctable8 (char *blk_adr,long blk_len);


int calc_with_crctable16 (char *blk_adr,long blk_len)
{
	int crc16_temp;
	int i,j;

	crc16_temp = 0xffffffffL;

	for(i=0;i<blk_len;i++)
		crc16_temp = crctable16[((crc16_temp>>16) ^ (short)(((blk_adr[i*2]<<8)&0xff00)+(blk_adr[(i*2)+1]&0xff))) & 0xFFFFL] ^ (crc16_temp << 16); 
	return crc16_temp ^ 0xffffffffL;
}

int calc_with_crctable8 (char *blk_adr,long blk_len)
{
	int crc8_temp;
	int i,j;

	crc8_temp = 0xffffffffL;
	for(i=0;i<blk_len;i++)
			crc8_temp = crctable[((crc8_temp>>24) ^ blk_adr[i]) & 0xffL] ^ (crc8_temp<<8);
	return crc8_temp ^ 0xffffffff;
}


int main()
{
	int result;

	char test_buffer[]={1,2,3,4,5,6,7,8};
	//solution: { 0xebf47227 }

	result = calc_with_crctable16(test_buffer,4);
	printf("---------->result = 0x%x\n",result);
	
	result = calc_with_crctable8(test_buffer,8);
	printf("---------->result = 0x%x\n",result);

	return 0;
}

