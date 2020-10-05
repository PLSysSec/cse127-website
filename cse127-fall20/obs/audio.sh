#!/bin/bash
# systemctl --user restart pulseaudio.service
pacmd load-module module-echo-cancel aec_method=webrtc aec_args="analog_gain_control=0\ digital_gain_control=0\ voice_detection=1\ mobile=0\ noise_suppression=1" source_name=noechosource sink_name=noechosink
# pacmd set-default-source noechosource
# pacmd set-default-sink noechosink
pacmd load-module module-virtual-source source_name=zoom_source uplink_sink=zoom_sink
