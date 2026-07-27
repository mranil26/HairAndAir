// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

/**
 * Hair and Air Module
 * 
 * This module provides wind simulation and groom deformation for Unreal Engine 5.6+
 * It integrates with the Groom Deformer Graph system to create realistic hair and fur dynamics.
 */
class FHairAndAirModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Get the module instance */
	static inline FHairAndAirModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHairAndAirModule>("HairAndAir");
	}

	/** Check if the module is loaded */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HairAndAir");
	}

private:
	void InitializeDeformerGraphNodes();
};