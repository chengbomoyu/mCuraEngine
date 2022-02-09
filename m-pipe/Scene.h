//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#ifndef SCENE_H
#define SCENE_H

#include "ExtruderTrain.h" //To store the extruders in the scene.
#include "MeshGroup.h" //To store the mesh groups in the scene.
#include "settings/Settings.h" //To store the global settings.

namespace cura
{

/*
 * Represents a scene that should be sliced.
 */
class Scene
{
public:
    /*!
     * \brief 场景的全局设定.
     */
    Settings settings;

    /*!
     * \brief Which extruder to evaluate each setting on, if different from the
     * normal extruder of the object it's evaluated for.
     */
    std::unordered_map<std::string, ExtruderTrain*> limit_to_extruder;

    /*!
     * \brief 场景里的网格.
     */
    std::vector<MeshGroup> mesh_groups;

    /*!
     * \brief 场景里的挤出机.
     */
    std::vector<ExtruderTrain> extruders;

    /*!
     * \brief 正在切片过程的网格。
     */
    std::vector<MeshGroup>::iterator current_mesh_group;

    /*!
     * \brief 创建一个空的场景.
     */
    Scene(const size_t num_mesh_groups);

    /*!
     * \brief 打印提示所有的输入命令.
    */
    const std::string getAllSettingsString() const;

    /*!
     * \brief 生成打印指令到网格组。
     * \param mesh_group 准备切片的网格组
     */
    void processMeshGroup(MeshGroup& mesh_group);

private:
    Scene(const Scene&) = delete; //禁止复制
    Scene& operator =(const Scene&) = delete; //禁止引用
};

} //namespace cura

#endif //SCENE_H