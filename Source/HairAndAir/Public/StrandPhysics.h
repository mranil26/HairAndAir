// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Strand.h"

/**
 * Strand Physics Engine
 * Handles Verlet integration and constraint solving
 * Simulates realistic hair physics with wind and gravity
 */
class FStrandPhysics
{
public:
	FStrandPhysics();
	~FStrandPhysics() = default;

	// Simulation parameters
	void SetGravity(FVector InGravity) { Gravity = InGravity; }
	void SetWindForce(FVector InWind) { WindForce = InWind; }
	void SetAirDrag(float InDrag) { AirDrag = FMath::Clamp(InDrag, 0.0f, 1.0f); }
	void SetIterations(int32 InIterations) { ConstraintIterations = FMath::Max(1, InIterations); }

	// Simulation step
	void Simulate(FHairStrand& Strand, float DeltaTime);

	// Individual operations
	void ApplyForces(FHairStrand& Strand, float DeltaTime);
	void VerletIntegration(FHairStrand& Strand, float DeltaTime);
	void SolveConstraints(FHairStrand& Strand);
	void ApplyCollisions(FHairStrand& Strand);

private:
	// Forces
	FVector Gravity = FVector(0.0f, 0.0f, -981.0f);  // Default Earth gravity (cm/s²)
	FVector WindForce = FVector::ZeroVector;
	float AirDrag = 0.05f;

	// Solver settings
	int32 ConstraintIterations = 5;

	// Constraint solving
	void SolveDistanceConstraint(FHairStrand& Strand, const FDistanceConstraint& Constraint);
	void SolveBendConstraint(FHairStrand& Strand, const FBendConstraint& Constraint);

	// Helper functions
	FVector CalculateWind(FVector Position, float Time);
};