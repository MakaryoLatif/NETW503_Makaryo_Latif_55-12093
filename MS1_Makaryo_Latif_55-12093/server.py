import socket
import select
import sys
import threading

PORT = 5605
ADDR = ('127.0.0.1', PORT)
clients = []

def threaded(client_socket, client_address):
    print("[NEW CONNECTION] " + str(client_address) + " connected.")
    while True:
       data = client_socket.recv(1024).decode()
       if not data:
          break
       if data == "CLOSE SOCKET":
          client_socket.close()
          print(f"Connection with {client_address} closed")
          break
       response = data.upper()
       client_socket.send(response.encode())

def main():
   print("Server is starting ...")
   server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
   server_socket.bind((ADDR))
   server_socket.listen(5)
   while True :
       client_socket,client_address = server_socket.accept()
       threading.Lock().acquire()
       clients.append(client_socket)
       print(f"New connection from {client_address}")
       client_thread = threading.Thread(target=threaded, args=(client_socket, client_address))
       client_thread.start()
       print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")

 
if __name__ == "__main__":
   main()