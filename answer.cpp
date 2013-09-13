// (C) copyright 1996 Sacha Prins

#include <fstream.h>
#include <strstrea.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "\work\modemengine\modemengine.hpp"

int bits_per_sample=4;
int device= 1;
char * file_name= NULL;
char message_name[20]= "";
char * com_port= NULL;
BOOL debug= FALSE;

void usage();
void parse_arg(int argc, char * argv[]);
void answer();
MODEM_ENGINE::MODEMRESPONSE response (MODEM_ENGINE & me, int timeout=600);

//*****************************************************************************
int main (int argc, char * argv[]) {

 parse_arg(argc, argv);

 cout << "bits per sample: " << bits_per_sample << endl
      << "device         : " << device << endl
      << "file name      : " << file_name << endl
      << "com port       : " << com_port << endl;


 int i=0;
 while (TRUE) {
   strstream * str= new strstream();
   *str << i << ".msg" << ends;
   strcpy(message_name, str->str());
   answer();
   delete str;
   i++;

 } /* endwhile */


};


//*****************************************************************************
void answer() {

 MODEM_ENGINE me(com_port);

 ifstream fin(file_name, ios::bin);
 if (!fin.good()) {
    usage();
    exit(0);
 }

 HFILE message;
 ULONG ulAction=0;

 if (DosOpen(message_name,
             &message,
             &ulAction,
             0,
             FILE_NORMAL ,
             OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
             OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_READWRITE,
             0) != NO_ERROR) {

    usage();
    exit(0);
 }

 if (me.mResultCode () == MODEM_ENGINE::noerror) {

    MODEM_ENGINE::MODEMRESPONSE mr;

    cout << endl << "Initializing the modem..." << endl;

    me.mInitialize();
    response (me);

    cout << endl << "Waiting for call..." << endl;

    mr= response(me);
    while (mr.code != MODEM_ENGINE::ring) {
       mr= response(me);
    } /* endwhile */

    me.vmSetDevice(MODEM_ENGINE::voice);
    response (me);

    me.vmSetSpeed();
    response (me);

    me.vmSetSilenceDetection(FALSE);
    response (me);

    switch (bits_per_sample) {
      case 2:
      me.vmSetBits(MODEM_ENGINE::two);
      break;
      case 3:
      me.vmSetBits(MODEM_ENGINE::three);
      break;
      case 4:
      me.vmSetBits(MODEM_ENGINE::four);
      break;
    } /* endswitch */

    response (me);

    switch (device) {
     case 1: // Phone line
       me.vmSetLine(MODEM_ENGINE::line);
       response (me);

       me.mAnswer();
       response (me);

       break;

     case 2: // Phone line monitor
       me.vmSetLine(MODEM_ENGINE::lineMonitor);
       response (me);

       me.mAnswer();
       response (me);

       break;

    } /* endswitch */

    HFILE com_port;

    me.vmTransmit(com_port);
    response (me);

    unsigned char buf[1024];
    ULONG cbWritten=0, bitcount=0;

    cout << "Initializing done..." << endl << "Playing file..." << endl;

    while (!fin.eof()) {

       fin.read(buf, sizeof(buf));
       bitcount+= fin.gcount();
       DosWrite(com_port, &buf, fin.gcount(), &cbWritten);
    }

    cout << bitcount << " bytes written" << endl;

    me.vmStopTransmit();
    mr= response (me, 50);

    while (mr.code==MODEM_ENGINE::none) {
       me.vmStopTransmit();
       mr= response (me, 50);
    } /* endwhile */

    cout << "Playing done..." << endl;

    me.vmBeep();
    response(me);

    me.vmReceive(message);
    response(me);

    char c;
    c=me.mWaitForDLECode();

    while (c != 'q' && c != 'b' && c !='a' && c !='c' && c !='d' && c !='e' && c !='f' && c !='s') {

       c=me.mWaitForDLECode();
    } /* endwhile */

    me.vmStopReceive();
    mr= response (me, 50);

    while (mr.code==MODEM_ENGINE::none) {
       me.vmStopTransmit();
       mr= response (me, 50);
    } /* endwhile */

    cout << "Recording done..." << endl << "Resetting the modem..." << endl;

    me.mInitialize();
    response (me);

    DosClose(message);

    cout << "All done..." << endl;


 } else {
    cout << endl << "Unable to open the '" << com_port << "' device." << endl;
 }
}


//*****************************************************************************
MODEM_ENGINE::MODEMRESPONSE response (MODEM_ENGINE & me, int timeout) {

 MODEM_ENGINE::MODEMRESPONSE mr;

    do {
       mr= me.mWaitForModemResponse (timeout);
       if (debug) cout << mr.verbose << endl;
       if (mr.verbose[0]== 0) {
          mr.code= MODEM_ENGINE::none;
       }
    } while ((mr.code != MODEM_ENGINE::ok) &&
             (mr.code != MODEM_ENGINE::error) &&
             (mr.code != MODEM_ENGINE::connect) &&
             (mr.code != MODEM_ENGINE::none) &&
             (mr.code != MODEM_ENGINE::ring) &&
             (mr.code != MODEM_ENGINE::vcon));

   return mr;
}

//*****************************************************************************
void parse_arg(int argc, char * argv[]) {

 for (int i=1; i< argc; i++) {

    if (!strncmp(argv[i], "-d:", 3)) {
      device= atoi(argv[i]+3);
      if (device != 1 && device != 2) {
         usage();
         exit(0);
      }
    } else {
     if (!strncmp(argv[i], "-b:", 3)) {
        bits_per_sample= atoi(argv[i]+3);
        if (bits_per_sample != 2 && bits_per_sample != 3 && bits_per_sample != 4) {
           usage();
           exit(0);
        }
        cout << argv[i]+3 << "\n";
     } else {
        if (!strncmp(argv[i], "-f:", 3)) {

          file_name= strdup(argv[i]+3);
        } else {
           if (!strncmp(argv[i], "-c:", 3)) {

              com_port= strdup(argv[i]+3);
           } else {
              if (!strncmp(argv[i], "-de", 3)) {

                 debug= TRUE;
              } else {

                usage();
                exit(0);

              } /* endif */
           } /* endif */
        } /* endif */
     } /* endif */
    } /* endif */
 } /* endfor */

 if (file_name==NULL || com_port==NULL) {
    usage();
    exit(0);
 } else {
 } /* endif */

};


//*****************************************************************************
void usage(){

 cout << "* Required parameters: " << endl << endl
      << "-f:filename, where 'filename' is the name (+ path) of the greeting file." << endl << endl
      << "-c:comport, where 'comport' is the name of the device the voice modem is" << endl << " connected to." << endl << endl
      << "* Optional parameters:" << endl << endl
      << "-b:bits, where 'bits' is either 2, 3 or 4 and stands for the sampling rate of" << endl << " the file to be played, this defaults to 4" << endl
      << " The bitrate is for the incoming AND outgoing message the same."<<endl
      << "-d:device, where 'device' is either 1, or 2." << endl
      << " 1 stands for telephone line. This defaults to 1" << endl
      << " 2 stands for telephone line with monitor. This defaults to 1" << endl << endl
      << "-debug turns debug info on." << endl << endl
      << "* Example:" << endl << endl
      << "answer -f:c:\\path\\greeting.msg -c:com1 -b:3 -d:2" << endl;
};
