#define WIN32_LEAN_AND_MEAN

#ifndef _YAVR_HEADER_H_
#define _YAVR_HEADER_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#elif __linux__ 
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton()
#include <netdb.h> // gethostbyname()
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>
#include <iomanip>
#include <filesystem>
#include <thread>

#include <openssl/ssl.h>
#include <openssl/err.h>

#ifdef _WINDLL
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#define DEFAULT_SIZE 100
#define PERFIX "[YAVR] "
#define STRING_NULL ""
#define U2A_VERSION "0.0.1-pre"

#ifdef _WIN64
#define BUILD_PLATFORM "x64"
#else
#define BUILD_PLATFORM "x86"
#endif

#endif