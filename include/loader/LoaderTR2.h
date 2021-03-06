/*!
 * \file include/loader/LoaderTR2.h
 * \brief TR2 level file loader
 *
 * \author xythobuz
 */

#ifndef _LOADER_LOADER_TR2_H_
#define _LOADER_LOADER_TR2_H_

#include <array>
#include <cstdint>

#include "RoomData.h"
#include "RoomMesh.h"
#include "SkeletalModel.h"
#include "utils/binary.h"
#include "loader/Loader.h"

class LoaderTR2 : public Loader {
  public:
    virtual int load(std::string f);

  protected:
    virtual void loadPalette();
    virtual void loadTextures();
    virtual void loadRoomLights();
    virtual void loadRoomStaticMeshes(std::vector<StaticModel*>& staticModels);
    virtual void loadRoomDataEnd(int16_t& alternateRoom, unsigned int& roomFlags);
    virtual void loadRoomVertex(RoomVertexTR2& vert);
    virtual void loadRoomMesh(std::vector<IndexedRectangle>& rectangles,
                              std::vector<IndexedRectangle>& triangles,
                              uint16_t& numRectangles, uint16_t& numTriangles);
    virtual void loadRooms();
    virtual void loadFloorData();
    virtual void loadMeshes();
    virtual void loadMoveables();
    virtual void loadStaticMeshes();
    virtual void loadTextiles();
    virtual void loadSprites();
    virtual void loadCameras();
    virtual void loadSoundSources();
    virtual void loadBoxesOverlapsZones();
    virtual void loadAnimatedTextures();
    virtual void loadItems();
    virtual void loadCinematicFrames();
    virtual void loadDemoData();
    virtual void loadSoundMap();
    virtual void loadSoundDetails();
    virtual void loadSampleIndices();

    virtual void loadExternalSoundFile(std::string f);
    virtual int loadSoundFiles(BinaryReader& sfx, unsigned int count = 0);

    virtual int getPaletteIndex(uint16_t index);
    virtual void loadAngleSet(BoneFrame* bf, BinaryReader& frame, uint16_t numMeshes,
                              uint16_t startingMesh, uint32_t meshTree,
                              uint32_t numMeshTrees, std::vector<int32_t> meshTrees);
    virtual BoneFrame* loadFrame(BinaryReader& frame, uint16_t numMeshes,
                                 uint16_t startingMesh, uint32_t meshTree,
                                 uint32_t numMeshTrees, std::vector<int32_t> meshTrees);
};

#endif

