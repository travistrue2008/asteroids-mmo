//
//  CatalystEnumeration.h
//  
//
//  Created by Travis True on 1/5/12.
//  Copyright (c) 2012 TRUESoft Entertainment. All rights reserved.
//

#ifndef CATALYST_ENUMERATION_H
#define CATALYST_ENUMERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>


namespace CatalystEngine
{
	// COMMENT OUT TO REMOVE SHADER DEBUGGING
	// ===========================================
	#define _SHADER_DEBUG 1
	// ===========================================


	#define COLLECTION_SUCCESS					1		// collection operation was successful
	#define COLLECTION_INVALID					0		// undefined error occurred (failed to delete)
	#define COLLECTION_NULL_ELEMENT				-1		// element to be added to the collection is NULL
	#define COLLECTION_LIMIT_REACHED			-2		// cannot add element to the collection because the limit has been reached
	#define COLLECTION_INVALID_TYPE				-3		// collection item cannot be added to the collection because it's type doesn't match the collection's type
	#define COLLECTION_DUPLICATE_FOUND			-4		// collection item cannot be added because its name matches another item already in the collection
	#define COLLECTION_NO_PARENT				-5		// no parent collection

	#define CATALYST_MAX_PROPERTIES				1024
	#define CATALYST_MAX_TIMERS					32
	#define CATALYST_MAX_SOUNDS					32
	#define CATALYST_MAX_SOURCES				64
	#define CATALYST_MAX_TRIGGERS				128
	#define CATALYST_MAX_CAMERAS				32
	#define CATALYST_MAX_SPLINES				128
	#define CATALYST_MAX_POINTLIGHTS			32
	#define CATALYST_MAX_SPOTLIGHTS				32
	#define CATALYST_MAX_STATIC_MODELS			128
	#define CATALYST_MAX_DYNAMIC_MODELS			64
	#define CATALYST_MAX_OBJECTS				512
	#define CATALYST_MAX_TERRAIN				8
	#define CATALYST_MAX_WATER					4
	#define CATALYST_MAX_PARTICLE_SYSTEMS		32
	#define CATALYST_MAX_STARGRIDS				16
	#define CATALYST_MAX_ELEMENTS				1024
	#define CATALYST_MAX_UBER_SHADERS			32

	#define CATALYST_MAX_ENABLED_POINTLIGHTS	2
	#define CATALYST_MAX_ENABLED_SPOTLIGHTS		2

	#define UBER_LINEAR_FOG						1		// turned on in the scene
	#define UBER_LIGHTING						2		// turned on in the scene
	#define UBER_SPECULAR_LIGHTING				4		// turned on in the scene
	#define UBER_GLOBAL_LIGHT					8		// turned on in the scene
	#define UBER_POINT_LIGHT					16		// turned on in the scene
	#define UBER_SPOT_LIGHT						32		// turned on in the scene
	#define UBER_TEXTURE_MAPPING				64		// turned on in the model
	#define UBER_AMBIENT_MAPPING				128		// turned on in the model
	#define UBER_DIFFUSE_MAPPING				256		// turned on in the model
	#define UBER_SPECULAR_MAPPING				512		// turned on in the model
	#define UBER_BUMP_MAPPING					1024	// turned on in the model
	#define UBER_NORMAL_MAPPING					2048	// turned on in the model
	#define UBER_ENVIRONMENT_MAPPING			4096	// turned on in the model

	#define GL_VERTEX_ATTRIB0					0
	#define GL_VERTEX_ATTRIB1					1
	#define GL_VERTEX_ATTRIB2					2
	#define GL_VERTEX_ATTRIB3					3
	#define GL_VERTEX_ATTRIB4					4
	#define GL_VERTEX_ATTRIB5					5
	#define GL_VERTEX_ATTRIB6					6
	#define GL_VERTEX_ATTRIB7					7

	#define NUM_CUBE_VERTS						8
	#define NUM_CUBE_INDICES					(8*3)
	#define NUM_SPHERE_VERTS					162
	#define NUM_SPHERE_INDICES					320*3
	#define NUM_CAMERA_VERTS					(9*2*2)+8
	#define NUM_CAMERA_INDICES					(16*4)+(16*4)+(16*2)+24
	#define NUM_POINTLIGHT_VERTS				8+1+8
	#define NUM_POINTLIGHT_INDICES				64
	#define NUM_SPOTLIGHT_VERTS					8+1
	#define NUM_SPOTLIGHT_INDICES				32
	#define NUM_SOURCE_VERTS					24+2
	#define NUM_SOURCE_INDICES					(16*3)+(16*2)+(16*2)

	#define PARTICLE_TEXTURE_SIZE				32
	#define NUM_SPLINE_VERTICES					20

	#define MAX_MIPMAP_LEVELS					8
	#define MAX_TEXTURE_SIZE					1024


	enum SceneRenderFlags
	{
		SCENE_RENDER_NORMALS=1,
		SCENE_RENDER_HELPERS=2,
		SCENE_RENDER_BOUNDING_VOLUMES=4,
		SCENE_RENDER_BONES=8
	};


	enum EntryTypes
	{
		ACTION_NONE=0,
		ACTION_TEXT,
		ACTION_BOOL,
		ACTION_INT,
		ACTION_FLOAT,
		ACTION_CHOICE
	};


	enum TransitionState
	{
		TRANSITION_NONE=0,
		TRANSITION_OUT,
		TRANSITION_IN
	};


	enum IntervalMode
	{
		INTERVAL_MODE_NORMAL=0,
		INTERVAL_MODE_REVERSE,
		INTERVAL_MODE_LOOP
	};


	enum IntervalType
	{
		INTERVAL_TYPE_LINEAR=0,
		INTERVAL_TYPE_QUADRATIC_IN,
		INTERVAL_TYPE_CUBIC_IN,
		INTERVAL_TYPE_CUBIC_OUT,
		INTERVAL_TYPE_CUBIC_INOUT,
		INTERVAL_TYPE_CUBIC_OUTIN,
		INTERVAL_TYPE_CUBIC_BACKIN,
		INTERVAL_TYPE_CUBIC_OUTBACK,
		INTERVAL_TYPE_QUARTIC_IN,
		INTERVAL_TYPE_QUARTIC_OUT,
		INTERVAL_TYPE_QUARTIC_OUTIN,
		INTERVAL_TYPE_QUARTIC_BACKIN,
		INTERVAL_TYPE_QUARTIC_OUTBACK,
		INTERVAL_TYPE_QUINTIC_IN,
		INTERVAL_TYPE_QUINTIC_OUT,
		INTERVAL_TYPE_QUINTIC_INOUT,
		INTERVAL_TYPE_ELASTIC_IN,
		INTERVAL_TYPE_ELASTIC_OUT
	};


	enum IntervalState
	{
		INTERVAL_STATE_STOP,
		INTERVAL_STATE_START,
		INTERVAL_STATE_PAUSE
	};


	enum WidgetTransitionState
	{
		WIDGET_TRANSITION_NONE=0,
		WIDGET_TRANSITION_HIDING,
		WIDGET_TRANSITION_SHOWING
	};


	enum SpriteTypes
	{
		SPRITE_2D=0,
		SPRITE_BILLBOARD
	};


	enum BoundingBoxPlanes
	{
		BBOX_PLANE_TOP=0,
		BBOX_PLANE_BOTTOM,
		BBOX_PLANE_LEFT,
		BBOX_PLANE_RIGHT,
		BBOX_PLANE_NEAR,
		BBOX_PLANE_FAR
	};


	enum FBOTypes
	{
		FBO_TYPE_COLOR=0,	// FBO with color attachement only
		FBO_TYPE_DEPTH,		// FBO with depth attachement only
		FBO_TYPE_FULL		// FBO with color and depth attachements
	};


	enum ScreenEffects
	{
		RENDER_TARGET_NONE=0,		// NoEffect():			no post-processing by default
		RENDER_TARGET_BLUR,			// SetSimpleBlur():		blur the render target
		RENDER_TARGET_GLOW,			// SetGlow():			2-pass render that additively blends emissive materials and glow textures
		RENDER_TARGET_BLOOM,		// SetBloom():			apply bloom the entire render target
		RENDER_TARGET_DESATURATE,	// SetDesaturate():		decolorizes the render target to black-and-white
		RENDER_TARGET_INVERT,		// SetInvertColor():	inverts the color for every pixel
		RENDER_TARGET_INTERLACE,	// SetInterlaced():		adds interlaced lines similar to older CRT consoles
		RENDER_TARGET_CUSTOM		// SetCustomShader():	automatically set with SetCustomShader()
	};


	enum ProjectionModes
	{
		PROJECTION_MODE_PERSPECTIVE=0,
		PROJECTION_MODE_ORTHOGONAL=1
	};


	enum FrustumPlanes
	{
		FRUSTUM_PLANE_TOP		= 0,
		FRUSTUM_PLANE_BOTTOM	= 1,
		FRUSTUM_PLANE_LEFT		= 2,
		FRUSTUM_PLANE_RIGHT		= 3,
		FRUSTUM_PLANE_NEAR		= 4,
		FRUSTUM_PLANE_FAR		= 5
	};


	enum FrustumVisiblity
	{
		FRUSTUM_VISIBILITY_NONE=0,
		FRUSTUM_VISIBILITY_PART=1,
		FRUSTUM_VISIBILITY_FULL=2
	};


	enum StarNodeState
	{
		STAR_NODE_UNLOCKED=0,
		STAR_NODE_TEMPORARY,
		STAR_NODE_LOCKED
	};


	enum SplineType
	{
		SPLINE_TYPE_2D=0,
		SPLINE_TYPE_3D
	};


	enum AnimatorTypes
	{
		ANIMATOR_NONE=0,
		ANIMATOR_MOVEMENT,
		ANIMATOR_ROTATION,
		ANIMATOR_SCALE,
		ANIMATOR_SPLINE,
		ANIMATOR_PIVOT
	};


	enum GamePropertyDataTypes
	{
		GAME_PROPERTY_INTEGER=0,
		GAME_PROPERTY_DECIMAL,
		GAME_PROPERTY_STRING,
		GAME_PROPERTY_VECTOR2,
		GAME_PROPERTY_VECTOR3,
		GAME_PROPERTY_VECTOR4,
		GAME_PROPERTY_MATRIX
	};


	enum ModelBoundingType
	{
		MODEL_BOUNDING_NONE=0,
		MODEL_BOUNDING_SPHERE,
		MODEL_BOUNDING_BOX
	};


	enum MD5PlaybackState
	{
		MD5_PLAYBACK_STOP=0,
		MD5_PLAYBACK_PLAY,
		MD5_PLAYBACK_PAUSE
	};


	enum MD5AnimationChannelMode
	{
		MD5_ANIMATION_CHANNEL0=0,
		MD5_ANIMATION_CHANNEL1
	};


	enum ParticleProjection
	{
		PARTICLE_PROJECTION_2D=0,
		PARTICLE_PROJECTION_3D
	};


	enum TimerModes
	{
		TIMER_STOPWATCH=0,
		TIMER_COUNTDOWN,
		TIMER_CYCLE
	};


	enum TimerStates
	{
		TIMER_START=0,
		TIMER_STOP,
		TIMER_PAUSE
	};
}

#endif // CATALYST_ENUMERATION_H
