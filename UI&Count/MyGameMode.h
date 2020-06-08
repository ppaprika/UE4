// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGCPP_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	//ɾ��������ʾ��widget�������µ�widget��ӵ��ӿ�
	UFUNCTION(Blueprintcallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	//��ʼ���˵�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	//Ŀǰ������ʾ��widget
	UPROPERTY()
		UUserWidget* CurrentWidget;
	
};
