//
// Created by Sajad  on 2019-12-29.
//

#ifndef PLAYER_EVENT_PARSER_H
#define PLAYER_EVENT_PARSER_H

#endif //PLAYER_EVENT_PARSER_H

#include <stdio.h>
#include <stdlib.h>


void foundNOTEOFF(FILE * file , FILE * NT , unsigned char byte , unsigned char note){
    int pos = 0;


}
double getFreq(int note){

    float freq[] = {16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,16.35,27.50,29.14,30.87,32.70,34.65,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41,69.30,73.42,77.78,82.41,87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77,1046.50,1108.7,1174.6,1244.5,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53,2093.00,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520.00,3729.31,3951.07,4186.01,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040.00,7458.62,7902.13};
    return freq[note - 1];

}
int findEventKind(unsigned char byte , FILE *file , Track *track , Event * event , FILE * NT){
static int currTEMPO = 0;
static int noteOnSet = 0;
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
            event->event = MidiTempoChanged;
            unsigned char tempo [3];
            fread(tempo,3,1,file);
            int TEMPO = tempo[0] << 16 | tempo[1] << 8 | tempo[2];

            printf("TEMPO is %d\n" ,TEMPO);
            currTEMPO = TEMPO;
            event->TEMPO = TEMPO;
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
            printf("find note off on with channel of %d and note %d \n", byte - 0x80, note);
            printf("DELTA TIME HERE IS %d\n", event->deltaTime);
            if(noteOnSet == 1) {
                fprintf(NT, "%d %d\n", currTEMPO, event->deltaTime);
                noteOnSet = 0;
            }
            fread(&note, 1, 1, file);

    } //note off
    else if(byte >= 0x90 && byte < 0xA0){
        event->event = MidiNotePressed;
        char note;
        fread(&note , 1 , 1 ,file);
        float freq = getFreq(note);
        printf("find note on with channel of %d and note %d \n" , byte - 0x90 , note);

        printf("Freq is %f\n" , freq);
        if(noteOnSet == 0) {
            fprintf(NT, "%lf ", freq);
            noteOnSet = 1;
        }
        fread(&note , 1 , 1, file);
        long long int posHolder = 0;


    } // note on
    else if(byte >= 0xA0 && byte < 0xB0){

        char note;
        fread(&note , 1 , 1 ,file);
        printf("find key pressure with channel of %d and note %d \n" , byte - 0xA0 , note);
        fread(&note , 1 , 1, file);
    } // key pressure
    else if(byte >= 0xC0 && byte < 0xD0){
        unsigned char instru;
        fread(&instru , 1 , 1 , file);
        printf("find set instrument with channel of %d and set to %d\n " , byte - 0xC0 , instru);
    } // set instrument
    else if(byte >= 0xB0 && byte < 0xC0){

        char note;
        fread(&note , 1 , 1 ,file);
        printf("find unnecessary event\n");
        fread(&note , 1 , 1, file);
    } else if(byte >= 0xD0 && byte < 0xF0){
        if(byte >= 0xD0 &&  byte < 0xE0){
            char note;
            fread(&note , 1 , 1 ,file);
            printf("find unnecessary event\n");
            return 1;

        } else{
            char note;
            fread(&note , 1 , 1 ,file);
            printf("find unnecessary event\n");
            fread(&note , 1 , 1, file);

        }

    }


}


