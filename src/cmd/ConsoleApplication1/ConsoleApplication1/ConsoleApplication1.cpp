// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <Ws2tcpip.h>



int main()
{

	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	SOCKET sock;
	int error = 0;

	char buf[32];


	// winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);

	// ソケットの設定
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock0, (struct sockaddr *)&addr, sizeof(addr));


	// TCPクライアントからの接続要求を待てる状態にする
	listen(sock0, 5);
	
	while (1) {
		// TCPクライアントからの接続要求を受け付ける
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);

		// 誰から接続されたか確認
		printf("accepted connection from %s, port=%d\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		// 5文字送信
		error = send(sock, "HELLO", 5, 0);

		// クライアントからデータを受信
		memset(buf, 0, sizeof(buf));
		int n = recv(sock, buf, sizeof(buf), 0);
		printf("%d, %s\n", n, buf);

		// TCPセッションの終了
		closesocket(sock);
	}

    return 0;
}
