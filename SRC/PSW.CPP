#include	<windows.h>
#include	<stdio.h>
#include	"pkzip.h"

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_psw(unsigned char *,unsigned long);



void	decode_psw(unsigned char *borg,unsigned long sorg)
{
	unsigned char	*bsrc;
	unsigned long	ssrc;
	unsigned char	*bdst;
	unsigned long	sdst=0x1000000;

	PKZIP			pkzip;
	HANDLE			hwsp;
	char			tfn[0x100];
	unsigned char	endc[4];
	unsigned long	tul1;

	endc[0]=0;	endc[1]=0;	endc[2]=0;	endc[3]=0;
	bdst=new unsigned char[sdst];

	bsrc=borg+strlen((char *)(borg+0x0a))+0x0b;	//0x0A+0x01
	for(ssrc=0;ssrc<sorg;ssrc++){			//元ファイルの終端が明確でない為
		tul1=memcmp(bsrc+ssrc,endc,4);		//00 00 00 00を終端扱い
		if(tul1==0){	break;		}		//合致すればbreak=ssrcがサイズ
	}

	sdst=pkzip.m_extract(	bsrc,
							ssrc,
							bdst,
							sdst	);

	sprintf(tfn,"%se",borg+0x0a);			//extracted
	hwsp=NonOverWriteCreateFile((LPCSTR)tfn);
	if(hwsp==(HANDLE)-1){
		printf("\tError\tcan't create %s\n",tfn);
		exit(-1);									}
	WriteFile(hwsp,bdst,sdst,&tul1,NULL);
	CloseHandle(hwsp);
	delete[]	bdst;
/*
	if(strcmp(tfn,"drneo_rl.a3pe")==0){
		sprintf(tfn,"drneo_rln.a3pe");
		bdst=new unsigned char[0x1000000];

		for(tul1=0x59144d;tul1!=0x59146d;tul1++){
//			tul1=0x59144d;		//back
//			tul1=0x59145d;		//start
//			tul1=0x5923a0;		//max
			bsrc=borg+tul1;
			ssrc=0x1068;
			sdst=0x1000000;

			sdst=pkzip.m_extract(	bsrc,
									ssrc,
									bdst,
									sdst	);

printf("%08d / %08d\n",tul1,sdst);
		}

//		hwsp=NonOverWriteCreateFile((LPCSTR)tfn);
//		if(hwsp==(HANDLE)-1){
//			printf("\tError\tcan't create %s\n",tfn);
//			exit(-1);									}
//		WriteFile(hwsp,bdst,sdst,&tul1,NULL);
//		CloseHandle(hwsp);
//		delete[]	bdst;
	}
*/
}



