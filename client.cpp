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
#include <fstream>
#define LIMIT 250
using namespace std;

int main()
{

	int sockfd;			//Socket descriptor
	char buffer;
	struct addrinfo cli,*res;
	memset(&cli,0,sizeof(cli));
	cli.ai_family=AF_INET;
	cli.ai_socktype=SOCK_STREAM;

	getaddrinfo("127.0.0.1","3590",&cli,&res);  //Filling struct addrinfo
	sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol); //Creating Socket

	if(connect(sockfd,res->ai_addr,res->ai_addrlen)==-1) //Connecting to proxy
	{
		perror("error connecting");
		return 0;
	}

	cout<<"The Files Present on the server are:\n";
	int count = 0;
	while(recv(sockfd,&buffer,1,0))  //Receiving list of files
	{
		if(buffer=='\0')
		break;
		cout<<buffer;
	}



	char req[20];
	cout<<"Enter the file to Download\n"; //Input filename
	cin>>req;

	send(sockfd,req,strlen(req),0); //sending filename
	send(sockfd,"\0",1,0);


	ofstream myfile;		//writing received data into file
 	myfile.open ("copy.txt");
	while(recv(sockfd,&buffer,1,0))
	{
		if(buffer=='\0')
		break;
		cout<<buffer;
 		myfile<<buffer; 
	}

	close(sockfd);







}



