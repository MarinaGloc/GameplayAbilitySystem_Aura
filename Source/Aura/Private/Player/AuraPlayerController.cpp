// Copyright Marina Gloc


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true; // Enable replication for this player controller, it replicates to all clients in multiplayer games
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    
    CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    if (!CursorHit.bBlockingHit) return;

    LastActor = ThisActor;
    ThisActor = CursorHit.GetActor();

    /**
    * Line trace from cursor. There are severa scenarios
    * 1. LastActor is null && ThisActor is null
    *   - Do nothing
    * 2. LastActor is null && ThisActor is valid
    *   - Highlight ThisActor
    * 3. LastActor is valid && ThisActor is null
    *   - Unhighlight LastActor
    * 4. Both actors are valid, but LastActor != ThisActor
    *   - Unhighlight LastActor, and highlight ThisActor
    * 5. Both actors are valid, and LastActor == ThisActor
    *  - Do nothing
    **/

    if(LastActor == nullptr){
        if(ThisActor != nullptr)
        {
            //Case 2
            ThisActor->HighlightActor(); // Highlight the new actor under the cursor
        }
        else
        {
            //Case 1
            // Do nothing, no actors to highlight or unhighlight
        }
    }
    else // LastActor is valid
    {
        if(ThisActor == nullptr)
        {
            //Case 3
            LastActor->UnhighlightActor(); // Unhighlight the last actor
        }
        else{
            if (LastActor != ThisActor)
            {
                //Case 4
                LastActor->UnhighlightActor(); // Unhighlight the last actor
                ThisActor->HighlightActor(); // Highlight the new actor under the cursor
            }
            else
            {
                //Case 5
                // Do nothing, both actors are the same
            }
        }
    }
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

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Additional input setup can be done here if needed

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if(APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
    }
}
