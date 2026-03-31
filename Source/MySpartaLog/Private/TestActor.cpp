#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

}
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hello from MySpartaLog Module!"));

	UE_LOG(LogTemp, Warning, TEXT("Hello from MySpartaLog Module!"));
}

