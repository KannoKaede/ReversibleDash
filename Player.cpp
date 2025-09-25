#include "Player.h"
#include "DxLib.h"
#include "UI.h"
#include "InGame.h"
#include "Main.h"

int modelHandle;



//void Player::StartUp(){
//    modelHandle = MV1LoadModel("Resource/PlayerModel.mv1");
//    MV1SetScale(modelHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
//    MV1SetPosition(modelHandle, position);
//    MV1SetRotationXYZ(modelHandle, direction);
//}
void Player::Move() {
    position.x += moveSpeed;
    MV1DrawModel(modelHandle);
}


void Player::ChangeSpeed() {
    float speedUpPos = goalPosition[stageNumber] / 4;
    if (position.x > speedUpPos * changeSpeedCount && changeSpeedCount <= 4) {
        moveSpeed = changeSpeedCount >= 3 ? FIRST_SPEED * (changeSpeedCount - 1) : FIRST_SPEED * (1 + 0.3f * changeSpeedCount);
        changeSpeedCount++;
    }
    else {
        return;
    }
}

void Player::Jump() {
    static int jumpHoldFrame = 0;          // ジャンプボタンを押しているフレーム数
    const int shortJumpFrame = 15;          // 短押し → 中ジャンプのしきい値
    const int midJumpFrame = 30;         // 長押し → 高ジャンプのしきい値

    // 地面にいるときだけジャンプ開始
    if (position.y == 0 && jumpPower == 0) {
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            jumpPower = 3.5f;   // 最低ジャンプ力（従来の約半分）
            jumpHoldFrame = 0;
        }
    }

    // ジャンプ中処理（上昇中のみ可変にする）
    if (jumpPower > 0 || position.y > 0) {
        if (jumpPower > 0 && CheckHitKey(KEY_INPUT_SPACE)) {
            jumpHoldFrame++;

            if (jumpHoldFrame == shortJumpFrame) {
                jumpPower += 2.0f;   // 中ジャンプ補強（小さめ）
            }
            else if (jumpHoldFrame == midJumpFrame) {
                jumpPower += 1.5f;   // 高ジャンプ補強（さらに小さめ）
            }
        }

        // 位置更新
        position.y += jumpPower;
        jumpPower -= 0.2f;   // 重力で減速

        // 着地判定
        if (position.y < 0) {
            position.y = 0;
            jumpPower = 0;
            jumpHoldFrame = 0;
        }
    }
}
