#ifndef __LIB_MIDI_PARSER_HEADER_
#define __L  IB_MIDI_PARSER_HEADER

#include <stdbool.h>
#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_END
#endif

static int SIZE_OF_EVENTS = 1;
EXTERN_C

float C0  = 16.35;
float Cs0 =  17.32;
float D0  = 18.35;
float Ds0 =  19.45;
float E0  = 20.60;
float F0  = 21.83;
float Fs0 =  23.12;
float G0  = 24.50;
float Gs0 =  16.35;
float A0  = 27.50;
float As0 =  29.14;
float B0  = 30.87;
float C1  = 32.70;
float Cs1 =  34.65;
float D1  = 36.71;
float Ds1 =  38.89;
float E1  = 41.20;
float F1  = 43.65;
float Fs1 =  46.25;
float G1  = 49.00;
float Gs1 =  51.91;
float A1  = 55.00;
float As1 =  58.27;
float B1  = 61.74;
float C2  = 65.41;
float Cs2 =  69.30;
float D2  = 73.42;
float Ds2 =  77.78;
float E2  = 82.41;
float F2  = 87.31;
float Fs2 =  92.50;
float G2  = 98.00;
float Gs2 =  103.83;
float A2  = 110.00;
float As2 =  116.54;
float B2  = 123.47;
float C3  = 130.81;
float Cs3 =  138.59;
float D3  = 146.83;
float Ds3 =  155.56;
float E3  = 164.81;
float F3  = 174.61;
float Fs3 =  185.00;
float G3  = 196.00;
float Gs3 =  207.65;
float A3  = 220.00;
float As3 =  233.08;
float B3  = 246.94;
float C4  = 261.63;
float Cs4 =  277.18;
float D4  = 293.66;
float Ds4 =  311.13;
float E4  = 329.63;
float F4  = 349.23;
float Fs4 =  369.99;
float G4  = 392.00;
float Gs4 =  415.30;
float A4  = 440.00;
float As4 =  466.16;
float B4  = 493.88;
float C5  = 523.25;
float Cs5 =  554.37;
float D5  = 587.33;
float Ds5 =  622.25;
float E5  = 659.25;
float F5  = 698.46;
float Fs5 =  739.99;
float G5  = 783.99;
float Gs5 =  830.61;
float A5  = 880.00;
float As5 =  932.33;
float B5  = 987.77;
float C6  = 1046.50;
float Cs6 =  1108.73;
float D6  = 1174.66;
float Ds6 =  1244.51;
float E6  = 1318.51;
float F6  = 1396.91;
float Fs6 =  1479.98;
float G6  = 1567.98;
float Gs6 =  1661.22;
float A6  = 1760.00;
float As6 =  1864.66;
float B6  = 1975.53;
float C7  = 2093.00;
float Cs7 =  2217.46;
float D7  = 2349.32;
float Ds7 =  2489.02;
float E7  = 2637.02;
float F7  = 2793.83;
float Fs7 =  2959.96;
float G7  = 3135.96;
float Gs7 =  3322.44;
float A7  = 3520.00;
float As7 =  3729.31;
float B7  = 3951.07;
float C8  = 4186.01;
float Cs8 =  4434.92;
float D8  = 4698.63;
float Ds8 =  4978.03;
float E8  = 5274.04;
float F8  = 5587.65;
float Fs8 =  5919.91;
float G8  = 6271.93;
float Gs8 =  6644.88;
float A8  = 7040.00;
float As8 =  7458.62;
float B8  = 7902.13;
EXTERN_C_END
float getVal(char * name){
    float* p;
    p = (float*)dlsym(RTLD_SELF, name);
    return *(p);

}

typedef struct {
    int MThd;
    int length;
    int format;
    int tracks;
    int division;
}HeaderChunk;


typedef enum {
    Mthd,
    Hlength,
    format,
    tracks,
    division

}HeaderTag;
typedef enum
{
	MidiSequenceNumber,
	MidiTextEvent,
	MidiNewLyric,
	MidiNewMarker,
	MidiNewCuePoint,
	MidiNewChannelPrefix,
	MidiPortChange,
	MidiTempoChanged,
	MidiSMTPEOffset,
	MidiNewTimeSignature,
	MidiNewKeySignature,
	MidiSequencerSpecificEvent,
	MidiNoteReleased,
	MidiNotePressed,
	MidiPolyphonicPressure,
	MidiControllerValueChanged,
	MidiProgramChanged,
	MidiPressureOfChannelChanged,
	MidiPitchBendChanged,
} EventType;

typedef struct
{
    int TEMPO;
    int deltaTime;
    int event;
    int note;
    int velocity;
    float freq;
} Event;
typedef struct
{
    int ID;
    int size;
    Event *events;

} Track; // TODO fill track struct later

#endif
