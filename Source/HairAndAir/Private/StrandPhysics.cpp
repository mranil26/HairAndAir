// Copyright Hair and Air. All Rights Reserved.

#include "StrandPhysics.h"
#include "Math/Rotator.h"

FStrandPhysics::FStrandPhysics()
{
}

void FStrandPhysics::Simulate(FHairStrand& Strand, float DeltaTime)
{
	// Clamp delta time to avoid instability
	DeltaTime = FMath::Min(DeltaTime, 0.033f);  // Max 30ms per frame

	// Step 1: Apply forces (gravity, wind, air drag)
	ApplyForces(Strand, DeltaTime);

	// Step 2: Verlet integration (update positions)
	VerletIntegration(Strand, DeltaTime);

	// Step 3: Solve constraints iteratively
	for (int32 i = 0; i < ConstraintIterations; ++i)
	{
		SolveConstraints(Strand);
	}

	// Step 4: Handle collisions
	ApplyCollisions(Strand);
}

void FStrandPhysics::ApplyForces(FHairStrand& Strand, float DeltaTime)
{
	for (int32 i = 1; i < Strand.GetSegmentCount(); ++i)  // Skip root segment
	{
		FStrandSegment& Segment = Strand.GetSegment(i);

		// Skip pinned segments
		if (Segment.bIsPinned)
		{
			continue;
		}

		// Apply gravity
		FVector TotalForce = Gravity;

		// Apply wind
		TotalForce += WindForce;

		// Apply air drag
		TotalForce -= Segment.Velocity * AirDrag;

		// Update velocity
		Segment.Velocity += (TotalForce / Segment.Mass) * DeltaTime;

		// Apply damping
		Segment.Velocity *= Segment.Damping;
	}
}

void FStrandPhysics::VerletIntegration(FHairStrand& Strand, float DeltaTime)
{
	for (int32 i = 1; i < Strand.GetSegmentCount(); ++i)  // Skip root
	{
		FStrandSegment& Segment = Strand.GetSegment(i);

		if (Segment.bIsPinned)
		{
			continue;
		}

		// Verlet: x_new = 2*x_current - x_previous + a*dt²
		FVector Acceleration = Segment.Velocity / Segment.Mass;
		FVector NewPosition = Segment.CurrentPosition + (Segment.CurrentPosition - Segment.PreviousPosition) * (1.0f - 0.1f) + Acceleration * DeltaTime * DeltaTime;

		Segment.PreviousPosition = Segment.CurrentPosition;
		Segment.CurrentPosition = NewPosition;
	}
}

void FStrandPhysics::SolveConstraints(FHairStrand& Strand)
{
	// Solve distance constraints
	for (const FDistanceConstraint& Constraint : Strand.GetDistanceConstraints())
	{
		SolveDistanceConstraint(Strand, Constraint);
	}

	// Solve bend constraints
	for (const FBendConstraint& Constraint : Strand.GetBendConstraints())
	{
		SolveBendConstraint(Strand, Constraint);
	}
}

void FStrandPhysics::SolveDistanceConstraint(FHairStrand& Strand, const FDistanceConstraint& Constraint)
{
	FStrandSegment& SegmentA = Strand.GetSegment(Constraint.SegmentA);
	FStrandSegment& SegmentB = Strand.GetSegment(Constraint.SegmentB);

	FVector Delta = SegmentB.CurrentPosition - SegmentA.CurrentPosition;
	float CurrentDistance = Delta.Length();

	if (CurrentDistance < 0.001f)
	{
		return;  // Avoid division by zero
	}

	float Difference = (CurrentDistance - Constraint.TargetDistance) / CurrentDistance;
	FVector Offset = Delta * Difference * Constraint.Stiffness * 0.5f;

	// Apply offset to both segments (if not pinned)
	if (!SegmentA.bIsPinned)
	{
		SegmentA.CurrentPosition += Offset;
	}
	if (!SegmentB.bIsPinned)
	{
		SegmentB.CurrentPosition -= Offset;
	}
}

void FStrandPhysics::SolveBendConstraint(FHairStrand& Strand, const FBendConstraint& Constraint)
{
	FStrandSegment& SegmentA = Strand.GetSegment(Constraint.SegmentA);
	FStrandSegment& SegmentB = Strand.GetSegment(Constraint.SegmentB);
	FStrandSegment& SegmentC = Strand.GetSegment(Constraint.SegmentC);

	FVector BA = (SegmentA.CurrentPosition - SegmentB.CurrentPosition).GetSafeNormal();
	FVector BC = (SegmentC.CurrentPosition - SegmentB.CurrentPosition).GetSafeNormal();

	float CurrentAngle = FMath::Acos(FMath::Clamp(FVector::DotProduct(BA, BC), -1.0f, 1.0f));
	float AngleDifference = CurrentAngle - Constraint.TargetAngle;

	// Simple angle constraint - rotate segments back toward target angle
	FVector RotationAxis = FVector::CrossProduct(BA, BC).GetSafeNormal();
	
	float RotationAmount = AngleDifference * Constraint.Stiffness * 0.1f;
	FQuat Rotation = FQuat(RotationAxis, RotationAmount);

	if (!SegmentA.bIsPinned)
	{
		SegmentA.CurrentPosition = SegmentB.CurrentPosition + Rotation.RotateVector(BA) * (SegmentA.CurrentPosition - SegmentB.CurrentPosition).Length();
	}

	if (!SegmentC.bIsPinned)
	{
		SegmentC.CurrentPosition = SegmentB.CurrentPosition + Rotation.RotateVector(BC) * (SegmentC.CurrentPosition - SegmentB.CurrentPosition).Length();
	}
}

void FStrandPhysics::ApplyCollisions(FHairStrand& Strand)
{
	// TODO: Implement self-collision and environment collision detection
	// For now, this is a placeholder
}

FVector FStrandPhysics::CalculateWind(FVector Position, float Time)
{
	// This can be extended with Perlin noise for more complex wind patterns
	return WindForce;
}