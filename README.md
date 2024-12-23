Attempt to replace some C library's functions and extend it by adding stl-like containers, macro helpers, cross-os network management & "other stuff"

List of desirable features:
- Language hacks:
  - [x] Virtual inheritance emulation
  - [x] Generic structs/methods/functions
- Memory:
  - [x] Generic default allocators
  - [x] No open C stdlib header usages
- Containers:
  - Static:
    - [x] Generic static array
  - Dynamic:
    - [x] Generic dynamic array
    - [x] Generic string + char_type defined implementations (char|char8|char16|char32|char64)
    - Associative arrays:
      - [x] Red-black tree set
      - [x] Red-black tree map
      - [ ] Chaining hash table set
      - [ ] Chaining hash table map
      - [ ] Open addressing hash table set
      - [ ] Open addressing hash table map
- Filesystem:
  - Network:
    - [x] Cross-platform sockets (linux/windows)
    - [x] Cross-platform blocking client (linux/windows)
    - [x] Cross-platform non-blocking client (linux/windows)
    - [x] Cross-platform blocking server (linux/windows)
    - [x] Cross-platform non-blocking server (linux/windows)
    - [ ] Connections/packages polling (select/poll(/epoll?))
    - [ ] Secure connections establishing (handshakes/etc)
    - [ ] Http/1.1 non-blocking client
    - [ ] Http/1.1 non-blocking server
    - [ ] Http/2 non-blocking client
    - [ ] Http/2 non-blocking server
  - File:
    - [ ] Cross-platform blocking file handlers (linux/windows)
    - [ ] Cross-platform non-blocking file handlers (linux/windows)
- Multitasking:
  - [x] Cross-platform threads management:
    - [x] Native threads usage wrappers
    - [x] Container-like threads usage wrappers
    - [x] Atomics
    - [ ] Mutexes
    - [ ] Semaphores
  - [ ] Cross-platform proccesses management
  - [ ] Cross-platform daemons management
  - IPC:
    - [ ] Cross-platform messages queue
    - [ ] Cross-platform pipes

List of "other stuff":
- Language hacks:
  - [x] Common lifecycle methods macro wrapper
- Helpers:
  - [x] Generic format print (for wide-strings and char-strings)
- Containers:
  - Static:
    - [x] Generic string view
    - [x] Generic pair type
    - [x] Generic optional type
    - [x] Generic result type
  - Dynamic:
    - [x] Generic array storage type
    - [x] Generic refernce counters (atomic & non-atomic with in-place construction optimization (control block + value))
    - [x] Json
      - [x] Value holder
      - [x] Serializer/deserializer
