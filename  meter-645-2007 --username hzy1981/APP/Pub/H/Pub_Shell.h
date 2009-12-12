#ifndef PUB_SHELL_H
#define PUB_SHELL_H

#undef EXT
#ifdef PUB_SHELL_C
#define EXT
#else
#define EXT extern
#endif

EXT INT8U Shell_Bg_Print_Switch(INT8U argc, INT8S **argv);
EXT void Shell_Proc();
#endif