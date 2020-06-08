// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMarker.h"

// Sets default values
AQuestMarker::AQuestMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ScenceRoot"));
	ParticalSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireComponent"));

	SetRootComponent(Root);
	ParticalSystem->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AQuestMarker::BeginPlay()
{
	Super::BeginPlay();
	RefreshVisibility();
	GetQuestManager()->CompletedQuest.AddDynamic(this, &AQuestMarker::QuestUpdated);
}

void AQuestMarker::QuestUpdated(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	RefreshVisibility();
}

// Called every frame
void AQuestMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestMarker::RefreshVisibility_Implementation()
{
	AQuestManager* QuestManager = GetQuestManager();
	FQuestInfo Quest = QuestManager->GetQuest(QuestName);
	if (Quest.Progress == ShowAtProgress && QuestManager->isActiveQuest(Quest.QuestId)) {
		ParticalSystem->SetVisibility(true);
	}
	else {
		ParticalSystem->SetVisibility(false);
	}

}

