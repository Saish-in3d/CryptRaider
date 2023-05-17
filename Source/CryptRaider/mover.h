// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API Umover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Umover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		FVector CurrentLocation;

	UPROPERTY(EditAnywhere)
		FVector StartLocation;

	UPROPERTY(EditAnywhere)
		FVector MoveDistance;

	UPROPERTY(EditAnywhere)
		float Time;

	FVector TargetLocation;

	FVector Step;

	float Speed;

	FVector NewLocation;

	UPROPERTY(EditAnywhere)
		bool ShallMove = false;

	void MoveUp(float DeltaTime);

	void MoveStartLocation(float DeltaTime);

	void OpenDoor();

	void CloseDoor();

};
