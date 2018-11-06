#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
long int size;
long int i,k;
long int mas[100];


void traverse(char const *dir)
{
	char name[PATH_MAX];
	DIR *d;
	struct dirent *dd;
	off_t o;
	struct stat s;
	char *delim = "/";
	char symbol='a';
	if (!strcmp(dir, "/")) delim = "";
	if (!(d = opendir(dir))) {
		perror(dir);
		return;
	}
	while ((dd = readdir(d))) {
		if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, ".."))
		continue;
		snprintf(name, PATH_MAX, "%s%s%s", dir, delim, dd->d_name);
		if (lstat(name, &s) < 0) continue;
		if (S_ISDIR(s.st_mode)) {
		o = telldir(d);
		closedir(d);
		traverse(name);
		if (!(d = opendir(dir))) {
			perror(dir);
			return;
		}
		seekdir(d, o);
		} else {
			if (dd->d_name[0]==symbol) {
				if (s.st_nlink==1) {
					size=size+s.st_size;
					//printf("%ld\n",s.st_size);
				} else {
					printf("%ld",i);
					if (i==0) {
						size=size+s.st_size;
						mas[0]=s.st_ino;
						i++;
						printf("%ld",s.st_ino);
					} else {
						int fl=0;
						for (k=0; k<i; k++){
							if (mas[k]==s.st_ino) fl=1;
						
						}
						if (!fl) {
							size=size+s.st_size;
							//mas=realloc(mas,strlen(mas)+1);
							mas[i]=s.st_ino;
							i++;
							printf("akakaka");
						}
					}
				}
				printf("%s: %ld\n",dd->d_name,s.st_size);
				//printf("%ld",s.st_nlink);
			}
		}
	}
	closedir(d);
}

int main(void)
{
	size=0;
	i=0;
//	*mas=calloc(1,1);
	traverse("/home/katerina/work3/tests");
//	for (int k=i-1; k>=0; k--) {
//		free(&mas[k]);
//	}
	printf("%ld\n",size);
	return 0;
}
