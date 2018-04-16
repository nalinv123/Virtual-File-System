#define MAXINODE 50
#define READ 1
#define WRITE 2
#define MAXFILESIZE 1024
#define REGULAR 1
#define SPECIAL 2
#define START 0
#define CURRENT 1
#define END 2
#define TRUE 1
#define FALSE 0

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

typedef int BOOL;

typedef struct superblock
{
	int TotalInodes;
	int FreeInode;
}SUPERBLOCK, *PSUPERBLOCK;

typedef struct inode
{
	char FileName[50];
	int InodeNumber;
	int FileSize;
	int FileActualSize;
	int FileType;
	char *Buffer;
	int LinkCount;
	int ReferenceCount;
	int permission;
	struct inode *next;
}INODE, *PINODE, **PPINODE;

typedef struct filetable
{
	int readoffset;
	int writeoffset;
	int count;
	int mode;
	PINODE ptrinode;
}FILETABLE, *PFILETABLE;

typedef struct ufdt
{
	PFILETABLE ptrfiletable;
}UFDT;

typedef struct directory
{
	char FileName[12];
	int InodeNumber;
}DIRECTORY, *PDIRECTORY;

void CreateDILB();
void InitialiseSuperBlock();
void ls_file();
void ls_All();
void man(char *);
void DisplayHelp();
int GetFDFromName(char *);
PINODE Get_Inode(char *);
void CloseAllFile();
int stat_file(char *);
int fstat_file(int);
int CreateFile(char *, int);
int rm_File(char *);
int OpenFile(char *, int);
int CloseFileByName(char *);
int WriteFile(int, char *, int);
int ReadFile(int, char *, int);
int truncate_File(char *);
int Ftruncate(int);
int LseekFile(int, int, int);
int GetFileOffset(char *);
int chmod(char *, int);
int CreateDirectory(char *);
int OpenDirectory(char *, int);
int ReadDirectory(int, char *);
int WriteDirectory(int, char *, int);
int namei(char *);
void CreateBackup();
void RestoreBackup();
BOOL CheckLoginDetails(char *, char *, char *, char *);
