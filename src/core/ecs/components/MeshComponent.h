//
// Created by Dimme on 10/03/2021.
//

#ifndef I3D_MESHCOMPONENT_H
#define I3D_MESHCOMPONENT_H

#include <vector>
#include "../Component.h"
#include "../../shared/engine_graphic.h"


class MeshComponent : public Component {
public:
    explicit MeshComponent();

    void render();

    void setMesh(const Mesh& meshIn);

    void setScale(float scale);

    void reset();

    ~MeshComponent();

private:
    float scale = 1;
    bool isStartTick = true;

    // Data
    Mesh mesh;

    void tick() override;
};


#endif //I3D_MESHCOMPONENT_H
