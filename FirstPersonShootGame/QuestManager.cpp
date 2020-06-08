// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 AQuestManager::GetQuestIndex(FName QuestId) const
{
	int32 i = 0;
	for (auto info : QuestList) {
		if (QuestId == info.QuestId) {
			return i;
		}
		i++;
	}
	return -1;
}



// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AQuestManager::CompleteQuest_Implementation(FName QuestId, bool CompleteWholeQuest)
{
	int32 QuestIndex = GetQuestIndex(QuestId);
	if (CompleteWholeQuest) {
		QuestList[QuestIndex].Progress = QuestList[QuestIndex].ProgressTotal;
	}
	else {
		QuestList[QuestIndex].Progress = FMath::Min((QuestList[QuestIndex].Progress) + 1, QuestList[QuestIndex].ProgressTotal);
	}
	CompletedQuest.Broadcast(QuestIndex);
	return QuestIndex;
}

