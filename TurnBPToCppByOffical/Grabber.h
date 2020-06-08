// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFrameWork/Actor.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class BLUEPRINTSTOCPP_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
		FVector GetHoldLocation() const;

	UFUNCTION(BlueprintPure)
		FVector GetMaxGrabLocation() const;

	UFUNCTION(BlueprintPure)
		UPhysicsHandleComponent* GetPhysicsComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		bool TraceForPhysicsBodies(AActor*& HitActor, UPrimitiveComponent*& HitComponent);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void NotifyQuestActor(AActor* Actor);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float MaxGrabDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HoldDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float GrabRadius;

	UFUNCTION(BlueprintCallable)
		void Grab();

	UFUNCTION(BlueprintCallable)
		void Release();		
};
