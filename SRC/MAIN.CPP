#include	<windows.h>
#include	<stdio.h>

extern	void	decode_dat(HANDLE);
//extern	void	decode_dat(unsigned char *,unsigned long);
extern	void	decode_psw(unsigned char *,unsigned long);

extern	void	decode_pswe(unsigned char *,unsigned long);
extern	void	decode_a3pe(unsigned char *,unsigned long);
extern	void	decode_pake(unsigned char *,unsigned long);
extern	void	decode_tgs(unsigned char *,unsigned long);



void	main(void)
{	char			file[_MAX_PATH];
	char			*tfpa;
	char			*tfpb;
	HANDLE			hndl;
	unsigned char	*buff=0;
	unsigned long	size;
	char			drive[MAX_PATH];
	char			dir[MAX_PATH];
	char			fname[MAX_PATH];
	char			ext[MAX_PATH];
	unsigned long	tmp;

	printf("PS2 Rio de carnival Converter\n");
	printf("\t\tProg. By AZUCO\n\n");



	strcpy(file,GetCommandLine());	//コマンドラインをコピーする

	tfpa=strrchr(file,' ');		//一番最後のスペース以降をファイル名と見なす
	tfpa++;

	tfpb=strrchr(tfpa,'"');		//ダブルクオートありの場合
	if(tfpb!=NULL)	*tfpb=0;

	tfpb=strrchr(tfpa,'>');		//リダイレクトの場合
	if(tfpb!=NULL)	*tfpb=0;



	tfpb=&file[0];
loop:
	if(*tfpa=='\\'){	*(tfpb+0)='\\';
						*(tfpb+1)='\\';
						tfpa++;
						tfpb+=2;
						goto loop;		}
	if(*tfpa>=0x20){	*tfpb=*tfpa;
						tfpa++;
						tfpb++;
						goto loop;		}
						*tfpb=0;



//strcpy(file,"E:\\src\\riotan\\PSWE\\ani_study_riop.pswe");

	hndl=CreateFile(file,
					GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hndl==(HANDLE)-1){
		printf("Riotan <data file>\n");
		printf("\tError\tsource file not found\n");
		exit(-1);	}

	_splitpath(file,drive,dir,fname,ext);

printf("%s / %s \n",ext,file);

	if(	strcmp(_strlwr(ext),".dat")==0)		decode_dat(hndl);
	else{
		size=GetFileSize(hndl,NULL);
		buff=new unsigned char[size];
		ReadFile(hndl,buff,size,&tmp,NULL);	}
	CloseHandle(hndl);

printf("read end\n");

//	if(	strcmp(_strlwr(ext),".dat")==0)		decode_dat(buff,size);
	if(	strcmp(_strlwr(ext),".psw")==0){
		if(	strcmp(_strlwr(fname),"netlogo")==0)	goto skip_psw;
		if(	strcmp(_strlwr(fname),"tecmologo")==0)	goto skip_psw;
											decode_psw(buff,size);
skip_psw:									NULL;					}
	if(	strcmp(_strlwr(ext),".pswe")==0)	decode_pswe(buff,size);
	if(	strcmp(_strlwr(ext),".a3pe")==0)	decode_a3pe(buff,size);
	if(	strcmp(_strlwr(ext),".pake")==0)	decode_pake(buff,size);
	if(	strcmp(_strlwr(ext),".tgs")==0)		decode_tgs(buff,size);

	if(	strcmp(_strlwr(ext),".bin")==0)		decode_psw(buff,size);
	if(	strcmp(_strlwr(ext),".g2p")==0)		decode_psw(buff,size);
	if(	strcmp(_strlwr(ext),".a3p")==0)		decode_psw(buff,size);
	if(	strcmp(_strlwr(ext),".pak")==0)		decode_psw(buff,size);

	if(buff!=0)	delete[]	buff;
}
