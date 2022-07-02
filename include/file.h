#ifndef _YAVR_FILE_H_
#define _YAVR_FILE_H_

#include "err.h"

/*

	U2A File

	Err:
	- 10001 -> No file name
	- 10002 -> Cannot open file
	- 10003 -> Cannot create file

*/

namespace YAVR {

	enum class FileType {

		Default, Line

	};

	class File : public YAVR::Templates::Err {

	private:
		std::string FileName;
		std::fstream* sFile;
		std::vector<std::string> Values;
		YAVR::FileType FT;

	public:
		std::vector<std::string> Data, Variables;

		File(std::string FileName = "", YAVR::FileType FT = FileType::Default) {
			this->FileName = FileName;
			this->FT = FT;
		}

		void SetFileName(std::string Name);
		std::string GetFileName();
		void Create(std::ios_base::openmode Params = std::ios::binary | std::ios::in | std::ios::out);
		void Open(std::ios_base::openmode Params = std::ios::binary | std::ios::in | std::ios::out);
		void Load(std::string str = "");
		void Parse();
		void Print();
		void Add(std::string Variable, std::string Value = "");
		void AddToFile(std::string Value, bool ReOpen = false);
		int Find(std::string Variable);
		std::string GetValue(std::string Variable);
		std::vector<std::string> GetValues(std::string Variable);
		void Clear();
		void Close();
		bool is_open() {
			if (sFile != NULL) {
				return sFile->is_open();
			}
			else {
				return false;
			}
		}
		void Save();
		void Destroy();

	};

}

#endif