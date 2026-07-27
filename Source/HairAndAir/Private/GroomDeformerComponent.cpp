// Copyright Hair and Air. All Rights Reserved.

#include "GroomDeformerComponent.h"
#include "WindSimulation.h"
#include "GroomComponent.h"
#include "Kismet/GameplayStatics.h"

UGroomDeformerComponent::UGroomDeformerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.016f; // ~60 FPS
}

void UGroomDeformerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try to find wind simulation if not assigned
	if (!BoundWindSimulation)
	{
		FindAndBindWindSimulation();
	}

	UE_LOG(LogTemp, Warning, TEXT("GroomDeformerComponent initialized on %s"), *GetOwner()->GetName());
}

void UGroomDeformerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bEnableDeformation || !BoundWindSimulation)
	{
		return;
	}

	// Get wind force from the bound wind simulation
	FVector WindForce = BoundWindSimulation->GetWindForce(GetOwner()->GetActorLocation());

	// Apply damping to smooth the deformation
	CurrentVelocity = FMath::Lerp(CurrentVelocity, WindForce * DeformationIntensity, 1.0f - DampingFactor);

	// Update groom deformation
	UpdateGroomDeformation(CurrentVelocity, DeltaTime);
}

void UGroomDeformerComponent::FindAndBindWindSimulation()
{
	// Search for wind simulation actor in the level
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWindSimulation::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		BoundWindSimulation = Cast<AWindSimulation>(FoundActors[0]);
		UE_LOG(LogTemp, Warning, TEXT("Found Wind Simulation: %s"), *BoundWindSimulation->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Wind Simulation found in level"));
	}
}

bool UGroomDeformerComponent::IsDeformationActive() const
{
	return bEnableDeformation && BoundWindSimulation != nullptr;
}

void UGroomDeformerComponent::SetDeformationIntensity(float NewIntensity)
{
	DeformationIntensity = FMath::Clamp(NewIntensity, 0.0f, 2.0f);
	UE_LOG(LogTemp, Warning, TEXT("Deformation Intensity set to: %f"), DeformationIntensity);
}

float UGroomDeformerComponent::GetDeformationIntensity() const
{
	return DeformationIntensity;
}

void UGroomDeformerComponent::UpdateGroomDeformation(FVector WindForce, float DeltaTime)
{
	// This function will be expanded to work with the Deformer Graph system
	// For now, it serves as a placeholder for deformation calculations
	
	UGroomComponent* GroomComp = GetAttachedGroomComponent();
	if (!GroomComp)
	{
		return;
	}

	// Apply wind force to groom
	// The actual deformation will be applied through the Deformer Graph in future updates
	UE_LOG(LogTemp, Warning, TEXT("Applying wind deformation to groom: %f"), WindForce.Length());
}

UGroomComponent* UGroomDeformerComponent::GetAttachedGroomComponent() const
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}

	return Owner->FindComponentByClass<UGroomComponent>();
}
