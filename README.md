# file-transfer-cpp
c++ socket programming file transfer

This is a Socket Programming practice program to send and receiving files over C sockets using a proxy server.
In this implementaion the client connects to the proxy server , the proxy server conncets to the main server.
Main server then sends the list of available files by executing ls(unix command to get directory contents) and
then sending the output to client through proxy.The client then sends the request of file to the server via proxy.
The server then sends the file to client.
  Simple C socket programming functions are used to set up socket(),bind(),listen(),connect(),accept(),send()and recv().
  


