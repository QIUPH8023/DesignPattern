#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>

// 抽象基类，定义通用操作接口
class Component {
public:
    virtual ~Component() = default;

    // 获取节点名称
    virtual std::string getName() const = 0;

    // 显示节点信息（调试用）
    virtual void display() const = 0;

    // 添加子节点（仅容器节点实现）
    virtual void add(std::shared_ptr<Component> component) {}

    // 移除子节点（仅容器节点实现）
    virtual void remove(std::shared_ptr<Component> component) {}

    // 获取子节点（仅容器节点实现）
    virtual std::shared_ptr<Component> getChild(int index) const { return nullptr; }
};

#endif // COMPONENT_H
