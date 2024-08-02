#define NPROC 64                  // max open processes
#define NCPU 8                    // max cpus
#define NOFILE 16                 // max open files per process
#define NFILE 100                 // max open files per system
#define NINODE 50                 // max number of active inodes
#define NDEV 10                   // max major device number
#define ROOTDEV 1                 // device number of file system root disk
#define MAXARG 32                 // max exec arg.
#define MAXOPBLOCKS 10            // max number of locks any FS op writes
#define LOGSIZE (MAXOPBLOCKS * 3) // max data blocks on-disk
#define NBUF (MAXOPBLOCKS * 3)    // size of disk block cache
#define FSSIZE 1000               // size of file system in  blocks
#define MAXPATH 128               // max file path name