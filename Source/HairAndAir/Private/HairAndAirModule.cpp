// Copyright Hair and Air. All Rights Reserved.

#include "HairAndAirModule.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FHairAndAirModule"

void FHairAndAirModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module

	UE_LOG(LogTemp, Warning, TEXT("HairAndAir Module has started!"));

	// Initialize custom deformer graph nodes
	InitializeDeformerGraphNodes();
}

void FHairAndAirModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this before unloading the module.

	UE_LOG(LogTemp, Warning, TEXT("HairAndAir Module has shut down!"));
}

void FHairAndAirModule::InitializeDeformerGraphNodes()
{
	// Initialize any custom deformer graph nodes here
	// This will be expanded with wind simulation nodes
	UE_LOG(LogTemp, Warning, TEXT("Initializing Deformer Graph nodes..."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHairAndAirModule, HairAndAir)