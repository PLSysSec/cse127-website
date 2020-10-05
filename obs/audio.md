1. run audio.sh
2. in zoom:
   - set speaker = zoom_sink
3. in obs:
   - add zoom_sink to desktop audio
   - set non echo canceling yeti to monitor

   - in the audio mixer, add noise supression filter and noise gate
   - in the audio mixer choose the echo cancellaled mic
   - make sure monitor and output is set for both
4. in pavucontrol:
   - set the yeti mic level to base
5. once you're done adjusting mic settings:
   - in obs audio mixer: set yeti to output only (no monitor) to stay sane
