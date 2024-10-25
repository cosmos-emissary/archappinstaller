# archappinstaller

This application provides a user-friendly interface for installing predefined applications. It is written using GTK.

## Requirements

To run this project, you need the following libraries installed:

- GTK 3
- GLib
- GIO

### Installing Required Libraries on Arch Linux

You can install the necessary libraries using the following command:

```bash
sudo pacman -S base-devel gtk3
```
Project Setup

Clone the project:

bash

git clone https://github.com/your_username/application-installer.git
cd application-installer

Compile the application:

bash

gcc -o application_installer application_installer.c `pkg-config --cflags --libs gtk+-3.0 gio-2.0 gdk-3.0`

