// (C) copyright 1996 Sacha Prins

#include <string.h>
#include <stream.h>
#include <stdlib.h>
#include "\work\modemengine\modemengine.hpp"

int bits_per_sample=4;
int device= 1;
char * file_name= NULL;
char * com_port= NULL;
BOOL debug= FALSE;

void usage();
void parse_arg(int argc, char * argv[]);
void record();
MODEM_ENGINE::MODEMRESPONSE response (MODEM_ENGINE & me, int timeout=600);

//*****************************************************************************
int main (int argc, char * argv[]) {

 parse_arg(argc, argv);

 cout << "bits per sample: " << bits_per_sample << endl;
 cout << "device         : " << device << endl;
 cout << "file name      : " << file_name << endl;
 cout << "com port       : " << com_port << endl;

 record();

};


//*****************************************************************************
void record() {

 MODEM_ENGINE me(com_port);

 HFILE com_port;
 ULONG ulAction=0;
 if (DosOpen(file_name,
             &com_port,
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

    cout << endl << "Initializing the modem..." << endl;

    me.mInitialize();
    response (me);

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
    case 1:
       me.vmSetLine(MODEM_ENGINE::mic);
       response (me);

       break;

    case 2: {
       me.vmSetLine(MODEM_ENGINE::phone);
       response (me);

       cout << endl << "Pick up the handset." << endl << endl;

       char c;
       c= me.mWaitForDLECode();
       while (c != 't') {
          c= me.mWaitForDLECode();
       } /* endwhile */
       }

       break;

    case 3:
       me.vmSetLine(MODEM_ENGINE::line);
       response (me);

       me.mAnswer();
       response (me);

       break;

    case 4:
       me.vmSetLine(MODEM_ENGINE::lineMonitor);
       response (me);

       me.mAnswer();
       response (me);

       break;

    } /* endswitch */

    cout << "Initializing done..." << endl << "Recording file, press enter to stop..." << endl;

    me.vmReceive(com_port);
    response (me);

    char x[1];

    cin.read(x, 1);

    MODEM_ENGINE::MODEMRESPONSE mr;
    me.vmStopReceive();
    mr= response (me, 50);

    while (mr.code==MODEM_ENGINE::none) {
       me.vmStopTransmit();
       mr= response (me, 50);
    } /* endwhile */

    cout << "Recording done..." << endl << "Resetting the modem..." << endl;

    me.mInitialize();
    response (me);

    cout << "All done..." << endl;

 } else {
    cout << "Unable to open the '" << com_port << "' device.\n";
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
             (mr.code != MODEM_ENGINE::vcon));

   return mr;
}

//*****************************************************************************
void parse_arg(int argc, char * argv[]) {

 for (int i=1; i< argc; i++) {

    if (!strncmp(argv[i], "-d:", 3)) {
      device= atoi(argv[i]+3);
      if (device != 1 && device != 2 && device != 3 && device != 4) {
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
      << "-f:filename, where 'filename' is the name (+ path) of the file to be played." << endl << endl
      << "-c:comport, where 'comport' is the name of the device the voice modem is\n   connected to." << endl << endl
      << "* Optional parameters:" << endl << endl
      << "-b:bits, where 'bits' is either 2, 3 or 4 and stands for the sampling rate of" << endl << " the file to be played, this defaults to 4" << endl << endl
      << "-d:device, where 'device' is either 1, 2, 3 or 4." << endl
      << " 1 stands for modem mic," << endl
      << " 2 stands for phone handset." << endl
      << " 3 stands for telephone line." << endl
      << " 4 stands for telephone line with monitor. This defaults to 1" << endl << endl
      << "-debug turns debugging information on." << endl << endl
      << "* Example:" << endl << endl
      << "record -f:c:\\path\\file.msg -c:com1 -b:3 -d:2" << endl;
};
