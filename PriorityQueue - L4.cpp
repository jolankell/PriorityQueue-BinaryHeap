////
// Name: Nolan Kelly
// Class: CS 233
// Description: This program is a priority queue which is prioritized based 
// criteria based in the function passed through to the PriorityQueue class 
// object when it is created. Multiple methods of priority are displayed in 
// this program and output displaying them is printed to the output screen.
////

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Process.h"
#include "PriorityQueue.h"


vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

vector<Process*> load(const string& filename) {
	vector<Process*> list;
	ifstream file(filename);

	string str;
	while (getline(file, str)) {
		vector<string> tokens = split(str, ',');
		list.push_back(new Process(tokens[0], stoi(tokens[1]), stoi(tokens[2]), static_cast<Process::PriorityLevel>(stoi(tokens[3]))));
	}

	return list;
}

using namespace std;

int main() {

	vector<Process*> processes = load("ProcessList.txt");

	cout << "Processes as read from File\n";
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	for (Process* process : processes) // access by reference to avoid copying
	{
		cout << (*process) << endl;    // displaying processing that are to be enqueue....debug information
	}
	cout << endl;

	// Part 2 A prioritize by ID: ascending order

	PriorityQueue<Process*> processqLambdaA([](Process* first, Process* second) {
			return (first->getID() > second->getID());
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambdaA.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaA sorted by ID value (least to greatest): " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaA.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		cout << *(processqLambdaA.dequeue()) << " ";
		cout << endl;
	}

	cout << endl << endl;

	// Part 2 B prioritize by PriorityLevel Reverse 

	PriorityQueue<Process*> processqLambdaB([](Process* first, Process* second) {
			return (first->getPriorityLevel() > second->getPriorityLevel());
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambdaB.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaB sorted by priority level numerically (least to greatest): " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaB.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		cout << *(processqLambdaB.dequeue()) << " ";
		cout << endl;
	}

	cout << endl << endl;

	// Part 2 C prioritize by Size Large to small

	PriorityQueue<Process*> processqLambdaC([](Process* first, Process* second) {
			return (first->getSize() < second->getSize());
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambdaC.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaC sorted by size (greatest to least): " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaC.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		cout << *(processqLambdaC.dequeue()) << " ";
		cout << endl;
	}

	cout << endl << endl;

	// Part 2 D prioritize by Name as in Dictionary (shift to lower during comparison)

	PriorityQueue<Process*> processqLambdaD([](Process* first, Process* second) {
			string word1 = first->getName();
			string word2 = second->getName();
			int shorterWord = 0; char ch1, ch2;

			if (word1.length() < word2.length()) {
				shorterWord = word1.size();
			}
			else {
				shorterWord = word2.size();
			}

			for (int i = 0; i < shorterWord; i++) {
				ch1 = tolower(word1[i]);
				ch2 = tolower(word2[i]);

				if (ch1 > ch2) {
					return true;
				}
				else if (ch1 == ch2) {
					continue;
				}
				else {
					return false;
				}
			}
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambdaD.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaD sorted by name (a-z): " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaD.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		  cout << *(processqLambdaD.dequeue()) << " ";
		  cout << endl;
	}

	cout << endl << endl;

	// Part 2 E prioritize by Name Reverse Dictionary (shift to lower during comparison)
	
	PriorityQueue<Process*> processqLambdaE([](Process* first, Process* second) {
			string word1 = first->getName();
			string word2 = second->getName();
			int shorterWord = 0; char ch1, ch2;

			if (word1.length() < word2.length()) {
				shorterWord = word1.size();
			}
			else {
				shorterWord = word2.size();
			}

			for (int i = 0; i < shorterWord; i++) {
				ch1 = tolower(word1[i]);
				ch2 = tolower(word2[i]);

				if (ch1 < ch2) {
					return true;
				}
				else if (ch1 == ch2) {
					continue;
				}
				else {
					return false;
				}
			}
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambdaE.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaE sorted by name (z-a): " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaE.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		cout << *(processqLambdaE.dequeue()) << " ";
		cout << endl;
	}	

	cout << endl << endl;

	// Part 2 F prioritize by PriorityLevel Critcal then High then ALL others equal(i.e.rough order they arrived)

	PriorityQueue<Process*> processqLambdaF([](Process* first, Process* second) {
			auto process1 = first->getPriorityLevel();
			auto process2 = second->getPriorityLevel();

			Process compareValue("USED FOR COMARIONS IN PART F", -10, -10, static_cast<Process::PriorityLevel>(1));

			if (process2 <= compareValue.getPriorityLevel() && process1 > compareValue.getPriorityLevel()) {
				return true;
			}

			else if (process2 <= compareValue.getPriorityLevel() && process1 <= compareValue.getPriorityLevel()) {

				if (process2 < process1) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
	});


	for (Process* process : processes) // access by reference to avoid copying
	{
	processqLambdaF.enqueue(process);
	}
	cout << endl;

	cout << "processqLambdaF sorted by priority level: " << endl;
	cout << setw(5) << "ID" << left << setw(25) << "  Name:" << right << endl;
	while (processqLambdaF.length() > 0) {
		/*cout << setw(18) << left << "Length of queue: " << processqLambdaA.length();*/
		cout << *(processqLambdaF.dequeue()) << " ";
		cout << endl;
	}

	cout << endl << endl;

	system("pause");
	return 0;
}
/* Screen output:
Processes as read from File
   ID  Name:
	0  System Idle Process        Level: 0  Size:      8
	4  System                     Level: 2  Size:   3240
   72  Secure System              Level: 1  Size:   3808
  560  smss.exe                   Level: 0  Size:    392
  920  csrss.exe                  Level: 3  Size:   2336
   96  wininit.exe                Level: 0  Size:    964
  736  services.exe               Level: 1  Size:   9112
  768  lsass.exe                  Level: 2  Size:  17704
  904  svchost.exe                Level: 3  Size:    784
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 1256  winlogon.exe               Level: 1  Size:   2868
 1464  dwm.exe                    Level: 3  Size:  52572
  220  igfxCUIService.exe         Level: 1  Size:   1500
 2184  WUDFHost.exe               Level: 3  Size:   2292
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
 2680  Memory Compression         Level: 3  Size:  70228
 2264  dasHost.exe                Level: 0  Size:   4208
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
 3668  wlanext.exe                Level: 1  Size:   6476
 3692  conhost.exe                Level: 0  Size:   1040
 3816  spoolsv.exe                Level: 3  Size:  16488
 3140  ibtsiva.exe                Level: 1  Size:    736
 3248  GfExperienceService.exe    Level: 3  Size:   4028
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
 3696  mfemms.exe                 Level: 2  Size:   3336
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 3796  EvtEng.exe                 Level: 2  Size:   5012
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
 3812  RegSrvc.exe                Level: 3  Size:   1632
 3836  NvNetworkService.exe       Level: 2  Size:   2768
 4140  PEFService.exe             Level: 0  Size:    572
 4148  sqlwriter.exe              Level: 2  Size:   1768
 4176  mcsacore.exe               Level: 1  Size:   5836
 4196  IRMTService.exe            Level: 0  Size:   3512
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
 4840  mfevtps.exe                Level: 0  Size:   1352
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 5200  RAVBg64.exe                Level: 3  Size:   4264
 5408  vmms.exe                   Level: 1  Size:  13344
 5740  MMSSHOST.exe               Level: 1  Size: 106464
 6716  unsecapp.exe               Level: 3  Size:   1156
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 6904  mfefire.exe                Level: 2  Size:   5104
 7004  mcapexe.exe                Level: 1  Size:   2688
 7600  vmcompute.exe              Level: 1  Size:   2208
 3640  mcshield.exe               Level: 2  Size:  39924
 7224  saUI.exe                   Level: 0  Size:   6344
 8256  sihost.exe                 Level: 3  Size:  20200
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
 8608  taskhostw.exe              Level: 0  Size:  13496
 8884  ctfmon.exe                 Level: 0  Size:   9508
 9148  explorer.exe               Level: 2  Size: 222536
 8532  igfxEM.exe                 Level: 2  Size:   4108
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
 9132  SearchUI.exe               Level: 1  Size: 167240
10528  RuntimeBroker.exe          Level: 2  Size:  19776
10824  SettingSyncHost.exe        Level: 1  Size:   4248
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
15076  MSASCuiL.exe               Level: 3  Size:   3612
15092  RtkNGUI64.exe              Level: 3  Size:   7952
15912  WavesSvc64.exe             Level: 3  Size:  17876
15316  AppVShNotify.exe           Level: 3  Size:   1496
16272  jusched.exe                Level: 2  Size:   2580
 4700  SearchIndexer.exe          Level: 3  Size:  72256
 5112  IAStorIcon.exe             Level: 1  Size:  12060
13580  ioc.exe                    Level: 2  Size:   7976
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
12208  DCCService.exe             Level: 1  Size:  13736
13336  MDLCSvc.exe                Level: 2  Size:  39152
10764  WmiPrvSE.exe               Level: 0  Size:  57328
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
14484  DeliveryService.exe        Level: 3  Size:  18128
15404  DellUpService.exe          Level: 1  Size:  63192
 1660  DellUpTray.exe             Level: 3  Size:  27804
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
 7512  jhi_service.exe            Level: 3  Size:    904
 2648  LMS.exe                    Level: 0  Size:   2344
 4696  PRSvc.exe                  Level: 2  Size:  37120
16572  RichVideo.exe              Level: 0  Size:   1208
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
13532  LockApp.exe                Level: 3  Size:  12908
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
11540  nvapiw.exe                 Level: 2  Size:   4252
 8272  dllhost.exe                Level: 3  Size:   8004
 7108  Calculator.exe             Level: 2  Size:  31340
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
 9256  iexplore.exe               Level: 3  Size:  23540
12432  McVulCtr.exe               Level: 3  Size:  16524
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
18228  SnippingTool.exe           Level: 2  Size:  11556
18704  OneDrive.exe               Level: 3  Size:  75964
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 4636  RzSDKServer.exe            Level: 1  Size:   1288
 1416  RazerCentralService.exe    Level: 0  Size:  31184
18268  GameManagerService.exe     Level: 1  Size:  84852
12188  RzSDKService.exe           Level: 1  Size:   3536
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
22344  Razer Central.exe          Level: 2  Size:  75728
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
23148  SkypeHost.exe              Level: 2  Size:  51556
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
12508  jucheck.exe                Level: 3  Size:  36948
19108  chrome.exe                 Level: 2  Size: 248996
 8808  POWERPNT.EXE               Level: 1  Size: 276400
24052  WWAHost.exe                Level: 2  Size:  57364
15896  McUICnt.exe                Level: 3  Size:   2044
17256  imstrayicon.exe            Level: 2  Size:   1016
11908  devenv.exe                 Level: 3  Size: 361976
24020  PerfWatson2.exe            Level: 2  Size:  60788
13796  VcxprojReader.exe          Level: 1  Size:  38224
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
11536  smartscreen.exe            Level: 0  Size:  15696
26036  vcpkgsrv.exe               Level: 3  Size:  41600
18884  cmd.exe                    Level: 0  Size:   3124
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
21600  tasklist.exe               Level: 1  Size:   7840


processqLambdaA sorted by ID value (least to greatest):
   ID  Name:
	0  System Idle Process        Level: 0  Size:      8
	4  System                     Level: 2  Size:   3240
   72  Secure System              Level: 1  Size:   3808
   96  wininit.exe                Level: 0  Size:    964
  220  igfxCUIService.exe         Level: 1  Size:   1500
  560  smss.exe                   Level: 0  Size:    392
  736  services.exe               Level: 1  Size:   9112
  768  lsass.exe                  Level: 2  Size:  17704
  904  svchost.exe                Level: 3  Size:    784
  920  csrss.exe                  Level: 3  Size:   2336
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 1256  winlogon.exe               Level: 1  Size:   2868
 1416  RazerCentralService.exe    Level: 0  Size:  31184
 1464  dwm.exe                    Level: 3  Size:  52572
 1660  DellUpTray.exe             Level: 3  Size:  27804
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
 2184  WUDFHost.exe               Level: 3  Size:   2292
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
 2264  dasHost.exe                Level: 0  Size:   4208
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
 2648  LMS.exe                    Level: 0  Size:   2344
 2680  Memory Compression         Level: 3  Size:  70228
 3140  ibtsiva.exe                Level: 1  Size:    736
 3248  GfExperienceService.exe    Level: 3  Size:   4028
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
 3640  mcshield.exe               Level: 2  Size:  39924
 3668  wlanext.exe                Level: 1  Size:   6476
 3692  conhost.exe                Level: 0  Size:   1040
 3696  mfemms.exe                 Level: 2  Size:   3336
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 3796  EvtEng.exe                 Level: 2  Size:   5012
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
 3812  RegSrvc.exe                Level: 3  Size:   1632
 3816  spoolsv.exe                Level: 3  Size:  16488
 3836  NvNetworkService.exe       Level: 2  Size:   2768
 4140  PEFService.exe             Level: 0  Size:    572
 4148  sqlwriter.exe              Level: 2  Size:   1768
 4176  mcsacore.exe               Level: 1  Size:   5836
 4196  IRMTService.exe            Level: 0  Size:   3512
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
 4636  RzSDKServer.exe            Level: 1  Size:   1288
 4696  PRSvc.exe                  Level: 2  Size:  37120
 4700  SearchIndexer.exe          Level: 3  Size:  72256
 4840  mfevtps.exe                Level: 0  Size:   1352
 5112  IAStorIcon.exe             Level: 1  Size:  12060
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 5200  RAVBg64.exe                Level: 3  Size:   4264
 5408  vmms.exe                   Level: 1  Size:  13344
 5740  MMSSHOST.exe               Level: 1  Size: 106464
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
 6716  unsecapp.exe               Level: 3  Size:   1156
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 6904  mfefire.exe                Level: 2  Size:   5104
 7004  mcapexe.exe                Level: 1  Size:   2688
 7108  Calculator.exe             Level: 2  Size:  31340
 7224  saUI.exe                   Level: 0  Size:   6344
 7512  jhi_service.exe            Level: 3  Size:    904
 7600  vmcompute.exe              Level: 1  Size:   2208
 8256  sihost.exe                 Level: 3  Size:  20200
 8272  dllhost.exe                Level: 3  Size:   8004
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
 8532  igfxEM.exe                 Level: 2  Size:   4108
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
 8608  taskhostw.exe              Level: 0  Size:  13496
 8808  POWERPNT.EXE               Level: 1  Size: 276400
 8884  ctfmon.exe                 Level: 0  Size:   9508
 9132  SearchUI.exe               Level: 1  Size: 167240
 9148  explorer.exe               Level: 2  Size: 222536
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 9256  iexplore.exe               Level: 3  Size:  23540
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
10528  RuntimeBroker.exe          Level: 2  Size:  19776
10764  WmiPrvSE.exe               Level: 0  Size:  57328
10824  SettingSyncHost.exe        Level: 1  Size:   4248
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
11536  smartscreen.exe            Level: 0  Size:  15696
11540  nvapiw.exe                 Level: 2  Size:   4252
11908  devenv.exe                 Level: 3  Size: 361976
12188  RzSDKService.exe           Level: 1  Size:   3536
12208  DCCService.exe             Level: 1  Size:  13736
12432  McVulCtr.exe               Level: 3  Size:  16524
12508  jucheck.exe                Level: 3  Size:  36948
13336  MDLCSvc.exe                Level: 2  Size:  39152
13532  LockApp.exe                Level: 3  Size:  12908
13580  ioc.exe                    Level: 2  Size:   7976
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
13796  VcxprojReader.exe          Level: 1  Size:  38224
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
14484  DeliveryService.exe        Level: 3  Size:  18128
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
15076  MSASCuiL.exe               Level: 3  Size:   3612
15092  RtkNGUI64.exe              Level: 3  Size:   7952
15316  AppVShNotify.exe           Level: 3  Size:   1496
15404  DellUpService.exe          Level: 1  Size:  63192
15896  McUICnt.exe                Level: 3  Size:   2044
15912  WavesSvc64.exe             Level: 3  Size:  17876
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
16272  jusched.exe                Level: 2  Size:   2580
16572  RichVideo.exe              Level: 0  Size:   1208
17256  imstrayicon.exe            Level: 2  Size:   1016
18228  SnippingTool.exe           Level: 2  Size:  11556
18268  GameManagerService.exe     Level: 1  Size:  84852
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
18704  OneDrive.exe               Level: 3  Size:  75964
18884  cmd.exe                    Level: 0  Size:   3124
19108  chrome.exe                 Level: 2  Size: 248996
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
21600  tasklist.exe               Level: 1  Size:   7840
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
22344  Razer Central.exe          Level: 2  Size:  75728
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
23148  SkypeHost.exe              Level: 2  Size:  51556
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
24020  PerfWatson2.exe            Level: 2  Size:  60788
24052  WWAHost.exe                Level: 2  Size:  57364
26036  vcpkgsrv.exe               Level: 3  Size:  41600



processqLambdaB sorted by priority level numerically (least to greatest):
   ID  Name:
	0  System Idle Process        Level: 0  Size:      8
  560  smss.exe                   Level: 0  Size:    392
 2264  dasHost.exe                Level: 0  Size:   4208
 4140  PEFService.exe             Level: 0  Size:    572
11536  smartscreen.exe            Level: 0  Size:  15696
18884  cmd.exe                    Level: 0  Size:   3124
 4196  IRMTService.exe            Level: 0  Size:   3512
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
 4840  mfevtps.exe                Level: 0  Size:   1352
10764  WmiPrvSE.exe               Level: 0  Size:  57328
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 3692  conhost.exe                Level: 0  Size:   1040
 2648  LMS.exe                    Level: 0  Size:   2344
16572  RichVideo.exe              Level: 0  Size:   1208
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
   96  wininit.exe                Level: 0  Size:    964
 7224  saUI.exe                   Level: 0  Size:   6344
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 1416  RazerCentralService.exe    Level: 0  Size:  31184
 8608  taskhostw.exe              Level: 0  Size:  13496
 8884  ctfmon.exe                 Level: 0  Size:   9508
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
21600  tasklist.exe               Level: 1  Size:   7840
 4176  mcsacore.exe               Level: 1  Size:   5836
 5112  IAStorIcon.exe             Level: 1  Size:  12060
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
12208  DCCService.exe             Level: 1  Size:  13736
 3668  wlanext.exe                Level: 1  Size:   6476
 5408  vmms.exe                   Level: 1  Size:  13344
15404  DellUpService.exe          Level: 1  Size:  63192
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
 5740  MMSSHOST.exe               Level: 1  Size: 106464
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
 1256  winlogon.exe               Level: 1  Size:   2868
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
 3140  ibtsiva.exe                Level: 1  Size:    736
 7004  mcapexe.exe                Level: 1  Size:   2688
 7600  vmcompute.exe              Level: 1  Size:   2208
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
   72  Secure System              Level: 1  Size:   3808
 4636  RzSDKServer.exe            Level: 1  Size:   1288
  220  igfxCUIService.exe         Level: 1  Size:   1500
18268  GameManagerService.exe     Level: 1  Size:  84852
12188  RzSDKService.exe           Level: 1  Size:   3536
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
  736  services.exe               Level: 1  Size:   9112
 8808  POWERPNT.EXE               Level: 1  Size: 276400
 9132  SearchUI.exe               Level: 1  Size: 167240
10824  SettingSyncHost.exe        Level: 1  Size:   4248
13796  VcxprojReader.exe          Level: 1  Size:  38224
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
18228  SnippingTool.exe           Level: 2  Size:  11556
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
22344  Razer Central.exe          Level: 2  Size:  75728
 4148  sqlwriter.exe              Level: 2  Size:   1768
	4  System                     Level: 2  Size:   3240
  768  lsass.exe                  Level: 2  Size:  17704
16272  jusched.exe                Level: 2  Size:   2580
24052  WWAHost.exe                Level: 2  Size:  57364
13580  ioc.exe                    Level: 2  Size:   7976
13336  MDLCSvc.exe                Level: 2  Size:  39152
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
10528  RuntimeBroker.exe          Level: 2  Size:  19776
24020  PerfWatson2.exe            Level: 2  Size:  60788
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
 4696  PRSvc.exe                  Level: 2  Size:  37120
 3836  NvNetworkService.exe       Level: 2  Size:   2768
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 7108  Calculator.exe             Level: 2  Size:  31340
 6904  mfefire.exe                Level: 2  Size:   5104
11540  nvapiw.exe                 Level: 2  Size:   4252
 3696  mfemms.exe                 Level: 2  Size:   3336
 3640  mcshield.exe               Level: 2  Size:  39924
 8532  igfxEM.exe                 Level: 2  Size:   4108
17256  imstrayicon.exe            Level: 2  Size:   1016
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 9148  explorer.exe               Level: 2  Size: 222536
23148  SkypeHost.exe              Level: 2  Size:  51556
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
19108  chrome.exe                 Level: 2  Size: 248996
 3796  EvtEng.exe                 Level: 2  Size:   5012
 8256  sihost.exe                 Level: 3  Size:  20200
15896  McUICnt.exe                Level: 3  Size:   2044
18704  OneDrive.exe               Level: 3  Size:  75964
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
 3812  RegSrvc.exe                Level: 3  Size:   1632
15076  MSASCuiL.exe               Level: 3  Size:   3612
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
26036  vcpkgsrv.exe               Level: 3  Size:  41600
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
 2184  WUDFHost.exe               Level: 3  Size:   2292
 9256  iexplore.exe               Level: 3  Size:  23540
 3816  spoolsv.exe                Level: 3  Size:  16488
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
 1660  DellUpTray.exe             Level: 3  Size:  27804
 6716  unsecapp.exe               Level: 3  Size:   1156
 7512  jhi_service.exe            Level: 3  Size:    904
 5200  RAVBg64.exe                Level: 3  Size:   4264
13532  LockApp.exe                Level: 3  Size:  12908
 8272  dllhost.exe                Level: 3  Size:   8004
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
15316  AppVShNotify.exe           Level: 3  Size:   1496
 4700  SearchIndexer.exe          Level: 3  Size:  72256
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
  920  csrss.exe                  Level: 3  Size:   2336
 3248  GfExperienceService.exe    Level: 3  Size:   4028
  904  svchost.exe                Level: 3  Size:    784
 1464  dwm.exe                    Level: 3  Size:  52572
 2680  Memory Compression         Level: 3  Size:  70228
15912  WavesSvc64.exe             Level: 3  Size:  17876
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
14484  DeliveryService.exe        Level: 3  Size:  18128
11908  devenv.exe                 Level: 3  Size: 361976
12508  jucheck.exe                Level: 3  Size:  36948
15092  RtkNGUI64.exe              Level: 3  Size:   7952
12432  McVulCtr.exe               Level: 3  Size:  16524



processqLambdaC sorted by size (greatest to least):
   ID  Name:
11908  devenv.exe                 Level: 3  Size: 361976
 8808  POWERPNT.EXE               Level: 1  Size: 276400
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
19108  chrome.exe                 Level: 2  Size: 248996
 9148  explorer.exe               Level: 2  Size: 222536
 9132  SearchUI.exe               Level: 1  Size: 167240
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
 5740  MMSSHOST.exe               Level: 1  Size: 106464
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
18268  GameManagerService.exe     Level: 1  Size:  84852
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
18704  OneDrive.exe               Level: 3  Size:  75964
22344  Razer Central.exe          Level: 2  Size:  75728
 4700  SearchIndexer.exe          Level: 3  Size:  72256
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
 2680  Memory Compression         Level: 3  Size:  70228
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
15404  DellUpService.exe          Level: 1  Size:  63192
24020  PerfWatson2.exe            Level: 2  Size:  60788
24052  WWAHost.exe                Level: 2  Size:  57364
10764  WmiPrvSE.exe               Level: 0  Size:  57328
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
 1464  dwm.exe                    Level: 3  Size:  52572
23148  SkypeHost.exe              Level: 2  Size:  51556
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
26036  vcpkgsrv.exe               Level: 3  Size:  41600
 3640  mcshield.exe               Level: 2  Size:  39924
13336  MDLCSvc.exe                Level: 2  Size:  39152
13796  VcxprojReader.exe          Level: 1  Size:  38224
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
 4696  PRSvc.exe                  Level: 2  Size:  37120
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
12508  jucheck.exe                Level: 3  Size:  36948
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
 7108  Calculator.exe             Level: 2  Size:  31340
 1416  RazerCentralService.exe    Level: 0  Size:  31184
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
 1660  DellUpTray.exe             Level: 3  Size:  27804
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
 9256  iexplore.exe               Level: 3  Size:  23540
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
 8256  sihost.exe                 Level: 3  Size:  20200
10528  RuntimeBroker.exe          Level: 2  Size:  19776
14484  DeliveryService.exe        Level: 3  Size:  18128
15912  WavesSvc64.exe             Level: 3  Size:  17876
  768  lsass.exe                  Level: 2  Size:  17704
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
12432  McVulCtr.exe               Level: 3  Size:  16524
 3816  spoolsv.exe                Level: 3  Size:  16488
11536  smartscreen.exe            Level: 0  Size:  15696
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
12208  DCCService.exe             Level: 1  Size:  13736
 8608  taskhostw.exe              Level: 0  Size:  13496
 5408  vmms.exe                   Level: 1  Size:  13344
13532  LockApp.exe                Level: 3  Size:  12908
 5112  IAStorIcon.exe             Level: 1  Size:  12060
18228  SnippingTool.exe           Level: 2  Size:  11556
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
 8884  ctfmon.exe                 Level: 0  Size:   9508
  736  services.exe               Level: 1  Size:   9112
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
 8272  dllhost.exe                Level: 3  Size:   8004
13580  ioc.exe                    Level: 2  Size:   7976
15092  RtkNGUI64.exe              Level: 3  Size:   7952
21600  tasklist.exe               Level: 1  Size:   7840
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
 3668  wlanext.exe                Level: 1  Size:   6476
 7224  saUI.exe                   Level: 0  Size:   6344
 4176  mcsacore.exe               Level: 1  Size:   5836
 6904  mfefire.exe                Level: 2  Size:   5104
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
 3796  EvtEng.exe                 Level: 2  Size:   5012
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
 5200  RAVBg64.exe                Level: 3  Size:   4264
11540  nvapiw.exe                 Level: 2  Size:   4252
10824  SettingSyncHost.exe        Level: 1  Size:   4248
 2264  dasHost.exe                Level: 0  Size:   4208
 8532  igfxEM.exe                 Level: 2  Size:   4108
 3248  GfExperienceService.exe    Level: 3  Size:   4028
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
   72  Secure System              Level: 1  Size:   3808
15076  MSASCuiL.exe               Level: 3  Size:   3612
12188  RzSDKService.exe           Level: 1  Size:   3536
 4196  IRMTService.exe            Level: 0  Size:   3512
 3696  mfemms.exe                 Level: 2  Size:   3336
	4  System                     Level: 2  Size:   3240
18884  cmd.exe                    Level: 0  Size:   3124
 1256  winlogon.exe               Level: 1  Size:   2868
 3836  NvNetworkService.exe       Level: 2  Size:   2768
 7004  mcapexe.exe                Level: 1  Size:   2688
16272  jusched.exe                Level: 2  Size:   2580
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
 2648  LMS.exe                    Level: 0  Size:   2344
  920  csrss.exe                  Level: 3  Size:   2336
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
 2184  WUDFHost.exe               Level: 3  Size:   2292
 7600  vmcompute.exe              Level: 1  Size:   2208
15896  McUICnt.exe                Level: 3  Size:   2044
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 4148  sqlwriter.exe              Level: 2  Size:   1768
 3812  RegSrvc.exe                Level: 3  Size:   1632
  220  igfxCUIService.exe         Level: 1  Size:   1500
15316  AppVShNotify.exe           Level: 3  Size:   1496
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
 4840  mfevtps.exe                Level: 0  Size:   1352
 4636  RzSDKServer.exe            Level: 1  Size:   1288
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
16572  RichVideo.exe              Level: 0  Size:   1208
 6716  unsecapp.exe               Level: 3  Size:   1156
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 3692  conhost.exe                Level: 0  Size:   1040
17256  imstrayicon.exe            Level: 2  Size:   1016
   96  wininit.exe                Level: 0  Size:    964
 7512  jhi_service.exe            Level: 3  Size:    904
  904  svchost.exe                Level: 3  Size:    784
 3140  ibtsiva.exe                Level: 1  Size:    736
 4140  PEFService.exe             Level: 0  Size:    572
  560  smss.exe                   Level: 0  Size:    392
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
	0  System Idle Process        Level: 0  Size:      8



processqLambdaD sorted by name (a-z):
   ID  Name:
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
15316  AppVShNotify.exe           Level: 3  Size:   1496
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
 7108  Calculator.exe             Level: 2  Size:  31340
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
19108  chrome.exe                 Level: 2  Size: 248996
18884  cmd.exe                    Level: 0  Size:   3124
 3692  conhost.exe                Level: 0  Size:   1040
  920  csrss.exe                  Level: 3  Size:   2336
 8884  ctfmon.exe                 Level: 0  Size:   9508
 2264  dasHost.exe                Level: 0  Size:   4208
12208  DCCService.exe             Level: 1  Size:  13736
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
14484  DeliveryService.exe        Level: 3  Size:  18128
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
15404  DellUpService.exe          Level: 1  Size:  63192
 1660  DellUpTray.exe             Level: 3  Size:  27804
11908  devenv.exe                 Level: 3  Size: 361976
 8272  dllhost.exe                Level: 3  Size:   8004
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
 1464  dwm.exe                    Level: 3  Size:  52572
 3796  EvtEng.exe                 Level: 2  Size:   5012
 9148  explorer.exe               Level: 2  Size: 222536
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 1048  fontdrvhost.exe            Level: 0  Size:   1956
18268  GameManagerService.exe     Level: 1  Size:  84852
 3248  GfExperienceService.exe    Level: 3  Size:   4028
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
 5112  IAStorIcon.exe             Level: 1  Size:  12060
 3140  ibtsiva.exe                Level: 1  Size:    736
 9256  iexplore.exe               Level: 3  Size:  23540
  220  igfxCUIService.exe         Level: 1  Size:   1500
 8532  igfxEM.exe                 Level: 2  Size:   4108
17256  imstrayicon.exe            Level: 2  Size:   1016
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
13580  ioc.exe                    Level: 2  Size:   7976
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
 4196  IRMTService.exe            Level: 0  Size:   3512
 7512  jhi_service.exe            Level: 3  Size:    904
12508  jucheck.exe                Level: 3  Size:  36948
16272  jusched.exe                Level: 2  Size:   2580
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
 2648  LMS.exe                    Level: 0  Size:   2344
13532  LockApp.exe                Level: 3  Size:  12908
  768  lsass.exe                  Level: 2  Size:  17704
 7004  mcapexe.exe                Level: 1  Size:   2688
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
 4176  mcsacore.exe               Level: 1  Size:   5836
 3640  mcshield.exe               Level: 2  Size:  39924
15896  McUICnt.exe                Level: 3  Size:   2044
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
12432  McVulCtr.exe               Level: 3  Size:  16524
13336  MDLCSvc.exe                Level: 2  Size:  39152
 2680  Memory Compression         Level: 3  Size:  70228
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 6904  mfefire.exe                Level: 2  Size:   5104
 3696  mfemms.exe                 Level: 2  Size:   3336
 4840  mfevtps.exe                Level: 0  Size:   1352
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
 5740  MMSSHOST.exe               Level: 1  Size: 106464
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
15076  MSASCuiL.exe               Level: 3  Size:   3612
11540  nvapiw.exe                 Level: 2  Size:   4252
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
 3836  NvNetworkService.exe       Level: 2  Size:   2768
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
18704  OneDrive.exe               Level: 3  Size:  75964
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
 4140  PEFService.exe             Level: 0  Size:    572
24020  PerfWatson2.exe            Level: 2  Size:  60788
 8808  POWERPNT.EXE               Level: 1  Size: 276400
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
 4696  PRSvc.exe                  Level: 2  Size:  37120
 5200  RAVBg64.exe                Level: 3  Size:   4264
22344  Razer Central.exe          Level: 2  Size:  75728
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
 1416  RazerCentralService.exe    Level: 0  Size:  31184
 3812  RegSrvc.exe                Level: 3  Size:   1632
16572  RichVideo.exe              Level: 0  Size:   1208
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
15092  RtkNGUI64.exe              Level: 3  Size:   7952
10528  RuntimeBroker.exe          Level: 2  Size:  19776
 4636  RzSDKServer.exe            Level: 1  Size:   1288
12188  RzSDKService.exe           Level: 1  Size:   3536
 7224  saUI.exe                   Level: 0  Size:   6344
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
 4700  SearchIndexer.exe          Level: 3  Size:  72256
 9132  SearchUI.exe               Level: 1  Size: 167240
   72  Secure System              Level: 1  Size:   3808
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
  736  services.exe               Level: 1  Size:   9112
10824  SettingSyncHost.exe        Level: 1  Size:   4248
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
 8256  sihost.exe                 Level: 3  Size:  20200
23148  SkypeHost.exe              Level: 2  Size:  51556
11536  smartscreen.exe            Level: 0  Size:  15696
  560  smss.exe                   Level: 0  Size:    392
18228  SnippingTool.exe           Level: 2  Size:  11556
 3816  spoolsv.exe                Level: 3  Size:  16488
 4148  sqlwriter.exe              Level: 2  Size:   1768
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
  904  svchost.exe                Level: 3  Size:    784
	4  System                     Level: 2  Size:   3240
	0  System Idle Process        Level: 0  Size:      8
 8608  taskhostw.exe              Level: 0  Size:  13496
21600  tasklist.exe               Level: 1  Size:   7840
 6716  unsecapp.exe               Level: 3  Size:   1156
26036  vcpkgsrv.exe               Level: 3  Size:  41600
13796  VcxprojReader.exe          Level: 1  Size:  38224
 7600  vmcompute.exe              Level: 1  Size:   2208
 5408  vmms.exe                   Level: 1  Size:  13344
15912  WavesSvc64.exe             Level: 3  Size:  17876
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
   96  wininit.exe                Level: 0  Size:    964
 1256  winlogon.exe               Level: 1  Size:   2868
 3668  wlanext.exe                Level: 1  Size:   6476
10764  WmiPrvSE.exe               Level: 0  Size:  57328
 2184  WUDFHost.exe               Level: 3  Size:   2292
24052  WWAHost.exe                Level: 2  Size:  57364



processqLambdaE sorted by name (z-a):
   ID  Name:
24052  WWAHost.exe                Level: 2  Size:  57364
 2184  WUDFHost.exe               Level: 3  Size:   2292
10764  WmiPrvSE.exe               Level: 0  Size:  57328
 3668  wlanext.exe                Level: 1  Size:   6476
 1256  winlogon.exe               Level: 1  Size:   2868
   96  wininit.exe                Level: 0  Size:    964
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
15912  WavesSvc64.exe             Level: 3  Size:  17876
 5408  vmms.exe                   Level: 1  Size:  13344
 7600  vmcompute.exe              Level: 1  Size:   2208
13796  VcxprojReader.exe          Level: 1  Size:  38224
26036  vcpkgsrv.exe               Level: 3  Size:  41600
 6716  unsecapp.exe               Level: 3  Size:   1156
21600  tasklist.exe               Level: 1  Size:   7840
 8608  taskhostw.exe              Level: 0  Size:  13496
	4  System                     Level: 2  Size:   3240
	0  System Idle Process        Level: 0  Size:      8
  904  svchost.exe                Level: 3  Size:    784
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
 4148  sqlwriter.exe              Level: 2  Size:   1768
 3816  spoolsv.exe                Level: 3  Size:  16488
18228  SnippingTool.exe           Level: 2  Size:  11556
  560  smss.exe                   Level: 0  Size:    392
11536  smartscreen.exe            Level: 0  Size:  15696
23148  SkypeHost.exe              Level: 2  Size:  51556
 8256  sihost.exe                 Level: 3  Size:  20200
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
10824  SettingSyncHost.exe        Level: 1  Size:   4248
  736  services.exe               Level: 1  Size:   9112
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
   72  Secure System              Level: 1  Size:   3808
 9132  SearchUI.exe               Level: 1  Size: 167240
 4700  SearchIndexer.exe          Level: 3  Size:  72256
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
 7224  saUI.exe                   Level: 0  Size:   6344
12188  RzSDKService.exe           Level: 1  Size:   3536
 4636  RzSDKServer.exe            Level: 1  Size:   1288
10528  RuntimeBroker.exe          Level: 2  Size:  19776
15092  RtkNGUI64.exe              Level: 3  Size:   7952
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
16572  RichVideo.exe              Level: 0  Size:   1208
 3812  RegSrvc.exe                Level: 3  Size:   1632
 1416  RazerCentralService.exe    Level: 0  Size:  31184
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
22344  Razer Central.exe          Level: 2  Size:  75728
 5200  RAVBg64.exe                Level: 3  Size:   4264
 4696  PRSvc.exe                  Level: 2  Size:  37120
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
 8808  POWERPNT.EXE               Level: 1  Size: 276400
24020  PerfWatson2.exe            Level: 2  Size:  60788
 4140  PEFService.exe             Level: 0  Size:    572
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
18704  OneDrive.exe               Level: 3  Size:  75964
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
 3836  NvNetworkService.exe       Level: 2  Size:   2768
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
11540  nvapiw.exe                 Level: 2  Size:   4252
15076  MSASCuiL.exe               Level: 3  Size:   3612
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
 5740  MMSSHOST.exe               Level: 1  Size: 106464
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
 4840  mfevtps.exe                Level: 0  Size:   1352
 3696  mfemms.exe                 Level: 2  Size:   3336
 6904  mfefire.exe                Level: 2  Size:   5104
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
 2680  Memory Compression         Level: 3  Size:  70228
13336  MDLCSvc.exe                Level: 2  Size:  39152
12432  McVulCtr.exe               Level: 3  Size:  16524
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
15896  McUICnt.exe                Level: 3  Size:   2044
 3640  mcshield.exe               Level: 2  Size:  39924
 4176  mcsacore.exe               Level: 1  Size:   5836
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
 7004  mcapexe.exe                Level: 1  Size:   2688
  768  lsass.exe                  Level: 2  Size:  17704
13532  LockApp.exe                Level: 3  Size:  12908
 2648  LMS.exe                    Level: 0  Size:   2344
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
16272  jusched.exe                Level: 2  Size:   2580
12508  jucheck.exe                Level: 3  Size:  36948
 7512  jhi_service.exe            Level: 3  Size:    904
 4196  IRMTService.exe            Level: 0  Size:   3512
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
13580  ioc.exe                    Level: 2  Size:   7976
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
17256  imstrayicon.exe            Level: 2  Size:   1016
 8532  igfxEM.exe                 Level: 2  Size:   4108
  220  igfxCUIService.exe         Level: 1  Size:   1500
 9256  iexplore.exe               Level: 3  Size:  23540
 3140  ibtsiva.exe                Level: 1  Size:    736
 5112  IAStorIcon.exe             Level: 1  Size:  12060
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
 3248  GfExperienceService.exe    Level: 3  Size:   4028
18268  GameManagerService.exe     Level: 1  Size:  84852
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 9148  explorer.exe               Level: 2  Size: 222536
 3796  EvtEng.exe                 Level: 2  Size:   5012
 1464  dwm.exe                    Level: 3  Size:  52572
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
 8272  dllhost.exe                Level: 3  Size:   8004
11908  devenv.exe                 Level: 3  Size: 361976
 1660  DellUpTray.exe             Level: 3  Size:  27804
15404  DellUpService.exe          Level: 1  Size:  63192
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
14484  DeliveryService.exe        Level: 3  Size:  18128
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
 4204  DDVDataCollector.exe       Level: 2  Size: 101536
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
12208  DCCService.exe             Level: 1  Size:  13736
 2264  dasHost.exe                Level: 0  Size:   4208
 8884  ctfmon.exe                 Level: 0  Size:   9508
  920  csrss.exe                  Level: 3  Size:   2336
 3692  conhost.exe                Level: 0  Size:   1040
18884  cmd.exe                    Level: 0  Size:   3124
19108  chrome.exe                 Level: 2  Size: 248996
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
 7108  Calculator.exe             Level: 2  Size:  31340
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
15316  AppVShNotify.exe           Level: 3  Size:   1496
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108



processqLambdaF sorted by priority level:
   ID  Name:
	0  System Idle Process        Level: 0  Size:      8
  560  smss.exe                   Level: 0  Size:    392
 2264  dasHost.exe                Level: 0  Size:   4208
 4140  PEFService.exe             Level: 0  Size:    572
11536  smartscreen.exe            Level: 0  Size:  15696
18884  cmd.exe                    Level: 0  Size:   3124
 4196  IRMTService.exe            Level: 0  Size:   3512
 4216  SecurityHealthService.exe  Level: 0  Size:  11248
 4840  mfevtps.exe                Level: 0  Size:   1352
10764  WmiPrvSE.exe               Level: 0  Size:  57328
 1048  fontdrvhost.exe            Level: 0  Size:   1956
 3692  conhost.exe                Level: 0  Size:   1040
 2648  LMS.exe                    Level: 0  Size:   2344
16572  RichVideo.exe              Level: 0  Size:   1208
15036  ApplicationFrameHost.exe   Level: 0  Size:  29108
   96  wininit.exe                Level: 0  Size:    964
 7224  saUI.exe                   Level: 0  Size:   6344
 9156  FileCoAuth.exe             Level: 0  Size:   7572
 1416  RazerCentralService.exe    Level: 0  Size:  31184
 8608  taskhostw.exe              Level: 0  Size:  13496
 8884  ctfmon.exe                 Level: 0  Size:   9508
 3804  WavesSysSvc64.exe          Level: 0  Size:   2312
 9668  ShellExperienceHost.exe    Level: 0  Size: 118844
13948  GoogleCrashHandler64.exe   Level: 0  Size:    112
23540  ServiceHub.DataWarehouseH  Level: 0  Size:  54628
21332  ScriptedSandbox64.exe      Level: 1  Size: 117596
 9476  OfficeClickToRun.exe       Level: 1  Size:  57308
16072  backgroundTaskHost.exe     Level: 1  Size:  21440
21600  tasklist.exe               Level: 1  Size:   7840
 4176  mcsacore.exe               Level: 1  Size:   5836
 5112  IAStorIcon.exe             Level: 1  Size:  12060
13960  McCSPServiceHost.exe       Level: 1  Size:  16920
 3292  RtkAudioService64.exe      Level: 1  Size:   1408
11024  IntelTechnologyAccessServ  Level: 1  Size:  10588
 4356  DDVRulesProcessor.exe      Level: 1  Size:   6776
12208  DCCService.exe             Level: 1  Size:  13736
 3668  wlanext.exe                Level: 1  Size:   6476
 5408  vmms.exe                   Level: 1  Size:  13344
15404  DellUpService.exe          Level: 1  Size:  63192
 6532  IAStorDataMgrSvc.exe       Level: 1  Size:  33336
 5740  MMSSHOST.exe               Level: 1  Size: 106464
14420  SupportAssistAgent.exe     Level: 1  Size:  56664
 1256  winlogon.exe               Level: 1  Size:   2868
 8376  DDVCollectorSvcApi.exe     Level: 1  Size:   1288
 3140  ibtsiva.exe                Level: 1  Size:    736
 7004  mcapexe.exe                Level: 1  Size:   2688
 7600  vmcompute.exe              Level: 1  Size:   2208
 8524  PresentationFontCache.exe  Level: 1  Size:   5104
   72  Secure System              Level: 1  Size:   3808
 4636  RzSDKServer.exe            Level: 1  Size:   1288
  220  igfxCUIService.exe         Level: 1  Size:   1500
18268  GameManagerService.exe     Level: 1  Size:  84852
12188  RzSDKService.exe           Level: 1  Size:   3536
 8584  DropboxUpdate.exe          Level: 1  Size:   1256
21856  CefSharp.BrowserSubproces  Level: 1  Size:  15496
  736  services.exe               Level: 1  Size:   9112
 8808  POWERPNT.EXE               Level: 1  Size: 276400
 9132  SearchUI.exe               Level: 1  Size: 167240
10824  SettingSyncHost.exe        Level: 1  Size:   4248
13796  VcxprojReader.exe          Level: 1  Size:  38224
20040  ServiceHub.Host.Node.x86.  Level: 1  Size:  33072
13688  ServiceHub.SettingsHost.e  Level: 1  Size:  65940
 2268  NVDisplay.Container.exe    Level: 1  Size:   8032
15076  MSASCuiL.exe               Level: 3  Size:   3612
 4700  SearchIndexer.exe          Level: 3  Size:  72256
16272  jusched.exe                Level: 2  Size:   2580
15316  AppVShNotify.exe           Level: 3  Size:   1496
15912  WavesSvc64.exe             Level: 3  Size:  17876
 2220  ServiceHub.Host.CLR.x86.e  Level: 3  Size:  37520
15092  RtkNGUI64.exe              Level: 3  Size:   7952
 4148  sqlwriter.exe              Level: 2  Size:   1768
13336  MDLCSvc.exe                Level: 2  Size:  39152
12508  jucheck.exe                Level: 3  Size:  36948
14076  DellSupportAssistRemedati  Level: 3  Size:  41864
22592  Microsoft.Photos.exe       Level: 2  Size: 252412
10528  RuntimeBroker.exe          Level: 2  Size:  19776
 2184  WUDFHost.exe               Level: 3  Size:   2292
19108  chrome.exe                 Level: 2  Size: 248996
 8532  igfxEM.exe                 Level: 2  Size:   4108
15896  McUICnt.exe                Level: 3  Size:   2044
 3768  IntelCpHDCPSvc.exe         Level: 2  Size:   1152
 4696  PRSvc.exe                  Level: 2  Size:  37120
 6716  unsecapp.exe               Level: 3  Size:   1156
 3796  EvtEng.exe                 Level: 2  Size:   5012
11908  devenv.exe                 Level: 3  Size: 361976
 3592  LegacyCsLoaderService.exe  Level: 3  Size:   3984
 3640  mcshield.exe               Level: 2  Size:  39924
11540  nvapiw.exe                 Level: 2  Size:   4252
 3248  GfExperienceService.exe    Level: 3  Size:   4028
 7108  Calculator.exe             Level: 2  Size:  31340
13964  GoogleCrashHandler.exe     Level: 2  Size:    212
12432  McVulCtr.exe               Level: 3  Size:  16524
18436  ServiceHub.VSDetouredHost  Level: 2  Size:  71992
 3812  RegSrvc.exe                Level: 3  Size:   1632
 9984  ServiceHub.IdentityHost.e  Level: 3  Size:  41832
 5144  IntelCpHeciSvc.exe         Level: 2  Size:   1148
 2680  Memory Compression         Level: 3  Size:  70228
17256  imstrayicon.exe            Level: 2  Size:   1016
24052  WWAHost.exe                Level: 2  Size:  57364
21924  Razer Synapse 3.exe        Level: 3  Size:  16660
  768  lsass.exe                  Level: 2  Size:  17704
24020  PerfWatson2.exe            Level: 2  Size:  60788
26036  vcpkgsrv.exe               Level: 3  Size:  41600
 3752  IpOverUsbSvc.exe           Level: 3  Size:   4284
	4  System                     Level: 2  Size:   3240
 5200  RAVBg64.exe                Level: 3  Size:   4264
23148  SkypeHost.exe              Level: 2  Size:  51556
 7512  jhi_service.exe            Level: 3  Size:    904
 3816  spoolsv.exe                Level: 3  Size:  16488
 9148  explorer.exe               Level: 2  Size: 222536
 1464  dwm.exe                    Level: 3  Size:  52572
 6904  mfefire.exe                Level: 2  Size:   5104
 8272  dllhost.exe                Level: 3  Size:   8004
 9256  iexplore.exe               Level: 3  Size:  23540
 4468  MCVULA~1.EXE               Level: 3  Size:   2452
 8256  sihost.exe                 Level: 3  Size:  20200
 3696  mfemms.exe                 Level: 2  Size:   3336
19288  Razer Synapse Service Pro  Level: 3  Size:  27088
22344  Razer Central.exe          Level: 2  Size:  75728
 4296  ModuleCoreService.exe      Level: 3  Size:  81100
14484  DeliveryService.exe        Level: 3  Size:  18128
  920  csrss.exe                  Level: 3  Size:   2336
 3836  NvNetworkService.exe       Level: 2  Size:   2768
13532  LockApp.exe                Level: 3  Size:  12908
 4632  OUTLOOK.EXE                Level: 2  Size: 252756
18704  OneDrive.exe               Level: 3  Size:  75964
 1916  Razer Synapse Service.exe  Level: 2  Size:  36980
  904  svchost.exe                Level: 3  Size:    784
 1660  DellUpTray.exe             Level: 3  Size:  27804
 6724  MfeAVSvc.exe               Level: 2  Size: 101536
18228  SnippingTool.exe           Level: 2  Size:  11556
13580  ioc.exe                    Level: 2  Size:   7976
 4204  DDVDataCollector.exe       Level: 2  Size: 101536


Press any key to continue . . .

C:\Users\jolan\source\repos\PriorityQueue - L4\x64\Debug\PriorityQueue - L4.exe (process 27432) exited with code 0 (0x0).
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .*/