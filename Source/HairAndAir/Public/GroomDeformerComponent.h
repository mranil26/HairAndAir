// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GroomComponent.h"
#include "GroomDeformerComponent.generated.h"

class AWindSimulation;

/**
 * Groom Deformer Component
 * 
 * This component handles the deformation of Groom assets based on wind simulation.
 * Attach this component to any actor with a GroomComponent to enable wind effects.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HAIRANDAIR_API UGroomDeformerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGroomDeformerComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Groom settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom Deformation")
	float DeformationIntensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom Deformation")
	float DampingFactor = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom Deformation")
	bool bEnableDeformation = true;

	// Wind simulation reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	class AWindSimulation* BoundWindSimulation = nullptr;

	// Blueprint functions
	UFUNCTION(BlueprintCallable, Category = "Groom Deformation")
	void FindAndBindWindSimulation();

	UFUNCTION(BlueprintCallable, Category = "Groom Deformation")
	bool IsDeformationActive() const;

	UFUNCTION(BlueprintCallable, Category = "Groom Deformation")
	void SetDeformationIntensity(float NewIntensity);

	UFUNCTION(BlueprintCallable, Category = "Groom Deformation")
	float GetDeformationIntensity() const;

private:
	// Find attached groom component
	UGroomComponent* GetAttachedGroomComponent() const;

	// Apply deformation calculations
	void UpdateGroomDeformation(FVector WindForce, float DeltaTime);

	// Velocity for smoothing deformations
	FVector CurrentVelocity = FVector::ZeroVector;
};
