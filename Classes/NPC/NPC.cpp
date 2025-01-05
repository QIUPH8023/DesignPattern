#include "NPC.h"

NPC::NPC() {}

NPC::~NPC() {}

bool NPC::init(const std::string& spriteFile, const NPCType& _npctype)
{
    if (!Sprite::initWithFile(spriteFile)) {
        return false;
    }

    npctype = _npctype;

    switch (npctype) {
        case NPCType::ALEX:
            dialog = NPC_ALEX_DIALOG;
            break;
        case NPCType::ABIGAIL:
            dialog = NPC_ABIGAIL_DIALOG;
            break;
        case NPCType::CAROLINE:
            dialog = NPC_CAROLINE_DIALOG;
            break;
        case NPCType::LEWIS:
            dialog = NPC_LEWIS_DIALOG;
            break;
        default:
            break;
    }

    return true;
}

NPC* NPC::create(const std::string& spriteFile, const NPCType& _npctype)
{
    NPC* npc = new(std::nothrow) NPC();
    if (npc && npc->init(spriteFile, _npctype)) {
        npc->autorelease();
        return npc;
    }
    else {
        delete npc;
        return nullptr;
    }
}

std::string NPC::getDialog()
{
	return dialog[dialogIndex];
}

void NPC::advanceDialog()
{
    if (dialogIndex < dialog.size() - 1) {
        dialogIndex++;
    }
    else {
        CCLOG("chat end");
    }
}

void NPC::jumpToDialog(int index)
{
    if (index >= 0 && index < dialog.size()) {
        dialogIndex = index;
    }
    else {
        CCLOG("invalid session index");
    }
}

NPCType& NPC::getNPCType() 
{
    return npctype;
}

std::string NPC::getHead() 
{
    switch (npctype) 
    {
        case ALEX:
            return "NPC/AlexPortrait.png";
            break;
        case ABIGAIL:
            return "NPC/AbigailPortrait.png";
            break;
        case CAROLINE:
            return "NPC/CarolinePortrait.png";
            break;
        case LEWIS:
            return "NPC/LewisPortrait.png";
            break;
    }
}

void NPC::setNPCLove(int amount) 
{
    npclove += amount;
}

std::string NPC::getNPCName() 
{
    switch (npctype)
    {
        case ALEX:
            return "Alex";
            break;
        case ABIGAIL:
            return "Abigail";
            break;
        case CAROLINE:
            return "Caroline";
            break;
        case LEWIS:
            return "Lewis";
            break;
    }

}

std::string NPC::getNPCLikability() 
{
    if (npclove < 20) 
    {
        return "stranger";
    }
    else if(npclove < 60) 
    {
        return "friend";
    }
    else 
    {
        return "close friend";
    }
}
