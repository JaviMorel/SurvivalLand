// Fill out your copyright notice in the Description page of Project Settings.


#include "BruteAIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BruteAICharacter.h"
#include "../SurvivalLandCharacter.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ABruteAIController::CheckPlayer()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	ABruteAICharacter* Brute = Cast<ABruteAICharacter>(PPawn);
	if (Brute == nullptr) return;

	FVector StartPosition = Brute->GetActorLocation() + Brute->GetActorForwardVector() * Brute->StartPos;

	FVector EndPosition = StartPosition + Brute->GetActorForwardVector() * Brute->Length;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(PPawn);

	TArray<FHitResult> OutHits;

	bool bResult = UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(),
		StartPosition,
		EndPosition,
		Brute->Radius,
		Brute->Height,
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
		Brute->Radius,
		Brute->Height,
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
				FVector StartPositionPlayer = Brute->GetActorLocation();
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

#if WITH_EDITOR
				/*
				UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(),
					StartPositionPlayer,
					EndPositionPlayer,
					LineObjectTypes,
					false,
					ActorsToIgnore,
					EDrawDebugTrace::ForDuration,
					OutHits,
					true);
					*/
#endif
				bool NoObstacles = true;
				if(bResult)
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

				if(NoObstacles)
				{
					if(CharacterPlayer->IsDead || CharacterPlayer->IsInvisible)
					{
						SecondsLeftSeeingPlayer = 0.f;
						PlayerSeen = false;
						Brute->SpotLight->SetLightColor(Brute->NoDetectionColor);
						Brute->GetCharacterMovement()->MaxWalkSpeed = Brute->WalkSpeed;
						PBlackboardComponent->SetValueAsObject("PlayerDetected", NULL);
					}
					else
					{
						Brute->SpotLight->SetLightColor(Brute->DetectionColor);
						Brute->GetCharacterMovement()->MaxWalkSpeed = Brute->RunSpeed;
						PBlackboardComponent->SetValueAsObject("PlayerDetected", PPlayerPawn);
						Player = PPlayerPawn;
						PlayerSeen = true;
						SecondsLeftSeeingPlayer = Brute->SecondsStopSeeingPlayer;
						PBlackboardComponent->SetValueAsBool("PlayerWarnedByInformer", false);
					}
					return;
				}
				
			}
		}
	}	
	
	if(PlayerSeen && SecondsLeftSeeingPlayer > 0.f && !CharacterPlayer->IsDead) //If I am not seeing them but I still have seconds left, I follow them
	{
		Brute->SpotLight->SetLightColor(Brute->SeekingDetectionColor);
		SecondsLeftSeeingPlayer -= GetWorld()->GetDeltaSeconds() * 30;
		Brute->GetCharacterMovement()->MaxWalkSpeed = Brute->RunSpeed;
		PBlackboardComponent->SetValueAsObject("PlayerDetected", PPlayerPawn);
		Player = PPlayerPawn;
		PBlackboardComponent->SetValueAsBool("PlayerWarnedByInformer", false);
		return;
	}

	//If the player is close the brute, it will "hear" they

	StartPosition = Brute->GetActorLocation();

	EndPosition = StartPosition + Brute->GetActorForwardVector() * Brute->LenghtHear;

	bResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		StartPosition,
		StartPosition,
		Brute->RadiusHear,
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
			Brute->RadiusHear,
			ObjectTypes,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			OutHits,
			true);
	#endif
*/
	if (bResult)  //If I am hearing the player
	{
		for (int32 i = 0; i < OutHits.Num(); ++i)
		{
			FHitResult Hit = OutHits[i];
			if (Hit.GetActor() == PPlayerPawn && !CharacterPlayer->IsDead && !CharacterPlayer->IsInvisible)
			{
				float SpeedPlayer = CharacterPlayer->GetMovementComponent()->Velocity.Normalize();
				if (SpeedPlayer > 0)
				{
					Brute->SpotLight->SetLightColor(Brute->SeekingDetectionColor);
					SecondsLeftSeeingPlayer = Brute->SecondsStopSeeingPlayer;
					Brute->GetCharacterMovement()->MaxWalkSpeed = Brute->RunSpeed;
					PBlackboardComponent->SetValueAsObject("PlayerDetected", PPlayerPawn);
					Player = PPlayerPawn;
					PBlackboardComponent->SetValueAsBool("PlayerWarnedByInformer", false);
					return;
				}			}
		}
	}

	//If not, set that I am not watching them
	SecondsLeftSeeingPlayer = 0.f;
	PlayerSeen = false;
	Brute->SpotLight->SetLightColor(Brute->NoDetectionColor);
	Brute->GetCharacterMovement()->MaxWalkSpeed = Brute->WalkSpeed;
	PBlackboardComponent->SetValueAsObject("PlayerDetected", NULL);
	
}

void ABruteAIController::SetNextWaypoint()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	ABruteAICharacter* Brute = Cast<ABruteAICharacter>(PPawn);
	if (Brute == nullptr) return;

	if (Brute->Waypoints.Num() <= 0) return;

	FVector TargetWaypointPos = Brute->Waypoints[Brute->CurrentWaypoint]->GetActorLocation();

	PBlackboardComponent->SetValueAsVector("CurrentWaypoint", TargetWaypointPos);

}

void ABruteAIController::UpdateNextWaypoint()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	ABruteAICharacter* Brute = Cast<ABruteAICharacter>(PPawn);
	if (Brute == nullptr) return;

	if (Brute->Waypoints.Num() <= 0) return;

	if (Brute->CurrentWaypoint == Brute->Waypoints.Num() - 1)
		Brute->CurrentWaypoint = 0;
	else
		++Brute->CurrentWaypoint;
}

void ABruteAIController::MoveToPlayer()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	APawn* PPawn = GetPawn();
	ABruteAICharacter* Brute = Cast<ABruteAICharacter>(PPawn);
	if (Brute == nullptr) return;

	MoveToActor(Player);
}

void ABruteAIController::PlayerDetectedByInformer(FVector InformerLastPosPlayer)
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	PBlackboardComponent->SetValueAsBool("PlayerWarnedByInformer", true);
	PBlackboardComponent->SetValueAsVector("InformerLastPosPlayer", InformerLastPosPlayer);
}

void ABruteAIController::ReachLastLocationOfPlayer()
{
	UBlackboardComponent* PBlackboardComponent = BrainComponent->GetBlackboardComponent();
	PBlackboardComponent->SetValueAsBool("PlayerWarnedByInformer", false);
}