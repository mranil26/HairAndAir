// Copyright Hair and Air. All Rights Reserved.

#include "Strand.h"

FHairStrand::FHairStrand()
{
}

void FHairStrand::Initialize(FVector RootPosition, int32 SegmentCount, float SegmentLength)
{
	Segments.Empty();
	DistanceConstraints.Empty();
	BendConstraints.Empty();

	if (SegmentCount <= 0)
	{
		return;
	}

	// Create root segment (pinned)
	Segments.Add(FStrandSegment(RootPosition, true));

	// Create remaining segments
	FVector CurrentPos = RootPosition;
	for (int32 i = 1; i < SegmentCount; ++i)
	{
		CurrentPos.Z -= SegmentLength;  // Grow downward
		Segments.Add(FStrandSegment(CurrentPos, false));
	}

	// Create distance constraints between consecutive segments
	for (int32 i = 0; i < Segments.Num() - 1; ++i)
	{
		AddDistanceConstraint(i, i + 1, SegmentLength, 0.95f);
	}

	// Create bend constraints for natural bending (every 2 segments)
	if (Segments.Num() >= 3)
	{
		for (int32 i = 0; i < Segments.Num() - 2; ++i)
		{
			AddBendConstraint(i, i + 1, i + 2, 0.8f);
		}
	}
}

void FHairStrand::AddDistanceConstraint(int32 SegmentA, int32 SegmentB, float Distance, float Stiffness)
{
	if (SegmentA >= 0 && SegmentA < Segments.Num() &&
		SegmentB >= 0 && SegmentB < Segments.Num())
	{
		DistanceConstraints.Add(FDistanceConstraint(SegmentA, SegmentB, Distance, Stiffness));
	}
}

void FHairStrand::AddBendConstraint(int32 SegmentA, int32 SegmentB, int32 SegmentC, float Stiffness)
{
	if (SegmentA >= 0 && SegmentA < Segments.Num() &&
		SegmentB >= 0 && SegmentB < Segments.Num() &&
		SegmentC >= 0 && SegmentC < Segments.Num())
	{
		// Calculate the angle between segments
		FVector AB = (Segments[SegmentB].CurrentPosition - Segments[SegmentA].CurrentPosition).GetSafeNormal();
		FVector BC = (Segments[SegmentC].CurrentPosition - Segments[SegmentB].CurrentPosition).GetSafeNormal();
		float Angle = FMath::Acos(FMath::Clamp(FVector::DotProduct(AB, BC), -1.0f, 1.0f));

		BendConstraints.Add(FBendConstraint(SegmentA, SegmentB, SegmentC, Angle, Stiffness));
	}
}

void FHairStrand::SetMass(float InMass)
{
	for (FStrandSegment& Segment : Segments)
	{
		Segment.Mass = InMass;
	}
}

void FHairStrand::SetDamping(float InDamping)
{
	for (FStrandSegment& Segment : Segments)
	{
		Segment.Damping = InDamping;
	}
}

void FHairStrand::SetRootPosition(FVector NewRoot)
{
	if (Segments.Num() > 0)
	{
		Segments[0].CurrentPosition = NewRoot;
		Segments[0].PreviousPosition = NewRoot;
	}
}

void FHairStrand::Reset()
{
	for (FStrandSegment& Segment : Segments)
	{
		Segment.Velocity = FVector::ZeroVector;
	}
}

void FHairStrand::ApplyForce(FVector Force)
{
	for (int32 i = 1; i < Segments.Num(); ++i)  // Skip root
	{
		Segments[i].Velocity += (Force / Segments[i].Mass);
	}
}