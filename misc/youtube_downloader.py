################################################
##
## Brian Behnke
## 12/23/2022
##
## Simple script to download YouTube videos
## Usage: python youtube_downloader.py <video_url_1> <video_url_2> ... <video_url_n>
## Ex:    python youtube_downloader.py https://www.youtube.com/watch?v=dQw4w9WgXcQ https://www.youtube.com/watch?v=LmQKZmQh1ZQ
##
## Requirements:
##      Pytube: https://pytube.io/en/latest/
##      FFmpeg: https://ffmpeg.org/
##
################################################

from pytube import YouTube
from pytube import exceptions
from ffmpy  import FFmpeg
from ffmpy  import FFRuntimeError

from pathlib import Path

import sys
import os


# Define paths
downloads_audio = str(Path.home() / 'Downloads\\audio')
downloads_video = str(Path.home() / 'Downloads\\video')
video_dir       = str(Path.home() / 'Videos\\YouTube')
ffmpeg_exe      = str(Path.home() / 'ffmpeg-2022-12-21-git-eef763c705-full_build\\bin\\ffmpeg.exe')


# YouTube uses Dynamic Adaptive Streaming over HTTP (DASH) for video quality over 720p.
# This streaming technique requires downloading the audio and video separately.
def get_highest_quality(link):
    yt = YouTube(link)
    title = ''.join(i for i in yt.title if i not in r'\/:*?<>|"')

    # Check the link for 1440p quality.
    streams = yt.streams.filter(resolution='1440p')
    res = '1440p'

    # 1440p not found, check for 1080p
    if len(streams) == 0:
        streams = yt.streams.filter(resolution='1080p')
        res = '1080p'

    # 1080p not found, can download audio and video together.
    if len(streams) == 0:
        print(f'\nDownloading {title} at highest available quality...')
        yt.streams.get_highest_resolution().download(video_dir)         # Gets the highest quality up to 720p
        print('Download complete.')
        return None, None, None

    # Video has either 1440p or 1080p options
    video = streams[0]
    if video is not None:
        print(f'\nDownloading {title} at {res}...')
        
        # Get_audio_only() automatically gets highest quality audio stream.
        video_path, audio_path = download(video, yt.streams.get_audio_only())
        print("Download complete.")
        return video_path, audio_path, title
    else:
        print('Something, somewhere messed up.')



# Downloads video and audio, then stores the files in downloads directories
def download(video, audio):
    try:
        video_path = video.download(downloads_video)
        audio_path = audio.download(downloads_audio)

        return video_path, audio_path

    except exceptions.PytubeError as e:
        print(e)


# Uses ffmpeg to merge the audio and video files and stores the output in the Videos directory.
# Video files are either MP4 or WebM. This function just copies the merged file and give it an .mp4 extension.
# There doesn't appear to be a loss of quality with this method, but maybe with a better understanding of
# video encoding, checking the original extension and re-encoding accordingly might produce better results.
def merge_a_and_v(video_path, audio_path, title):
    print('Merging audio and video...')
    try:
        ff = FFmpeg(
            executable=ffmpeg_exe,
            inputs={video_path: None, audio_path: None},
            outputs={video_dir + '\\' + title + '.mp4': '-c copy'}
        )
        ff.run()

    except FFRuntimeError as e:
        print(e)

    # Deletes downloaded files to save space.
    print('Deleting original files...')
    os.remove(video_path)
    os.remove(audio_path)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('\nToo few arguments.')
        print('Usage: python youtube_downloader.py <video_url_1> <video_url_2> ... <video_url_n>')
        exit()

    for arg in sys.argv[1:]:
        video_path, audio_path, title = get_highest_quality(arg)
        if video_path is not None or audio_path is not None or title is not None:
            merge_a_and_v(video_path, audio_path, title)