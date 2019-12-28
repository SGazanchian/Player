#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "beep.h"
#include "MIDI_header.h"

int readDeltaTime(FILE * file , Track * track , Event * event);
int readEvent(FILE * file ,  Track * track , Event * event);
int readTrackChunck(FILE *file, Track *tracks, Event *event);
void readHeader(FILE * file , HeaderChunk *headerChunk);
int Endian_Status = 0;
enum read_status{
    err,
    succ,
};//TODO use read status to manage return value from functions
enum endian_state{
    Little,
    Big


}; // get endian state of cpu and machine
int changeEndian(int x); // change endian for every machine to BIG
void find_Endian_ness(); // get endian state of cpu and machine
void playfromTxt(char *path); // phase 1 of project
void playfromMidi(char * path);
int Read_Bytes(int id , int length , FILE * file , HeaderChunk *headerChunk);
int main() {
    find_Endian_ness();
    //playfromTxt("/Users/sadra/CLionProjects/project/NOTES.txt");
    playfromMidi("/Users/sadra/CLionProjects/project/stiilDre.mid");
    return 0;
}
void playfromMidi(char * path){

    FILE* file = fopen(path , "rb");
    HeaderChunk headerChunk;
    readHeader(file,&headerChunk);
    Track tracks[headerChunk.tracks];
    Event *events = (Event *)malloc(sizeof(Event) * SIZE_OF_EVENTS); // malloc one size of array to events
    int filePointer = 0;
    readTrackChunck(file, &tracks[0] , events);
    /*for (int i = 0; i < headerChunk.tracks; ++i) {
        readTrackChunck(file, &tracks[i] , events);
        printf("MOVE %d FORWARD\n" , tracks[i].size);
        filePointer += tracks[i].size;
        fseek(file,tracks[i].size , SEEK_CUR);
        filePointer += 8; // 4 for header 4 for size
    }
    printf("File pointer is %d \n" , filePointer);
    fseek(file , -filePointer , SEEK_CUR);//TODO delete that for read track at once*/
    fclose(file);

}
int Read_Bytes(int id , int length , FILE * file , HeaderChunk *headerChunk){
    if(id == Mthd) {
        char buffer[5];
        fread(buffer, length, 1, file);
        if (strcmp((buffer), "MThd") == 0){
            headerChunk->MThd = 1;
            puts("Header found : MThd");
            //puts(buffer);
            return 1;
    } else{
            puts("invalid MIDI file");
            return -1;
        }

    }
    if(id == Hlength){
        int a = 0;
        fread( &a, length ,1,file);
        a = changeEndian(a);
        headerChunk->length = a;
        printf("Length is %d\n" , a);
        return 1;
    }
    if(id == format){
        unsigned char a[length];
        fread( a, length ,1,file);
        int number;
        if(Endian_Status == Little) {
             number = a[1] | a[0] << 8;
        } else{

             number = a[0] | a[1] << 8;
        }
        if(number == 0 || number == 1 || number == 2) {
            headerChunk->length = number;
            printf("Format is %d\n", number);
            return 1;
        } else{
            return -1;
        }
    }
    if(id == tracks){
        unsigned char a[length];
        fread( a, length ,1,file);
        int number;
        if(Endian_Status == Little) {
            number = a[1] | a[0] << 8;
        } else{

           number = a[0] | a[1] << 8;
        }
        headerChunk->tracks = number;
        printf("Number of Tracks is %d\n" , number);
        return 1;
    }
    if(id == division){
        unsigned char a[length];
        fread( a, length ,1,file);
        int number;
        if(Endian_Status == Little) {
            number = a[1] | a[0] << 8;
        } else{
            number = a[0] | a[1] << 8;
        }
        headerChunk->division = number;
        printf("Division is %d\n" , number);
        return 1;
    }
    return 0;
}
void playfromTxt(char * path){
    FILE *file = fopen(path , "r");
    char mode[200] = "";
    fscanf(file,"%s" , mode);
    fscanf(file,"%s" , mode);
    for (int i = 0; i < strlen(mode); ++i) {
        if(mode[i] == '#'){
            mode[i] = 's';
        }
    }
    char t[200];
    fscanf(file,"%s" , t);
    int length = 0;
    fscanf(file,"%d" , &length);
    int status = 1;
    beep(getVal(mode) , length);
    while (status != EOF){
        status = fscanf(file,"%s" , mode);
        if(strcmp(mode,"-N") != 0){
            continue;
        }
        char note[4] = "";
        fscanf(file , "%s" , note);
        char temp[3] = "";
        fscanf(file , "%s" , temp);
        int length = 0;
        fscanf(file , "%d" , &length);
        for (int i = 0; i < strlen(note); ++i) {
            if(note[i] == '#'){
                note[i] = 's';
            }
        }
        puts(note);
        beep(getVal(note), length);
    }
    fclose(file);

}
int changeEndian(int  x){

    if(Endian_Status == Little) {
        return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) | ((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
    }

    return x;


}
void find_Endian_ness(){
    int num = 1;
    if (*(char *)&num == 1)
    {
        Endian_Status = Little;
    }
    else
    {
        Endian_Status = Big;
    }


}
void readHeader(FILE * file , HeaderChunk * headerChunk){

    if(Read_Bytes(Mthd,4,file,headerChunk) == -1){
        exit(0);// bad file founded
    } //Read MThd
    if(Read_Bytes(Hlength , 4 , file , headerChunk) == -1){
        exit(0);// bad file founded

    }// read length for HeaderChunk
    if(Read_Bytes(format , 2 , file , headerChunk) == -1){
        puts("Bad Format");
        exit(0);// bad file founded

    }//Read format : {0 , 1 , 2}
    if(Read_Bytes(tracks , 2 , file , headerChunk) == -1){
        puts("Bad Tracks");
        exit(0);// bad file founded

    }//Read number of tracks
    if(Read_Bytes(division , 2 , file , headerChunk) == -1){
        puts("Bad Division");
        exit(0);// bad file founded

    }// Read Time Division



}
int readTrackChunck(FILE *file, Track *tracks, Event *event){
    char buffer[5] = {0};
    fread(buffer, 4, 1, file);
    if (strcmp((buffer), "MTrk") == 0){
        tracks->ID = 1;
        int sizeOfTrackes = 0;
        fread(&sizeOfTrackes , 4 , 1 , file);
        sizeOfTrackes = changeEndian(sizeOfTrackes);
        printf("FOUND track WITH size OF %d\n" , sizeOfTrackes );
        tracks->size = sizeOfTrackes;
        readEvent(file , tracks,event);
        return 1;
    } else{

        puts("INVALID TRACK");
        exit(10);
    }
    return 0;
}
int readEvent(FILE * file , Track * track , Event * event){//TODO fix readEvent
    Event currEvent;
    currEvent.deltaTime = readDeltaTime(file, track , event);



}

int readDeltaTime(FILE * file , Track * track , Event * event){
    int counter = 1;
    unsigned char deltaTime[4];
    deltaTime[0] = fgetc(file);
    while (deltaTime[counter - 1] > 0x80 && counter < 5){
        deltaTime[counter++] = fgetc(file);
    }

   switch (counter) {
       case 1:
           printf("%d" , deltaTime[0]);
           break;
       case 2: {
            int delta = 0;
           if(Endian_Status == Little) {
               delta = deltaTime[1] | deltaTime[0] << 8;
           } else{

               delta = deltaTime[0] | deltaTime[1] << 8;
           }

           printf("%d" , delta);

           break;
       }

       case 3: {
           int result = (((unsigned int) deltaTime[0]) << 16) | (((unsigned int) deltaTime[1]) << 8) |
                        ((unsigned int) deltaTime[2]);

           printf("%d" , result);
       }

       //case 4:



   }

    }
}