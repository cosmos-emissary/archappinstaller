#!/bin/bash

APP_NAME="Arch Application Installer"
DESKTOP_FILE="$HOME/.local/share/applications/arch-application-installer.desktop"
EXEC_PATH="$HOME/git/archappinstaller/gtk_installer"
ICON_PATH="$HOME/git/archappinstaller/logo.jpg" 

cat <<EOL > "$DESKTOP_FILE"
[Desktop Entry]
Version=1.0
Type=Application
Name=$APP_NAME
Comment=Install various applications easily
Exec=$EXEC_PATH
Icon=$ICON_PATH
Terminal=false
Categories=Utility;Application;
EOL

chmod +x "$DESKTOP_FILE"

echo "Desktop entry for '$APP_NAME' has been created successfully."
echo "You can find it in your applications menu."