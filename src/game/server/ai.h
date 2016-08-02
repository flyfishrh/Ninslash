#ifndef GAME_SERVER_AI_H
#define GAME_SERVER_AI_H

#include <base/vmath.h>
#include <game/pathfinding.h>


#include "ai_protocol.h"

#define RAD 0.017453292519943295769236907684886f
#define PI 3.14159265358979323846


enum Events
{
	EVENT_DROPWEAPON,
	EVENT_DIE,
	EVENT_STOP,
	EVENT_FLEE,
	EVENT_FINDHUMAN,
	EVENT_ENABLESHOPPING,
	EVENT_STARTLE,
	EVENT_TALK1,
	EVENT_TALK2,
	EVENT_TALK3,
	EVENT_TALK4,
	EVENT_TALK5,
	EVENT_TALK6,
	EVENT_TALK7,
	EVENT_TALK8,
	EVENT_TALK9,
	EVENT_TALK10,
	EVENT_TALK11,
	EVENT_TALK12,
	EVENT_TALK13,
	EVENT_TALK14,
	EVENT_TALK15,
	EVENT_TALK16,
	EVENT_TALK17,
	EVENT_TALK18,
	EVENT_TALK19,
	NUM_EVENTS
};


class CAI
{
	class CGameContext *m_pGameServer;
	class CPlayer *m_pPlayer;
	
	class CPlayer *m_pTargetPlayer;
	
	int m_UnstuckCount;
	vec2 m_StuckPos;
	
	CWaypointPath *m_pPath;
	CWaypointPath *m_pVisible;
	
	bool m_HookMoveLock;
	
	
	int m_HookReleaseTick;
	int m_HookTick;	
	
protected:
	
	CGameContext *GameServer() const { return m_pGameServer; }
	CPlayer *Player() const { return m_pPlayer; }
	
	
	// events for talking & stuff
	bool m_Event[NUM_EVENTS];
	int m_EventTriggerTick[NUM_EVENTS];
	
	void ResetEvents();
	void TickEvents();
	virtual void OnEvent(int EventNum);
	
	virtual void DoBehavior() = 0;
	
	void ReactToPlayer();
	
	bool m_AutoWeaponChange;
	
	// emotions
	float m_aAnger[16]; // MAX_CLIENTS
	float m_aAttachment[16]; // MAX_CLIENTS
	
	float m_TotalAnger;
	
	void Panic();
	int m_PanicTick;
	
	void ClearEmotions();
	void HandleEmotions();
	
	float m_TargetAngle;
	float m_TurnSpeed;
	
	int m_DontMoveTick;
	
	vec2 m_Pos;
	vec2 m_LastPos;
	int m_LastMove;
	int m_LastJump;
	
	vec2 m_Direction;
	vec2 m_DisplayDirection;
	
	int m_Move;
	int m_Jump;
	int m_Attack;
	int m_LastAttack;
	
	int m_Hook;
	int m_LastHook;
	
	
	int m_NextReaction;
	int m_ReactionTime;
	
	int m_Sleep;
	int m_Stun;
	
	bool m_WayFound;
	
	// last spotted the enemy here
	vec2 m_PlayerPos;
	vec2 m_PlayerDirection;
	int m_PlayerDistance;
	int m_PlayerSpotTimer;
	int m_PlayerSpotCount;
	int m_EnemiesInSight;
	
	vec2 m_OldTargetPos;
	vec2 m_TargetPos;
	vec2 m_WaypointPos;
	vec2 m_WaypointDir;
	
	bool m_WaypointUpdateNeeded;
	int m_WayPointUpdateTick;
	int m_WayVisibleUpdateTick;
	
	int m_WayPointUpdateWait;
	
	int m_TargetTimer;
	int m_AttackTimer;
	int m_HookTimer;
	int m_HookReleaseTimer;
	
	bool MoveTowardsPlayer(int Dist = 0);
	bool MoveTowardsTarget(int Dist = 0);
	bool MoveTowardsWaypoint(int Dist = 0);
	
	void Unstuck();
	void HeadToMovingDirection();
	void JumpIfPlayerIsAbove();
	
	bool UpdateWaypoint();
	void HookMove();
	void WallRun();
	void AirJump();
	void DoJumping();
	
	void RandomlyStopShooting();
	
	// kf
	bool SeekRandomHuman();
	void ShootAtClosestHuman();
	bool SeekClosestHumanInSight();
	
	bool SeekRandomEnemy();
	bool SeekClosestFriend();
	bool SeekClosestHuman();
	bool SeekClosestEnemy();
	bool SeekClosestEnemyInSight();
	
	void ShootAtClosestEnemy();
	int WeaponShootRange();
	
	int m_ItemUseTick;
	
	void UseItems();
	
public:
	CAI(class CGameContext *pGameServer, class CPlayer *pPlayer);
	
	virtual ~CAI(){
		if (m_pPath)
			delete m_pPath;
	}
	
	void TriggerEvent(int EventNum, float InHowManySeconds = 0.0f);

	int m_ChatterStartTick;
	int m_ChatterEndTick;
	
	void Reset();
	void Tick();
	void UpdateInput(int *Data); // MAX_INPUT_SIZE
	
	bool SeekBombArea();
	bool SeekBomb();
	
	int m_Special;
	
	bool m_InputChanged;
	
	virtual void OnCharacterSpawn(class CCharacter *pChr);
	
	void Zzz(int Time);
	void Stun(int Time);
	
	void StandStill(int Time);
	
	virtual void ReceiveDamage(int CID, int Dmg);

	bool EventTriggered(int EventNum)
	{
		return m_EventTriggerTick[EventNum];
	}
	
	int GetMove(){ return m_Move; }
};



#endif