#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "audio/include/AudioEngine.h"
#include "AudioStrategy.h"
#include <memory>
#include <string>

 // 音频引擎设置
extern int g_backgroundMusicSign;
extern float g_backgroundMusicVolume;

// 音频策略接口
extern std::unique_ptr<AudioStrategy> audioStrategy;

// 音频播放方法
void audioPlayer(const std::string& audioPath, bool isLoop);
void audioPlayer_StopBackgroundMusic();

#endif // !_AUDIO_PLAYER_H_
