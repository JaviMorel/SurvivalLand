// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerAIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "InformerAICharacter.h"
#include "../SurvivalLandCharacter.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BruteAICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

void AInformerAIController::CheckPlayer()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	AInformerAICharacter* Informer = Cast<AInformerAICharacter>(PPawn);
	if (Informer == nullptr) return;

	const FVector StartPosition = Informer->GetActorLocation() + Informer->GetActorForwardVector() * Informer->StartPos;

	const FVector EndPosition = StartPosition + Informer->GetActorForwardVector() * Informer->Length;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(PPawn);

	TArray<FHitResult> OutHits;

	bool bResult = UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(),
		StartPosition,
		EndPosition,
		Informer->Radius,
		Informer->Height,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		true);
/*
#if WITH_EDITOR
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(),
		StartPosition,
		EndPosition,
		Informer->Radius,
		Informer->Height,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true);
		
#endif
*/

	APawn* PPlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ASurvivalLandCharacter* CharacterPlayer = Cast<ASurvivalLandCharacter>(PPlayerPawn);
	if (CharacterPlayer == nullptr) return;

	if (bResult)  //If I am seeing the player
	{
		for (int32 i = 0; i < OutHits.Num(); ++i)
		{
			FHitResult Hit = OutHits[i];

			if (Hit.GetActor() == PPlayerPawn)
			{
				FVector StartPositionPlayer = Informer->GetActorLocation();
				FVector EndPositionPlayer = PPlayerPawn->GetActorLocation();

				TArray<TEnumAsByte<EObjectTypeQuery>> LineObjectTypes;
				LineObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

				bResult = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(),
					StartPositionPlayer,
					EndPositionPlayer,
					LineObjectTypes,
					false,
					ActorsToIgnore,
					EDrawDebugTrace::None,
					OutHits,
					true);

/*
#if WITH_EDITOR
				
				UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(),
					StartPositionPlayer,
					EndPositionPlayer,
					LineObjectTypes,
					false,
					ActorsToIgnore,
					EDrawDebugTrace::ForDuration,
					OutHits,
					true);
					
#endif
*/
				bool NoObstacles = true;
				if (bResult)
				{
					for (int32 y = 0; y < OutHits.Num(); ++y)
					{
						FHitResult HitLine = OutHits[y];

						if (HitLine.GetActor() != PPlayerPawn)
						{
							NoObstacles = false;
						}
					}
				}

				if (NoObstacles)
				{
					if (CharacterPlayer->IsDead || CharacterPlayer->IsInvisible)
					{
						SecondsLeftSeeingPlayer = 0.f;
						PlayerSeen = false;
						Informer->SpotLight->SetHiddenInGame(false);
						Informer->GetCharacterMovement()->MaxWalkSpeed = Informer->WalkSpeed;
						PBlackboardComponent->SetValueAsObject("PlayerDetected", NULL);
						Informer->SetWarning(false);
					}
					else
					{
						Informer->SpotLight->SetHiddenInGame(true);
						Informer->GetCharacterMovement()->MaxWalkSpeed = Informer->RunSpeed;
						PBlackboardComponent->SetValueAsObject("PlayerDetected", PPlayerPawn);
						Player = PPlayerPawn;
						LastPlayerPos = Player->GetActorLocation();
						PlayerSeen = true;
						SecondsLeftSeeingPlayer = Informer->SecondsStopSeeingPlayer;
						WarnBrutes(Informer);
						Informer->SetWarning(true);
					}
					return;
				}

			}
		}
	}

	if (PlayerSeen && SecondsLeftSeeingPlayer > 0.f && !CharacterPlayer->IsDead) //If I am not seeing them but I still have seconds left, I follow them
	{
		Informer->SpotLight->SetHiddenInGame(true);
		SecondsLeftSeeingPlayer -= GetWorld()->GetDeltaSeconds() * 30;
		Informer->GetCharacterMovement()->MaxWalkSpeed = Informer->RunSpeed;
		PBlackboardComponent->SetValueAsObject("PlayerDetected", PPlayerPawn);
		Player = PPlayerPawn;
		WarnBrutes(Informer);
		Informer->SetWarning(true);
		return;
	}

	//If not, set that I am not watching them
	SecondsLeftSeeingPlayer = 0.f;
	PlayerSeen = false;
	Informer->SpotLight->SetHiddenInGame(false);
	Informer->GetCharacterMovement()->MaxWalkSpeed = Informer->WalkSpeed;
	PBlackboardComponent->SetValueAsObject("PlayerDetected", NULL);
	Informer->SetWarning(false);

}

void AInformerAIController::SetNextWaypoint()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	AInformerAICharacter* Informer = Cast<AInformerAICharacter>(PPawn);
	if (Informer == nullptr) return;

	if (Informer->Waypoints.Num() <= 0) return;

	FVector TargetWaypointPos = Informer->Waypoints[Informer->CurrentWaypoint]->GetActorLocation();

	PBlackboardComponent->SetValueAsVector("CurrentWaypoint", TargetWaypointPos);

}

void AInformerAIController::UpdateNextWaypoint()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	AInformerAICharacter* Informer = Cast<AInformerAICharacter>(PPawn);
	if (Informer == nullptr) return;

	if (Informer->Waypoints.Num() <= 0) return;

	if (Informer->CurrentWaypoint == Informer->Waypoints.Num() - 1)
		Informer->CurrentWaypoint = 0;
	else
		++Informer->CurrentWaypoint;
}

void AInformerAIController::FleeToPlayer()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	AInformerAICharacter* Informer = Cast<AInformerAICharacter>(PPawn);
	if (Informer == nullptr) return;
	if (Player == nullptr) return;

	FRotator Rotation =	UKismetMathLibrary::FindLookAtRotation(Informer->GetActorLocation(), Player->GetActorLocation());
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotation);
	ForwardVector *= Informer->UnitsFleeToPlayer;

	FVector TargetLocation = Informer->GetActorLocation() + ForwardVector;
	
	TargetLocation = UKismetMathLibrary::MakeVector(TargetLocation.X, TargetLocation.Y, Informer->GetActorLocation().Z);

	FVector RandomTargetLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), TargetLocation, Informer->RandomRadiusFleeToPlayer);
	
	//MoveToLocation(RandomTargetLocation);

	PBlackboardComponent->SetValueAsVector("WaypointToFlee", RandomTargetLocation);

	//MoveToActor(Player);
}

void AInformerAIController::WarnBrutes(AInformerAICharacter* Informer)
{
	const FVector StartPosition = Informer->GetActorLocation();

	const FVector EndPosition = StartPosition + Informer->GetActorForwardVector() * Informer->Length;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Informer);

	TArray<FHitResult> OutHits;

	bool bResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		StartPosition,
		StartPosition,
		Informer->RadiusWarnBrutes,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		true);

/*
#if WITH_EDITOR
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		StartPosition,
		StartPosition,
		Informer->RadiusWarnBrutes,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true);
#endif

*/
	if (bResult)  //If I am seeing the player
	{
		for (int32 i = 0; i < OutHits.Num(); ++i)
		{
			FHitResult Hit = OutHits[i];
			ABruteAICharacter* Brute = Cast<ABruteAICharacter>(Hit.GetActor());

			if (Brute != nullptr)
			{
				Brute->BeingWarned(LastPlayerPos);
			}
		}
	}
}