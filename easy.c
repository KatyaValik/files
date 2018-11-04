#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
void traverse(char const *dir)
{
	char name[PATH_MAX];
	DIR *d;
	struct dirent *dd;
	off_t o;
	struct stat s;
	char *delim = "/";
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
			printf("%s\n", name);
		}
	}
	closedir(d);
}

int main(void)
{
	traverse("/");
	return 0;
}
