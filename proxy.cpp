#include <unistd.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#define LIMIT 250
using namespace std;

int main()
{


	cout<<"Proxy Started\n";
	int proxyfd,clisockfd,portno;
	char buffer[LIMIT]={0};
	char  buff;
	struct addrinfo serv,*res,cli,*cli_res;
	memset(&serv,0,sizeof (serv)); //Setting struct to zero
	serv.ai_family=AF_UNSPEC;
	serv.ai_socktype=SOCK_STREAM;	//Filling struct
	serv.ai_flags=AI_PASSIVE;
	char *serv_Addr="127.0.0.1";
	char *port="3590"
	getaddrinfo(NULL,port,&serv,&res);
	proxyfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol); //creating socket
	bind(proxyfd,res->ai_addr,res->ai_addrlen);	//bindin socket to port

	listen(proxyfd,1);	//ready to accept connections
	int cli_len=sizeof(cli);
	clisockfd=accept(proxyfd,(struct sockaddr *)&cli,(socklen_t *)&cli_len); //accepting connections
	char *ip;
	cli_res=&cli;
	struct sockaddr_in *sin = (struct sockaddr_in *) cli_res;
    	ip = inet_ntoa(sin->sin_addr);
	cout<<"Client Connected :"<<ip<<endl;

	/*acting client to the main server*/

	int sockfd;

	struct addrinfo proxy,*res1;
	memset(&proxy,0,sizeof(proxy));	//Creating socket to connect to server
	proxy.ai_family=AF_UNSPEC;
	proxy.ai_socktype=SOCK_STREAM;

	getaddrinfo(serv_Addr,"5000",&proxy,&res1);
	sockfd=socket(res1->ai_family,res1->ai_socktype,res1->ai_protocol);

	if(connect(sockfd,res1->ai_addr,res1->ai_addrlen)==-1)
	{
		perror("Error connecting");	//connecting to server
	}
	cout<<"Connected to Server"<<endl;
	char file_list;
	while(recv(sockfd,&file_list,1,0))	//receiving filelist from server
	{
		send(clisockfd,&file_list,1,0);	//sending filelist to client
		if(file_list=='\0')
		break;
		cout<<file_list;
	}
	while(recv(clisockfd,&file_list,1,0))	//receiving request from client
	{	

		send(sockfd,&file_list,1,0);	//sending request to server
		if(file_list=='\0')
		break;
	}
	while(recv(sockfd,&file_list,1,0))	//receiving file from server
	{	
		send(clisockfd,&file_list,1,0);	//sending file to client
		cout<<file_list;
		if(file_list=='\0')
		break;
	}
	close(sockfd);

	close(clisockfd);			//closing sockets
	close(proxyfd);


}
