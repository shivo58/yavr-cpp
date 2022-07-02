#ifndef _YAVR_TEMPLATES_ERR_H_
#define _YAVR_TEMPLATES_ERR_H_

#include "yavr.header.h"

/*

	U2A 2019

*/

namespace YAVR::Templates {

	class Err {

	private:
		std::vector<int> mErr;

	public:
		void AddErr(int iErr);
		void DelErr(int iErr);
		bool FindErr(int iErr);
		std::string GetErr();
		void ClearErr();

	};


}

#endif