
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

WSADATA wsaData;
int iResult;
DWORD dwError;
SOCKET sockfd;
char* IP = "192.168.11.128";	//对方的IP
short PORT = 10111;
typedef struct sockaddr SA;
char name[20];	//用于存放文件名

/* 1启动客户端,连接服务器*/
void init()
{
	printf("client starting...\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(IP);

	if(connect(sockfd, (SOCKADDR*)&addr, sizeof(addr)) == -1){
		dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("Host not found\n");
				exit(-1);
            } else if (dwError == WSANO_DATA) {
                printf("No data record found\n");
				exit(-1);
            } else {
                printf("Function failed with error: %ld\n", dwError);
				exit(-1);
            }
        }
        perror("Can not connect to server.");
        printf("Client start failed!\n");
        exit(-1);
	}

	printf("Client start successed!\n");
	printf("Type <q> to exit.\n");
}
 
int get_user_input(char *str, int size)
{
	printf("Client>: ");
	fgets(str, size, stdin);
	return strlen(str);
}
 
/* 2通信 */
void start()
{
    int size = 0;
    char msg[100] = {};    
    char str[100] = {};
    do {
        memset(msg, 0, sizeof(msg));
        size = get_user_input(msg, sizeof(msg));
        printf("Send message to Server: %s", msg);
        send(sockfd, msg, size + 1, 0);
        recv(sockfd, str, sizeof(msg), 0);
        printf("Server return message: %s", str);
        if (!strcmp(msg, "bye\n"))
        {
            exit(0);
        }
    } while(1);
    closesocket(sockfd);
}

int main1()
{
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    init();//连接服务器
    start();//发送
    return 0;
	WSACleanup();
}

int main(int argc,char **argv)
{
    int err;
	DWORD dwError;
    WSADATA wsaData;

	// 初始化 Socket 类库
    err = WSAStartup(MAKEWORD(2,2), &wsaData);//协议库的版本信息
    if (!err) {
        printf("客户端嵌套字已经打开!\n");
    } else {
        printf("ERROR:客户端的嵌套字打开失败!\n");
        return 1;//结束
    }

	// 获取 Socket 对象
    SOCKET Socket = socket(AF_INET,SOCK_STREAM,0);

	// 连接服务器
    SOCKADDR_IN addr_in;
    addr_in.sin_addr.s_addr = inet_addr("192.168.11.128");
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(10111);
    //bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//注意第三个参数
    //listen(clientSocket,5);
    err = connect(Socket, (SOCKADDR*)&addr_in, sizeof(SOCKADDR));//开始连接
    if (!err) {
        printf("服务器已连接!\n");
    } else {
        printf("ERROR:服务器连接失败!\n");
		dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("Host not found\n");
            } else if (dwError == WSANO_DATA) {
                printf("No data record found\n");
            } else {
                printf("Function failed with error: %ld\n", dwError);
            }
        }
        WSACleanup();
        return 1;//结束
    }
    char receiveBuf[100];
    if (true){
        printf("Send: %s\n", "hello, this is client");
        send(Socket, "hello, this is client",strlen("hello, this is client") + 1, 0);

        recv(Socket, receiveBuf, 101, 0);
        printf("Recv: %s\n", receiveBuf);

        closesocket(Socket);
    }
    WSACleanup();
    return 0;
}