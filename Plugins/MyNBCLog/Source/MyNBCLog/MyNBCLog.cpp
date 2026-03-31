#include "MyNBCLog.h"

#define LOCTEXT_NAMESPACE "FMyNBCLogModule"

void FMyNBCLogModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("MyNBCLog Plugin has started!"));
}

void FMyNBCLogModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyNBCLogModule, MyNBCLog)