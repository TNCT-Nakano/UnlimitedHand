#ifndef __TASK__HEADER__
#define __TASK__HEADER__

void cmd_insert(const char* cc,void (*fn)(int,char**));
void help(int argc,char** argv);
void dummy(int argc,char** argv);
void vibration(int argc,char** argv);
void vibration_on(int argc,char** argv);
void vibration_off(int argc,char** argv);
void ack(int argc,char** argv);
void ems(int argc,char** argv);
#endif
