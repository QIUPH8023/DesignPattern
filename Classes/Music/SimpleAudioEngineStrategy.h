#ifndef SIMPLE_AUDIO_ENGINE_STRATEGY_H
#define SIMPLE_AUDIO_ENGINE_STRATEGY_H

#include "AudioStrategy.h"
#include "audio/include/SimpleAudioEngine.h"  // 包含 SimpleAudioEngine 头文件

class SimpleAudioEngineStrategy : public AudioStrategy {
public:
    int play(const std::string& filePath, bool loop) override {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(), loop);
        return 0;  // SimpleAudioEngine 不返回音频 ID
    }

    void pauseAll() override {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    }

    void resumeAll() override {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    }

    void stopAll() override {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    }
};

#endif // SIMPLE_AUDIO_ENGINE_STRATEGY_H
