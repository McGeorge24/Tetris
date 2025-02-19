#include "MusicDriver.h"

MusicDriver::MusicDriver(float transitionDuration) {
    currentTrackIndex = 0;
    nextTrackIndex = 0;
    isMusicTransitioning = false;
    shouldSwitchMusic = false;
    lastMusicChangeLevel = 0;
    transitionTime = transitionDuration;
    InitAudioDevice();
}

MusicDriver::~MusicDriver() {
    for (auto& track : musicTracks) {
        UnloadMusicStream(track.music);
    }
    CloseAudioDevice();
}


void MusicDriver::musicTransitionThread() {
    float elapsedTime = 0.0f;
    float startVolume = musicTracks[currentTrackIndex].volume;

    PlayMusicStream(musicTracks[nextTrackIndex].music);
    SetMusicVolume(musicTracks[nextTrackIndex].music, 0.0f);

    while (elapsedTime < transitionTime) {
        elapsedTime += GetFrameTime();
        float t = elapsedTime / transitionTime;

        float currentVolume = startVolume * (1.0f - t);
        SetMusicVolume(musicTracks[currentTrackIndex].music, currentVolume);
        musicTracks[currentTrackIndex].volume = currentVolume;

        float nextVolume = t;
        SetMusicVolume(musicTracks[nextTrackIndex].music, nextVolume);
        musicTracks[nextTrackIndex].volume = nextVolume;

        UpdateMusicStream(musicTracks[currentTrackIndex].music);
        UpdateMusicStream(musicTracks[nextTrackIndex].music);

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    StopMusicStream(musicTracks[currentTrackIndex].music);
    SetMusicVolume(musicTracks[nextTrackIndex].music, 1.0f);
    musicTracks[nextTrackIndex].volume = 1.0f;

    currentTrackIndex = nextTrackIndex;
    isMusicTransitioning = false;
}

void MusicDriver::addTrack(const std::string & filePath) {
    Music music = LoadMusicStream(filePath.c_str());
    musicTracks.push_back({ music, 1.0f });
}

void MusicDriver::play() {
    if (!musicTracks.empty()) {
        PlayMusicStream(musicTracks[currentTrackIndex].music);
    }
}

void MusicDriver::triggerMusicChange(int level, int trackIndex) {
    if (!isMusicTransitioning && level > lastMusicChangeLevel && trackIndex < musicTracks.size()) {
        nextTrackIndex = trackIndex;
        shouldSwitchMusic = true;
    }
}