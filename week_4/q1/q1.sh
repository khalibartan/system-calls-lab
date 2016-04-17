gcc q1_server.c -o server
xterm -e "./server" &
gcc q1_client.c -o client
xterm -e "./client" &
