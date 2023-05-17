// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxComponent.h"



UTriggerBoxComponent::UTriggerBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UTriggerBoxComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



void UTriggerBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TArray<AActor*>(Actors);
	GetOverlappingActors(Actors);

	if(Actors.Num()>0)
	{
		for (AActor* Actor : Actors)
		{
			if (Actor->ActorHasTag("AcceptableActor") && Mover && !Actor->ActorHasTag("Grabbed"))
			{
				UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
				if (Component)
				{
					Component->SetSimulatePhysics(false);
				}
				Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

				Mover->OpenDoor();
				UE_LOG(LogTemp, Display, TEXT("oppening"));
				return;
			}
			else 
			{
				Mover->CloseDoor();
				UE_LOG(LogTemp, Display, TEXT("closing"));
			}
		}
	}
	else
	{
		Mover->CloseDoor();
		UE_LOG(LogTemp, Display, TEXT("closing"));
	}

}

void UTriggerBoxComponent::SetMover(Umover* NewMover)
{
	Mover = NewMover;
}
