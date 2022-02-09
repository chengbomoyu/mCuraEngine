//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#ifndef SLICE_H
#define SLICE_H

#include "Scene.h" //To store the scene to slice.

namespace cura
{

class Slice
{
public:
    /*!
     * \brief 创建一个需要切片的实例
     * \param num_mesh_groups 一共有多少网格需要切片
     */
    Slice(const size_t num_mesh_groups);

    Scene scene;//必须切分的场景

    /*!
     * \brief 对场景进行切片，并生成G代码
     */
    void compute();

    /*!
     * \brief 清空切片实例，为下一次做准备，因为不允许修改已经切片的实例，因此这是唯一可以恢复初始切片的方法。
     */
    void reset();

private:
    Slice(const Slice& other) = delete; //禁止复制
    Slice& operator =(const Slice& other) = delete;//禁止引用
};

} //namespace cura

#endif //SLICE_H