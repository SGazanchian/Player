//
// Created by Sajad  on 2019-12-29.
//

#ifndef PLAYER_EVENT_PARSER_H
#define PLAYER_EVENT_PARSER_H

#endif //PLAYER_EVENT_PARSER_H


#include <stdio.h>
#include <stdlib.h>
#define DUMP(varname) fprintf(stderr, "%s = %x", #varname, varname);
int findEventKind(unsigned char byte , FILE *file , Track *track , Event * event){


    if((int)byte == 0xff){

        unsigned char kind;
        fread(&kind , 1 , 1,file);
        if((kind) == 0x58) {
            unsigned char length;
            fread(&length,1,1,file);
            printf("found Time signature event with %d bytes of data\n" , length);//TODO read time signature correctly
            event->event = MidiNewTimeSignature;
            fseek(file,length,SEEK_CUR);
            return 1;//1 is for 0x58
        }
        if(kind == 0x51){
            unsigned char length;
            fread(&length,1,1,file);
            printf("found Set Tempo in microseconds per quarter note with %d bytes of data\n" , length);
            event->event = -1;
            fseek(file,length,SEEK_CUR);
            return 1;

        }
        if(kind == 0x2F){
            puts("FOUND END OF TRACK");
            return -1;
        }
        if(kind == 0x03){
            unsigned char length;
            fread(&length,1,1,file);
            unsigned char Name [length + 1];
            fread(&Name , length , 1 , file);
            Name[length] = '\0';
            printf("found Name : %s\n" , Name);

        }
    }//meta event
    else if(byte >= 0x80 && byte < 0x90){
        char note;
        fread(&note , 1 , 1 ,file);
        printf("find off on with channel of %d and note %d \n" , byte - 0x80 , note);
        fread(&note , 1 , 1, file);
    } //note off
    else if(byte >= 0x90 && byte < 0xA0){
        char note;
        fread(&note , 1 , 1 ,file);
        printf("find note on with channel of %d and note %d \n" , byte - 0x80 , note);
        fread(&note , 1 , 1, file);


    } // note on
    else if(byte >= 0xA0 && byte < 0xB0){} // key pressure
    else if(byte >= 0xC0 && byte < 0xD0){
        unsigned char instru;
        fread(&instru , 1 , 1 , file);
        printf("find set instrument with channel of %d and set to %d\n " , byte - 0xC0 , instru);
    } // set instrument




}