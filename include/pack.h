#ifndef _YAVR_PACK_H_
#define _YAVR_PACK_H_

#include "yavr.h"

/*

	U2A Pack

	Err:
	- 11001 -> Something wrong with file

*/

namespace YAVR {

	class Pack : public YAVR::Templates::Err {

	private:
		std::string Prefix = "YAVR_PACK";
		YAVR::File* PackFile;
		std::vector < std::string > File, Content;

	public:
		Pack(std::string FileName = "") {
			PackFile = new YAVR::File(FileName);
		}

		void Create() {
			PackFile->Create();
		}
		void Open();
		void setFileName(std::string Name);
		std::string GetFileName() {
			return PackFile->GetFileName();
		}
		bool AddFile(std::string Path);
		void Load();
		void Print();
		std::string getFile(std::string FileName);
		bool is_open() {
			return PackFile->is_open();
		}
		void Unload();
		void Close() {
			PackFile->Close();
		}

	};

}

#endif