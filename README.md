# Minitalk - 42 school project

## Project Overview
**Minitalk** is a simple client-server communication program using **UNIX signals**. The goal is to transmit messages from a client to a server using only signals `SIGUSR1` and `SIGUSR2` to communicate. This project emphasizes low-level signal handling and process communication.

---

## Executables

- `server`: Displays its PID. Listens for signals from the client, reconstructs the message bit by bit, and displays it once fully received.
  
- `client`: Sends a message to the server using its PID. Transmits each bit via `SIGUSR1` or `SIGUSR2`, waiting for `SIGUSR2` back from the server before proceeding to next. If no acknowledgment is received, client exits with failure. Receipt of `SIGUSR1` confirms successful message delivery.


---

## Build Instructions
Use `Makefile` to build both executables:

```zsh
make                              # Build both, client and server
./server                          # Start server to display PID and wait for a client
./client PID "string to send"     # Start client with two additional arguments, server´s PID and a string
