
# obnmtui

A native OpenBSD terminal network manager written in C, inspired by Linux NetworkManager's `nmtui`.

**Status:** Early prototype. Currently displays network interface information in a terminal interface. Wi-Fi scanning, connecting, and saved network management are planned features.

## Features

- Terminal interface using `ncurses`
- Display network interface information
- Refresh interface information with `r`
- Exit with `q`
- Designed specifically for OpenBSD

## Requirements

- OpenBSD
- C compiler (`cc`)
- BSD Make (`make`)
- Curses library

These tools are normally available on a standard OpenBSD installation.

## Installation

### 1. Clone the repository

Install Git if necessary:

```sh
doas pkg_add git
```

Clone the repository:

```sh
git clone https://github.com/YOUR_USERNAME/obnmtui.git
cd obnmtui
```

Replace `YOUR_USERNAME` with your GitHub username.

### 2. Compile the program

Build the application using OpenBSD's BSD Make:

```sh
make
```

If compilation succeeds, an executable named `obnmtui` should be created in the project directory.

### 3. Run obnmtui

Start the application:

```sh
./obnmtui
```

You do not need to run the application as root to display interface information.

## Usage

| Key | Action |
|---|---|
| `r` | Refresh interface information |
| `q` | Quit the application |

The application currently reads network interface information using OpenBSD's `/sbin/ifconfig` command.

## Optional: Install system-wide

To make `obnmtui` available from any directory:

```sh
doas install -m 755 obnmtui /usr/local/bin/obnmtui
```

You can then launch it with:

```sh
obnmtui
```

To uninstall:

```sh
doas rm -f /usr/local/bin/obnmtui
```

## Troubleshooting

### `make` fails

Ensure that you are using OpenBSD's BSD Make and that the source files and `Makefile` are in the same directory.

Check the compiler:

```sh
cc --version
```

### `./obnmtui` does not exist

Compile the program first:

```sh
make
```

### The terminal display looks incorrect

Try using a terminal with a supported terminal type:

```sh
echo $TERM
```

### Wi-Fi scanning and connecting are unavailable

These features have not been implemented yet. The current version only displays network interface information.

## Roadmap

- [x] Initial C terminal interface
- [x] Display network interface information
- [ ] Detect wireless interfaces automatically
- [ ] Display connection state and IP addresses
- [ ] Scan for nearby Wi-Fi networks
- [ ] Connect to WPA-protected networks
- [ ] Manage saved networks
- [ ] Improve error handling and terminal layout

## Security

- Do not run the entire application as root.
- Future connection features should use carefully controlled privileged operations.
- Wi-Fi passwords must not be written to logs or exposed in command-line arguments.
- Configuration changes should preserve file permissions
