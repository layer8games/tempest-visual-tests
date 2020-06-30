#include "stdafx.h"
#include <Boxes/Projectile.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Projectile::Projectile(void) 
: 
_maxDistance(25*25),
_sqrDistance(0),
_speedScale(0),
_startingLocation(0.0f),
_type(),
p_rigidBody(nullptr)
{
    Init();
    SetActive(false);
    p_rigidBody = TP::PhysicsFactory::Instance()->MakeRigidBody2D();
    p_rigidBody->SetObject(this);
}

Projectile::~Projectile(void)
{
    p_rigidBody.reset();
}

//==========================================================================================================================
//
//Virtual GameObject functions
//
//==========================================================================================================================
void Projectile::v_Update(void)
{		
    TM::Point2 deltaPos = _startingLocation - GetPosition();
    _sqrDistance = deltaPos.SqrMagnitude();
    
    if(_sqrDistance >= _maxDistance) 
    { 
        SetActive(false);
        _sqrDistance = 0;
        p_rigidBody->SetVelocity(0.0f, 0.0f);
    }

    p_rigidBody->Integrate();
    DefaultUpdate();
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================	
void Projectile::SetMaxDistance(F32 dist)
{
    _maxDistance = dist * dist;
}

F32 Projectile::GetMaxDistance(void)
{
    return real_sqrt(_maxDistance);
}

void Projectile::SetSpeedScale(F32 scale)
{
    _speedScale = scale;
}

F32 Projectile::GetSpeedScale(void)
{
    return _speedScale;
}

void Projectile::SetType(ProjectileType type)
{
    _startingLocation = GetPosition();

    switch(type)
    {
        case BULLET:
            SetMaxDistance(800.0f);
            p_rigidBody->SetMass(1000.0f);
            p_rigidBody->SetLinearDamping(0.99f);
            p_rigidBody->SetAcceleration(0.0f, 0.0f);
            //SetScale(5.0f, 5.0f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(301));
            _speedScale = 1000.0f;
            break;
        case ARTILLERY:
            SetMaxDistance(1000.0f);
            p_rigidBody->SetMass(8000.0f);
            p_rigidBody->SetLinearDamping(0.6f);
            p_rigidBody->SetAcceleration(0.0f, 0.0f);
            //SetScale(15.0f, 15.0f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(302));
            _speedScale = 1000.0f;
            break;
        case MISSILE:
            SetMaxDistance(1000.0f);
            p_rigidBody->SetMass(500.0f);
            p_rigidBody->SetLinearDamping(0.99f);
            p_rigidBody->SetAcceleration(500.0f, 0.0f);
            //SetScale(20.0f, 20.0f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(303));
            _speedScale = 300.0f;
            break;
        case FIRE_BALL:
            SetMaxDistance(300.0f);
            p_rigidBody->SetMass(50.0f);
            p_rigidBody->SetLinearDamping(0.99f);
            p_rigidBody->SetAcceleration(10.0f, 0.0f);
           // SetScale(7.5f, 7.5f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(304));
            _speedScale = 250.0;
            break;
        case LAZER:
            SetMaxDistance(6000.0f);
            p_rigidBody->SetMass(0.1f);
            p_rigidBody->SetLinearDamping(0.99f);
            p_rigidBody->SetAcceleration(0.0f, 0.0f);
            //SetScale(10.0f, 7.5f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(305));
            _speedScale	= 900.0f;
            break;
        case GRENADE:
            SetMaxDistance(200.0f);
            p_rigidBody->SetMass(75.0f);
            p_rigidBody->SetLinearDamping(0.25f);
            p_rigidBody->SetAcceleration(0.0f, 0.0f);
            //SetScale(15.0f, 15.0f);
            SetTexture(TE::TextureManager::Instance()->GetTexture(306));
            _speedScale	= 350.0f;
            break;
        default:
            TE::ErrorManager::Instance()->SetError(TE::ErrorCode::APPLICATION, "Boxes::Projectile -> No ProjectileType provided in constructor.");
        break;
    }
}

ProjectileType Projectile::GetType(void)
{
    return _type;
}
