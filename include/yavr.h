#ifndef _YAVR_H_
#define _YAVR_H_

#include "yavr.header.h"
#include "ymath.h"
#include "err.h"
#include "file.h"
#include "pack.h"
#include "hash.h"
#include "client.h"

namespace YAVR {
	std::string EncryptDecrypt(std::string toEncrypt);
	std::string CurrentDateTime(std::string Format = "%H_%M_%S-%Y.%m.%d");
	class Logs {
	private:
		YAVR::File* File;
	public:
		Logs() {
			File = new YAVR::File();
		}
		void Init(std::string Path = "logs/");
		void Write(std::string Text, bool Time=true);
		void Close();
	};
}

#endif