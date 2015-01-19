#ifndef _Remote_h
#define _Remote_h

#include "Move.h"

void remoteService();
void changeCmdState(int newState);
void processCommand(int);
void processCommand(int, int);

#endif