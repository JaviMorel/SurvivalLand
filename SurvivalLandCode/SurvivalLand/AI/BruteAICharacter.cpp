// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../SurvivalLandCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/SpotLightComponent.h"
#include "BruteAIController.h"

// Sets default values
ABruteAICharacter::ABruteAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABruteAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABruteAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectPlayerToPunch();
}

// Called to bind functionality to input
void ABruteAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABruteAICharacter::DetectPlayerToPunch()
{
	if(PlayerDetected) return;
	const FVector StartPosition = GetActorLocation() + GetActorForwardVector() * StartPosPunch;

	const FVector EndPosition = StartPosition + GetActorForwardVector() * LengthPunch;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> OutHits;

	bool bResult = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(),
		StartPosition,
		EndPosition,
		BoxSize,
		GetActorRotation(),
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		true);

#if WITH_EDITOR
	/*
	UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(),
		StartPosition,
		EndPosition,
		BoxSize,
		GetActorRotation(),
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true);
		*/
#endif

	if (!bResult)
	{
		PlayerDetected = false;
		return;
	}
	
	APawn* PPlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ASurvivalLandCharacter* CharacterPlayer = Cast<ASurvivalLandCharacter>(PPlayerPawn);
	if (CharacterPlayer == nullptr) return;
	
	for (int32 i = 0; i < OutHits.Num(); ++i)
	{
		FHitResult Hit = OutHits[i];

		if (Hit.GetActor() == PPlayerPawn)
		{
			if(!CharacterPlayer->IsDead && !CharacterPlayer->IsInvisible)
			{
				float TimeAnim = GetMesh()->GetAnimInstance()->Montage_Play(PushMontage);
				PlayerDetected = true;
				SetRightHandSphereActive(true);

				if (HitSound != nullptr)
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());

				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABruteAICharacter::StopPushAnim, TimeAnim, false);
				return;
			}
		}
	}

	PlayerDetected = false;
	
}

void ABruteAICharacter::StopPushAnim()
{
	PlayerDetected = false;
	SetRightHandSphereActive(false);
}

//IN BP
void ABruteAICharacter::SetRightHandSphereActive_Implementation(bool Value)
{
	
}

void ABruteAICharacter::BeingWarned(FVector PlayerPos)
{
	ABruteAIController* ControllerAI = Cast<ABruteAIController>(GetController());
	if (ControllerAI == nullptr) return;

	ControllerAI->PlayerDetectedByInformer(PlayerPos);

}