/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/StrixReplicatorComponent.h"

#include "StrixTransformSyncComponent.generated.h"

using namespace strix::client::ingame::sync;

/** Component used for synchronization of the transform of an actor.
 *  Synchronizes information about the rotation, translation and scale.
 *  
 *  Requires the StrixReplicatorComponent on the owner actor.
 */
 /// \cond
UCLASS(ClassGroup = (Strix), meta = (BlueprintSpawnableComponent))
/// \endcond
class STRIXSDK_API UStrixTransformSyncComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
	UStrixTransformSyncComponent();

protected:
	/** Custom BeginPlay function that registers the properties to synchronize,
	 *  namely rotation (pitch, yaw, roll), translation (x, y, z) and scale (x, y, z).
	 */
	void BeginPlay() override;

private:
	UStrixReplicatorComponent* m_replicator;

	const std::string m_rotationPropertyString = ".Rotation.";
	const std::string m_translationPropertyString = ".Translation.";
	const std::string m_scalePropertyString = ".Scale.";
};