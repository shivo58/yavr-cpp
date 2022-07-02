#include "yavr.h"

std::string YAVR::EncryptDecrypt(std::string toEncrypt) {
	/*char Key = 'b';
	std::string Output = toEncrypt;
	for (int i = 0; i < toEncrypt.size(); i++) {
		Output[i] = toEncrypt[i] ^ Key;
	}*/
	return toEncrypt;
}

std::string YAVR::CurrentDateTime(std::string Format) {
	time_t Now = time(0);
	struct tm TS;
	char DateTime[DEFAULT_SIZE];
	localtime_s(&TS, &Now);
	strftime(DateTime, sizeof(DateTime), Format.c_str(), &TS);
	return DateTime;
}

void YAVR::Logs::Init(std::string Path) {
	File->SetFileName(Path + YAVR::CurrentDateTime() + "-" + BUILD_PLATFORM + ".txt");
	File->Create();
	Write("##    ##    ###    ##     ## ########  \n");
	Write(" ##  ##    ## ##   ##     ## ##     ## \n");
	Write("  ####    ##   ##  ##     ## ##     ## \n");
	Write("   ##    ##     ## ##     ## ########  \n");
	Write("   ##    #########  ##   ##  ##   ##   \n");
	Write("   ##    ##     ##   ## ##   ##    ##  \n");
	Write("   ##    ##     ##    ###    ##     ## \n");
}

void YAVR::Logs::Write(std::string Text, bool Time) {
	File->AddToFile((Time ? "[" + CurrentDateTime() + "] " : "")+Text, true);
}

void YAVR::Logs::Close() {
	File->Close();
}