// Copyright Hair and Air. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Math/Vector.h"

/**
 * Strand Segment
 * Represents a single segment (node) in a hair strand
 * Uses Verlet integration for physics simulation
 */
struct FStrandSegment
{
	// Position data
	FVector CurrentPosition;
	FVector PreviousPosition;
	FVector Velocity;

	// Physical properties
	float Mass = 1.0f;
	float Damping = 0.99f;  // Air resistance

	// Pinned constraint (root segment)
	bool bIsPinned = false;

	FStrandSegment()
		: CurrentPosition(FVector::ZeroVector)
		, PreviousPosition(FVector::ZeroVector)
		, Velocity(FVector::ZeroVector)
	{
	}

	FStrandSegment(FVector InPosition, bool bInPinned = false)
		: CurrentPosition(InPosition)
		, PreviousPosition(InPosition)
		, Velocity(FVector::ZeroVector)
		, bIsPinned(bInPinned)
	{
	}
};

/**
 * Distance Constraint
 * Keeps two segments at a specific distance apart
 * Used to maintain strand integrity
 */
struct FDistanceConstraint
{
	int32 SegmentA;
	int32 SegmentB;
	float TargetDistance;
	float Stiffness = 0.95f;  // How much to enforce (0-1)

	FDistanceConstraint()
		: SegmentA(-1), SegmentB(-1), TargetDistance(0.0f)
	{
	}

	FDistanceConstraint(int32 InSegmentA, int32 InSegmentB, float InDistance, float InStiffness = 0.95f)
		: SegmentA(InSegmentA)
		, SegmentB(InSegmentB)
		, TargetDistance(InDistance)
		, Stiffness(InStiffness)
	{
	}
};

/**
 * Bend Constraint
 * Maintains natural bending of strand
 * Keeps three segments in angle relationship
 */
struct FBendConstraint
{
	int32 SegmentA;
	int32 SegmentB;
	int32 SegmentC;
	float TargetAngle;
	float Stiffness = 0.8f;  // How much to enforce (0-1)

	FBendConstraint()
		: SegmentA(-1), SegmentB(-1), SegmentC(-1), TargetAngle(0.0f)
	{
	}

	FBendConstraint(int32 InA, int32 InB, int32 InC, float InAngle, float InStiffness = 0.8f)
		: SegmentA(InA), SegmentB(InB), SegmentC(InC), TargetAngle(InAngle), Stiffness(InStiffness)
	{
	}
};

/**
 * Hair Strand
 * Complete hair strand with segments and constraints
 * Supports physics-based simulation
 */
class FHairStrand
{
public:
	FHairStrand();
	~FHairStrand() = default;

	// Creation
	void Initialize(FVector RootPosition, int32 SegmentCount, float SegmentLength);
	
	// Segment access
	int32 GetSegmentCount() const { return Segments.Num(); }
	FStrandSegment& GetSegment(int32 Index) { return Segments[Index]; }
	const FStrandSegment& GetSegment(int32 Index) const { return Segments[Index]; }
	
	FVector GetSegmentPosition(int32 Index) const { return Segments[Index].CurrentPosition; }
	void SetSegmentPosition(int32 Index, FVector NewPosition) { Segments[Index].CurrentPosition = NewPosition; }

	// Constraint management
	void AddDistanceConstraint(int32 SegmentA, int32 SegmentB, float Distance, float Stiffness = 0.95f);
	void AddBendConstraint(int32 SegmentA, int32 SegmentB, int32 SegmentC, float Stiffness = 0.8f);
	
	const TArray<FDistanceConstraint>& GetDistanceConstraints() const { return DistanceConstraints; }
	const TArray<FBendConstraint>& GetBendConstraints() const { return BendConstraints; }

	// Properties
	void SetMass(float InMass);
	void SetDamping(float InDamping);
	
	FVector GetRootPosition() const { return Segments.Num() > 0 ? Segments[0].CurrentPosition : FVector::ZeroVector; }
	void SetRootPosition(FVector NewRoot);

	// Physics state
	void Reset();
	void ApplyForce(FVector Force);

private:
	TArray<FStrandSegment> Segments;
	TArray<FDistanceConstraint> DistanceConstraints;
	TArray<FBendConstraint> BendConstraints;
};