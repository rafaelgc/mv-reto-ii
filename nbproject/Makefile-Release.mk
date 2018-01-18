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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/ba21678e/Pathfinding.o \
	${OBJECTDIR}/_ext/4c082089/Task.o \
	${OBJECTDIR}/_ext/4c082089/TaskPool.o \
	${OBJECTDIR}/_ext/4c082089/Worker.o \
	${OBJECTDIR}/_ext/c1b4e769/AnimatableContainer.o \
	${OBJECTDIR}/_ext/c1b4e769/Application.o \
	${OBJECTDIR}/_ext/c1b4e769/Clock.o \
	${OBJECTDIR}/_ext/c1b4e769/Layer.o \
	${OBJECTDIR}/_ext/c1b4e769/Log.o \
	${OBJECTDIR}/_ext/c1b4e769/RenderManager.o \
	${OBJECTDIR}/_ext/c1b4e769/ResourceLoader.o \
	${OBJECTDIR}/_ext/c1b4e769/Scene.o \
	${OBJECTDIR}/_ext/c1b4e769/SceneManager.o \
	${OBJECTDIR}/_ext/c1b4e769/ScreenDimensions.o \
	${OBJECTDIR}/_ext/b96e59bc/Entity.o \
	${OBJECTDIR}/_ext/b96e59bc/System.o \
	${OBJECTDIR}/_ext/342aa695/pugixml.o \
	${OBJECTDIR}/_ext/c1b94db7/Dijkstra.o \
	${OBJECTDIR}/_ext/c1b94db7/Mesh.o \
	${OBJECTDIR}/_ext/c1b94db7/Node.o \
	${OBJECTDIR}/_ext/c1b94db7/NodeDistance.o \
	${OBJECTDIR}/_ext/c1b94db7/NodeLink.o \
	${OBJECTDIR}/_ext/7f27223d/AABBDetection.o \
	${OBJECTDIR}/_ext/7f27223d/CircleCollisionDetection.o \
	${OBJECTDIR}/_ext/c1bc7cf7/Text.o \
	${OBJECTDIR}/_ext/e895b6da/TileSprite.o \
	${OBJECTDIR}/_ext/24ae7354/Layer.o \
	${OBJECTDIR}/_ext/24ae7354/Map.o \
	${OBJECTDIR}/_ext/24ae7354/Object.o \
	${OBJECTDIR}/_ext/24ae7354/ObjectLayer.o \
	${OBJECTDIR}/_ext/24ae7354/Tile.o \
	${OBJECTDIR}/_ext/24ae7354/TiledLoader.o \
	${OBJECTDIR}/_ext/e895b6da/Tileset.o \
	${OBJECTDIR}/Actor.o \
	${OBJECTDIR}/App.o \
	${OBJECTDIR}/BloodDrop.o \
	${OBJECTDIR}/Enemy.o \
	${OBJECTDIR}/GameScene.o \
	${OBJECTDIR}/GridMesh.o \
	${OBJECTDIR}/GridNode.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/ParticleManager.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/Spawn.o \
	${OBJECTDIR}/Vector2f.o \
	${OBJECTDIR}/Vector3f.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-i

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-i: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mv-reto-i ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/ba21678e/Pathfinding.o: ../ESE/include/ESE/AI/Pathfinding.tpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ba21678e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ba21678e/Pathfinding.o ../ESE/include/ESE/AI/Pathfinding.tpp

${OBJECTDIR}/_ext/4c082089/Task.o: ../ESE/src/ESE/Concurrency/Task.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4c082089
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4c082089/Task.o ../ESE/src/ESE/Concurrency/Task.cpp

${OBJECTDIR}/_ext/4c082089/TaskPool.o: ../ESE/src/ESE/Concurrency/TaskPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4c082089
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4c082089/TaskPool.o ../ESE/src/ESE/Concurrency/TaskPool.cpp

${OBJECTDIR}/_ext/4c082089/Worker.o: ../ESE/src/ESE/Concurrency/Worker.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4c082089
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4c082089/Worker.o ../ESE/src/ESE/Concurrency/Worker.cpp

${OBJECTDIR}/_ext/c1b4e769/AnimatableContainer.o: ../ESE/src/ESE/Core/AnimatableContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/AnimatableContainer.o ../ESE/src/ESE/Core/AnimatableContainer.cpp

${OBJECTDIR}/_ext/c1b4e769/Application.o: ../ESE/src/ESE/Core/Application.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/Application.o ../ESE/src/ESE/Core/Application.cpp

${OBJECTDIR}/_ext/c1b4e769/Clock.o: ../ESE/src/ESE/Core/Clock.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/Clock.o ../ESE/src/ESE/Core/Clock.cpp

${OBJECTDIR}/_ext/c1b4e769/Layer.o: ../ESE/src/ESE/Core/Layer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/Layer.o ../ESE/src/ESE/Core/Layer.cpp

${OBJECTDIR}/_ext/c1b4e769/Log.o: ../ESE/src/ESE/Core/Log.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/Log.o ../ESE/src/ESE/Core/Log.cpp

${OBJECTDIR}/_ext/c1b4e769/RenderManager.o: ../ESE/src/ESE/Core/RenderManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/RenderManager.o ../ESE/src/ESE/Core/RenderManager.cpp

${OBJECTDIR}/_ext/c1b4e769/ResourceLoader.o: ../ESE/src/ESE/Core/ResourceLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/ResourceLoader.o ../ESE/src/ESE/Core/ResourceLoader.cpp

${OBJECTDIR}/_ext/c1b4e769/Scene.o: ../ESE/src/ESE/Core/Scene.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/Scene.o ../ESE/src/ESE/Core/Scene.cpp

${OBJECTDIR}/_ext/c1b4e769/SceneManager.o: ../ESE/src/ESE/Core/SceneManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/SceneManager.o ../ESE/src/ESE/Core/SceneManager.cpp

${OBJECTDIR}/_ext/c1b4e769/ScreenDimensions.o: ../ESE/src/ESE/Core/ScreenDimensions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b4e769
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b4e769/ScreenDimensions.o ../ESE/src/ESE/Core/ScreenDimensions.cpp

${OBJECTDIR}/_ext/b96e59bc/Entity.o: ../ESE/src/ESE/EntitySystem/Entity.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b96e59bc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b96e59bc/Entity.o ../ESE/src/ESE/EntitySystem/Entity.cpp

${OBJECTDIR}/_ext/b96e59bc/System.o: ../ESE/src/ESE/EntitySystem/System.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b96e59bc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b96e59bc/System.o ../ESE/src/ESE/EntitySystem/System.cpp

${OBJECTDIR}/_ext/342aa695/pugixml.o: ../ESE/src/ESE/External/pugixml.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/342aa695
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/342aa695/pugixml.o ../ESE/src/ESE/External/pugixml.cpp

${OBJECTDIR}/_ext/c1b94db7/Dijkstra.o: ../ESE/src/ESE/Mesh/Dijkstra.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b94db7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b94db7/Dijkstra.o ../ESE/src/ESE/Mesh/Dijkstra.cpp

${OBJECTDIR}/_ext/c1b94db7/Mesh.o: ../ESE/src/ESE/Mesh/Mesh.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b94db7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b94db7/Mesh.o ../ESE/src/ESE/Mesh/Mesh.cpp

${OBJECTDIR}/_ext/c1b94db7/Node.o: ../ESE/src/ESE/Mesh/Node.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b94db7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b94db7/Node.o ../ESE/src/ESE/Mesh/Node.cpp

${OBJECTDIR}/_ext/c1b94db7/NodeDistance.o: ../ESE/src/ESE/Mesh/NodeDistance.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b94db7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b94db7/NodeDistance.o ../ESE/src/ESE/Mesh/NodeDistance.cpp

${OBJECTDIR}/_ext/c1b94db7/NodeLink.o: ../ESE/src/ESE/Mesh/NodeLink.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1b94db7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1b94db7/NodeLink.o ../ESE/src/ESE/Mesh/NodeLink.cpp

${OBJECTDIR}/_ext/7f27223d/AABBDetection.o: ../ESE/src/ESE/Physics/AABBDetection.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f27223d
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f27223d/AABBDetection.o ../ESE/src/ESE/Physics/AABBDetection.cpp

${OBJECTDIR}/_ext/7f27223d/CircleCollisionDetection.o: ../ESE/src/ESE/Physics/CircleCollisionDetection.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f27223d
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f27223d/CircleCollisionDetection.o ../ESE/src/ESE/Physics/CircleCollisionDetection.cpp

${OBJECTDIR}/_ext/c1bc7cf7/Text.o: ../ESE/src/ESE/Text/Text.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c1bc7cf7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c1bc7cf7/Text.o ../ESE/src/ESE/Text/Text.cpp

${OBJECTDIR}/_ext/e895b6da/TileSprite.o: ../ESE/src/ESE/TileEngine/TileSprite.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e895b6da
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e895b6da/TileSprite.o ../ESE/src/ESE/TileEngine/TileSprite.cpp

${OBJECTDIR}/_ext/24ae7354/Layer.o: ../ESE/src/ESE/TileEngine/TiledLoader/Layer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/Layer.o ../ESE/src/ESE/TileEngine/TiledLoader/Layer.cpp

${OBJECTDIR}/_ext/24ae7354/Map.o: ../ESE/src/ESE/TileEngine/TiledLoader/Map.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/Map.o ../ESE/src/ESE/TileEngine/TiledLoader/Map.cpp

${OBJECTDIR}/_ext/24ae7354/Object.o: ../ESE/src/ESE/TileEngine/TiledLoader/Object.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/Object.o ../ESE/src/ESE/TileEngine/TiledLoader/Object.cpp

${OBJECTDIR}/_ext/24ae7354/ObjectLayer.o: ../ESE/src/ESE/TileEngine/TiledLoader/ObjectLayer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/ObjectLayer.o ../ESE/src/ESE/TileEngine/TiledLoader/ObjectLayer.cpp

${OBJECTDIR}/_ext/24ae7354/Tile.o: ../ESE/src/ESE/TileEngine/TiledLoader/Tile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/Tile.o ../ESE/src/ESE/TileEngine/TiledLoader/Tile.cpp

${OBJECTDIR}/_ext/24ae7354/TiledLoader.o: ../ESE/src/ESE/TileEngine/TiledLoader/TiledLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/24ae7354
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24ae7354/TiledLoader.o ../ESE/src/ESE/TileEngine/TiledLoader/TiledLoader.cpp

${OBJECTDIR}/_ext/e895b6da/Tileset.o: ../ESE/src/ESE/TileEngine/Tileset.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e895b6da
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e895b6da/Tileset.o ../ESE/src/ESE/TileEngine/Tileset.cpp

${OBJECTDIR}/Actor.o: Actor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Actor.o Actor.cpp

${OBJECTDIR}/App.o: App.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/App.o App.cpp

${OBJECTDIR}/BloodDrop.o: BloodDrop.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BloodDrop.o BloodDrop.cpp

${OBJECTDIR}/Enemy.o: Enemy.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemy.o Enemy.cpp

${OBJECTDIR}/GameScene.o: GameScene.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GameScene.o GameScene.cpp

${OBJECTDIR}/GridMesh.o: GridMesh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GridMesh.o GridMesh.cpp

${OBJECTDIR}/GridNode.o: GridNode.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GridNode.o GridNode.cpp

${OBJECTDIR}/Particle.o: Particle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/ParticleManager.o: ParticleManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ParticleManager.o ParticleManager.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/Spawn.o: Spawn.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Spawn.o Spawn.cpp

${OBJECTDIR}/Vector2f.o: Vector2f.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vector2f.o Vector2f.cpp

${OBJECTDIR}/Vector3f.o: Vector3f.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vector3f.o Vector3f.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
