// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestInfo.h"
#include "QuestManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestCompleteSignature, int32, Index);

UCLASS()
class BLUEPRINTSTOCPP_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Blueprintcallable, BlueprintPure)
		int32 GetQuestIndex(FName QuestId) const;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FQuestInfo> QuestList;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FQuestCompleteSignature CompletedQuest;

	UFUNCTION(Blueprintcallable, BlueprintPure)
	TArray<FQuestInfo>& GetQuests() {
		return QuestList;
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		int32 CompleteQuest(FName QuestId, bool CompleteWholeQuest);

	UFUNCTION(Blueprintcallable, BlueprintImplementableEvent)
		FQuestInfo GetQuest(FName Name);

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
		bool isActiveQuest(FName QuestId);

};
