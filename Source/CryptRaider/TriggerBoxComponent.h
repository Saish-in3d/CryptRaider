// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "mover.h"
#include "TriggerBoxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	class Umover* Mover;

protected:
	virtual void BeginPlay() override;

	

public:
	UTriggerBoxComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetMover(Umover* NewMover);

};
