#ifndef AUDIO_ENGINE_STRATEGY_H
#define AUDIO_ENGINE_STRATEGY_H

#include "AudioStrategy.h"
#include "audio/include/AudioEngine.h"  // 包含 AudioEngine 头文件

class AudioEngineStrategy : public AudioStrategy 
{
public:
    int play(const std::string& filePath, bool loop) override 
    {
        return cocos2d::experimental::AudioEngine::play2d(filePath, loop);
    }

    void pauseAll() override 
    {
        cocos2d::experimental::AudioEngine::pauseAll();
    }

    void resumeAll() override 
    {
        cocos2d::experimental::AudioEngine::resumeAll();
    }

    void stopAll() override 
    {
        cocos2d::experimental::AudioEngine::stopAll();
    }
};

#endif // AUDIO_ENGINE_STRATEGY_H
