# Socket Programming

## 🔹 What is Socket Programming?

A socket is like a "virtual plug" that lets two programs (processes) talk to each other over a network (or even on the same machine).

Think of it like a phone system:

- **Server** = waiting for calls.
- **Client** = dialing in.
- **Socket** = the phone line.

## 🔸 General Flow (Server Side)

### 1. Create a socket → like buying a phone.

**C Code Snippet:**
```c
int sock = socket(AF_INET, SOCK_STREAM, 0);
```

**Explanations:**
- `AF_INET` → IPv4.
- `SOCK_STREAM` → TCP (reliable, connection-based).
- `0` → default protocol for TCP.

### 2. Bind socket to an address and port → like registering your phone number.

**C Code Snippet:**
```c
bind(sock, (struct sockaddr *)&addr, sizeof(addr));
```

**Explanation:** Associates the socket with an IP (127.0.0.1) and a port (12000).

### 3. Listen for connections → like waiting for calls.

**C Code Block:**
```c
listen(sock, 20);
```

**Explanations:**
- Now the socket is a "listening socket".
- 20 means up to 20 waiting calls in the queue.

### 4. Accept a connection → like answering the phone.

**C Code Block:**
```c
int client_sock = accept(sock, (struct sockaddr *)&client, &len);
```

**Explanations:**
- Returns a new socket (`client_sock`) just for talking to that client.
- The original socket keeps listening for more.

### 5. Send/Receive data → like talking on the phone.

**C Code Block:**
```c
send(client_sock, msg, strlen(msg), 0);
recv(client_sock, buffer, sizeof(buffer), 0);
```

### 6. Close sockets → like hanging up the call.

**C Code Block:**
```c
close(client_sock);
close(sock);
```
