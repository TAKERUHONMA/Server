// �w�b�_�E���C�u����
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVER_PORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGE_LENGTH = 1024;

int main()
{
	//WinSock�̏�����
	WSADATA wsaData;

	//WinSock2.2 ����������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//�G���[����
		return 0;
	}

	//���X���\�P�b�g�̍쐬
	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET)
	{
		//�G���[����
		return 0;
	}

	//�Œ�A�h���X�̊��蓖��
	SOCKADDR_IN bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listenSock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		//�G���[����
		return 0;
	}

	//���X����Ԃɐݒ�
	if (listen(listenSock, 1) != 0)
	{
		//�G���[����
		return 0;
	}

	// �ڑ��v����t�E�R�l�N�V�����̊m���E�R�l�N�V�����m���ς݃\�P�b�g�̍쐬
	SOCKADDR_IN fromAddr;
	int addrlen = sizeof(fromAddr);
	SOCKET sock = accept(listenSock, (SOCKADDR*)&fromAddr, &addrlen);

	if (sock == INVALID_SOCKET)
	{
		//�G���[����
		return 0;
	}

	//����M�̃��[�v
	while (true)
	{
		char buff[MESSAGE_LENGTH]; //����M�����̊i�[�̈�

		//��M
		int ret = recv(sock, buff, sizeof(buff), 0);
		if (ret == SOCKET_ERROR)
		{
			//�G���[����
			return 0;
		}

		//�\��
		std::cout << buff << std::endl;

		//����
		std::cout << "���O����";
		std::cin >> buff;

		//���M
		ret = send(sock, buff, sizeof(buff), 0);
		if (ret == SOCKET_ERROR)
		{
			//�G���[����
			return 0;
		}
	}

	//�ؒf
	shutdown(sock, SD_BOTH);

	//�R�l�N�V�����m���ς݃\�P�b�g�̔j��
	closesocket(sock);

	//WinSock�I������
	if (WSACleanup() != 0)
	{
		//�G���[����
		return 0;
	}
	return 0;
}