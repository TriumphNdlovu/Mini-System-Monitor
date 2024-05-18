# System Information Monitor

This C++ program gathers and displays system information, including memory usage, system name, and user details, in an HTML file that refreshes every 5 seconds. The HTML file is styled with basic CSS to improve readability.

## Features

- Retrieves and displays:
  - Hostname
  - Operating System
  - Node Name
  - Release
  - Version
  - Machine Type
  - User Name
  - Total RAM
  - Free RAM
  - Shared RAM
  - Buffered RAM
  - Total Swap
  - Free Swap
- Generates an HTML file that auto-refreshes every 5 seconds to update the displayed information.
- Opens the HTML file in the default web browser automatically.

## Prerequisites

- C++ compiler (e.g., g++)
- Standard C++ library
- System libraries: `unistd.h`, `sys/sysinfo.h`, `sys/utsname.h`, `pwd.h`

## Getting Started

### Compilation

To compile the program, use a C++ compiler. For example, with `g++`:

```sh
g++ SystemMonitor.cpp -o system_monitor
