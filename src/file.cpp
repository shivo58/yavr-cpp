#include "file.h"

void YAVR::File::SetFileName(std::string Name) {
	this->FileName = Name;
}

std::string YAVR::File::GetFileName() {
	return FileName;
}

void YAVR::File::Create(std::ios_base::openmode Params) {
	if (!FileName.empty()) {
		sFile = new std::fstream(FileName.c_str(), std::ios::out | std::ios::trunc);
		if (sFile->is_open()) {
			sFile->close();
			Open(Params);
		}
		else { AddErr(10003); }
	}
}

void YAVR::File::Open(std::ios_base::openmode Params) {
	if (!FileName.empty()) {
		ClearErr();
		sFile = new std::fstream(FileName.c_str(), Params);
		if (!sFile->is_open()) {
			AddErr(10002);
		}
	}
	else { AddErr(10001); }
}

void YAVR::File::Add(std::string Variable, std::string Value) {
	if (!Variable.empty()) {
		Variables.push_back(Variable);
		if (FT != YAVR::FileType::Line && !Value.empty()) {
			Values.push_back(Value);
		}
	}
}

void YAVR::File::AddToFile(std::string Value, bool ReOpen) {
	if (sFile->is_open() || ReOpen) {
		if (ReOpen) {
			if (!is_open()) {
				Open(std::ios_base::app);
			}
			else { Close(); Open(std::ios_base::app); }
		}
		*sFile << Value;
		if (ReOpen) {
			Close();
		}
	}
}

int YAVR::File::Find(std::string Variable) {
	for (int i = 0; i < static_cast<int>(Variables.size()); i++) {
		if (Variables[i] == Variable) {
			return i;
		}
	}
	return -1;
}

std::string YAVR::File::GetValue(std::string Variable) {
	for (int i = 0; i < static_cast<int>(Variables.size()); i++) {
		if (Variables[i] == Variable) {
			return Values[i];
		}
	}
	return STRING_NULL;
}

std::vector<std::string> YAVR::File::GetValues(std::string Variable)
{
	std::vector<std::string> Values;
	for (int i = 0; i < static_cast<int>(Variables.size()); i++) {
		if (Variables[i] == Variable) {
			Values.push_back(this->Values[i]);
		}
	}
	return Values;
}

void YAVR::File::Save() {
	if (FT == FileType::Default) {
		Create();
		for (int i = 0; i < static_cast<int>(Variables.size()); i++) {
			AddToFile(Variables[i] + (static_cast<int>(Values.size()) > i ? (!Values[i].empty() ? " = " + Values[i] : "") : "") + "\n");
		}
	}
	else if (FT == FileType::Line) {

	}
}

void YAVR::File::Load(std::string str) {
	if (is_open() || str != "") {
		std::string Temp;
		if (str == "") {
			while (std::getline(*sFile, Temp)) {
				Data.push_back(Temp);
				Temp.clear();
			}
		}
		else {
			for (int i = 0; i < static_cast<int>(str.size()) + 1; i++) {
				if (str[i] != '\n' && i != static_cast<int>(str.size()) && str[i] != '|') {
					Temp += str[i];
				}
				else {
					Data.push_back(Temp);
					Temp.clear();
				}
			}
		}
	}
}

void YAVR::File::Parse() {
	if (!Data.empty()) {
		if (FT == FileType::Default) {
			std::string Temp;
			bool WritingValue = false;
			for (int i = 0; i < static_cast<int>(Data.size()); i++) {
				for (int j = 0; j < static_cast<int>(Data[i].size()); j++) {
					if (isalpha(Data[i][j]) != 0 || ispunct(Data[i][j]) != 0 || isdigit(Data[i][j]) != 0 || Data[i][j] == ' ') {
						Temp += Data[i][j];
					}
					if (Data[i][j] == '=' && !WritingValue) {
						if (Temp[Temp.length() - 2] == ' ') {
							Temp.erase(Temp.length() - 1);
						}
						Temp.erase(Temp.length() - 1);
						Variables.push_back(Temp);
						WritingValue = true;
						Temp.clear();
					}
					if (WritingValue && j >= static_cast<int>(Data[i].size()) - 1) {
						if (Temp[0] == ' ') {
							Temp.erase(0, 1);
						}
						Values.push_back(Temp);
						WritingValue = false;
					}
				}
				Temp.clear();
			}
		}
	}
}

void YAVR::File::Print() {
	if (FT == FileType::Default) {
		for (int i = 0; i < static_cast<int>(Variables.size()); i++) {
			std::cout << "[" << i << "] " << Variables[i] << (static_cast<int>(Values.size()) > i ? (!Values[i].empty() ? " = " + Values[i] : "") : "") << std::endl;
		}
	}
	else if (FT == FileType::Line) {
		for (int i = 0; i < static_cast<int>(Data.size()); i++) {
			std::cout << Data[i] << std::endl;
		}
	}
}

void YAVR::File::Clear() {
	std::vector<std::string>().swap(Variables);
	std::vector<std::string>().swap(Values);
	std::vector<std::string>().swap(Data);
}

void YAVR::File::Close() {
	if (sFile != NULL && is_open()) {
		sFile->close();
	}
}

void YAVR::File::Destroy() {
	Clear();
	Close();
}