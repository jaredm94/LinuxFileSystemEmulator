// -------------------------
// Luke Weber, Jared Meade
// CptS 360 - Final Project
// -------------------------

// Import statements
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <ext2fs/ext2_fs.h>
#include <libgen.h>
#include <string.h>
#include <sys/stat.h>

// define shorter TYPES, save typing efforts
typedef struct ext2_group_desc  GD;
typedef struct ext2_super_block SUPER;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;    // need this for new version of e2fs

GD    *gp;
SUPER *sp;
INODE *ip;
DIR   *dp; 

#define BLOCK_SIZE        1024
#define BLKSIZE           1024
#define BITS_PER_BLOCK    (8*BLOCK_SIZE)
#define INODES_PER_BLOCK  (BLOCK_SIZE/sizeof(INODE))

// Block number of EXT2 FS on FD
#define SUPERBLOCK        1
#define GDBLOCK           2
#define BBITMAP           3
#define IBITMAP           4
#define INODEBLOCK        5
#define ROOT_INODE        2

// Default dir and regulsr file modes
#define DIR_MODE          0040777 
#define FILE_MODE         0100644
#define SUPER_MAGIC       0xEF53
#define SUPER_USER        0

// Proc status
#define FREE              0
#define BUSY              1
#define KILLED            2

// Table sizes
#define NMINODES          50
#define NMOUNT            10
#define NPROC             10
#define NFD               10
#define NOFT              50

// Open File Table
typedef struct Oft{
  int   mode;
  int   refCount;
  struct Minode *inodeptr;
  long  offset;
} OFT;

// PROC structure
typedef struct Proc{
  int   uid;
  int   pid;
  int   gid;
  int   ppid;
  int   status;

  struct Minode *cwd;
  OFT   *fd[NFD];

  struct Proc *next;
  struct Proc *parent;
  struct Proc *child;
  struct Proc *sibling;
} PROC;
      
// In-memory inodes structure
typedef struct Minode{		
  INODE INODE;               // disk inode
  int   dev, ino;

  int   refCount;
  int   dirty;
  int   mounted;
  struct Mount *mountptr;
  char     name[128];           // name string of file
} MINODE;

// Mount Table structure
typedef struct Mount{
  int  ninodes;
  int  nblocks;
  int  bmap;
  int  imap;
  int  iblock;
  int  dev, busy;   
  struct Minode *mounted_inode;
  char   name[256]; 
  char   mount_name[64];
} MOUNT;

// Function declarations
// Utilities
int mount_root();
int init();
MINODE *iget();
OFT *falloc();
int iput();
// Etc.
int sync();
int quit();
// Level 1
int menu();
int make_dir();
int change_dir(char* pathname);
int pwd();
int list_dir();
int rmdir();
int creat_file(char *pathname);
int link();
int unlink();
int symlink();
int rm_file(char *pathname);
int chmod_file(char *permisions);
int stat_file(char *pathname);
int touch_file(char *pathname);
// Level 2
int open_file(char *pathname);
int close_file(char *pathname);
int pfd();
int lseek_file();
int access_file();
int read_file();
int write_file();
int cat_file();
int cp_file();
int mv_file();
// Level 3
int mount();
int umount();
int cs();
int do_fork();
int do_ps();

/*         UTILITY FUNCTIONS              */

  int Tokenize(char * path,char ret[][128],char * tok)// tokenize a string and return an array of each detokenized string.
  {
    char * s = NULL;
    char pathcpy[128];// copy of path
  
    
    Node * start= NULL;// node we want to make our CwD
    
    strncpy(pathcpy,path, 128); // a copy of the path to strtok
    s= strtok(pathcpy, tok);     // break up "a/b/c/d" into token
    strcpy(ret[0],s);// first token added
    
    for(i=0;(s = strtok(0, tok));i++)
    {     // keep calling strtok() with NULL string
        
        strcpy(ret[i+1],s);
        
    }
    
    strcpy(ret[i+1],"\0");
  }
    /*************************/
