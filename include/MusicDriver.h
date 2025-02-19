#pragma once
#include <atomic>
#include <thread>
#include <string>
#include <vector>
#include <raylib.h>

class MusicDriver {
private:
    struct TrackInfo {
        Music music;
        float volume;
    };

    std::vector<TrackInfo> musicTracks;
    std::atomic<int> currentTrackIndex;
    std::atomic<int> nextTrackIndex;
    std::atomic<bool> isMusicTransitioning;
    std::atomic<bool> shouldSwitchMusic;
    std::atomic<int> lastMusicChangeLevel;
    float transitionTime;

    void musicTransitionThread();

public:
    MusicDriver(float transitionDuration);
    ~MusicDriver();

    // Prevent copying and assignment
    MusicDriver(const MusicDriver&) = delete;
    MusicDriver& operator=(const MusicDriver&) = delete;

    void addTrack(const std::string& filePath);
    void play();
    void update(int currentLevel);
    void triggerMusicChange(int level, int trackIndex);
};
