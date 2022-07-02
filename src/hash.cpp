#include "hash.h"

/*std::string YAVR::Hash::SHA256(std::vector<std::string> Data) {
    unsigned char Hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX SHA;
    SHA256_Init(&SHA);
    for (int i = 0; i < Data.size(); i++) {
        SHA256_Update(&SHA, Data[i].c_str(), Data[i].size());
    }
    SHA256_Final(Hash, &SHA);
    std::stringstream SHAHash;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        SHAHash << std::hex << std::setw(2) << std::setfill('0') << (int)Hash[i];
    }
    return SHAHash.str();
}*/