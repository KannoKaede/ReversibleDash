#include "Audio.h"
#include "Main.h"
#include "Stage.h"
#include "UI.h"

StageManager stageManager;

void StageManager::SetUp() {
	cityHandle = MV1LoadModel("Resource/Stages/city.mv1");
	carHandle[0] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_1.mv1");
	carHandle[1] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_2.mv1");
	carHandle[2] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_3.mv1");
	carHandle[3] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_4.mv1");
	carHandle[4] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_1.mv1");
	carHandle[5] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_2.mv1");
	carHandle[6] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_3.mv1");
	carHandle[7] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_4.mv1");

	cloudHandle[0] = MV1LoadModel("Resource/Stages/Clouds/Cloud_1.mv1");
	cloudHandle[1] = MV1LoadModel("Resource/Stages/Clouds/Cloud_2.mv1");
	cloudHandle[2] = MV1LoadModel("Resource/Stages/Clouds/Cloud_3.mv1");
	cloudHandle[3] = MV1LoadModel("Resource/Stages/Clouds/Cloud_4.mv1");
	cloudHandle[4] = MV1LoadModel("Resource/Stages/Clouds/Cloud_5.mv1");

	CarsSetUp();
	CloudsSetUp();

	// コンストラクタでモデルを設定できないのでここでモデルを設定する
	for (int i = 1; i < MAX_STAGE_NUM; i++) {
		for (int j = 0; j < carArray[i].size(); j++) {
			carArray[i][j].SetCarHandle(carHandle[carArray[i][j].GetCarHandle()]);
		}
		for (int k = 0; k < cloudArray[i].size(); k++) {
			cloudArray[i][k].SetCloudHandle(cloudHandle[cloudArray[i][k].GetCloudHandle()]);
		}
	}

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < MV1GetMaterialNum(cityHandle); i++)	// ステージのモデル
	{
		MV1SetMaterialDifColor(cityHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(cityHandle, i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(cityHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(cityHandle, i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(cityHandle, i, 3.0f);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < MV1GetMaterialNum(carHandle[i]); j++) {
			MV1SetMaterialDifColor(carHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(carHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(carHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(carHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(carHandle[i], j, 3.0f);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < MV1GetMaterialNum(cloudHandle[i]); j++) {
			MV1SetMaterialDifColor(cloudHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(cloudHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(cloudHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(cloudHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(cloudHandle[i], j, 3.0f);
		}
	}
}

void StageManager::CarsSetUp() {
	carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 2000));
		//std::vector<Car> carArray[MAX_STAGE_NUM] = {	// ステージごとの車の情報を格納
		//	{},	// ステージ0は存在しないので空 車4500足したらいい感じ	選択してる車で来てる、上の雲出来てない
		//	// ステージ1
		//	{
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,3500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,9000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,10500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,13000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13900),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,14600),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15300),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16700),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,17400),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18100),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18800),
		//	},
		//	// ステージ2
		//	{
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,1500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,3000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5700),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,6300),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7700),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,11500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,12200),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,12900),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13600),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,14300),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15700),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,19000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,19700),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,20400),
		//	},
		//	// ステージ3
		//	{
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,4000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,10000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,16400),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,20000),
		//	},
		//	// ステージ4
		//	{
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,8000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,10000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,11500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,13500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,21000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,25000),
		//	},
		//	// ステージ5
		//	{
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,8000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,11500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,14000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,20500),
		//	},
		//	// ステージ6
		//	{
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7800),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,12000),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,15000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15900),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16600),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,17300),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18700),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,19500),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,22500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,25500),
		//		Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,29000),
		//		Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,31000),
		//	},
		//};
		//
}

void StageManager::CloudsSetUp() {
	cloudArray[1].push_back(Cloud(CloudModelRandom(), -480));
	//std::vector<Cloud> cloudArray[MAX_STAGE_NUM] = {
	//	{},
	//	// ステージ1
	//	{
	//		Cloud(CloudRandom,7240),
	//		Cloud(CloudRandom,7480),
	//		Cloud(CloudRandom,7720),
	//		Cloud(CloudRandom,7960),
	//		Cloud(CloudRandom,8200),
	//		Cloud(CloudRandom,8440),
	//		Cloud(CloudRandom,8680,true),
	//		// 隙間
	//		Cloud(CloudRandom,9320),
	//		Cloud(CloudRandom,9560),
	//		Cloud(CloudRandom,9800),
	//		Cloud(CloudRandom,10040),
	//		Cloud(CloudRandom,10280),
	//		Cloud(CloudRandom,10520,true),
	//		// 隙間
	//		Cloud(CloudRandom,11160),
	//		Cloud(CloudRandom,11400),
	//		Cloud(CloudRandom,11640,true),
	//		// 隙間
	//		Cloud(CloudRandom,11800),
	//		Cloud(CloudRandom,12040),
	//		Cloud(CloudRandom,12280),
	//		Cloud(CloudRandom,12520),
	//		Cloud(CloudRandom,12760),
	//		Cloud(CloudRandom,13000),
	//		Cloud(CloudRandom,13240),
	//		Cloud(CloudRandom,13480,true),
	//	},
	//	// ステージ2
	//	{
	//		Cloud(CloudRandom,2440),
	//		Cloud(CloudRandom,2680),
	//		Cloud(CloudRandom,2920),
	//		Cloud(CloudRandom,3160),
	//		Cloud(CloudRandom,3400),
	//		Cloud(CloudRandom,3640),
	//		Cloud(CloudRandom,3880,true),
	//		// 隙間
	//		Cloud(CloudRandom,4520),
	//		Cloud(CloudRandom,4760),
	//		Cloud(CloudRandom,5000,true),
	//		// 隙間
	//		Cloud(CloudRandom,6360),
	//		Cloud(CloudRandom,6500),
	//		Cloud(CloudRandom,6740),
	//		Cloud(CloudRandom,6980),
	//		Cloud(CloudRandom,7220,true),
	//		// 隙間
	//		Cloud(CloudRandom,7860),
	//		Cloud(CloudRandom,8100),
	//		Cloud(CloudRandom,8340,true),
	//		// 隙間
	//		Cloud(CloudRandom,8980),
	//		Cloud(CloudRandom,9220),
	//		Cloud(CloudRandom,9460),
	//		Cloud(CloudRandom,9700,true),
	//		// 隙間
	//		Cloud(CloudRandom,11000),
	//		Cloud(CloudRandom,11240),
	//		Cloud(CloudRandom,11480),
	//		Cloud(CloudRandom,11720),
	//		Cloud(CloudRandom,11960),
	//		Cloud(CloudRandom,12200,true),
	//		// 隙間
	//		Cloud(CloudRandom,12840),
	//		Cloud(CloudRandom,13080),
	//		Cloud(CloudRandom,13320),
	//		Cloud(CloudRandom,13560),
	//		Cloud(CloudRandom,13800,true),
	//	},
	//	// ステージ3
	//	{
	//		Cloud(CloudRandom,5500),
	//		Cloud(CloudRandom,5740),
	//		Cloud(CloudRandom,5980),
	//		Cloud(CloudRandom,6220),
	//		Cloud(CloudRandom,6460),
	//		Cloud(CloudRandom,6700,true),
	//		// 隙間
	//		Cloud(CloudRandom,7340),
	//		Cloud(CloudRandom,7580),
	//		Cloud(CloudRandom,7820),
	//		Cloud(CloudRandom,8060,true),
	//		// 隙間
	//		Cloud(CloudRandom,9200),
	//		Cloud(CloudRandom,9440),
	//		Cloud(CloudRandom,9680),
	//		Cloud(CloudRandom,9920,true),
	//		// 隙間
	//		Cloud(CloudRandom,10540),
	//		Cloud(CloudRandom,10780),
	//		Cloud(CloudRandom,11020),
	//		Cloud(CloudRandom,11260),
	//		Cloud(CloudRandom,11500,true),
	//	},
	//	// ステージ4
	//	{
	//	Cloud(CloudRandom,2500),
	//	Cloud(CloudRandom,2740),
	//	Cloud(CloudRandom,2980),
	//	Cloud(CloudRandom,3220),
	//	Cloud(CloudRandom,3460),
	//	Cloud(CloudRandom,3700,true),
	//	// 隙間
	//	Cloud(CloudRandom,4340),
	//	Cloud(CloudRandom,4580),
	//	Cloud(CloudRandom,4820),
	//	Cloud(CloudRandom,5060,true),
	//	// 隙間
	//	Cloud(CloudRandom,7500),
	//	Cloud(CloudRandom,7740),
	//	Cloud(CloudRandom,7980),
	//	Cloud(CloudRandom,8220),
	//	Cloud(CloudRandom,8460,true),
	//	// 隙間
	//	Cloud(CloudRandom,9100),
	//	Cloud(CloudRandom,9340),
	//	Cloud(CloudRandom,9580),
	//	Cloud(CloudRandom,9820,true),
	//	// 隙間
	//	Cloud(CloudRandom,11320),
	//	Cloud(CloudRandom,11560),
	//	Cloud(CloudRandom,11800),
	//	Cloud(CloudRandom,12040),
	//	Cloud(CloudRandom,12280),
	//	Cloud(CloudRandom,12520),
	//	Cloud(CloudRandom,12760),
	//	Cloud(CloudRandom,13000),
	//	Cloud(CloudRandom,13240,true),
	//	},
	//	// ステージ5
	//	{
	//	Cloud(CloudRandom,2800),
	//	Cloud(CloudRandom,3040),
	//	Cloud(CloudRandom,3280),
	//	Cloud(CloudRandom,3520),
	//	Cloud(CloudRandom,3760),
	//	Cloud(CloudRandom,4000,true),
	//	// 隙間
	//	Cloud(CloudRandom,4640),
	//	Cloud(CloudRandom,4880),
	//	Cloud(CloudRandom,5120),
	//	Cloud(CloudRandom,5360,true),
	//	// 隙間
	//	Cloud(CloudRandom,6000),
	//	Cloud(CloudRandom,6240),
	//	Cloud(CloudRandom,6480),
	//	Cloud(CloudRandom,6720),
	//	Cloud(CloudRandom,6960),
	//	Cloud(CloudRandom,7200,true),
	//	// 隙間
	//	Cloud(CloudRandom,8440),
	//	Cloud(CloudRandom,8680),
	//	Cloud(CloudRandom,8920,true),
	//	// 隙間
	//	Cloud(CloudRandom,9560),
	//	Cloud(CloudRandom,9800),
	//	Cloud(CloudRandom,10040),
	//	Cloud(CloudRandom,10280),
	//	Cloud(CloudRandom,10520,true),
	//	// 隙間
	//	Cloud(CloudRandom,11520),
	//	Cloud(CloudRandom,11760),
	//	Cloud(CloudRandom,12000),
	//	Cloud(CloudRandom,12240),
	//	Cloud(CloudRandom,12480,true),
	//	// 隙間
	//	Cloud(CloudRandom,13120),
	//	Cloud(CloudRandom,13360),
	//	Cloud(CloudRandom,13600),
	//	Cloud(CloudRandom,13840),
	//	Cloud(CloudRandom,14080),
	//	Cloud(CloudRandom,14320),
	//	Cloud(CloudRandom,14560,true),
	//	},
	//	// ステージ6
	//	{
	//	Cloud(CloudRandom,2500),
	//	Cloud(CloudRandom,2740),
	//	Cloud(CloudRandom,2980),
	//	Cloud(CloudRandom,3220),
	//	Cloud(CloudRandom,3460),
	//	Cloud(CloudRandom,3700),
	//	Cloud(CloudRandom,3940),
	//	Cloud(CloudRandom,4180,true),
	//	// 隙間
	//	Cloud(CloudRandom,4820),
	//	Cloud(CloudRandom,5060),
	//	Cloud(CloudRandom,5300,true),
	//	// 隙間
	//	Cloud(CloudRandom,8300),
	//	Cloud(CloudRandom,8540),
	//	Cloud(CloudRandom,8780),
	//	Cloud(CloudRandom,9020),
	//	Cloud(CloudRandom,9260),
	//	Cloud(CloudRandom,9500,true),
	//	// 隙間
	//	Cloud(CloudRandom,10140),
	//	Cloud(CloudRandom,10380),
	//	Cloud(CloudRandom,10620,true),
	//	// 隙間
	//	Cloud(CloudRandom,11260),
	//	Cloud(CloudRandom,11500),
	//	Cloud(CloudRandom,11740),
	//	Cloud(CloudRandom,11980),
	//	Cloud(CloudRandom,12020,true),
	//	// 隙間
	//	Cloud(CloudRandom,14980),
	//	Cloud(CloudRandom,15220),
	//	Cloud(CloudRandom,15460),
	//	Cloud(CloudRandom,15700),
	//	Cloud(CloudRandom,15940),
	//	Cloud(CloudRandom,16180),
	//	Cloud(CloudRandom,16420,true),

	//	Cloud(CloudRandom,17580),
	//	Cloud(CloudRandom,17820),
	//	Cloud(CloudRandom,18060),
	//	Cloud(CloudRandom,18300,true),
	//	},
	//};
}



void StageManager::Draw(Player& _player) {
	bool test = false;
	// 背景ステージの描画と衝突判定の設定
	MV1DrawModel(cityHandle);
	if (IsCollision(_player, VGet(12000, 0, 0), 40, 20000, false, false))test = true;	// リファクタリング：ステージを全部作り終わったら定数に変更
	// 車の描画
	if (!base.GetIsGameStop()) carMoveX += -7;	// 車を左に移動させていく
	for (int i = 0; i < carArray[base.GetStageNumber()].size(); i++) {
		Car car = carArray[base.GetStageNumber()][i];	// 描画用に一時的に取得
		VECTOR drawPos = VAdd(car.GetPosition(), VGet(carMoveX, 0, 0));
		MV1SetPosition(car.GetCarHandle(), drawPos);	// 車の座標を更新
		MV1DrawModel(car.GetCarHandle());
		// 衝突したらゲームオーバーに設定
		if (!base.GetIsGameStop() && IsCollision(_player, drawPos, car.GetHeight(), car.GetRadius(), true, false)) {
			fadeManager.ChangeUIState(GAMEOVER, fadeManager.NOTFADE);
			audioManager.PlaySE(audioManager.JINGLE_GAMEOVER);
		}
	}

	// 雲の描画

	for (int j = 0; j < cloudArray[base.GetStageNumber()].size(); j++) {
		Cloud cloud = cloudArray[base.GetStageNumber()][j];
		MV1SetPosition(cloud.GetCloudHandle(), cloud.GetPosition());
		MV1DrawModel(cloud.GetCloudHandle());
		if (IsCollision(_player, cloud.GetPosition(), cloud.GetHeight(), cloud.GetRadius(), false, cloud.GetIsScoreAdd())) {
			test = true;
		}
	}

	_player.SetIsGround(test);
}

bool StageManager::IsCollision(Player& _player, const VECTOR& _objPos, float _height, float _radius, bool _isObstacles, bool _isCloudScoreAdd) {
	VECTOR playerPos = _player.GetPosition();
	VECTOR playerScale = _player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > _objPos.x - _radius) && (playerPos.x - playerScale.x < _objPos.x + _radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (_player.GetIsGravityBottom() && playerPos.y <= _objPos.y + _height && playerPos.y + playerScale.y >= _objPos.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!_player.GetIsGravityBottom() && playerPos.y >= _objPos.y + _height && playerPos.y - playerScale.y <= _objPos.y);

	//足場の判定
	if (!_isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			_player.SetGroundPosY(_objPos.y + _height);	// 足場となる座標を保存
			float objRightDis = base.ClampNumF((_objPos.x + _radius) - playerPos.x, 0, 500);
			if (_isCloudScoreAdd && _player.CheckChangeJumpDis(objRightDis)) {
				_player.SetJumpDis(objRightDis);
			}
			return true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			return false;
		}
	}
	// 車の判定
	else {
		float objLeftDis = base.ClampNumF((_objPos.x - _radius) - playerPos.x, 0, 500);
		if (collisionX && collisionY) return true;	// 車の中にプレイヤーが侵入したら
		else if (!collisionX && collisionY && _player.CheckChangeJumpDis(objLeftDis)) {
			_player.SetJumpDis(objLeftDis);
		}
	}
	return false;
}

bool StageManager::IsClear(float _playerPosX) {
	return _playerPosX >= GOAL_POS_X[base.GetStageNumber()] + CLEAR_CHANGE_DIS;	// ゴール後一定以上進んだらクリア画面の遷移を可能にするフラグをtrueにする
}

void StageManager::Initialization() {
	carMoveX = 0;	// 車の移動座標の初期化
	// 背景ステージの座標をステージに合わせて変更
	cityDrawPos.z = CITY_POS_Z[base.GetStageNumber()];
	MV1SetPosition(cityHandle, cityDrawPos);
}