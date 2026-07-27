// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GroomDeformerInterface.generated.h"

class AWindSimulation;

/**
 * Groom Deformer Interface
 * 
 * This interface defines how Hair and Air plugin interacts with Groom assets
 * and the Deformer Graph system.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UGroomDeformerInterface : public UInterface
{
	GENERATED_BODY()
};

class IGroomDeformerInterface
{
	GENERATED_BODY()

public:
	/**
	 * Apply wind deformation to groom
	 * @param WindForce - The wind force vector to apply
	 * @param DeltaTime - Frame delta time
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Groom Deformation")
	void ApplyWindDeformation(FVector WindForce, float DeltaTime);

	/**
	 * Get the current deformation intensity
	 * @return Current deformation intensity value
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Groom Deformation")
	float GetDeformationIntensity();

	/**
	 * Set deformation intensity
	 * @param Intensity - New deformation intensity
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Groom Deformation")
	void SetDeformationIntensity(float Intensity);

	/**
	 * Bind this groom to a wind simulation actor
	 * @param WindSimulation - The wind simulation actor to bind to
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Groom Deformation")
	void BindToWindSimulation(AWindSimulation* WindSimulation);
};