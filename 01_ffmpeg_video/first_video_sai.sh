#check information
ffprobe -i 1_f.mp4 -show_format -v quiet

#transfer gif to MP4
ffmpeg -i 1.gif -vf scale=480:-2,format=yuv420p 1.mp4
ffmpeg -i 2.gif -vf scale=480:-2,format=yuv420p 2.mp4
ffmpeg -i 3.gif -vf scale=480:-2,format=yuv420p 3.mp4
ffmpeg -i 4.gif -vf scale=480:-2,format=yuv420p 4.mp4
ffmpeg -i 5.gif -vf scale=480:-2,format=yuv420p 5.mp4
ffmpeg -i 6.gif -vf scale=480:-2,format=yuv420p 6.mp4
ffmpeg -i 7.gif -vf scale=480:-2,format=yuv420p 7.mp4
ffmpeg -i 8.gif -vf scale=480:-2,format=yuv420p 8.mp4
ffmpeg -i 9.gif -vf scale=480:-2,format=yuv420p 9.mp4
ffmpeg -i 10.gif -vf scale=480:-2,format=yuv420p 10.mp4
ffmpeg -i 11.gif -vf scale=480:-2,format=yuv420p 11.mp4
ffmpeg -i 12.gif -vf scale=480:-2,format=yuv420p 12.mp4
ffmpeg -i 13.gif -vf scale=480:-2,format=yuv420p 13.mp4
ffmpeg -i 14.gif -vf scale=480:-2,format=yuv420p 14.mp4
ffmpeg -i 15.gif -vf scale=480:-2,format=yuv420p 15.mp4
ffmpeg -i 16.gif -vf scale=480:-2,format=yuv420p 16.mp4  

#cut audio
ffmpeg -i robots.mp3 -ss 00:01:15 -t 00:00:40 -acodec copy bgm.mp3 

#add blur effect and set all videos into same frame size
ffmpeg -i 1.mp4 -lavfi "color=color=black@.5:size=480x270:d=1[dark]; [0:v]crop=480:270[blurbase]; [blurbase]boxblur=luma_radius='min(h,w)/20':luma_power=1:chroma_radius='min(cw,ch)/20':chroma_power=1[blurred]; [blurred][dark]overlay[darkened]; [darkened]scale=480:360[bg]; [0:v]scale=-1:360[fg]; [bg][fg]overlay=(W-w)/2:(H-h)/2" 1_blur.mp4  

#cut video
ffmpeg -ss 00:00:00 -t 00:00:01.24 -i 2.mp4 -c:v libx264 -preset superfast -c:a copy 2_f.mp4

# change frame rate
ffmpeg -i input.mov -qscale 0 -r 25 -y output.mov 

# change volume
ffmpeg -i input.wav -af volume=+3dB output.wav

#change speed of video
ffmpeg -i 1.mp4 -vframes 50 1_f.mp4

#combine video and audio
ffmpeg -y -i output.mp4 -i bgm.mp3 -c:v copy -c:a aac -strict experimental -map 0:v:0 -map 1:a:0 sailiu.mp4  
 
#concatenating media files
ffmpeg -y -f concat -safe 0 -i mylist.txt -c copy output.mp4  

#audio fade
ffmpeg -i 1.mp4 -af afade=t=in:st=0:d=3,afade=t=out:st=35:d=5 1_fade.mp4 
 
