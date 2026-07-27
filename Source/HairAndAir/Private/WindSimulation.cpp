// Copyright Hair and Air. All Rights Reserved.

#include "WindSimulation.h"
#include "Containers/Map.h"
#include "Math/Vector.h"

AWindSimulation::AWindSimulation()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.016f; // ~60 FPS

	// Set default root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AWindSimulation::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Wind Simulation started!"));
}

void AWindSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Accumulate time for wind variations
	TimeAccumulator += DeltaTime;

	// Reset time accumulator to prevent overflow
	if (TimeAccumulator > 1000.0f)
	{
		TimeAccumulator = 0.0f;
	}
}

FVector AWindSimulation::GetWindForce(FVector Position)
{
	FVector WindForce = WindDirection.GetSafeNormal() * WindStrength;

	// Apply variable wind if enabled
	if (bEnableVariableWind)
	{
		WindForce = ApplyTurbulence(WindForce, 0.016f);
	}

	return WindForce;
}

void AWindSimulation::SetWindStrength(float NewStrength)
{
	WindStrength = FMath::Max(0.0f, NewStrength);
	UE_LOG(LogTemp, Warning, TEXT("Wind Strength set to: %f"), WindStrength);
}

void AWindSimulation::SetWindDirection(FVector NewDirection)
{
	WindDirection = NewDirection.GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("Wind Direction set to: X=%f, Y=%f, Z=%f"), WindDirection.X, WindDirection.Y, WindDirection.Z);
}

FVector AWindSimulation::ApplyTurbulence(FVector BaseWind, float DeltaTime)
{
	// Simple sine-wave based turbulence
	float TurbulenceX = FMath::Sin(TimeAccumulator * WindFrequency) * WindTurbulence;
	float TurbulenceY = FMath::Cos(TimeAccumulator * WindFrequency * 0.7f) * WindTurbulence;
	float TurbulenceZ = FMath::Sin(TimeAccumulator * WindFrequency * 0.5f) * WindTurbulence * 0.5f;

	FVector TurbulenceVector(TurbulenceX, TurbulenceY, TurbulenceZ);

	return BaseWind + TurbulenceVector;
}

float AWindSimulation::CalculatePerlinNoise(float X, float Y, float Z) const
{
	// Simplified Perlin noise implementation
	// This is a basic placeholder that can be expanded for more realistic results
	return FMath::Sin(X * 0.1f) * FMath::Cos(Y * 0.1f) * FMath::Sin(Z * 0.1f);
}