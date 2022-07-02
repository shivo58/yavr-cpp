#ifndef _YAVR_CLIENT_H_
#define _YAVR_CLIENT_H_

#include "yavr.header.h"

namespace YAVR {

	namespace Socket {

		enum SocketClientType {
			UDP, TCP
		};

		class Client {

		private:
			//SOCKET Socket;
			SocketClientType SCT;
			struct sockaddr_in ServerInfo;
			struct addrinfo Hints,
				* Result = NULL,
				* PTR = NULL;
			std::string IP = "0.0.0.0";
			int Port = 1000, Len, iResult;

			void InitWinsock();
			void InitSSL();

			SSL_CTX* CTX;
			SSL* ssl;

			bool Connected = false, iSSL;

		public:
			Client(SocketClientType SCT = UDP, bool iSSL = false) {
				this->iSSL = iSSL;
				this->SCT = SCT;
			}

			/*SOCKET getSocket() {
				return Socket;
			}*/
			void SetIP(std::string IP, int Port) {
				this->IP = IP;
				this->Port = Port;
			}
			std::string getCerts();
			bool isConnected() {
				return Connected;
			}
			bool Connect(bool SendMsg=true);
			bool Reconnect();
			bool Send(std::string Data);
			std::string Recv();
			void Disconnect();

		};

	}

}

#endif