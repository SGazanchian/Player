//
// Created by Sajad  on 2019-12-29.
//

#ifndef PLAYER_EVENT_PARSER_H
#define PLAYER_EVENT_PARSER_H

#endif //PLAYER_EVENT_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#define DUMP(varname) fprintf(stderr, "%s = %x", #varname, varname);
void findEventKind(unsigned char byte){


    if((int)byte == 0xff){}//meta event
    else if(byte >= 0x80 && byte < 0x90){printf("find note off with channel of %d" , byte - 0x80);} //note off
    else if(byte >= 0x90 && byte < 0xA0){} // note on
    else if(byte >= 0xA0 && byte < 0xB0){} // key pressure





}