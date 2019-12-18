#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
int main(int argc, char** argv)
{
    int sd;
    struct sockaddr_in addr;
    int yes = 1;
    char ch[50];

    if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
 
    // 送信先アドレスとポート番号を設定する
    // 受信プログラムと異なるあて先を設定しても UDP の場合はエラーにはならない
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = inet_addr("192.168.234.255");

    setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));
 
    while(1)
    {
    	puts("文字列を入力してください. 送信できる文字はひらがな16文字,アルファベット50文字までです.");

    	gets(ch);
 
	    // パケットをUDPで送信
    	if(sendto(sd, ch, 50, 0,
        	      (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        	perror("sendto");
        	return -1;
    	}
    }
 
    close(sd);
 
    return 0;
}
