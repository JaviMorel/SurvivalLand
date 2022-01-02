// Fill out your copyright notice in the Description page of Project Settings.


#include "InformerAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../SurvivalLandCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/SpotLightComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AInformerAICharacter::AInformerAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInformerAICharacter::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->Stop();
}

// Called every frame
void AInformerAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Warning && !AudioComponent->IsPlaying())
	{
		Shouting();
	}
}

// Called to bind functionality to input
void AInformerAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AInformerAICharacter::Shouting()
{
	AudioComponent->Play();
}
