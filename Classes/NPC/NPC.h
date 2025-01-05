/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     NPC.h
 * File Function: NPC类的定义
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#ifndef _NPC_H_
#define _NPC_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "../NPC/NPCComponent.h"

class NPC : public cocos2d::Sprite, public NPCComponent
{
public:

	// 初始化
	bool init(const std::string& spriteFile, const NPCType& _npctype);

	// 创建NPC
	static NPC* create(const std::string& spriteFile, const NPCType& _npctype);

	std::string getDialog();

	// 推进到下一个对话
	void advanceDialog();

	// 跳转到指定的对话
	void jumpToDialog(int index);

	// 修改NPC好感度
	void setNPCLove(int amount);

	// 获取NPC好感度等级
	std::string getNPCLikability();

	// 获取NPC头像
	std::string getHead();
	
	// 获取NPC名称
	NPCType& getNPCType();

	// 获取NPC姓名
	std::string getNPCName();
private:

	NPC();    // 构造函数
	~NPC();   // 析构函数

	int npclove = 0;                  // NPC 的好感度
	NPCType npctype;                  // NPC 的名称
	std::vector<std::string> dialog;  // NPC 的对话内容
	int dialogIndex = 0;              // 当前对话的索引

};

#endif // _NPC_H_
