#include <stdio.h>
#include <sys/stat.h>
#include <time.h>



int main (int argc, char * argv[]) {
    struct stat buf;
    int buf_size = sizeof(buf) / sizeof(int);
    stat (argv[1], &buf);
    char* data1 = asctime(localtime(&buf.st_atime));
    char* data2 = asctime(localtime(&buf.st_mtime));
    char* data3 = asctime(localtime(&buf.st_ctime));
    //*/
    printf("device inode resides on %d\n", buf.st_dev);
    printf("inode's number %llu\n", buf.st_ino);
    printf("inode protection mode %d\n", buf.st_mode);
    printf("number of hard links to the file %d\n", buf.st_nlink);
    printf("user-id of owner %d\n", buf.st_uid);
    printf("group-id of owner %d\n", buf.st_gid);
    printf("device type, for special file inode %d\n", buf.st_rdev);
    printf("file size, in bytes %lld\n", buf.st_size);
    printf("blocks allocated for file %lld\n", buf.st_blocks);
    printf("optimal file sys I/O ops blocksize %d\n", buf.st_blksize);
    printf("user defined flags for file %d\n", buf.st_flags);
    printf("file generation number %d\n", buf.st_gen);
    printf("device inode resides on %d\n", buf.st_dev);
    printf("device inode resides on %d\n", buf.st_dev);
    
    
    printf("time of last access %s\n", data1);
    printf("time of last data modification %s\n", data2);
    printf("time of last file status change %s\n", data3);

    
    return 0;
}
//Documents/GitHub/EDU/Sem3/Dir/Dir8/
