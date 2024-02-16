/******************************************************************************
	PS2 4bit tile decoding
******************************************************************************/
#include	<windows.h>
#include	<stdio.h>



void	decode_ps2_d4t(
	unsigned char		*src,
	unsigned long		sx,
	unsigned long		sy		)
{	unsigned long		sz=sx*sy;
	unsigned long		cx,cy;
	unsigned char		*ba;
	unsigned char		*bb;

	ba=new unsigned char[sx*sy*4];
	bb=new unsigned char[sx*sy*4];

	memset(ba,0x00,sx*sy*4);
	memcpy(bb,src ,sx*sy*4);

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=2){
			memcpy(ba+(cy*sx+cx+0)*4,bb+(cy*sx+cx+1)*4,4);
			memcpy(ba+(cy*sx+cx+1)*4,bb+(cy*sx+cx+0)*4,4);
	}	}

	memcpy(src,ba,sx*sy*4);

	delete[]	ba;
	delete[]	bb;
}
