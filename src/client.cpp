#include "client.h"

#pragma comment(lib,"ws2_32.lib")

void YAVR::Socket::Client::InitWinsock() {
    /*WSADATA wsaData;
    int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Result == -1) {

    }*/
}

void YAVR::Socket::Client::InitSSL() {
    /*const SSL_METHOD* Method = TLS_client_method();
    CTX = SSL_CTX_new(Method);
    if (CTX == nullptr)
    {
        ERR_print_errors_fp(stderr);
        //exit(EXIT_FAILURE);
    }
    ssl = SSL_new(CTX);
    if (ssl == nullptr){
        fprintf(stderr, "SSL_new() failed\n");
    }*/
}

bool YAVR::Socket::Client::Connect(bool SendMsg){
    /*InitWinsock();
    if (SCT == UDP) {
        Len = sizeof(ServerInfo);
        ServerInfo.sin_family = AF_INET;
        ServerInfo.sin_port = htons(Port);
        inet_pton(AF_INET, IP.c_str(), &ServerInfo.sin_addr);
        Socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (Socket != NULL) {
            Connected = true;
            if (SendMsg) {
                Send(STRING_NULL);
            }
            return true;
        }
        return false;
    }
    else {
        ZeroMemory(&Hints, sizeof(Hints));
        Hints.ai_family = AF_UNSPEC;
        Hints.ai_socktype = SOCK_STREAM;
        Hints.ai_protocol = IPPROTO_TCP;
        iResult = getaddrinfo(IP.c_str(), std::to_string(Port).c_str(), &Hints, &Result);
        if (iResult != 0) {
            //printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }
        // Attempt to connect to an address until one succeeds
        for (PTR = Result; PTR != NULL; PTR = PTR->ai_next) {
            Socket = socket(PTR->ai_family, PTR->ai_socktype, PTR->ai_protocol);
            if (Socket == INVALID_SOCKET) {
                //printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return 1;
            }
            iResult = connect(Socket, PTR->ai_addr, (int)PTR->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(Socket);
                Socket = INVALID_SOCKET;
                continue;
            }
            break;
        }
        freeaddrinfo(Result);
        if (Socket == INVALID_SOCKET) {
            //printf("Unable to connect to server!\n");
            WSACleanup();
            return false;
        }
        else {
            if (iSSL) {
                InitSSL();
                SSL_set_fd(ssl, Socket);
                const int Status = SSL_connect(ssl);
                if (Status != 1){
                    SSL_get_error(ssl, Status);
                    ERR_print_errors_fp(stderr); //High probability this doesn't do anything
                    fprintf(stderr, "SSL_connect failed with SSL_get_error code %d\n", Status);
                    return false;
                }
            }
            Connected = true;
            return true;
        }
    }*/
    return true;
}

std::string YAVR::Socket::Client::getCerts(){
    /*if (iSSL && ssl != nullptr) {
        std::string Res;
        X509* Cert = SSL_get_peer_certificate(ssl);
        if (Cert != nullptr){
            Res += "Server certificates:\n";
            char* line = X509_NAME_oneline(X509_get_subject_name(Cert), 0, 0);
            Res += "Subject: "+std::string(line)+"\n";
            delete line;
            line = X509_NAME_oneline(X509_get_issuer_name(Cert), 0, 0);
            Res += "Issuer: " + std::string(line)+"\n";
            delete line;
            X509_free(Cert);
        } else {
            Res += "No client certificates configured.\n";
        }
        return Res;
    }
    return STRING_NULL;*/
    return STRING_NULL;
}

bool YAVR::Socket::Client::Reconnect() {
    if (isConnected()) {
        Disconnect();
        return Connect();
    }
    return false;
}

bool YAVR::Socket::Client::Send(std::string Data) {
    /*if (SCT == UDP) {
        if (sendto(Socket, Data.c_str(), static_cast<int>(Data.size()), 0, (sockaddr*)&ServerInfo, Len) != SOCKET_ERROR) {
            return true;
        }
        return false;
    }
    else {
        if (iSSL) {
            iResult = SSL_write(ssl, Data.c_str(), (int)strlen(Data.c_str()));
            if (iResult <= 0) {
              //  int Error = SSL_get_error(ssl, iResult);
                //if (Error == SSL_ERROR_ZERO_RETURN) {
                    Disconnect();
               // }
                return false;
            }
        }
        else {
            iResult = send(Socket, Data.c_str(), (int)strlen(Data.c_str()), 0);
            if (iResult == SOCKET_ERROR) {
                Disconnect();
                return false;
            }
        }
        return true;
    }*/
    return false;
}

std::string YAVR::Socket::Client::Recv() {
    /*if (isConnected()) {
        std::string Data;
        if (SCT == UDP) {
            char test[30720];
            memset(test, 0, sizeof test);
            if (recvfrom(Socket, test, sizeof(test), 0, (sockaddr*)&ServerInfo, &Len) != SOCKET_ERROR) {
                return test;
            }
        }
        else {
            char chData[DEFAULT_SIZE * 10];
            memset(chData, NULL, sizeof(chData));
            if (iSSL) {
                iResult = SSL_read(ssl, chData, sizeof(chData));
                if (iResult > 0) {
                    return chData;
                }
                else if (iResult < 0) {
                    int err = SSL_get_error(ssl, iResult);
                    std::cout << "error is " << err << std::endl;
                }
            }
            else {
                iResult = recv(Socket, chData, sizeof(chData), 0);
                if (iResult > 0) {
                    return chData;
                }
            }
        }
    }
    return STRING_NULL;*/
    return STRING_NULL;
}

void YAVR::Socket::Client::Disconnect() {
    /*if (isConnected()) {
        if (SCT == UDP) {
            if (Socket != NULL) {
                closesocket(Socket);
            }
        }
        else {
            iResult = shutdown(Socket, SD_BOTH);
            if (iResult == SOCKET_ERROR) {
                //printf("shutdown failed with error: %d\n", WSAGetLastError());
                closesocket(Socket);
                WSACleanup();
            }
        }
        if (iSSL) {
            if (ssl != nullptr) {
                SSL_free(ssl);
            }
            if (CTX != nullptr) {
                SSL_CTX_free(CTX);
            }
        }
        Connected = false;
    }*/
}