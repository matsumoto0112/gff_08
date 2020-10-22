/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StrixReplicatorComponent.h"
#include "StrixAnimationSyncComponent.generated.h"

/** Component used for synchronization of the variables stored on
 *  the animation blueprints. For a property to be replicated the 'Replication'
 *  parameter needs to be set to 'Replicated' or 'RepNotify'.
 *  
 *  Requires the StrixReplicatorComponent on the owner actor.
 */
/// \cond
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// \endcond
class STRIXSDK_API UStrixAnimationSyncComponent : public UActorComponent
{
    GENERATED_BODY()

public:
	UStrixAnimationSyncComponent();

	/** Custom BeginPlay function that registers the properties to synchronize,
	 *  based on the 'Replication' parameter settings.
	 */
	void BeginPlay() override;

private:
	UStrixReplicatorComponent * m_replicator;
	USkeletalMeshComponent* m_skeleton;

	void SyncProperties();
};
