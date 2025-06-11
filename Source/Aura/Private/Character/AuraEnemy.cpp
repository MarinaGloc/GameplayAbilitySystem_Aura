// Copyright Marina Gloc


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // Set the mesh to block visibility channel

    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true); // Enable replication for the ability system component

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
}

void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true); // Enable custom depth rendering for highlighting
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Set a custom depth stencil value for the mesh

    Weapon->SetRenderCustomDepth(true); // Enable custom depth rendering for the weapon mesh
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // Set a custom depth stencil value for the weapon mesh
}

void AAuraEnemy::UnhighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);  // Set the flag to false when unhighlighted
    Weapon->SetRenderCustomDepth(false);
}