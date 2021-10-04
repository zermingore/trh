#!/bin/bash

set -e


desktop_entry="$(cat << 'EOF'
[Desktop Entry]
Name=trh
GenericName=trh
Comment=Translation tool
Comment[de]=Übersetzung Werkzeug
Comment[fr]=Outil de traduction
Exec=sh -c 'cd __SED_PATH__ && ./trh'
Icon=
Terminal=false
PrefersNonDefaultGPU=true
Type=Application
Categories=GNOME;GTK;Utility;
StartupNotify=false
Keywords=traduction;
EOF
)"

root_path=$(git rev-parse --show-toplevel)

if [ -z $root_path ]; then
  echo "Unable to find the root of the git repo; Aborting..."
  exit 1
fi


desktop_entry="${desktop_entry/__SED_PATH__/${root_path}}"
echo "$desktop_entry" > trh.desktop

echo "You may want to run:"
echo "cp thr.desktop /usr/share/applications/"
