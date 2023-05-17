// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "CryptRaiderCharacter.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PhysicsHandle)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * 200;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	

}

void UGrabber::SweepTrace()
{
	
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	
	bool IsHit = GetWorld()->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, Sphere);

	if (IsHit)
	{
		AActor* HitActor = OutHit.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor->GetActorNameOrLabel());
		//DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.f, 25.f, FColor::Green, false, 5.f);
		//DrawDebugSphere(GetWorld(), OutHit.Location, 5.f, 25.f, FColor::Red, false, 5.f);
		HitComponent = OutHit.GetComponent();
		OutHit.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(OutHit.GetComponent(), NAME_None, OutHit.ImpactPoint, OutHit.GetComponent()->GetComponentRotation());
		OutHit.GetComponent()->SetSimulatePhysics(true);
		OutHit.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OutHit.GetActor()->Tags.Add("Grabbed");
	}
	
}

void UGrabber::Grab()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

		SweepTrace();
	}
	
}

void UGrabber::Release()
{
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		UE_LOG(LogTemp, Display, TEXT("Released"));
		HitComponent->WakeAllRigidBodies();
		OutHit.GetActor()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

