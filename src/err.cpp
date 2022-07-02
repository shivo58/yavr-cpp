#include "err.h"

void YAVR::Templates::Err::AddErr(int iErr) {
	mErr.push_back(iErr);
}

void YAVR::Templates::Err::DelErr(int iErr) {
	for (int i = 0; i < static_cast<int>(mErr.size()); i++) {
		if (mErr[i] == iErr) {
			mErr.erase(mErr.begin() + i);
			break;
		}
	}
}

bool YAVR::Templates::Err::FindErr(int iErr) {
	for (int i = 0; i < static_cast<int>(mErr.size()); i++) {
		if (mErr[i] == iErr) {
			return true;
		}
	}
	return false;
}

std::string YAVR::Templates::Err::GetErr() {
	std::string Errors;
	int Size = static_cast<int>(mErr.size());
	for (int i = 0; i < Size; i++) {
		Errors += std::to_string(mErr[i]) += ( i != Size-1 ? "," : "");
	}
	return Errors;
}

void YAVR::Templates::Err::ClearErr() {
	mErr.clear();
}