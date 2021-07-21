// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Async/AsyncWork.h"
#include "BackgroundDoable.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BackgroundFunctionLibrary.generated.h"

class MultithreadedTask : public FNonAbandonableTask {
public:
	MultithreadedTask(UObject* obj) { this->obj = obj; }

	UObject* obj;

	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultithreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork() {
		IBackgroundDoable::Execute_MultithreadedFunction(obj);
	}
};
/**
 *
 */
UCLASS()
class DG_PROJECT_API UBackgroundFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void CallMultithreadFunction(UObject* obj) {
		(new FAutoDeleteAsyncTask<MultithreadedTask>(obj))->StartBackgroundTask();
	}
};
