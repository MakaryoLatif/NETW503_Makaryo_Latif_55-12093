import socket
import select
import sys
#initiate server socket with the TCP connection
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# binding the server socket with the localhost as ip and port number
port=5605
server_socket.bind(('127.0.0.1',port)) # '127.0.0.1' is the localhost in ipv4 format
# make the socket listen on this port
server_socket.listen(5)
# listening forever
while True :
    client_socket,client_address = server_socket.accept() # when a connection to a client is accepted
    print("Connection established with client")
    # open a conditional conection --> break the connection when 'CLOSE SOCKET' is recieved
    while True:
       # recieve message as bytes
       # decoding the bytes into characters
       data = client_socket.recv(1024).decode()
       if not data:
          break
       #Check if the message was 'CLOSE SOCKET' to close connection
       if data == "CLOSE SOCKET":
          client_socket.close()
          print("Connection with client closed")
          break
       # otherwise capitalize the decoded message
       response = data.upper()
       # send the response as bytes again
       client_socket.send(response.encode())
       