import os

def generate_markdown_tree(start_path, prefix="", max_depth=1, current_depth=0):
    """生成仅包含一级子目录的目录树"""
    # 如果当前深度超过最大限制，停止递归
    if current_depth >= max_depth:
        return []
    
    # 获取目录下的所有项目，过滤隐藏文件
    items = [item for item in os.listdir(start_path) if not item.startswith('.')]
    # 按名称排序
    items.sort()
    # 最后一个项目的索引
    last_index = len(items) - 1
    
    tree = []
    for i, item in enumerate(items):
        item_path = os.path.join(start_path, item)
        is_last = (i == last_index)
        
        # 确定前缀符号
        if is_last:
            tree.append(f"{prefix}└── {item}/" if os.path.isdir(item_path) else f"{prefix}└── {item}")
            new_prefix = f"{prefix}    "
        else:
            tree.append(f"{prefix}├── {item}/" if os.path.isdir(item_path) else f"{prefix}├── {item}")
            new_prefix = f"{prefix}│   "
        
        # 只递归到一级目录（current_depth=0时处理一级目录，不再深入）
        if os.path.isdir(item_path) and current_depth < max_depth - 1:
            tree.extend(generate_markdown_tree(item_path, new_prefix, max_depth, current_depth + 1))
    
    return tree

if __name__ == "__main__":
    # 替换为你的项目路径
    project_path = "./"
    # 生成目录树（只显示一级子目录）
    tree_lines = generate_markdown_tree(project_path)
    # 开头添加根目录
    tree_lines.insert(0, ".")
    # 组合成字符串
    tree_str = "\n".join(tree_lines)
    
    # 保存到tree.md（用代码块包裹）
    with open("tree.md", "w", encoding="utf-8") as f:
        f.write("```\n")
        f.write(tree_str)
        f.write("\n```\n")
    
    print("一级子目录树已保存到 tree.md")
    