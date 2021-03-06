#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <pwd.h>
//#include <grp.h>

void do_ls(char[]);
void dostat(char *);
void ls_r(const char *name, int level);
//void show_file_info(char *, struct stat *);
//void mode_to_letters(int, char[]);
//char * uid_to_name(uid_t);
//char * gid_to_name(gid_t);


void main(int ac, char *av[])
{
	if(ac==1)
		do_ls(".");
	else
	{
		while(--ac)
		{
			printf("%s:\n", *++av);
			do_ls(*av);
		}
	}
}

void do_ls(char dirname[])
{
	DIR	*dir_ptr;	//the directory
	struct dirent	*direntp;	//each entry
	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "this file: cannot open %s\n", dirname);
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
			printf("%s\n", direntp->d_name);
		closedir(dir_ptr);
	}
}

void ls_r(const char *name, int level)
{
	DIR *dir;
	struct dirent *entry;

	if(!(dir = opendir(name)))
		return;
	if(!(entry = readdir(dir)))
		return;
	do
	{
		if(entry->d_type == DT_DIR)
		{
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s%s", name,
					entry->d_name);
			path[len] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->
				d_name, "..") == 0)
				continue;
			printf("Dir name : %*s[%s]\n", level*2, "", 
				entry->d_name);
		ls_r(path, level +1);
		}
		else
			printf("%*sContents : %s\n", level*2, "", entry->d_name);
	} while (entry = readdir(dir));
	closedir(dir);
}
		


/*
void dostat(char *filename)
{
	struct stat info;
	if(stat(filename, &info) == -1)	//cannot stat
		perror(filename); //say why
	else	//else show info 
		show_file_info(filename, &info);
		
}

void show_file_info(char *filename, struct stat * info_p)

// display the info about -filename. The info is stored in struct at * info_p

{
	char * uid_to_name(), * ctime(), * gid_to_name(), * filemode();
	void mode_to_letters();
	char modestr[11];

	mode_to_letters( info_p -> st_mode, modestr );

	printf( "%s ", modestr );
	printf( "%4d ", (int) info_p->st_nlink);
	printf( "%-8s ", uid_to_name(info_p->st_uid) );
	printf( "%-8s ", gid_to_name(info_p->st_gid) );
	printf( "%8ld ", (long)info_p->st_size);
	printf( "%.12s ", 4+ctime(&info_p->st_mtime));
	printf( "%s\n", filename);
}

void mode_to_letters( int mode, char str[] )
{
	strcpy( str, "----------");	//default=no perms

	if (S_ISDIR(mode)) str[0] = 'd';	//directory?
	if (S_ISCHR(mode)) str[0] = 'c';	//char devices
	if (S_ISBLK(mode)) str[0] = 'b';	//block device
	
	if (mode & S_IRUSR) str[1] = 'r';	//3 bits for user
	if (mode & S_IWUSR) str[2] = 'w';
	if (mode & S_IXUSR) str[3] = 'x';

	if (mode & S_IRGRP) str[4] = 'r';	//3 bits for group
	if (mode & S_IWGRP) str[5] = 'w';
	if (mode & S_IXGRP) str[6] = 'x';

	if (mode & S_IROTH) str[7] = 'r';	//3 bits for other
	if (mode & S_IWOTH) str[8] = 'w';
	if (mode & S_IXOTH) str[9] = 'x';
}

char * uid_to_name(uid_t uid)
{
	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL)
	{
		sprintf(numstr, "% d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

char *gid_to_name(gid_t gid)
{
	struct group *getgrgid(), *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL)
	{
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}*/
