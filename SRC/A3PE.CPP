#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_a3pe(unsigned char *,unsigned long);
extern	void	decode_c8b2bmp(unsigned char *,char *);
extern	void	decode_g8b2bmp(unsigned char *,char *);
extern	void	decode_g4b2bmp(unsigned char *,char *);



void	decode_a3pe(unsigned char *src,unsigned long size)
{	unsigned char	*ITB=src+0x20;
	unsigned char	*INM=*(unsigned long *)(src+0x10)+src+8;
	unsigned long	 IMX=*(unsigned long *)(src+0x20);
	unsigned long	 INB;
	unsigned long	 IAD;
	unsigned char	*ITP;

	for(INB=0;INB!=IMX;INB++){
		IAD=*(unsigned long *)(ITB+0x28);
		if(IAD==0x01)	goto	item_skip;
		if(IAD==0x0f)	goto	item_skip;

		printf("%08X\n",IAD);

/*		ITP=src+IAD;
		if(	(*(unsigned long *)(ITP+0x00)==0x1000001e)	&&
			(*(unsigned long *)(ITP+0x0c)==0x5000001e)		){
			printf("Graphics 8bit palette - %s\n",(char *)INM);
			decode_c8b2bmp(ITP,(char *)INM);
			goto	item_skip;					}				//8bit-3
*/

		ITP=src+IAD;
		if(	(*(unsigned long *)(ITP+0x00)==0x10000046)	&&
			(*(unsigned long *)(ITP+0x0c)==0x50000046)		){
			printf("Graphics 8bit palette - %s\n",(char *)INM);
			decode_g8b2bmp(ITP,(char *)INM);
			goto	item_skip;					}				//8bit-1

		if(	(*(unsigned long *)(ITP+0x00)==0x1000000a)	&&
			(*(unsigned long *)(ITP+0x0c)==0x5000000a)		){
			printf("Graphics 4bit palette - %s\n",(char *)INM);
			decode_g4b2bmp(ITP,(char *)INM);
			goto	item_skip;					}						//4bit

			printf("item skip - %s\n",(char *)INM);
item_skip:
		INM+=strlen((char *)INM)+1;
		ITB+=0x30;
	}
}
