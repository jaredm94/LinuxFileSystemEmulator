#include <project.h>


char cwd[256];//current working directory.
char *t1 = "xwrxwrxwr-------";// used for permissions printing.
char *t2 = "----------------";


/********* LS COMMAND *********/

int ls_file(char *fname)
{
    struct stat fstat, *sp;
    int r, i;
    char ftime[64];
    char buffer[128];
    
    sp = &fstat;
    //printf("name=%s\n", fname); getchar();
    
    if ( (r = lstat(fname, &fstat)) < 0){
        printf("can't stat %s\n", fname);
        exit(1);
    }
    
    if ((sp->st_mode & 0xF000) == 0x8000)
        printf("%c",'-');
    if ((sp->st_mode & 0xF000) == 0x4000)
        printf("%c",'d');
    if ((sp->st_mode & 0xF000) == 0xA000)
        printf("%c",'l');
    
    for (i=8; i >= 0; i--){
        if (sp->st_mode & (1 << i))
            printf("%c", t1[i]);
        else
            printf("%c", t2[i]);
    }
    
    printf("%4d ",sp->st_nlink);
    printf("%4d ",sp->st_gid);
    printf("%4d ",sp->st_uid);
    printf("%8d ",sp->st_size);
    
    // print time
    strcpy(ftime, ctime(&sp->st_ctime));
    ftime[strlen(ftime)-1] = 0;
    printf("%s  ",ftime);
    
    // print name
    printf("%s", basename(fname));
    
    // print -> linkname if it's a symbolic file
    if ((sp->st_mode & 0xF000)== 0xA000)
    { // YOU FINISH THIS PART
        readlink(fname, buffer, sizeof(buffer)-1);
        // use readlink() SYSCALL to read the linkname
        printf(" -> %s", buffer);
    }
    printf("\n<p>");
    
    return 0;
}

int LS(char * fname,char * cwd)
{
    struct dirent *entry;
    DIR * dp;
    char buffer[128];
    
    if(fname[0]=='/')// if its a path name
    {
        if((dp=opendir(fname))==NULL){exit(1);}// if we fail to open the di
        
        while((entry = readdir(dp)) != NULL)
        {
            
            strcpy(buffer,fname);
            strcat(buffer,"/");
            strcat(buffer, entry->d_name);
            ls_file(buffer);
        }
        
    }
    else
    {
        strcpy(buffer,cwd);
        strcat(buffer,fname);
        
        if((dp=opendir(buffer))==NULL){exit(1);}// if we fail to open the dir
        
        while((entry = readdir(dp)) != NULL)
        {
            strcpy(buffer,cwd);
            strcat(buffer,fname);
            strcat(buffer,"/");
            strcat(buffer, entry->d_name);
            ls_file(buffer);
        }
    }
    
 /********* END OF LS COMMAND *********/   

// Displays command options
int menu()
{
    printf("[This is the menu]\n");
    
    return 1;
}
