#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
DIR *adir;
struct dirent *dirent1;
int atype;
char args[128] = ".";
struct stat fstat1;
struct passwd *pw;
struct group  *gr;

if (argv[1] != NULL && strlen(argv[1]) <= 128)
        strncpy(args, argv[1], sizeof(args) - 1);

if ((adir = opendir(args)) == NULL) {
        printf("error open dir %s\n", args);
        return(0);
}

for (atype = 0; atype < 3; atype++) {
        while ((dirent1 = readdir(adir)) != NULL) {
                if (atype == 0 && dirent1->d_type == DT_DIR) {
                        printf("DIR: ");
                        if ((dirent1->d_name[0] == '.' && dirent1->d_name[1] == '\0') ||
                           (dirent1->d_name[0] == '.' && dirent1->d_name[1] == '.' && dirent1->d_name[2] == '\0'))
                         printf("<. / ..>");
                        else
                                printf("[hidden dir]");
                        stat(args, &fstat1);
                        pw = getpwuid(fstat1.st_uid);
                        gr = getgrgid(fstat1.st_gid);
                        printf("| %s %s |", pw->pw_name, gr->gr_name);
                        printf("|inode=%ld | %s\n", dirent1->d_ino, dirent1->d_name);
                } else if (atype == 1 && dirent1->d_type == DT_REG) {
                        printf("FILE: ");
                        if (dirent1->d_name[0] == '.')
                                printf("[hidden file]");
                        stat(args, &fstat1);
                        pw = getpwuid(fstat1.st_uid);
                        gr = getgrgid(fstat1.st_gid);
                        printf("| %s %s |", pw->pw_name, gr->gr_name);
                        printf("|inode=%ld | %s\n", dirent1->d_ino, dirent1->d_name);
                } else if (atype == 2 && (dirent1->d_type != DT_DIR && dirent1->d_type != DT_REG)){
                        if (dirent1->d_type == DT_LNK)
                                printf("[symlink]");
                        stat(args, &fstat1);
                        pw = getpwuid(fstat1.st_uid);
                        gr = getgrgid(fstat1.st_gid);
                        printf("| %s %s |", pw->pw_name, gr->gr_name);
                        printf("|inode=%ld | type=%d | %s\n", dirent1->d_ino, dirent1->d_type, dirent1->d_name);
                }
        }

        rewinddir(adir);
}

closedir(adir);

}
