//Copyright (C) 2020 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#ifndef MESH_GROUP_H
#define MESH_GROUP_H

#include "mesh.h"
#include "utils/NoCopy.h"

namespace cura
{

class FMatrix4x3;

/*!
 * A MeshGroup is a collection with 1 or more 3D meshes.
 * 
 * One MeshGroup is a whole which is printed at once.
 * Generally there is one single MeshGroup, though when using one-at-a-time printing, multiple MeshGroups are processed consecutively.
 */
class MeshGroup : public NoCopy
{
public:
    std::vector<Mesh> meshes;
    Settings settings;

    Point3 min() const; //! 边界框的最小角
    Point3 max() const; //! 边界框的最大角

    void clear();

    void finalize();

    /*!
     * Scale the entire mesh group, with the bottom center as origin point.
     *
     * The mesh group is scaled around the bottom center of its bounding box. So
     * that's the center in the X and Y directions, but Z=0. This simulates the
     * shrinkage while sticking to the build plate.
     */
    void scaleFromBottom(const Ratio factor_xy, const Ratio factor_z);
};

/*!
 * \brief 从文件加载网格并将其存储在网格组中。.
 * 
 * \param meshgroup 用于存储STL的meshgroup
 * \param filename STL文件
 * \param transformation 所有顶点变换
 * \param object_parent_settings (可选) The parent settings object of the new mesh. 如果没有，选用meshgroup的默认
 * \return 是否被加载
 */
bool loadMeshIntoMeshGroup(MeshGroup* meshgroup, const char* filename, const FMatrix4x3& transformation, Settings& object_parent_settings);

} //namespace cura

#endif //MESH_GROUP_H
