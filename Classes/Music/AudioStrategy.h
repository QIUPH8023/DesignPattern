#ifndef AUDIO_STRATEGY_H
#define AUDIO_STRATEGY_H

#include <string>
//创建一个统一音频接口，定义音频的核心操作
class AudioStrategy 
{
public:
    virtual ~AudioStrategy() = default;

    // 播放音频
    virtual int play(const std::string& filePath, bool loop) = 0;

    // 暂停所有音频
    virtual void pauseAll() = 0;

    // 恢复所有音频
    virtual void resumeAll() = 0;

    // 停止所有音频
    virtual void stopAll() = 0;
};

#endif // AUDIO_STRATEGY_H
