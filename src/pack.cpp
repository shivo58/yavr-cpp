#include "pack.h"

void YAVR::Pack::setFileName(std::string FileName) {
	PackFile->SetFileName(FileName);
}

void YAVR::Pack::Open() {
	PackFile->Open();
	if (!PackFile->GetErr().empty()) {
		AddErr(11001);
	}
	else {
		PackFile->Load();
	}
}

std::string YAVR::Pack::getFile(std::string FileName) {
	for (int i = 0; i < File.size(); i++) {
		if (File[i] == FileName) {
			return Content[i];
		}
	}
	return STRING_NULL;
}

bool YAVR::Pack::AddFile(std::string Path) {
	if (is_open()) {
		YAVR::File* File = new YAVR::File(Path);
		File->Open();
		if (File->GetErr().empty()) {
			File->Load();
			File->Close();
			PackFile->AddToFile(Prefix + " " + YAVR::EncryptDecrypt(Path) + "\n");
			for (int i = 0; i < File->Data.size(); i++) {
				PackFile->AddToFile(File->Data[i] + "\n");
			}
			PackFile->AddToFile(Prefix + "_END" + "\n");
			return true;
		}
	}
	return false;
}

void YAVR::Pack::Load() {
	if (!PackFile->Data.empty()) {
		std::string Line, FileContent, FileName;
		bool Writing = false, NotFoundPrefix = true;
		for (int i = 0; i < PackFile->Data.size(); i++) {
			for (int j = 0; j < PackFile->Data[i].size(); j++) {
				Line += PackFile->Data[i][j];
				if (sizeof(Line) > 2 && Prefix.length()+5 > j) {
					if (Line[0] == Prefix[0] && Line[1] == Prefix[1]) {
						if (Line == Prefix && !Writing) {
							NotFoundPrefix = false;
							Writing = true;
							for (int x = static_cast<int>(Line.size()) + 1; x < PackFile->Data[i].size(); x++) {
								FileName += YAVR::EncryptDecrypt(std::string(1, PackFile->Data[i][x]));
							}
							break;
						}
						else if (Line == Prefix + "_END") {
							NotFoundPrefix = false;
							File.push_back(FileName);
							FileName.clear();
							Content.push_back(FileContent);
							FileContent.clear();
							Writing = false;
							break;
						}
					}
				}
			}
			if (Writing && NotFoundPrefix) {
				FileContent += Line + "\n";
			}
			NotFoundPrefix = true;
			Line.clear();
		}
	}

}

/*
void YAVR::Pack::Load(bool FastL) {
	if (PackFile->GetErr().empty() && PackFile->is_open()) {
		std::string Temp, PackFileContent, PackFileName;
		bool Writing = false, nFound = true;
		for (int i = 0; i < PackFile->Data.size(); i++) {
			for (int j = 0; j < PackFile->Data[i].size(); j++) {
				Temp += PackFile->Data[i][j];
				if (Temp[0] == 'U' && 100 > j) {
					if (Temp == YAVR::EncryptDecrypt("U2A_PACK_FILE")) {
						nFound = false;
						Writing = true;
						for (int x = static_cast<int>(Temp.size()) + 1; x < PackFile->Data[i].size(); x++) {
							PackFileName += PackFile->Data[i][x];
						}
						PackFileName = YAVR::EncryptDecrypt(PackFileName);
						break;
					}
					else if (Temp == YAVR::EncryptDecrypt("U2A_PACK_END_FILE")) {
						nFound = false;
						File.push_back(PackFileName);
						Content.push_back(PackFileContent);
						PackFileName.clear();
						PackFileContent.clear();
						Writing = false;
						break;
					}
				}
			}
			if (Writing && nFound) {
				PackFileContent += Temp + "\n";
			}
			nFound = true;
			Temp.clear();
		}
	}

}
*/

void YAVR::Pack::Print() {
	for (int i = 0; i < File.size(); i++) {
		printf("File[%i] -> %s (%zi)\n", i, File[i].c_str(), Content[i].length());
	}
}

void YAVR::Pack::Unload() {
	std::vector<std::string>().swap(File);
	std::vector<std::string>().swap(Content);
	PackFile->Destroy();
}