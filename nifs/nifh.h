#define private public
#define protected public
#include <niflib.h>
#include <MatTexCollection.h>
#include <NIF_IO.h>
#include <obj\NiObject.h>
#include <obj\NiNode.h>
#include <obj\BSFadeNode.h>
#include <Ref.h>
#include <obj\NiObject.h>
#include <gen\Header.h>
#include <obj\NiTriShape.h>
#include <obj\NiProperty.h>
#include <obj\NiTriShapeData.h>
#include <obj\BSLightingShaderProperty.h>
#include <obj\BSShaderTextureSet.h>
#include <obj\BSShaderProperty.h>
#include <obj\NiParticleBomb.h>
#include <obj\NiParticleColorModifier.h>
#include <obj\NiParticleGrowFade.h>
#include <obj\NiParticleMeshes.h>
#include <obj\NiParticleMeshesData.h>
#include <obj\NiParticleMeshModifier.h>
#include <obj\NiParticleModifier.h>
#include <obj\NiParticleRotation.h>
#include <obj\NiParticles.h>
#include <obj\NiParticlesData.h>
#include <obj\NiParticleSystem.h>
#include <obj\NiParticleSystemController.h>
#include <obj\NiMaterialProperty.h>
#include <obj\BSDismemberSkinInstance.h>
#include <obj\NiSkinData.h>
#include <obj\NiSkinInstance.h>
#include <gen\BodyPartList.h>
#include <obj\NiGeometry.h>
#include <obj\NiGeometryData.h>
#include <obj\NiSkinningLODController.h>
#include <obj\NiSkinningMeshModifier.h>
#include <obj\BSDismemberSkinInstance.h>
#include <obj\NiSkinPartition.h>
#include <obj\NiTriStrips.h>
#include <obj\NiTriStripsData.h>
#include <obj\NiSkinInstance.h>
#include <obj\BSLightingShaderProperty.h>
#include <obj\BSShaderProperty.h>
#include <obj\BSShaderLightingProperty.h>
#include <obj\BSShaderTextureSet.h>
#include <obj\NiShadeProperty.h>
#include <gen\enums.h>
#include <obj\NiWireframeProperty.h>
#include <obj\NiAlphaProperty.h>
#include <obj\NiStencilProperty.h>
#include <obj\NiShadeProperty.h>
#include <obj\NiVertexColorProperty.h>
#include <obj\NiDitherProperty.h>
#include <obj\NiSpecularProperty.h>
#include <obj\NiTextureProperty.h>
#include <obj\NiImage.h>
#include <nif_math.h>

#include "obj/NiWireframeProperty.h"
#include "obj/NiAlphaProperty.h"
#include "obj/NiStencilProperty.h"
#include "obj/NiShadeProperty.h"
#include "obj/NiVertexColorProperty.h"
#include "obj/NiDitherProperty.h"
#include "obj/NiSpecularProperty.h"
#include "obj/NiTextureProperty.h"
#include "obj/BSLightingShaderProperty.h"
#include "obj/BSShaderNoLightingProperty.h"
#include "obj/BSShaderPPLightingProperty.h"
#include "obj/BSShaderTextureSet.h"
#include "obj/SkyShaderProperty.h"
#include "obj/TileShaderProperty.h"
#include "obj/TallGrassShaderProperty.h"
#include "obj/Lighting30ShaderProperty.h"
#include <obj\TallGrassShaderProperty.h>
#include <obj\Lighting30ShaderProperty.h>
#include <obj\BSShaderNoLightingProperty.h>
#include <obj\BSShaderPPLightingProperty.h>
#include <obj\BSShaderTextureSet.h>
#include <obj\BSLightingShaderProperty.h>
#include <obj\NIAVObject.h>
#include <obj\BSEffectShaderProperty.h>
#include <obj\BSEffectShaderPropertyColorController.h>
#include <obj\BSEffectShaderPropertyFloatController.h>
#include <obj\NiFloatData.h>
#include <obj\NiFloatExtraData.h>
#include <obj\NiFloatExtraDataController.h>
#include <obj\NiFloatInterpController.h>
#include <obj\NiFloatInterpolator.h>
#include <obj\NiFloatsExtraData.h>
#include <obj\NiObjectNET.h>
#include <nif_basic_types.h>
#include <assimp\Importer.hpp>
#include <assimp\Exporter.hpp>
#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp\config.h>
#include <assimp\material.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>