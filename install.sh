usermod -aG uucp $USER # allow the current user to access serial devices

# download UI and make it executable
wget -O /usr/local/bin/smartinput_ng_ui https://github.com/niwla23/smartinput_ng/releases/download/ui-v0.1.0/smartinput-ng-ui
chmod a+x /usr/local/bin/smartinput_ng_ui

# download icon
wget -O /usr/share/icons/hicolor/128x128/apps/smartinput_ng.png https://github.com/niwla23/smartinput_ng/raw/main/smartinput_ng_ui/src-tauri/icons/128x128.png 

# download desktop file
wget -O /usr/share/applications/smartinput_ng_ui.desktop https://github.com/niwla23/smartinput_ng/raw/main/smartinput_ng_ui/smartinput_ng_ui.desktop

# install daemon
pip3 install smartinput-ng-daemon

# download service file
wget -O https://raw.githubusercontent.com/niwla23/smartinput_ng/main/smartinput_ng_daemon/smartinput_ng_daemon.service /etc/systemd/user/smartinput_ng_daemon.service

# reload daemon and enable service
systemctl --user daemon-reload 
systemctl --user enable --now smartinput_ng_daemon