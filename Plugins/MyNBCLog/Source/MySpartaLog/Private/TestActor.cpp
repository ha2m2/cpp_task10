#include "TestActor.h"
#include "MySpartaLog/MySpartaLog.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

}
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hello from MySpartaLog Module!"));

	UE_LOG(LogMySpartaModule, Display, TEXT("Actor call MySpartaLog Module!"));
}

