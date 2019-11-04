#include "EcsSystems.h"

void MoveMovables() {
    ecs::Apply<CompPos, CompMoveDir, CompHealth>([&](ecs::IEntity *movable) {
        CompMoveDir *dir = movable->GetComp<CompMoveDir>();
        CompPos *pos = movable->GetComp<CompPos>();
		CompSpeed* speed = movable->GetComp<CompSpeed>();
		if (dir->v.x || dir->v.y) {
			if (!(speed->CurStep % speed->speed)) {
				if (movable->GetComp<TagCollidable>()) {
					bool canMove = true;
					ecs::Apply<TagCollidable>([&](ecs::IEntity* collidable) {
						CompPos* colPos = collidable->GetComp<CompPos>();
						CompPosPattern* colPattern = collidable->GetComp<CompPosPattern>();
						if (colPos) {
							if (pos->v + dir->v == colPos->v)
								canMove = false;
						}
						else if (colPattern) {
							if (colPattern->positions.IsPosExists(pos->v.x + dir->v.x, pos->v.y + dir->v.y))
								canMove = false;
						}
						});
					if (canMove)
						pos->v += dir->v;
					else {
						if (dir->v.x && dir->v.y) {
							int tmp = dir->v.x;
							dir->v.x = 0;
							canMove = true;
							ecs::Apply<TagCollidable>([&](ecs::IEntity* collidable) {
								CompPos* colPos = collidable->GetComp<CompPos>();
								CompPosPattern* colPattern = collidable->GetComp<CompPosPattern>();
								if (colPos) {
									if (pos->v + dir->v == colPos->v)
										canMove = false;
								}
								else if (colPattern)
								{
									if (colPattern->positions.IsPosExists(pos->v.x + dir->v.x, pos->v.y + dir->v.y))
										canMove = false;
								}
								});
							dir->v.x = tmp;
							if (canMove)
								pos->v.y += dir->v.y;
							else {
								int tmp = dir->v.y;
								dir->v.y = 0;
								canMove = true;
								ecs::Apply<TagCollidable>([&](ecs::IEntity* collidable) {
									CompPos* colPos = collidable->GetComp<CompPos>();
									CompPosPattern* colPattern = collidable->GetComp<CompPosPattern>();
									if (colPos) {
										if (pos->v + dir->v == colPos->v)
											canMove = false;
									}
									else if (colPattern) {
										if (colPattern->positions.IsPosExists(pos->v.x + dir->v.x, pos->v.y + dir->v.y))
											canMove = false;
									}
									});
								dir->v.y = tmp;
								if (canMove)
									pos->v.x += dir->v.x;
							}
						}
					}
				}
				else
				{
					pos->v += dir->v;
				}
			}
			speed->CurStep++;
		}
		else if (speed->CurStep % speed->speed) {
			speed->CurStep++;
		}
    });
}

void MoveAttackArea()
{
    ecs::Apply<CompPos, CompCurrentAttackArea>([&](ecs::IEntity *ent)
    {
        CompCurrentAttackArea *areaComp = ent->GetComp<CompCurrentAttackArea>();
        ecs::IEntity *area = ecs::gEntityManager.GetEntityByDesc(areaComp->ent);
        area->GetComp<CompPosPattern>()->positions.pos = ent->GetComp<CompPos>()->v + areaComp->shift;
    });
}

void GameMoveSys::OnUpdate() {
	MoveMovables();
	MoveAttackArea();
}