/****************************************************************************
** WARNING: You need a HUGE memory model to run this.                      **
*****************************************************************************
** Demonstration of playing a single wave file using DMA                   **
**  by Steven H Don                                                        **
**                                                                         **
** For questions, feel free to e-mail me.                                  **
**                                                                         **
**    shd@geocities.com                                                    **
**    http://www.geocities.com/SiliconValley/Heights/8574                  **
**                                                                         **
****************************************************************************/
//Include files
#include <ALLOC.H>
#include <DOS.H>
#include <CONIO.H>
#include <STDIO.H>
void playwav(char wavefile[14],float delaytime);
struct WaveData {
  unsigned int SoundLength, Frequency;
  char *Sample;
};
struct HeaderType {
  long         RIFF;      //RIFF header
  char         NI1 [18];  //not important
  unsigned int Channels;  //channels 1 = mono; 2 = stereo
  long         Frequency; //sample frequency
  char         NI2 [6];   //not important
  char         BitRes;    //bit resolution 8/16 bit
  char         NI3 [12];  //not important
} Header;
struct WaveData Voice;         //Pointer to wave file
unsigned int    Base;          //Sound Blaster base address
char            WaveFile [25]; //File name for the wave file to be played
/****************************************************************************
** Checks to see if a Sound Blaster exists at a given address, returns     **
** true if Sound Blaster found, false if not.                              **
****************************************************************************/
int ResetDSP(unsigned int Test)
{
  //Reset the DSP
  outportb (Test + 0x6, 1);
  delay(10);
  outportb (Test + 0x6, 0);
  delay(10);
  //Check if (reset was succesfull
  if ((inportb(Test + 0xE) & 0x80 == 0x80) && (inportb(Test + 0xA) == 0xAA))
  {
    //DSP was found
    Base = Test;
    return (1);
  }
  else
    //No DSP was found
    return (0);
}
/****************************************************************************
** Send a byte to the DSP (Digital Signal Processor) on the Sound Blaster  **
****************************************************************************/
void WriteDSP(unsigned char Value)
{
  //Wait for the DSP to be ready to accept data
  while ((inportb(Base + 0xC) & 0x80) == 0x80);
  //Send byte
  outportb (Base + 0xC, Value);
}
/****************************************************************************
** Plays a part of the memory                                              **
****************************************************************************/
void PlayBack (struct WaveData *Wave)
{
  long          LinearAddress;
  unsigned int  Page, OffSet;
  unsigned char TimeConstant;
  TimeConstant = (65536 - (256000000 / Wave->Frequency)) >> 8;
  WriteDSP(0x40);                  //DSP-command 40h - Set sample frequency
  WriteDSP(TimeConstant);          //Write time constant
  //Convert pointer to linear address
  LinearAddress = FP_SEG (Wave->Sample);
  LinearAddress = (LinearAddress << 4) + FP_OFF (Wave->Sample);
  Page = LinearAddress >> 16;      //Calculate page
  OffSet = LinearAddress & 0xFFFF; //Calculate offset in the page
  /*
      Note - this procedure only works with DMA channel 1
  */
  outportb (0x0A, 5);              //Mask DMA channel 1
  outportb (0x0C, 0);              //Clear byte pointer
  outportb (0x0B, 0x49);           //Set mode
  /*
      The mode consists of the following:
      0x49 = binary 01 00 10 01
                    |  |  |  |
                    |  |  |  +- DMA channel 01
                    |  |  +---- Read operation (the DSP reads from memory)
                    |  +------- Single cycle mode
                    +---------- Block mode
  */
  outportb (0x02, OffSet & 0x100); //Write the offset to the DMA controller
  outportb (0x02, OffSet >> 8);
  outportb (0x83, Page);           //Write the page to the DMA controller
  outportb (0x03, Wave->SoundLength & 0x100);
  outportb (0x03, Wave->SoundLength >> 8);
  outportb (0x0A, 1);              //Unmask DMA channel
  WriteDSP(0x14);                  // DSP-command 14h - Single cycle playback
  WriteDSP(Wave->SoundLength & 0xFF);
  WriteDSP(Wave->SoundLength >> 8);
}
/****************************************************************************
** Loads a wave file into memory.                                          **
** This procedure expects a _very_ standard wave header.                   **
** It doesn't perform much error checking.                                 **
****************************************************************************/
int LoadVoice (struct WaveData *Voice, char *FileName)
{
  FILE *WAVFile;
  //If it can't be opened...
  WAVFile = fopen(FileName, "rb");
  if (WAVFile == NULL) {
    //..display error message
    return (0);
  }
  //Return length of file for sound length minus 48 bytes for .WAV header
  fseek(WAVFile, 0L, SEEK_END);
  Voice->SoundLength = ftell (WAVFile) - 48;
  fseek(WAVFile, 0L, SEEK_SET);
  //Check RIFF header
  if (Voice->SoundLength > 32000) {
    if (Voice->SoundLength > 64000) {
      Voice->SoundLength = 64000;
    }
  }
  free(Voice->Sample);
  Voice->Sample = (char *)malloc(Voice->SoundLength); //Assign memory
  if (!Voice->Sample) {
     
    return (0);
  }
  //Load the sample data
  fread(&Header, 46, 1, WAVFile);
  //Check RIFF header
  if (Header.RIFF != 0x46464952) {
    printf ("Not a wave file\n");
    return (0);
  }
  //Check channels
  if (Header.Channels != 1) {
    printf ("Not a mono wave file\n");
    return (0);
  }
  //Check bit resolution
  if (Header.BitRes != 8) {
    printf ("Not an 8-bit wave file\n");
    return (0);
  }
  Voice->Frequency = Header.Frequency;
  //Load the sample data
  fread(Voice->Sample, Voice->SoundLength + 2, 1, WAVFile);
  fclose (WAVFile); //Close the file
  return (1);
}
void playwav (char wavefile[14], float delaytime = 1.0 )
{
  if (ResetDSP (0x220)) {
    //at 220h
    printf ("");
  } else {
    if (ResetDSP (0x240)) {
      //at 240h
      printf ("");
    } else {
      //or none at all
      printf ("");
      return;
    }
  }
  //Load wave file
  if (LoadVoice (&Voice, wavefile)) {
    //Start playback
    PlayBack (&Voice);
    delay(delaytime*1000);
    //Stops DMA-transfer
    WriteDSP (0xD0);
  }
}