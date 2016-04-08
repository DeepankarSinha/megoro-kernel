#ifndef COMMAND_H
#define COMMAND_H
extern int clear();
extern int exec(int cmdno,char * cmdline);
extern int isvalidcmd(char * cmd);
extern char * getcmd(char*);
extern int showHelp(char *cmdline);
extern int showCPUinfo();
extern int request(char* cmdline);
extern int cpu_time();
#endif
