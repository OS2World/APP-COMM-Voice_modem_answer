         





         February 25, 1996, Amsterdam         
         Sacha Prins         
         for personal and business related mail: sprins@businessnet.net         
         for answering machine related mail: answer@businessnet.net         
         
         INTRODUCTION         
         
         Hi, I'm back. It been a long time since I released anything 
         related to The Answering Machine for OS/2. I obtained my masters 
         degree in computer science, and got a job as an internet con-
         sultant. My last project on the WWW is the businessNET site 
         (http://www.businessnet.net). I hope that you can understand the 
         time gap between the releases.         
         
         The prior release to this one was version 1.06p, the heavily 
         patched prototype version I started working on in 1994. Since 
         then a lot has changed. I have worked on the modem communication 
         and succeeded in creating a Voice Modem API in the form of a C++ 
         object that encapsulates the Voice Modem functionality. The sup-
         ported Voice Modems are those that are based on the Rockwell 
         voice command set. To see if you have such a modem you could 
         enter the following string in a terminal program "AT#CLS=?". If 
         you get a response that's similar to "0,1,2,8" you are in luck. 
         The response means something like:         
         0 - data         
         1 - class1 Fax         
         2  - class2 Fax         
         8 - Voice operation         
         There are other voice modems out there, in the form of ZyXEL and 
         Cirrus Logic versions. Those are not supported. The 1.06p and 
         prior versions were developed on a `Complete Communicator Gold' 
         from `The Complete PC'. This company is now owned by Boca, if my 
         information is right. Anyway, I've gotten a lot of reactions from 
         people owning a Voice Modem of some brand that would not work 
         correctly or at all. Those modems should work correctly now 
         (note: `should' does not equal `will'). I'm thinking of  `US 
         Robotics', `Elsa Microlink' and other new generation 28.8 voice 
         modems. This release (1.99a) is a very, very, very preliminary 
         alpha version of what someday might become version 2.0 of  The 
         Answering Machine for OS/2. This version will be based on my 
         Voice Modem API, which is incarnated as the `ME.DLL' Dynamic Link 
         Library, also included in this release. I'm releasing this ver-
         sion as a test version. I hope to come in contact with many voice 
         modem users to debug and perfect my API, and the application.         
         
         
         INCLUDED FILES         
         
         Included with this release are the following files:         
         answer.cpp         
         record.cpp         
         play.cpp         
         play.exe         
         record.exe         
         answer.EXE         
         ME.DLL         
         DMAIN.ZIP         
         Basically this release consists of 3 programs. One to `play' 
         Voice Modem audio files (ADPCM compressed audio) . One to `re-
         cord' those files. And one to act as a rudimentary `answer' - ing 

         





         machine. To find out how to run the programs , just execute them 
         without any parameters, and you'll see for yourself. One thing 
         not mentioned there is the way `answer.exe' stores the incoming 
         messages. The messages are numbered `0.msg' to `xxx.msg', in 
         incremental order. If you start the `answer.exe' program a second 
         time, the old messages will be overwritten, so save those in 
         another dir, or change their name.         
         I also included the source files of the three executables so that 
         you, if you are interested in those things, can see how bril-
         liantly simple it is to program a Voice Modem with my API. I'm 
         doing this because I'm also looking for customers that are 
         interested in buying a developer-kit, to make their own applica-
         tions.         
         The ModemEngine is located in the `ME.DLL'.         
         The `DMAIN.ZIP' package is a package from Rockwell that makes it 
         possible to convert the ADPCM files from your Voice Modem to and 
         from RIFF WAVE files. It's a DOS package, but those run perfectly 
         in a DOS box. I found this package on a Rockwell WWW-site 
         (http://www.tokyo.rockwell.com I believe) and I'm including in 
         it's totality. I hope that I'm not upsetting Rockwell people this 
         way, if so I'll remove the Rockwell package from my package.         
         
         FEEDBACK         
         
         I'm interested in all feedback, from users as well as developers. 
         I'm pretty short on time, so don't expect miracles. I'm also 
         looking for one (or more) good partners to make a GUI version of 
         the program. This because I'm short on time and I hate GUI, PM, 
         windoze, X-windows etc. programming, because I keep rebooting my 
         computer 20 times a day when doing this.         
         E-mail addresses are at the beginning of this note.         
         
         DISCLAIMER         
         
         
         I wrote this program with the idea of helping myself, and other 
         people with a voice-modem that use OS/2. I made it for fun, and 
         will therefore NOT take any responsibility for anything this 
         program will do. That includes any physical or mental damage to 
         you or your computer.         
         
         This software is provided `as is' without warranty of any kind, 
         either expressed or implied, including, but not limited to the 
         implied warranties of merchantability and fitness for a particu-
         lar purpose. The entire risk as to the quality and performance of 
         the program is with you. Some states do not allow the exclusion 
         of implied warranties, so the above  exclusions may not apply to 
         you. This warranty gives you specific legal rights and you may  
         also have other rights which vary from state to state. I have 
         taken due care in preparing the documentation and software to 
         ascertain their correctness and effectiveness. However, I do not 
         warrant that operation of this software will be uninterrupted or 
         error free. In no event shall I be liable for incidental or con-
         sequential damages in connection with or arising out of the 
         furnishing, performance, or use of this software.         
         
         LEGAL STUFF         
         
         This software is (c) by Sacha Prins.         
         
         All trademarks mentioned are owned by their respective owners.         
         
         You MAY try the program for as long as you like.         
         
         You MAY copy this software into any machine readable or printed 
         form for back-up or modification purposes in support of your use 

         





         of the software.         
         
         You MAY distribute the original unmodified version of this soft-
         ware, but you may not charge a fee exceeding $5.00 to cover the  
         cost of duplicating, shipping, and handling.         
         
         You may NOT use, copy, modify, sublicense, assign or transfer 
         this software and its license, or any copy or modification, in 
         whole or in part, except as expressly provided for in this 
         license.         
         
         