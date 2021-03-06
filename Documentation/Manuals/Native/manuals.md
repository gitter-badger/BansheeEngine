Manuals									{#manuals}
===============

# Quick start
[Getting started](@ref gettingStarted) - This is a short guide on how to create a fully functional Banshee application, aimed to get you up and running quickly, without going into too much detail.

# User manuals
A complete set of manuals covering all major functionality provided by Banshee, starting with basics and slowly guiding you through more advanced concepts. This should be the primary entry point for new users.
- [Startup and main loop](@ref startup)
- [Scene objects and components](@ref scenesAndComponents)
- **Resources**
 - [Basics and import](@ref resourceBasicsAndImport)
 - [Saving and loading](@ref resourceSavingAndLoading)
- **Utilities**
 - [Containers](@ref containers)
 - [Strings](@ref strings)
 - [Memory allocation](@ref memory)
 - [Smart pointers](@ref smartPointers) 
 - [Events](@ref events)
 - [File system](@ref fileSystem) 
 - [Math utilities](@ref mathUtilities)
 - [Logging messages](@ref logging)
 - [Measuring time](@ref time)
- **Graphics**
 - [Windows](@ref windows)
 - [Cameras](@ref cameras)
 - [Importing textures](@ref importingTextures)
 - [Importing meshes](@ref importingMeshes)
 - [Materials](@ref simpleMaterial)
 - [Rendering objects](@ref renderingObjects)
 - [Lighting](@ref lights)
 - [Image based lighting](@ref imageBasedLighting)
- **Input**
 - [Input polling](@ref inputPolling) 
 - [Input events](@ref inputEvents) 
 - [Virtual input](@ref virtualInput)
- [Creating custom components](@ref customComponents)
- [Serializing objects](@ref serializingObjects)
- **GUI**
 - [Sprite textures](@ref spriteTextures)
 - [Basic setup](@ref guiSetup)
 - [Elements](@ref guiElements)
 - [Layouts](@ref guiLayouts)
 - [Styles](@ref guiStyles)
 - [Importing fonts](@ref importingFonts)
 - [Localization](@ref guiLocalization)
- **Audio**
 - [Importing audio files](@ref importingAudio)
 - [Playing audio](@ref playingAudio)
- **Physics**
 - [Colliders](@ref colliders)
 - [Physics mesh import](@ref physicsMesh)
 - [Triggers](@ref triggers)
 - [Dynamic objects](@ref rigidbodies)
 - [Physics material](@ref physicsMaterial)
 - [Character controller](@ref characterController)
 - [Scene queries](@ref sceneQueries)
 - [Joints](@ref joints)
- **Animation**
 - [Loading animation clips](@ref animationClip)
 - [Playing animation](@ref animation)
 - [Bones](@ref bones)
 - [Advanced animation](@ref advancedAnimation)
- **Advanced**
 - [Manipulating textures](@ref advancedTextures)
 - [Offscreen rendering](@ref offscreenRendering)
 - [Creating meshes](@ref creatingMeshes)
 - [Advanced startup](@ref advancedStartup)
 - [Advanced RTTI](@ref advancedRtti)
 - [Advanced resources](@ref advResources)
 - [Prefabs](@ref prefabs)
 - [Cursors](@ref cursors)
 - [Profiling](@ref cpuProfiling)
 
# Developer manuals
A set of manuals covering advanced functionality intented for those wanting to extend the engine or tinker with the internals, rather than for normal users. You are expected to have read the user manuals first.
- [Architecture overview](@ref architecture) 
- **Low level rendering API**
 - [Core thread](@ref coreThread)
 - [GPU programs](@ref gpuPrograms)
 - [Non-programmable states](@ref nonProgrammableStates)
 - [Geometry](@ref geometry)
 - [Render targets](@ref renderTargets)
 - [Drawing](@ref drawing) 
 - [Load-store textures](@ref loadStoreTextures)
 - [GPU buffers](@ref gpuBuffers)
 - [Compute](@ref compute)
 - [Command buffers](@ref commandBuffers)
 - [GPU profiling](@ref gpuProfiling)
 - [Working example](@ref lowLevelRenderingExample)
- **More utilities**
 - [Modules](@ref modules)
 - [Advanced memory allocation](@ref advMemAlloc)
 - [Crash handling](@ref crashHandling)
 - [Dynamic libraries](@ref dynLib)
 - [Flags](@ref flags)
 - [Any](@ref any) 
 - [Unit tests](@ref unitTests)
- [Advanced materials](@ref advMaterials)
- [Threading](@ref threading)
- [Plugins](@ref plugins)
- **Renderer**
 - [Renderer extensions](@ref rendererExtensions)
 - [Creating a renderer plugin](@ref customRenderer)
- **Resources**
 - [Creating new resource types](@ref customResources)
 - [Creating custom importers](@ref customImporters)
- **Scripting**
 - [Exposing code to script API (automated)](@ref scriptingAuto)
 - **Exposing code to script API (manually)**
  - [Interacting with the script runtime](@ref mono)
  - [Script objects](@ref scriptObjects)
- [Extending the GUI system](@ref customGUI)
- [Porting to other platforms](@ref porting)
- [Code style](@ref codeStyle)
- [Quick reference](@ref quickref)
 
## General guides
Name                                      | Description
------------------------------------------|-------------
[BSLFX](@ref bsl)    	  		  		  | Provides a reference for the Banshee Shading Language syntax.