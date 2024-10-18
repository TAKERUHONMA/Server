// ヘッダ・ライブラリ
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVER_PORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGE_LENGTH = 1024;

int main()
{
	//WinSockの初期化
	WSADATA wsaData;

	//WinSock2.2 初期化処理
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//エラー処理
		return 0;
	}

	//リスンソケットの作成
	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET)
	{
		//エラー処理
		return 0;
	}

	//固定アドレスの割り当て
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listenSock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		//エラー処理
		return 0;
	}

	//リスン状態に設定
	if (listen(listenSock, 1) != 0)
	{
		//エラー処理
		return 0;
	}

	// 接続要求受付・コネクションの確立・コネクション確立済みソケットの作成
	SOCKADDR_IN fromAddr;
	int addrlen = sizeof(fromAddr);
	SOCKET sock = accept(listenSock, (SOCKADDR*)&fromAddr, &addrlen);

	if (sock == INVALID_SOCKET)
	{
		//エラー処理
		return 0;
	}

	//送受信のループ
	while (true)
	{
		char buff[MESSAGE_LENGTH]; //送受信文字の格納領域

		//受信
		int ret = recv(sock, buff, sizeof(buff), 0);
		if (ret == SOCKET_ERROR)
		{
			//エラー処理
			return 0;
		}

		//表示
		std::cout << buff << std::endl;

		//入力
		std::cout << "お前が後";
		std::cin >> buff;

		//送信
		ret = send(sock, buff, sizeof(buff), 0);
		if (ret == SOCKET_ERROR)
		{
			//エラー処理
			return 0;
		}
	}

	//切断
	shutdown(sock, SD_BOTH);

	//コネクション確率済みソケットの破棄
	closesocket(sock);

	//WinSock終了処理
	if (WSACleanup() != 0)
	{
		//エラー処理
		return 0;
	}
	return 0;
}