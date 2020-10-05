combined layouts:
  [copy basic to ~/.config/obs-studio/]

  webcam:
    crop: left 60, right 40, top 100, bottom 60
    resolution: 640x480
    position (top left): (20, 45)
  ipad:
    crop: left 122, right 122
    position (top right): (1900, 45)
    size: 1584x990 (this is after cropping, so scaled)
  chat:
    size: 540x657
    position (bottom left): (20,1035)
  term:
    size 1318x992
    position (top right): (1900, 45)
  web:
    size 1318x992
    position (top right): (1900, 45)

SCRIPTS:

obs-term makes terminal set for camera terminal:
  i3-msg floating enable
  i3-msg resize set 1352 1039

obs-term-full makes terminal for full screen:
  i3-msg floating enable
  i3-msg resize set 1920 1080

i3 config and keybindings:
  ...
  set $ws5 "5:obs"
  set $ws6 "6:obs-projector"
  ...
  for_window [ title="Chat" ] move to workspace $ws6
  for_window [ title="Chat" ] floating enable
  for_window [ title="Chat" ] resize set 540 657
  
  for_window [ title="OBS" ] move to workspace $ws5
  for_window [ title="Zoom" ] move to workspace $ws6
  for_window [ title="Windowed Projector" ] move to workspace $ws6
  ...
  bindsym $mod+o workspace $ws5; floating enable; resize set 1382 1039
  bindsym $mod+Shift+o workspace $ws5; floating enable; resize set 1920 1080
  bindsym $mod+c workspace $ws6; floating enable; resize set 540 657
