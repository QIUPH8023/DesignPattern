#include "cocos2d.h"
#include "string.h"
#include "AudioPlayer.h"
#include "proj.win32/Constant.h"
#include "AudioEngineStrategy.h"
#include "SimpleAudioEngineStrategy.h"

 // 全局变量定义
std::unique_ptr<AudioStrategy> audioStrategy;  // 音频策略
int g_backgroundMusicSign = -1;                // 背景音乐标识符
float g_backgroundMusicVolume = 1.0f;          // 背景音乐音量

// 播放音频
void audioPlayer(const std::string& audioPath, bool isLoop) {
    if (g_backgroundMusicSign != -1) {
        audioStrategy->stop(g_backgroundMusicSign);  // 停止当前背景音乐
    }
    g_backgroundMusicSign = audioStrategy->play(audioPath, isLoop);  // 播放新的背景音乐
    audioStrategy->setVolume(g_backgroundMusicSign, g_backgroundMusicVolume);
}

// 停止背景音乐
void audioPlayer_StopBackgroundMusic() {
    if (g_backgroundMusicSign != -1) {
        audioStrategy->stop(g_backgroundMusicSign);
        g_backgroundMusicSign = -1;
    }
}
