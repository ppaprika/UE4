// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Quests/QuestManager.h"
#include "QuestMarker.generated.h"

UCLASS()
class BLUEPRINTSTOCPP_API AQuestMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* ParticalSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Root;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
		AQuestManager* GetQuestManager();
	
	UFUNCTION()
		void QuestUpdated(int32 Index);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ShowAtProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName QuestName;

	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
		void RefreshVisibility();
};
