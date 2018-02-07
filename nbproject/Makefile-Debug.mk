#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/fc9f393e/Task.o \
	${OBJECTDIR}/_ext/fc9f393e/TaskPool.o \
	${OBJECTDIR}/_ext/fc9f393e/Worker.o \
	${OBJECTDIR}/_ext/d0c70054/AnimatableContainer.o \
	${OBJECTDIR}/_ext/d0c70054/Application.o \
	${OBJECTDIR}/_ext/d0c70054/Argument.o \
	${OBJECTDIR}/_ext/d0c70054/Arguments.o \
	${OBJECTDIR}/_ext/d0c70054/Clock.o \
	${OBJECTDIR}/_ext/d0c70054/Layer.o \
	${OBJECTDIR}/_ext/d0c70054/Log.o \
	${OBJECTDIR}/_ext/d0c70054/RenderManager.o \
	${OBJECTDIR}/_ext/d0c70054/ResourceLoader.o \
	${OBJECTDIR}/_ext/d0c70054/Scene.o \
	${OBJECTDIR}/_ext/d0c70054/SceneManager.o \
	${OBJECTDIR}/_ext/d0c70054/ScreenDimensions.o \
	${OBJECTDIR}/_ext/1bba57a7/Entity.o \
	${OBJECTDIR}/_ext/1bba57a7/System.o \
	${OBJECTDIR}/_ext/c9605200/pugixml.o \
	${OBJECTDIR}/_ext/d0cb57bd/Vector2f.o \
	${OBJECTDIR}/_ext/d0cb57bd/Vector3f.o \
	${OBJECTDIR}/_ext/d0cb66a2/Mesh.o \
	${OBJECTDIR}/_ext/d0cb66a2/Node.o \
	${OBJECTDIR}/_ext/d0cb66a2/NodeDistance.o \
	${OBJECTDIR}/_ext/4a28dd72/AABBDetection.o \
	${OBJECTDIR}/_ext/4a28dd72/CircleCollisionDetection.o \
	${OBJECTDIR}/_ext/d0ce95e2/Text.o \
	${OBJECTDIR}/_ext/17d2477f/Layer.o \
	${OBJECTDIR}/_ext/17d2477f/Map.o \
	${OBJECTDIR}/_ext/17d2477f/Object.o \
	${OBJECTDIR}/_ext/17d2477f/ObjectLayer.o \
	${OBJECTDIR}/_ext/17d2477f/Tile.o \
	${OBJECTDIR}/_ext/17d2477f/TiledLoader.o \
	${OBJECTDIR}/_ext/70e3385/Tileset.o \
	${OBJECTDIR}/Actor.o \
	${OBJECTDIR}/App.o \
	${OBJECTDIR}/Drop.o \
	${OBJECTDIR}/GameScene.o \
	${OBJECTDIR}/GridMesh.o \
	${OBJECTDIR}/GridNode.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/ParticleManager.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pthread
CXXFLAGS=-pthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lsfml-graphics -lsfml-window -lsfml-system -lGL -lsfml-audio

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-ii

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-ii: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-ii ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/fc9f393e/Task.o: ../ZeltaLib/src/Zelta/Concurrency/Task.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/fc9f393e
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fc9f393e/Task.o ../ZeltaLib/src/Zelta/Concurrency/Task.cpp

${OBJECTDIR}/_ext/fc9f393e/TaskPool.o: ../ZeltaLib/src/Zelta/Concurrency/TaskPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/fc9f393e
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fc9f393e/TaskPool.o ../ZeltaLib/src/Zelta/Concurrency/TaskPool.cpp

${OBJECTDIR}/_ext/fc9f393e/Worker.o: ../ZeltaLib/src/Zelta/Concurrency/Worker.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/fc9f393e
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fc9f393e/Worker.o ../ZeltaLib/src/Zelta/Concurrency/Worker.cpp

${OBJECTDIR}/_ext/d0c70054/AnimatableContainer.o: ../ZeltaLib/src/Zelta/Core/AnimatableContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/AnimatableContainer.o ../ZeltaLib/src/Zelta/Core/AnimatableContainer.cpp

${OBJECTDIR}/_ext/d0c70054/Application.o: ../ZeltaLib/src/Zelta/Core/Application.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Application.o ../ZeltaLib/src/Zelta/Core/Application.cpp

${OBJECTDIR}/_ext/d0c70054/Argument.o: ../ZeltaLib/src/Zelta/Core/Argument.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Argument.o ../ZeltaLib/src/Zelta/Core/Argument.cpp

${OBJECTDIR}/_ext/d0c70054/Arguments.o: ../ZeltaLib/src/Zelta/Core/Arguments.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Arguments.o ../ZeltaLib/src/Zelta/Core/Arguments.cpp

${OBJECTDIR}/_ext/d0c70054/Clock.o: ../ZeltaLib/src/Zelta/Core/Clock.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Clock.o ../ZeltaLib/src/Zelta/Core/Clock.cpp

${OBJECTDIR}/_ext/d0c70054/Layer.o: ../ZeltaLib/src/Zelta/Core/Layer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Layer.o ../ZeltaLib/src/Zelta/Core/Layer.cpp

${OBJECTDIR}/_ext/d0c70054/Log.o: ../ZeltaLib/src/Zelta/Core/Log.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Log.o ../ZeltaLib/src/Zelta/Core/Log.cpp

${OBJECTDIR}/_ext/d0c70054/RenderManager.o: ../ZeltaLib/src/Zelta/Core/RenderManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/RenderManager.o ../ZeltaLib/src/Zelta/Core/RenderManager.cpp

${OBJECTDIR}/_ext/d0c70054/ResourceLoader.o: ../ZeltaLib/src/Zelta/Core/ResourceLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/ResourceLoader.o ../ZeltaLib/src/Zelta/Core/ResourceLoader.cpp

${OBJECTDIR}/_ext/d0c70054/Scene.o: ../ZeltaLib/src/Zelta/Core/Scene.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/Scene.o ../ZeltaLib/src/Zelta/Core/Scene.cpp

${OBJECTDIR}/_ext/d0c70054/SceneManager.o: ../ZeltaLib/src/Zelta/Core/SceneManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/SceneManager.o ../ZeltaLib/src/Zelta/Core/SceneManager.cpp

${OBJECTDIR}/_ext/d0c70054/ScreenDimensions.o: ../ZeltaLib/src/Zelta/Core/ScreenDimensions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0c70054
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0c70054/ScreenDimensions.o ../ZeltaLib/src/Zelta/Core/ScreenDimensions.cpp

${OBJECTDIR}/_ext/1bba57a7/Entity.o: ../ZeltaLib/src/Zelta/EntitySystem/Entity.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1bba57a7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1bba57a7/Entity.o ../ZeltaLib/src/Zelta/EntitySystem/Entity.cpp

${OBJECTDIR}/_ext/1bba57a7/System.o: ../ZeltaLib/src/Zelta/EntitySystem/System.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1bba57a7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1bba57a7/System.o ../ZeltaLib/src/Zelta/EntitySystem/System.cpp

${OBJECTDIR}/_ext/c9605200/pugixml.o: ../ZeltaLib/src/Zelta/External/pugixml.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c9605200
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c9605200/pugixml.o ../ZeltaLib/src/Zelta/External/pugixml.cpp

${OBJECTDIR}/_ext/d0cb57bd/Vector2f.o: ../ZeltaLib/src/Zelta/Math/Vector2f.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0cb57bd
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0cb57bd/Vector2f.o ../ZeltaLib/src/Zelta/Math/Vector2f.cpp

${OBJECTDIR}/_ext/d0cb57bd/Vector3f.o: ../ZeltaLib/src/Zelta/Math/Vector3f.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0cb57bd
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0cb57bd/Vector3f.o ../ZeltaLib/src/Zelta/Math/Vector3f.cpp

${OBJECTDIR}/_ext/d0cb66a2/Mesh.o: ../ZeltaLib/src/Zelta/Mesh/Mesh.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0cb66a2
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0cb66a2/Mesh.o ../ZeltaLib/src/Zelta/Mesh/Mesh.cpp

${OBJECTDIR}/_ext/d0cb66a2/Node.o: ../ZeltaLib/src/Zelta/Mesh/Node.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0cb66a2
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0cb66a2/Node.o ../ZeltaLib/src/Zelta/Mesh/Node.cpp

${OBJECTDIR}/_ext/d0cb66a2/NodeDistance.o: ../ZeltaLib/src/Zelta/Mesh/NodeDistance.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0cb66a2
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0cb66a2/NodeDistance.o ../ZeltaLib/src/Zelta/Mesh/NodeDistance.cpp

${OBJECTDIR}/_ext/4a28dd72/AABBDetection.o: ../ZeltaLib/src/Zelta/Physics/AABBDetection.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4a28dd72
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a28dd72/AABBDetection.o ../ZeltaLib/src/Zelta/Physics/AABBDetection.cpp

${OBJECTDIR}/_ext/4a28dd72/CircleCollisionDetection.o: ../ZeltaLib/src/Zelta/Physics/CircleCollisionDetection.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4a28dd72
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a28dd72/CircleCollisionDetection.o ../ZeltaLib/src/Zelta/Physics/CircleCollisionDetection.cpp

${OBJECTDIR}/_ext/d0ce95e2/Text.o: ../ZeltaLib/src/Zelta/Text/Text.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d0ce95e2
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d0ce95e2/Text.o ../ZeltaLib/src/Zelta/Text/Text.cpp

${OBJECTDIR}/_ext/17d2477f/Layer.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Layer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/Layer.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Layer.cpp

${OBJECTDIR}/_ext/17d2477f/Map.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Map.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/Map.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Map.cpp

${OBJECTDIR}/_ext/17d2477f/Object.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Object.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/Object.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Object.cpp

${OBJECTDIR}/_ext/17d2477f/ObjectLayer.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/ObjectLayer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/ObjectLayer.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/ObjectLayer.cpp

${OBJECTDIR}/_ext/17d2477f/Tile.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Tile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/Tile.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/Tile.cpp

${OBJECTDIR}/_ext/17d2477f/TiledLoader.o: ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/TiledLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/17d2477f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/17d2477f/TiledLoader.o ../ZeltaLib/src/Zelta/TileEngine/TiledLoader/TiledLoader.cpp

${OBJECTDIR}/_ext/70e3385/Tileset.o: ../ZeltaLib/src/Zelta/TileEngine/Tileset.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/70e3385
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/70e3385/Tileset.o ../ZeltaLib/src/Zelta/TileEngine/Tileset.cpp

${OBJECTDIR}/Actor.o: Actor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Actor.o Actor.cpp

${OBJECTDIR}/App.o: App.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/App.o App.cpp

${OBJECTDIR}/Drop.o: Drop.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Drop.o Drop.cpp

${OBJECTDIR}/GameScene.o: GameScene.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GameScene.o GameScene.cpp

${OBJECTDIR}/GridMesh.o: GridMesh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GridMesh.o GridMesh.cpp

${OBJECTDIR}/GridNode.o: GridNode.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GridNode.o GridNode.cpp

${OBJECTDIR}/Particle.o: Particle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/ParticleManager.o: ParticleManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ParticleManager.o ParticleManager.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../ZeltaLib/include/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
