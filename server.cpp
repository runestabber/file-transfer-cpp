#include <unistd.h>
#include <string>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <iostream>
#define LIMIT 250
#define PORT 3490
#include <stdlib.h>
using namespace std;
int main()
{
	
	cout<<"Server Started\n";
	int sockfd,clisockfd,portno;
	char buffer[LIMIT]={0};	
	char buff;
	struct addrinfo serv,*res,cli,*cli_res;
	memset(&serv,0,sizeof (serv));
	serv.ai_family=AF_UNSPEC;			//Creating Sockets
	serv.ai_socktype=SOCK_STREAM;
	serv.ai_flags=AI_PASSIVE;

	getaddrinfo(NULL,"5000",&serv,&res);
	sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	bind(sockfd,res->ai_addr,res->ai_addrlen);

	listen(sockfd,1);		//ready to accept connections
	int cli_len=sizeof(cli);
	clisockfd=accept(sockfd,(struct sockaddr *)&cli,(socklen_t *)&cli_len);
	cout<<"Client Connected :";
	char *ip;
	cli_res=&cli;
	struct sockaddr_in *sin = (struct sockaddr_in *) cli_res;
  	ip = inet_ntoa(sin->sin_addr);



	cout<<ip<<endl;
	system("rm list.txt");		
	system("ls >>list.txt");	//Executing ls to get list of files
	ifstream ls("list.txt");


	while(ls.getline(buffer,LIMIT))			//Reading from file
	{

		send(clisockfd,buffer,strlen(buffer),0);	//Sending data to client
		send(clisockfd,"\n",1,0);
		cout<<buffer<<endl;



	}

	send(clisockfd,"\0",1,0);
	char p[30]={0};
	char s;
	int i=0;
	while(recv(clisockfd,&s,1,0))
	{
		p[i++]=s;			//Receiving file request
		if(s=='\0')	
		break;

	}

	cout<<"The file Requested is :\n";
	cout<<p<<endl;
	ifstream file_cpy(p);

	while(file_cpy.getline(buffer,LIMIT))	//Reading from file
	{
		cout<<buffer<<"\n";
		send(clisockfd,buffer,strlen(buffer),0);	//Sending file Contents
		send(clisockfd,"\n",1,0);
	}
	send(clisockfd,"\0",1,0);
	close(clisockfd);


	
}
