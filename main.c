// -------------------------
// Luke Weber, Jared Meade
// CptS 360 - Final Project
// -------------------------

// Project header
#include <project.h>

// Globals
MINODE minode[100],
       *root = 0;
PROC P0, P1;
PROC *running;

// Driver
int main(int argc, char *argv[])
{
    int i, cmd;
    char line[128], cname[64];

    // Array of command functions
    int (*fncns)(char *pathname) = {menu, make_dir, change_dir, pwd, list_dir, rmdir, creat_file, link, unlink, symlink, rm_file, chmod_file, chown_file, stat_file, touch_file, open_file, close_file, pfd, lseek_file, access_file, read_file, write_file, cat_file, cp_file, mv_file, mount, umount, cs, do_fork, do_ps, sync, quit};

    // Initiate the stuff, you know?
    init();

    // Mount root directory
    mount_root();

    // Loop command input
    while (1)
    {
      // Currently running process
      printf("P%d running: ", running->pid);
      // Get user input
      printf("Input command: ");
      fgets(line, 128, stdin);
      // Kill the \r char at end
      line[strlen(line) - 1] = 0;
      if (line[0] == 0) continue;

      sscanf(line, "%s %s %64c", cname, pathname, parameter);

      cmd = findCmd(cname); // map cname to an index

      // Call function from array
      fncns[cmd]();

      /* OLD SHIT
      switch(cmd)
      {
           // ------------ LEVEL 1 -------------------
           case 0 : menu();                   break;
           case 1 : make_dir();               break;
           case 2 : change_dir();             break;
           case 3 : pwd(cwd);                 break;
           case 4 : list_dir();               break;
           case 5 : rmdir();                  break;
           case 6 : creat_file();             break;
           case 7 : link();                   break;
           case 8 : unlink();                 break;
           case 9 : symlink();                break;
           case 10: rm_file();                break;
           case 11: chmod_file();             break;
           case 12: chown_file();             break;
           case 13: stat_file();              break;
           case 14: touch_file();             break;

           // -------------- LEVEL 2 ------------------
           case 20: open_file();              break;
           case 21: close_file();             break;
           case 22: pfd();                    break;
           case 23: lseek_file();             break;
           case 24: access_file();            break;
           case 25: read_file();              break;
           case 26: write_file();             break;
           case 27: cat_file();               break;
           case 28: cp_file();                break;
           case 29: mv_file();                break;

           // ------------- LEVEL 3 -------------------
           case 30: mount();                  break;
           case 31: umount();                 break;
           case 32: cs();                     break;
           case 33: do_fork();                break;
           case 34: do_ps();                  break;
          
           case 40: sync();                   break; 
           case 41: quit();                   break; 
           default: printf("invalid command\n");
                    break;
      }
    }*/
    
    // A. mount_root
    // B. ...

    // 1. Prompt user for command
    // 2. Tokenize command
    // 3. Interpret and run
    
      return 1;
}

int init()
{
    // (1). 2 PROCs, P0 with uid=0, P1 with uid=1, all PROC.cwd = 0
    // (2). MINODE minode[100]; all with refCount=0
    // (3). MINODE *root = 0;eturn 1;

    return 1;
}

// Mount root file system, establish / and CWDs
int mount_root()
{
    // Open device for RW
    // Read SUPER block to verify it's an EXT2 FS
    // Root = iget(dev, 2);    /* get root inode */
    // Let cwd of both P0 and P1 point at the root minode (refCount=3)
        // P0.cwd = iget(dev, 2); 
        // P1.cwd = iget(dev, 2);

    return 1;
}

int getino(int *dev, char *pathname)
{
        
    return -1;
}

INODE *iget(int dev, int ino)
{

    return 0;
}

int iput(MINODE *mip)
{

    return 1;
}
