// Fill out your copyright notice in the Description page of Project Settings.


#include "mover.h"

// Sets default values for this component's properties
Umover::Umover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Umover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	StartLocation = GetOwner()->GetActorLocation();
	Speed =FVector::Distance(StartLocation, MoveDistance) / Time;
	TargetLocation = StartLocation + MoveDistance;
	//Step = MoveDistance / 
	
}


// Called every frame
void Umover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ShallMove)
	{
		MoveUp(DeltaTime);
	}
	else
	{
		MoveStartLocation(DeltaTime);
	}
}

void Umover::MoveUp(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();
	NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	//CurrentLocation = CurrentLocation + Step;
	GetOwner()->SetActorLocation(NewLocation);
}

void Umover::MoveStartLocation(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();
	NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

}

void Umover::OpenDoor()
{
	ShallMove = true;
}

void Umover::CloseDoor()
{
	ShallMove = false;
}

