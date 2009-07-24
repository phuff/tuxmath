/*

        network.h

        Description: Provides routines for various networking functions to be used
                     in the LAN multiplayer game.
        Author: David Bruce ,Akash Gangil and the TuxMath team, (C) 2009

        Copyright: See COPYING file that comes with this distribution (briefly, GNU GPL version 2 or later)

*/




#ifndef NETWORK_H
#define NETWORK_H

#include "transtruct.h"


/* Networking setup and cleanup: */
int LAN_Setup(char *host, int port);
void LAN_Cleanup(void);

int LAN_SetName(char* name);

/* Network replacement functions for mathcards "API": */
/* These functions are how the client tells things to the server: */
int LAN_StartGame(void);
/* NOTE probably won't have this in multiplayer - new quests determined by server */
int LAN_NextQuestion(void);
int LAN_AnsweredCorrectly(MC_FlashCard* fc);
int LAN_NotAnsweredCorrectly(MC_FlashCard* fc);
int LAN_LeaveGame(void);
/* This is how the client receives messages from the server: */
int LAN_NextMsg(char* buf);





/* FIXME appears this one is basically the same as LAN_NextMsg() */
int check_messages(char *);
/* FIXME this should be local to network.c */
int Make_Flashcard(char* buf, MC_FlashCard* fc);

#endif // NETWORK_H