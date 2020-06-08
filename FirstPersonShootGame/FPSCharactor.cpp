// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharactor.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include "Myproject2.h"
#include "FPSProjectile.h"

// Sets default values
AFPSCharactor::AFPSCharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FPSCameraConponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraConponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FPSCameraConponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f + BaseEyeHeight));
	FPSCameraConponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraConponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharactor::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character is in Game now."));
	}
}

// Called every frame
void AFPSCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharactor::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharactor::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharactor::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharactor::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharactor::JumpPressed);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFPSCharactor::JumpReleased);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharactor::Fire);
}

void AFPSCharactor::MoveForward(float Value)
{
	//�õ���ת����Ȼ��õ���ת���µ�x�᷽�򣬲�����������Ͻ����ƶ�
	//FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector dir = GetActorForwardVector();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, dir.ToString());
	AddMovementInput(dir, Value);
}

void AFPSCharactor::MoveRight(float Value)
{
	//�����仰�ȼ�
	//FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	FVector dir = GetActorRightVector();
	AddMovementInput(dir, Value);
}

void AFPSCharactor::JumpPressed()
{
	bPressedJump = true;
}

void AFPSCharactor::JumpReleased()
{
	bPressedJump = false;
}

void AFPSCharactor::Fire()
{
	if (ProjectileClass) {
		FVector CameraLocation;      //���������λ��
		FRotator CameraRotation;      //�������ת
		GetActorEyesViewPoint(CameraLocation, CameraRotation);  //������������λ���Լ���ת

		//������Ҫ�ӵ��ھ�ͷǰ��һ�㣨offset����λ�ñ������ȥ
		//�ӵ�����λ�þ͵��ھ�ͷλ�ü��Ͼ�����ͷ��תת����offset
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		//�ӵ����䷽��͵��ھ�ͷ��ת�ķ���
		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;   //��ʱ��֪����ɶ
			//��world�ķ���SpawnActor�����ӵ�������ӵ�������AFPSProjectile���������࣬���������ProjectileClass֪ͨ
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile) {
				FVector LaunchDir = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDir);
			}
		}
	}
}



