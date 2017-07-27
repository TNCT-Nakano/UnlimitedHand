#ifndef __SERIAL_PORT__
#define __SERIAL_PORT__

//関数
typedef void (*func_t)(int,char**);
struct command{
  const char* cmd;
  func_t func;
};
typedef struct command command_t;
typedef struct command* command_ptr;




#endif
