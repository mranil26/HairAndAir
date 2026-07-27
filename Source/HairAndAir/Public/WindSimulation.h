// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindSimulation.generated.h"

/**
 * Wind Simulation Component
 * 
 * This class handles all wind calculations for the Hair and Air plugin.
 * It supports multiple wind types: directional, turbulent, and wave-based.
 */
UCLASS()
class HAIRANDAIR_API AWindSimulation : public AActor
{
	GENERATED_BODY()

public:
	AWindSimulation();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Wind Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	FVector WindDirection = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	float WindStrength = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	float WindFrequency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	float WindTurbulence = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Settings")
	bool bEnableVariableWind = true;

	// Wind Functions
	UFUNCTION(BlueprintCallable, Category = "Wind")
	FVector GetWindForce(FVector Position);

	UFUNCTION(BlueprintCallable, Category = "Wind")
	void SetWindStrength(float NewStrength);

	UFUNCTION(BlueprintCallable, Category = "Wind")
	void SetWindDirection(FVector NewDirection);

private:
	// Internal wind calculation methods
	float CalculatePerlinNoise(float X, float Y, float Z) const;
	FVector ApplyTurbulence(FVector BaseWind, float DeltaTime);

	// Time accumulator for wind waves
	float TimeAccumulator = 0.0f;
};