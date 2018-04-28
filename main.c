#include"header.h"

int main()
{
	char *ptr = NULL;
	int ret = 0, fd = 0, count = 0;
	char command[4][80], str[80], arr[1024], ch;
	char Username[10] = "admin", edUsername[10], Password[10] = "admin123", edPassword[10];
	
	/*printf("\nEnter Username : ");
	scanf("%[^\n]s",edUsername);
	while(getchar() != '\n');
	printf("\nEnter Password : ");
	scanf("%[^\n]s",edPassword);
	while(getchar() != '\n');
	
	if(CheckLoginDetails(Username, edUsername, Password, edPassword) == FALSE)
	{
		printf("\nYou have entered wrong credentials\n\n");
		return -1;
	}*/

	InitialiseSuperBlock();
	CreateDILB();
	
	/*printf("\nRestore previous data ");
	printf("\nPress 'y' : yes \nPress 'n' : no \n");
	ch = getchar();
	while(getchar() != '\n');
	
	if((ch == 'y') || (ch == 'Y'))
	{
		RestoreBackup();	
	}
	else if((ch != 'n') || (ch != 'n'))
	{
		printf("\n You have entered wrong character\n\n");
		return -1;
	}*/

	while (1)
	{
		fflush(stdin);
		strcpy(str, "");

		printf("\nVirtual File System : > ");
		fgets(str, 80, stdin);

		count = sscanf(str, "%s%s%s%s", command[0], command[1], command[2], command[3]);

		if (count == 1)
		{
			if (strcasecmp(command[0], "ls") == 0)
			{
				ls_file();
			}
			else if (strcasecmp(command[0], "closeall") == 0)
			{
				CloseAllFile();
				printf("\n All files closed successfully\n\n");
				continue;
			}
			else if (strcasecmp(command[0], "clear") == 0)
			{
				system("clear");
				continue;
			}
			else if (strcasecmp(command[0], "help") == 0)
			{
				DisplayHelp();
				continue;
			}
			else if (strcasecmp(command[0], "exit") == 0)
			{
				//CreateBackup();
				printf("\nTerminating Virtual File System\n\n");
				break;
			}
			else
			{
				printf("\nERROR : Command not found !!!\n");
				continue;
			}
		}
		else if (count == 2)
		{
			if (strcasecmp(command[0], "stat") == 0)
			{
				ret = stat_file(command[1]);
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : There is no such file\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "fstat") == 0)
			{
				ret = fstat_file(atoi(command[1]));
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : There is no such file\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "close") == 0)
			{
				ret = CloseFileByName(command[1]);
				if (ret == -1)
				{
					printf("\nERROR : There is no such file\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : File is not opened\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "rm") == 0)
			{
				ret = rm_File(command[1]);
				if (ret == -1)
				{
					printf("\nERROR : There is no such file\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "man") == 0)
			{
				man(command[1]);
			}
			else if (strcasecmp(command[0], "write") == 0)
			{
				/*fd = GetFDFromName(command[1]);
				if (fd == -1)
				{
					printf("\nERROR : Incorrect parameter\n");
					continue;
				}*/
                fd = OpenFile(command[1], READ+WRITE);
                if (fd < 0)
                {
                    printf("\nERROR : Wrong path\n");
                    continue;
                }
				printf("Enter the data :\n");
				scanf("%[^\n]s", arr);

				ret = strlen(arr);
				if (ret == 0)
				{
					printf("\nERROR : Incorrect parameter\n");
					continue;
				}
				ret = WriteFile(fd, arr, ret);
				if (ret == -1)
				{
					printf("\nERROR : Permission denied\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : There is no sufficient memory to write\n");
				}
				if (ret == -3)
				{
					printf("\nERROR : It is not reguler file\n");
				}
			}
			else if (strcasecmp(command[0], "truncate") == 0)
			{
				ret = truncate_File(command[1]);
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "ftruncate") == 0)
			{
				ret = Ftruncate(atoi(command[1]));
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : File not present\n");
				}
				continue;
			}
			else if (strcasecmp(command[0],"offset") == 0)
			{
				ret = GetFileOffset(command[1]);
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : File not present\n");
				}
				continue;
			}
			else if (strcasecmp(command[0],"LS") == 0)
			{
				if (strcmp(command[1], "-a") == 0)
				{
					ls_All();
				}
				continue;
			}
			else
			{
				printf("\nERROR : Command not found !!!\n");
				continue;
			}
		}
		else if (count == 3)
		{
			if (strcasecmp(command[0], "create") == 0)
			{
				ret = CreateFile(command[1], atoi(command[2]));
				if (ret >= 0)
				{
					printf("\nFile is successfully created with file descriptor : %d\n", ret);
				}
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : There is no inodes\n");
				}
				if (ret == -3)
				{
					printf("\nERROR : File already exists\n");
				}
				if (ret == -6)
				{
					printf("\nERROR : Memory allocation failure\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "open") == 0)
			{
				ret = OpenFile(command[1], atoi(command[2]));

				if (ret >= 0)
				{
					printf("\nFile is opened with file descriptor : %d\n", ret);
				}
				if (ret == -1)
				{
					printf("\nERROR : Incorrect paramaters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : File not present\n");
				}
				if (ret == -3)
				{
					printf("\nERROR : Permission denied\n");
				}
				if (ret == -4)
				{
					printf("\nERROR : Memory allocation failure\n");
				}
				if (ret == -5)
				{
					printf("\nERROR : Resources are finished\n");
				}
				if (ret == -6)
				{
					printf("\nERROR : It is directory\n");
				}
				continue;
			}
			else if (strcasecmp(command[0], "read") == 0)
			{
				/*fd = GetFDFromName(command[1]);
				if (fd == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
					continue;
				}*/
				fd = OpenFile(command[1], READ);
				if (fd < 0)
                {
                    printf("\nERROR : Wrong path\n");
                    continue;
                }
				if (atoi(command[2]) > MAXFILESIZE)
				{
					printf("\nERROR : File size too large\n");
				}

				ptr = (char *)malloc(sizeof(atoi(command[2] + 1)));
				if (ptr == NULL)
				{
					printf("\nERROR : Memory allocation failure\n");
					continue;
				}
				ret = ReadFile(fd, ptr, atoi(command[2]));
				if (ret == -1)
				{
					printf("\nERROR : File not existing\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : Permission denied\n");
				}
				if (ret == -3)
				{
					printf("\nERROR : Reached at end of file\n");
				}
				if (ret == -4)
				{
					printf("\nERROR : It is not regular file\n");
				}
				if (ret == 0)
				{
					printf("\nERROR : File empty\n");
				}
				if (ret > 0)
				{
					write(2, ptr, ret);
					printf("\n");
				}
				continue;
			}
			else if (strcasecmp(command[0],"chmod") == 0)
			{
				ret = chmod(command[1], atoi(command[2]));
				if (ret == -1)
				{
					printf("\nERROR : Incorrect parameters\n");
				}
				if (ret == -2)
				{
					printf("\nERROR : File not present\n");
				}
				if (ret == -3)
				{
					printf("\nERROR : Permission are already given\n");
				}
			}
			else
			{
				printf("\nERROR : Command not found !!!\n");
				continue;
			}
		}
		else if (count == 4)
		{
			if (strcasecmp(command[0], "lseek") == 0)
			{
				fd = GetFDFromName(command[1]);
				if (fd == -1)
				{
					printf("\nERROR : Incorrect parameter\n");
					continue;
				}
				ret = LseekFile(fd, atoi(command[2]), atoi(command[3]));
				if (ret == -1)
				{
					printf("\nERROR : Unable to perform lseek\n");
				}
			}
			else
			{
				printf("\nERROR : Command not found !!!\n");
				continue;
			}
		}
		else
		{
			printf("\nERROR : Command not found !!!\n");
			continue;
		}
	}

	return 0;
}
