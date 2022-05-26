sudo usermod -aG uucp $USER # allow the current user to access serial devices

# download UI and make it executable
sudo wget -O /usr/local/bin/smartinput_ng_ui https://github.com/niwla23/smartinput_ng/releases/download/ui-v0.1.0/smartinput-ng-ui
sudo chmod a+x /usr/local/bin/smartinput_ng_ui

# download icon
sudo wget -O /usr/share/icons/hicolor/128x128/apps/smartinput_ng.png https://github.com/niwla23/smartinput_ng/raw/main/smartinput_ng_ui/src-tauri/icons/128x128.png 

# download desktop file
sudo wget -O /usr/share/applications/smartinput_ng_ui.desktop https://github.com/niwla23/smartinput_ng/raw/main/smartinput_ng_ui/smartinput_ng_ui.desktop

# install daemon
sudo pip3 install -U smartinput-ng-daemon

# download service file
sudo wget -O /etc/systemd/user/smartinput_ng_daemon.service https://raw.githubusercontent.com/niwla23/smartinput_ng/main/smartinput_ng_daemon/smartinput_ng_daemon.service

# reload daemon and enable service
systemctl --user daemon-reload
systemctl --user enable --now smartinput_ng_daemon