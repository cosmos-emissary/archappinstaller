# Archappinstaller

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
### Project Setup
##### Make git folder(If you do not make git folder, pinstall.sh cannot run).
```bash
mkdir git
cd git
```
#### Clone the project:

```bash
git clone https://github.com/cosmos-emissary/archappinstaller.git
cd archappinstaller
```
#### If you want compile the application

```bash
gcc -o application_installer application_installer.c `pkg-config --cflags --libs gtk+-3.0 gio-2.0 gdk-3.0`
```
#### Now we can add application folder to this program
```bash
cd $HOME/.local/share/applications/
nano arch-app-installer.desktop
```
```
[Desktop Entry]
Version=1.0
Type=Application
Name=Arch App Installer
Comment=Install various applications easily
Exec=$HOME/git/archappinstaller/gtk_installer
Icon=$HOME/git/archappinstaller/logo.jpg
Terminal=false
Categories=Utility;Application;
```
### Or you can use the script
```bash
chmod +x pinstall.sh
./pinstall.sh
```
