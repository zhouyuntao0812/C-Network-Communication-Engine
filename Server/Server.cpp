// TCP server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<WinSock2.h>//winsock2�������windows���棬��Ϊ���ڵ�window�Ѿ�ʵ����winsock,�������ͻ
#include<windows.h>
using namespace std;
#pragma comment(lib,"ws2_32")//��ȷָ��Ҫ�õ��Ŀ�
int main()
{
	WORD ver = MAKEWORD(2, 2);//�汾��
	WSADATA data;//wsa����ָ��
	WSAStartup(ver, &data);
	//�����׽���
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//AF_INETΪ����汾�ţ�SOCK_STREAM ����Ϊʲô������,ʲô��һ��Э�������
	//������˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;//����󶨵�ַ������Ϊipv4
	_sin.sin_port = htons(4567);//����to����
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//��������ip�����Է��ʵ�
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&_sin, sizeof(_sin)))
		cout << "��ʧ��" << endl;
	else
		cout << "�󶨳ɹ�" << endl;
	//�����˿�listen
	if (SOCKET_ERROR == listen(sock, 5))//���5������
		cout << "����ʧ��" << endl;
	else
		cout << "�����ɹ�" << endl;
	//�ȴ�����accept
	sockaddr_in client = {};
	SOCKET csock = INVALID_SOCKET;
	int claddr = sizeof(sockaddr_in);
	char msgbuf[] = "hello i am server";
	while (true) {
		csock = accept(sock, (sockaddr*)&client, &claddr);//����ֱ���пͻ�������
		if (csock == INVALID_SOCKET)
			cout << "���յ���Ч�ͻ���sock" << endl;
		cout << "�¿ͻ�����" << inet_ntoa(client.sin_addr) << endl;
		//��ͻ��˷�������
		csock = send(csock, msgbuf, strlen(msgbuf) + 1, 0);
		if (csock == SOCKET_ERROR)
			cout << "������Ϣʧ��" << endl;
		else
			cout << "������Ϣ�ɹ�" << endl;
	}
	//�ر�����
	closesocket(sock);


	WSACleanup();
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
