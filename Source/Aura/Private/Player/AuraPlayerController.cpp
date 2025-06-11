// Copyright Marina Gloc


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true; // Enable replication for this player controller, it replicates to all clients in multiplayer games
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    check(AuraContext);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(AuraContext, 0); // Add the input mapping context with a priority of 0

    bShowMouseCursor = true; // Show the mouse cursor for this player controller
    DefaultMouseCursor = EMouseCursor::Default; // Set the default mouse cursor type

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock the mouse to the viewport
    InputModeData.SetHideCursorDuringCapture(false); // Do not hide the cursor during input capture
    SetInputMode(InputModeData); // Set the input mode to game and UI, allowing interaction with both game and UI elements

}