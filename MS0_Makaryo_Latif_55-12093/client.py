# Python program to implement server side of chat room.
import socket
import select
import sys
#initiate Client socket with the TCP connection
client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# binding the client socket with the localhost as ip and port number
port=5605
# try to connect to the server with associated port and id
client_socket.connect(('127.0.0.1',port)) #'127.0.0.1' is the localhost in ipv4 format
# open a connection until sending CLOSE SOCKET
while True:
   message=input("enter your message: ")
   # send message as bytes
   client_socket.send(message.encode())
   if not message:
        print("Empty message. Please enter a string.")
        continue
   if message == "CLOSE SOCKET":
        client_socket.close()
        break
   #recieve response if exists
   response = client_socket.recv(1024).decode()
   print("Server response: "  + response)

