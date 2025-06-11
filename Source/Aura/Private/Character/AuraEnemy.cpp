// Copyright Marina Gloc


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
    bIsHighlighted = true; // Set the flag to true when highlighted
}

void AAuraEnemy::UnhighlightActor()
{
    bIsHighlighted = false; // Set the flag to false when unhighlighted
}